#include<iostream>
#include<fstream>
using namespace std;
#include"Identity.h"
#include"globalFile.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"

int inputInt()
{
	int num;
	while (true)
	{
		if (!(cin >> num))
		{
			cout << "������Ϸ��ַ���" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
		{
			break;
		}
	}
	return num;
}

void managerMenu(Identity* &manager)
{
	while (true)
	{
		manager->operMenu();

		Manager* man = (Manager*)manager;

		int select = inputInt();

		switch (select)
		{
		case 1://����˺�
			man->addPerson();
			break;
		case 2://�鿴�˺�
			man->showPerson();
			break;
		case 3://�鿴������Ϣ
			man->showComputer();
			break;
		case 4://���ԤԼ
			man->cleanFile();
			break;
		case 0:
			delete manager;
			cout << "ע���ɹ���" << endl;
			return;
		default:
			cout << "��������ȷ�Ĺ��ܱ�ţ�" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

void studentMenu(Identity*& student)
{
	while (true)
	{
		student->operMenu();

		Student* stu = (Student*)student;

		int select = inputInt();

		switch (select)
		{
		case 1://����ԤԼ
			stu->applyOrder();
			break;
		case 2://�鿴�ҵ�ԤԼ
			stu->showMyOrder();
			break;
		case 3://�鿴����ԤԼ
			stu->showAllOrder();
			break;
		case 4://ȡ��ԤԼ
			stu->cancelOrder();
			break;
		case 0:
			delete student;
			cout << "ע���ɹ���" << endl;
			return;
		default:
			cout << "��������ȷ�Ĺ��ܱ�ţ�" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		teacher->operMenu();

		Teacher* tea = (Teacher*)teacher;

		int select = inputInt();

		switch (select)
		{
		case 1://�鿴����ԤԼ
			tea->showAllOrder();
			break;
		case 2://���ԤԼ
			tea->validOrder();
			break;
		case 0://ע����¼
			delete teacher;
			cout << "ע���ɹ���" << endl;
			return;
		default:
			cout << "��������ȷ�Ĺ��ܱ�ţ�" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

void login(string fileName, int type)
{
	Identity* person = NULL;//����ָ��

	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	//�����û���Ϣ
	int id = 0;
	string name;
	string pwd;

	if (type == 1)
	{
		cout << "������ѧ�ţ�" << endl;
		id = inputInt();
	}
	else if(type == 2)
	{
		cout << "������ְ���ţ�" << endl;
		id = inputInt();
	}
	cout << "�������û�����" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//ѧ�������֤
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "ѧ���˺���֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Student(fId, fName, fPwd);
				//����ѧ���Ӳ˵�
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//��ʦ�����֤
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "��ʦ�˺���֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Teacher(fId, fName, fPwd);
				//�����ʦ�Ӳ˵�
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա�����֤
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				cout << "����Ա�˺���֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Manager(fName, fPwd);
				//�������Ա�Ӳ˵�
				managerMenu(person);
				return;
			}
		}
	}
	cout << "��֤��¼ʧ�ܣ�" << endl;
}

int main()
{
	int select;
	while (true)
	{
		cout << "========================= ����ԤԼϵͳ =========================" << endl;
		cout << "\t\t--------------------------------\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|           1.ѧ����           |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|           2.��ʦ��           |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|           3.����Ա           |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|           0.�˳�             |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t--------------------------------\n";
		cout << "�����빦��ѡ��" << endl;

		select = inputInt();

		switch (select)
		{
		case 1://ѧ����
			login(STUDENT_FILE, select);
			break;
		case 2://��ʦ��
			login(TEACHER_FILE, select);
			break;
		case 3://����Ա
			login(ADMIN_FILE, select);
			break;
		case 0:
			cout << "��ӭ�´�ʹ�ã�" << endl;
			system("pause"); 
			return 0;
			break;
		default:
			cout << "��������ȷ�ı�ţ�" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	
	

	system("pause");

	return 0;
}