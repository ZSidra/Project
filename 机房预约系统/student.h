#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
#include"computerRoom.h"
#include"orderFile.h"

class Student :public Identity
{
public:
	Student();//Ĭ�Ϲ���

	Student(int id, string name, string pwd);//�вι���

	virtual void operMenu();//�˵�

	void applyOrder();//����ԤԼ

	void showMyOrder();//�鿴����ԤԼ

	void showAllOrder();//�鿴����ԤԼ

	void cancelOrder();//ȡ��ԤԼ

	void initcomputerRoom();

	int m_Id;//ѧ��ѧ��

	vector<ComputerRoom>vCom;//��������
};