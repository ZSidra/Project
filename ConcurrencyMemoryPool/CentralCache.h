#pragma once
#include"Common.h"

//����ģʽ
class CentralCache
{
public:
	static CentralCache* getInstance()
	{
		return &m_instance;
	}

	//��ȡһ���ǿ�Span
	Span* getOneSpan(SpanList& list, size_t size);
	//�����Ļ����ȡһ�������Ķ�����ȸ�ThreadCache
	size_t fetchRangeObj(void*& start, void*& end, size_t batch_num, size_t size);

	void releaseListToSpans(void* start, size_t size);

private:
	CentralCache()
	{}

	CentralCache(const CentralCache&) = delete;

	static CentralCache m_instance;

private:
	SpanList m_span_lists[NFREELIST];
};