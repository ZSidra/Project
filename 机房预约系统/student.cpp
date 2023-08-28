#include"student.h"

Student::Student()
{

}

Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->initcomputerRoom();
}

void Student::operMenu()
{
	cout << "��ӭ" << this->m_Name << "ͬѧ��¼��" << endl;
	cout << "\t\t-------------------------------\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t|          1.����ԤԼ         |\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t|          2.�鿴�ҵ�ԤԼ     |\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t|          3.�鿴����ԤԼ     |\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t|          4.ȡ��ԤԼ         |\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t|          0.ע����¼         |\n";
	cout << "\t\t|                             |\n";
	cout << "\t\t-------------------------------\n";
	cout << "�����빦��ѡ��" << endl;
 }

void Student::applyOrder()
{
	cout << "��������ʱ��Ϊ��һ������" << endl;
	cout << "����������ԤԼʱ�䣺" << endl;
	cout << "1.��һ" << endl;
	cout << "2.�ܶ�" << endl;
	cout << "3.����" << endl;
	cout << "4.����" << endl;
	cout << "5.����" << endl;

	int date;
	int interval;
	int room;

	while (true)
	{
		date = inputInt();
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "�����������������룺" << endl;
	}

	cout << "����������ԤԼ��ʱ��Σ�" << endl;
	cout << "1.����" << endl;
	cout << "2.����" << endl;

	while (true)
	{
		interval = inputInt();
		if (interval == 1 || interval == 2)
		{
			break;
		}
		cout << "�����������������룺" << endl;
	}

	cout << "��ѡ�������" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		cout << vCom[i].m_Comid << "�Ż�������Ϊ��" << vCom[i].m_MaxNum - vCom[i].m_Person<< endl;
	}

	while (true)
	{
		room = inputInt();
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "�����������������룺" << endl;
	}
	cout << "ԤԼ�ɹ�����ȴ���ʦ��ˣ�" << endl;
	vCom[room - 1].m_Person++;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();
}

void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		if (this->m_Id == atoi(of.m_OrderDate[i]["stuId"].c_str()))
		{
			cout << "ԤԼ���ڣ���" << of.m_OrderDate[i]["date"] << " ";
			cout << "ʱ��Σ�" << (of.m_OrderDate[i]["interval"] == "1" ? "����" : "����") << " ";
			cout << "�����ţ�" << of.m_OrderDate[i]["roomId"] << " ";
			string status = "״̬:";
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
}

void Student::showAllOrder()
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

void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		return;
	}
	cout << "������ȡ��������Լ��ɹ���ԤԼ��" << endl;
	vector<int>v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (this->m_Id == atoi(of.m_OrderDate[i]["stuId"].c_str()))
		{
				if (atoi(of.m_OrderDate[i]["status"].c_str()) == 1 || atoi(of.m_OrderDate[i]["status"].c_str()) == 2)
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
	}
	cout << "������ȡ���ļ�¼��0������" << endl;
	while (true)
	{
		int select = inputInt();
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			of.m_OrderDate[v[select - 1]]["status"] = "0";

			of.updateOrder();

			vCom[atoi(of.m_OrderDate[v[select - 1]]["roomId"].c_str()) - 1].m_Person--;

			cout << "ԤԼ��ȡ��!" << endl;
			return;
		}
		cout << "�����������������룺" << endl;
	}
}

void Student::initcomputerRoom()
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