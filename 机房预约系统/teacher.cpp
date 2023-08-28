#include"teacher.h"

Teacher::Teacher()
{
	
}

Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->initcomputerRoom();
}

void Teacher::operMenu()
{
	cout << "��ӭ" << this->m_Name << "ͬѧ��¼��" << endl;
	cout << "\t\t-------------------------------\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t|          1.�鿴����ԤԼ     |\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t|          2.���ԤԼ         |\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t|          0.ע����¼         |\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t-------------------------------\n";
	cout << "�����빦��ѡ��" << endl;
}

void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << "ԤԼ���ڣ���" << of.m_OrderDate[i]["date"] << "\t";
		cout << "ʱ��Σ�" << (of.m_OrderDate[i]["interval"] == "1" ? "����" : "����") << "\t";
		cout << "ѧ�ţ�" << of.m_OrderDate[i]["stuId"] << "\t";
		cout << "������" << of.m_OrderDate[i]["stuName"] << "\t";
		cout << "�����ţ�" << of.m_OrderDate[i]["roomId"] << "\t";
		string status = "״̬��";
		switch (atoi(of.m_OrderDate[i]["status"].c_str()))
		{
		case 1:
			status += "�����";
			break;
		case 2:
			status += "ԤԼ�ɹ�";
			break;
		case -1:
			status += "ԤԼʧ��";
			break;
		case 0:
			status += "ԤԼȡ��";
			break;
		}
		cout << status << endl;
	}
}

void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		return;
	}
	cout << "����˵�ԤԼ��¼��" << endl;
	vector<int>v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
			if (atoi(of.m_OrderDate[i]["status"].c_str()) == 1)
			{
				v.push_back(i);
				cout << index++ << "ؼ";
				cout << "ԤԼ���ڣ���" << of.m_OrderDate[i]["date"] << " ";
				cout << "ʱ��Σ�" << (of.m_OrderDate[i]["interval"] == "1" ? "����" : "����") << " ";
				cout << "�����ţ�" << of.m_OrderDate[i]["roomId"] << " ";
				string status = "״̬��";
				switch (atoi(of.m_OrderDate[i]["status"].c_str()))
				{
				case 1:
					status += "�����";
					break;
				case 2:
					status += "ԤԼ�ɹ�";
					break;
				case -1:
					status += "ԤԼʧ��";
					break;
				case 0:
					status += "ԤԼȡ��";
					break;
				}
				cout << status << endl;
		}
	}
	cout << "��ѡ����˵ļ�¼��0������" << endl;
	while (true)
	{
		int select = inputInt();

		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "��ѡ����˽����" << endl;
				cout << "1.ͨ��" << endl;
				cout << "2.��ͨ��" << endl;
				int ret = inputInt();
				if (ret == 1 || ret == 2)
				{
					if (ret == 1)
					{
						of.m_OrderDate[v[select - 1]]["status"] = "2";
					}
					else if (ret == 2)
					{
						of.m_OrderDate[v[select - 1]]["status"] = "-1";
						vCom[atoi(of.m_OrderDate[v[select - 1]]["roomId"].c_str()) - 1].m_Person--;
					}
				}
			}


			of.updateOrder();
			cout << "�����ɣ�" << endl;

			return;
		}
		cout << "�����������������룺" << endl;
	}
}

void Teacher::initcomputerRoom()
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

