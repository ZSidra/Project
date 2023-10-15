#pragma once
#include"Common.h"
#include"PageMap.h"

//����ģʽ
class PageCache
{
public:
	static PageCache* getInstance()
	{
		return &m_instance;
	}

	std::mutex& getMutex()
	{
		return m_page_mtx;
	}

	//��ȡһ��Kҳ��Span
	Span* newSpan(size_t k);
	//ͨ��pageidӳ�����Span
	Span* mapObjectToSpan(void* obj);
	//ҳ�ϲ�
	void releaseSpanToPageCache(Span* span);

private:
	PageCache()
	{}

	PageCache(const PageCache&) = delete;

	static PageCache m_instance;

private:
	//Span�����
	ObjectPool<Span> m_span_pool;

	SpanList m_span_lists[NPAGES];
	//pageid��Span��ӳ���ϵ
	TCMalloc_PageMap1<32 - PAGE_SHIFT> m_span_id_map;
	//����
	std::mutex m_page_mtx;
};