#include"Common.h"

class ThreadCache
{
public:
	//�����ڴ����
	void* allocate(size_t size);
	//�ͷ��ڴ����
	void deallocate(void* ptr, size_t size);
	//�����Ļ����ȡ����
	void* fetchFromCentralCache(size_t index, size_t size);

	void listExceeded(FreeList& list, size_t size);

private:
	FreeList m_free_lists[NFREELIST];
};

//�ֲ߳̾��洢��TLS������һ�ֱ����Ĵ洢��������������������ڵ��߳�����ȫ�ֿɷ��ʵģ����ǲ��ܱ������̷߳��ʵ��������ͱ��������ݵ��̶߳����ԡ�
static _declspec(thread) ThreadCache* p_tls_threadcache;