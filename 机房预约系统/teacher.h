#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
#include"orderFile.h"
#include"computerRoom.h"

class Teacher :public Identity
{
public:
	Teacher();//Ĭ�Ϲ���

	Teacher(int empId, string name, string pwd);//�вι���

	virtual void operMenu();//�˵�

	void showAllOrder();//�鿴����ԤԼ

	void validOrder();//���ԤԼ

	void initcomputerRoom();

	int m_EmpId;//ְ����

	vector<ComputerRoom>vCom;//��������
};
