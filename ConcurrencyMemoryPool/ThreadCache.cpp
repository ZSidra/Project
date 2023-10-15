#include"ThreadCache.h"
#include"CentralCache.h"

void* ThreadCache::allocate(size_t size)
{
	assert(size <= MAX_BYTES);
	size_t align_size = SizeClass::roundUp(size);
	size_t index = SizeClass::index(size);

	if (!m_free_lists[index].empty())
		return m_free_lists[index].pop();
	else
		return fetchFromCentralCache(index, align_size);
}
void ThreadCache::deallocate(void* ptr, size_t size)
{
	assert(ptr);
	assert(size < MAX_BYTES);
	
	size_t index = SizeClass::index(size);
	m_free_lists[index].push(ptr);

	// �������ȴ���һ������������ڴ�ʱ�ͷ���һ��list��centralcache
	if (m_free_lists[index].size() >= m_free_lists[index].getMaxSize())
	{
		listExceeded(m_free_lists[index], size);
	}

}

void* ThreadCache::fetchFromCentralCache(size_t index, size_t size)
{
	// ����ʼ���������㷨
	// 1���ʼ����һ����central cacheһ������Ҫ̫�࣬��ΪҪ̫���˿����ò���
	// 2������㲻Ҫ���size��С�ڴ�������ôbatchNum�ͻ᲻��������ֱ������
	// 3��sizeԽ��һ����central cacheҪ��batchNum��ԽС
	// 4��sizeԽС��һ����central cacheҪ��batchNum��Խ��
	size_t batch_num = min(m_free_lists[index].getMaxSize(), SizeClass::numMoveSize(size));
	if (m_free_lists[index].getMaxSize() == batch_num)
		m_free_lists[index].getMaxSize()++;

	void* start = nullptr;
	void* end = nullptr;
	size_t actual_num = CentralCache::getInstance()->fetchRangeObj(start, end, batch_num, size);

	assert(actual_num > 0);//���ٻ�ȡ��һ������ռ�
	if (actual_num == 1)
	{
		assert(start == end);
		return start;
	}
	else
	{
		m_free_lists[index].pushRange(*(void**)start, end , actual_num - 1);//����һ����ʣ�µĹҵ�����������
		return start;
	}
}

void ThreadCache::listExceeded(FreeList& list, size_t size)
{
	void* start = nullptr;
	void* end = nullptr;
	list.popRange(start, end, list.getMaxSize());

	CentralCache::getInstance()->releaseListToSpans(start, size);
}