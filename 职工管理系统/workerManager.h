#pragma once//��ֹͷ�ļ��ظ�����
#include<iostream>//�������������ͷ�ļ�
#include<fstream>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#define FILENAME "empFile.txt"
using namespace std;//ʹ�ñ�׼�������ռ�

class WorkerManager
{
public:

	WorkerManager();

	void Show_Menu();//�˵�

	void exitSystem();//�˳�ϵͳ

	int m_EmpNum;//ְ������

	Worker** m_EmpArray;//����ָ��

	void addEmp();//���ְ��

	void save();//�洢���ļ���

	bool m_FileIsEmpty;//�ļ��Ƿ�Ϊ��

	int get_EmpNum();//ͳ���ļ��е�����

	void init_Emp();//��ʼ��ְ��

	void showEmp();//��ʾְ��

	void delEmp();//ɾ��ְ��

	int isExist(int id);//�ж�id�Ƿ����

	bool isExist(string name);//ͨ���������Ҳ���ӡ

	void modEmp();//�޸�ְ��

	void findEmp();//����ְ��

	void sortEmp();//����

	void cleanFile();//�������

	~WorkerManager();
};
