#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;
#include"globalFile.h"

class OrderFile
{
public:
	OrderFile();

	void updateOrder();//����ԤԼ��¼

	int m_Size;//��¼ԤԼ����

	map<int, map<string, string>>m_OrderDate;//��¼����ԤԼ��Ϣ������ key��¼���� value�����¼��ֵ����Ϣ
};