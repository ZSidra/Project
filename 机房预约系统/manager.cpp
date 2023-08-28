#include<algorithm>
#include"manager.h"

void printStudent(Student& s)
{
	cout << "ѧ�ţ�" << s.m_Id << "�û�����" << s.m_Name << "���룺" << s.m_Pwd << endl;
}

void printTeacher(Teacher& t)
{
	cout << "ְ���ţ�" << t.m_EmpId << "�û�����" << t.m_Name << "���룺" << t.m_Pwd << endl;
}

Manager::Manager()
{

}

Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->initVector();
	this->initcomputerRoom();
}

void Manager::operMenu()
{
	cout << "��ӭ����Ա��" << this->m_Name << "��¼��" << endl;
	cout << "\t\t-------------------------------\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t|          1.����˺�         |\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t|          2.�鿴�˺�         |\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t|          3.�鿴������Ϣ     |\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t|          4.���ԤԼ         |\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t|          0.ע����¼         |\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t-------------------------------\n";
	cout << "�����빦��ѡ��" << endl;
}

void Manager::addPerson()
{
	cout << "����������˺ŵ����ͣ�" << endl;
	cout << "1.���ѧ���˺�" << endl;
	cout << "2.��ӽ�ʦ�˺�" << endl;

	string fileName;
	string tip;
	string errorTip;
	ofstream ofs;
	int select = inputInt();

	if (select == 1)
	{
		fileName = STUDENT_FILE;
		tip = "������ѧ�ţ�";
		errorTip = "��ѧ���Ѵ��ڣ���������ӣ�";
	}
	else
	{
		fileName = TEACHER_FILE;
		tip = "������ְ���ţ�";
		errorTip = "��ְ�����Ѵ��ڣ���������ӣ�";
	}

	ofs.open(fileName, ios::out | ios::app);

	cout << tip << endl;
	int id = inputInt();
	bool ret = this->checkRepeat(id, select);
	if (ret)
	{
		cout << errorTip << endl;
		return;
	}

	cout << "������������" << endl;
	string name;
	cin >> name;

	cout << "���������룺" << endl;
	string pwd;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ���" << endl;
	ofs.close();
	this->initVector();
}

void Manager::showPerson()
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1.�鿴ȫ��ѧ���˺�" << endl;
	cout << "2.�鿴ȫ����ʦ�˺�" << endl;

	int select = inputInt();

	if (select == 1)
	{
		cout << "ѧ���˺��б�" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else if (select == 2)
	{
		cout << "��ʦ�˺��б�" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
 }

void Manager::showComputer()
{
	cout << "������Ϣ���£�" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "������ţ�" << it->m_Comid << "�������������" << it->m_MaxNum << endl;
	}
}

void Manager::cleanFile()
{
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "��ճɹ���" << endl;
}

void Manager::initVector()
{
	vStu.clear();
	vTea.clear();
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ�ܣ�" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	ifs.close();

	ifs.open(TEACHER_FILE , ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ�ܣ�" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	ifs.close();
}

bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}

void Manager::initcomputerRoom()
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom cr;
	while (ifs >> cr.m_Comid && ifs >> cr.m_MaxNum && ifs >> cr.m_Person)
	{
		this->vCom.push_back(cr);
	}
	ifs.close();
}