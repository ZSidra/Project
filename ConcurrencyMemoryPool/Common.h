#pragma once
#include<iostream>
#include<thread>
#include<mutex>
#include<unordered_map>
#include<assert.h>
#ifdef _WIN32
#include<windows.h>
#else
//
#endif

using std::cout;
using std::endl;

//�������ռ�
static const size_t MAX_BYTES = 1024 * 256;
//Ͱ����
static const size_t NFREELIST = 208;

static const size_t NPAGES = 129;

static const size_t PAGE_SHIFT = 13;

#ifdef _WIN64
typedef long long PAGE_ID;
#elif _WIN32
typedef size_t PAGE_ID;
#else

#endif

//����ϵͳ�ӿ������ڴ�
inline static void* systemAlloc(size_t kpage)
{
	//������������windows��Linux
#ifdef _WIN32
	void* ptr = VirtualAlloc(0, kpage << 13, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
	// linux��brk mmap��
#endif

	if (ptr == nullptr)
		throw std::bad_alloc();

	return ptr;
}

inline static void systemFree(void* ptr)
{
#ifdef _WIN32
	VirtualFree(ptr, 0, MEM_RELEASE);
#else
	// sbrk unmmap��
#endif
}

template<class T>
class ObjectPool
{
public:
	T* New()
	{
		T* obj = nullptr;

		// ���Ȱѻ������ڴ������ٴ��ظ�����
		if (m_freeList)
		{
			void* next = *((void**)m_freeList);
			obj = (T*)m_freeList;
			m_freeList = next;
		}
		else
		{
			// ʣ���ڴ治��һ�������Сʱ�������¿����ռ�
			if (m_remainBytes < sizeof(T))
			{
				m_remainBytes = 128 * 1024;
				//_memory = (char*)malloc(_remainBytes);
				m_memory = (char*)systemAlloc(m_remainBytes >> 13);
				if (m_memory == nullptr)
				{
					throw std::bad_alloc();
				}
			}

			obj = (T*)m_memory;
			size_t objSize = sizeof(T) < sizeof(void*) ? sizeof(void*) : sizeof(T);
			m_memory += objSize;
			m_remainBytes -= objSize;
		}

		// ��λnew����ʾ����T�Ĺ��캯����ʼ��
		new(obj)T;

		return obj;
	}

	void Delete(T* obj)
	{
		// ��ʾ�������������������
		obj->~T();

		// ͷ��
		*(void**)obj = m_freeList;
		m_freeList = obj;
	}

private:
	char* m_memory = nullptr; // ָ�����ڴ��ָ��
	size_t m_remainBytes = 0; // ����ڴ����зֹ�����ʣ���ֽ���

	void* m_freeList = nullptr; // ���������������ӵ����������ͷָ��
};

//Ͱ
class FreeList
{
public:
	void push(void* obj)
	{
		assert(obj);
		//ͷ��
		*(void**)obj = m_free_list;
		m_free_list = obj;
		m_size++;
	}

	void pushRange(void* start , void* end , size_t n)
	{
		//ͷ��
		*(void**)end = m_free_list;
		m_free_list = start;


		// ������֤+�����ϵ�
		//int i = 0;
		//void* cur = start;
		//while (cur)
		//{
		//	cur = *(void**)cur;
		//	++i;
		//}

		//if (n != i)
		//{
		//	int x = 0;
		//}

		m_size += n;
	}

	void* pop()
	{
		//ͷɾ
		void* obj = m_free_list;
		m_free_list = *(void**)m_free_list;
		m_size--;

		return obj;
	}

	void popRange(void*& start, void*& end , size_t n)
	{
		if (n > m_size)
			int x = 0;
		assert(n <= m_size);

		start = m_free_list;
		end = start;

		for (size_t i = 0; i < n - 1; i++)
		{
			end = *(void**)end;
		}

		m_free_list = *(void**)end;
		*(void**)end = nullptr;
		m_size -= n;
	}

	size_t size()
	{
		return m_size;
	}

	size_t& getMaxSize()
	{
		return m_max_size;
	}

	bool empty()
	{
		return m_free_list == nullptr;
	}
private:
	void* m_free_list = nullptr;
	size_t m_size = 0;
	size_t m_max_size = 1;
};

class SizeClass
{
public:
	// ������������10%���ҵ�����Ƭ�˷�
	// [1,128]					8byte����	    freelist[0,16)
	// [128+1,1024]				16byte����	    freelist[16,72)
	// [1024+1,8*1024]			128byte����	    freelist[72,128)
	// [8*1024+1,64*1024]		1024byte����     freelist[128,184)
	// [64*1024+1,256*1024]		8*1024byte����   freelist[184,208)
	static inline size_t _roundUp(size_t size, size_t align_num)
	{
		size_t align_size;
		if (size % align_num != 0)
			align_size = (size / align_num + 1)*align_num;
		else
			align_size = size;

		return align_size;
	}
	
	//��������Ĵ�С
	static inline size_t roundUp(size_t bytes)
	{
		if (bytes <= 128)
			return _roundUp(bytes, 8);
		else if (bytes <= 1024)
			return _roundUp(bytes, 16);
		else if (bytes <= 1024 * 8)
			return _roundUp(bytes, 128);
		else if (bytes <= 1024 * 64)
			return _roundUp(bytes, 1024);
		else if (bytes <= 1024 * 256)
			return _roundUp(bytes, 1024 * 8);
		else
			return _roundUp(bytes, 1 << PAGE_SHIFT);
	}

	static inline size_t _index(size_t bytes, size_t align_num)
	{
		if (bytes % align_num == 0)
			return bytes / align_num - 1;
		else
			return bytes / align_num;
	}

	//����ӳ��Ŀ��Ͱ
	static inline size_t index(size_t bytes)
	{
		assert(bytes <= MAX_BYTES);

		// ÿ�������ж��ٸ�Ͱ
		static int group_array[4] = { 16, 56, 56, 56 };
		if (bytes <= 128) {
			return _index(bytes, 8);
		}
		else if (bytes <= 1024) {
			return _index(bytes - 128, 16) + group_array[0];
		}
		else if (bytes <= 8 * 1024) {
			return _index(bytes - 1024, 128) + group_array[1] + group_array[0];
		}
		else if (bytes <= 64 * 1024) {
			return _index(bytes - 8 * 1024, 1024) + group_array[2] + group_array[1] + group_array[0];
		}
		else if (bytes <= 256 * 1024) {
			return _index(bytes - 64 * 1024, 1024* 8) + group_array[3] + group_array[2] + group_array[1] + group_array[0];
		}
		else {
			assert(false);
		}

		return -1;
	}

	static size_t numMoveSize(size_t size)
	{
		assert(size > 0);

		size_t num = MAX_BYTES / size;

		if (num < 2)
			num = 2;
		else if (num > 512)
			num = 512;

		return num;
	}

	static size_t numMovePage(size_t size)
	{
		size_t num = numMoveSize(size);
		size_t npage = num * size;

		npage >>= PAGE_SHIFT;
		if (npage == 0)
			npage = 1;

		return npage;
	}
};




struct Span
{
	PAGE_ID m_page_id = 0;//��ʼҳ��
	size_t m_page_num = 0;//ҳ��
	size_t m_obj_size = 0;

	Span* m_prev = nullptr;
	Span* m_next = nullptr;

	size_t m_use_count = 0;//�����ThreadCache���ڴ����
	void* m_span_free_list = nullptr;//�ڴ���

	bool m_is_using = false;//�Ƿ�ʹ��
};

class SpanList
{
public:
	SpanList()
	{
		m_head = m_span_pool.New();
		m_head->m_prev = m_head;
		m_head->m_next = m_head;
	}

	Span* begin()
	{
		return m_head->m_next;
	}

	Span* end()
	{
		return m_head;
	}

	void pushFront(Span* new_span)
	{
		insert(begin(), new_span);
	}

	void insert(Span* pos, Span* new_span)
	{
		assert(pos);
		assert(new_span);

		Span* prev = pos->m_prev;
		// prev newspan pos
		prev->m_next = new_span;
		new_span->m_prev = prev;
		new_span->m_next = pos;
		pos->m_prev = new_span;
	}

	Span* popFront()
	{
		Span* front = m_head->m_next;
		erase(front);

		return front;
	}

	void erase(Span* pos)
	{
		assert(pos);
		assert(pos != m_head);

		Span* prev = pos->m_prev;
		Span* next = pos->m_next;

		prev->m_next = next;
		next->m_prev = prev;
	}

	bool empty()
	{
		return m_head->m_next == m_head;
	}

	std::mutex& getMutex()
	{
		return m_mtx;
	}
private:
	Span* m_head;
	ObjectPool<Span> m_span_pool;
	std::mutex m_mtx;//������
};