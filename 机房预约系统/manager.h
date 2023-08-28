#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"

class Manager :public Identity
{
public:
	Manager();//Ĭ�Ϲ���

	Manager(string name, string pwd);//�вι���

	virtual void operMenu();//�˵�

	void addPerson();//����˺�

	void showPerson();//�鿴�˺�

	void showComputer();//�鿴������Ϣ

	void cleanFile();//���ԤԼ��¼

	void initVector();//��ʼ������

	bool checkRepeat(int id, int type);//����ظ�

	void initcomputerRoom();

	vector<Student>vStu;//ѧ������

	vector<Teacher>vTea;//��ʦ����

	vector<ComputerRoom>vCom;//��������
};