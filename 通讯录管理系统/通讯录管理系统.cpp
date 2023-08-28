#include<iostream>
#include<string>
using namespace std;
#define MAX 1000

struct person
{
	string m_Name;
	int m_Sex;
	int m_Age;
	string m_Phone;
	string m_Addr;
};

struct addressbook
{
	person personArray[MAX];
	int m_Size;
};

void showMenu()
{
	cout << "****** ͨѶ¼����ϵͳ ******" << endl;
	cout << "****************************" << endl;
	cout << "*****   1.�����ϵ��   *****" << endl;
	cout << "*****   2.��ʾ��ϵ��   *****" << endl;
	cout << "*****   3.ɾ����ϵ��   *****" << endl;
	cout << "*****   4.������ϵ��   *****" << endl;
	cout << "*****   5.�޸���ϵ��   *****" << endl;
	cout << "*****   6.�����ϵ��   *****" << endl;
	cout << "*****   0.�˳�ͨѶ¼   *****" << endl;
	cout << "****************************" << endl;
}

void addPerson(addressbook* abs) {
	if (abs->m_Size == MAX)
	{
		cout << "ͨѶ¼�������޷����������ϵ��" << endl;
		return;
	}
	else
	{
		cout << "������������" << endl;
		string name;
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;

		cout << "�������Ա�" << endl;
		cout << "1 -- ��" << endl;
		cout << "2 -- Ů" << endl;
		int sex;
		
		while (true)
		{
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[abs->m_Size].m_Sex = sex;
				break;
			}

				cout << "������ı���������������룺" << endl;
				cin.clear();//�޸�������
				cin.ignore();//ȡ��������������е��ַ�
		}
	
				
		cout << "���������䣺" << endl;
		int age;	
		while (true)
		{
			cin >> age;
			if (sex < 150 || sex > 0)
			{
				abs->personArray[abs->m_Size].m_Age = age;
				break;
			}
				cout << "��������ȷ�����䣺" << endl;
				cin.clear();
				cin.ignore();
		}
		
		cout << "��������ϵ�绰��" << endl;
		string phone;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		cout << "�������ͥ��ַ��" << endl;
		string address;
		cin >> address;
		abs->personArray[abs->m_Size].m_Addr = address;

		abs->m_Size++;
		cout << "��ӳɹ�" << endl;
		system("pause");
		system("cls");
		return;
	}
}

void showPerson(addressbook* abs)
{
	if (abs -> m_Size == 0)
	{
		cout << "ͨѶ¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < abs->m_Size; i++)
		{
			cout << "������" << abs->personArray[i].m_Name << "\t" << "�Ա�" << (abs->personArray[i].m_Sex == 1 ? "��" : "Ů") << "\t" << "���䣺" 
				<< abs->personArray[i].m_Age << "\t" << "��ϵ�绰��" << abs->personArray[i].m_Phone << "\t" << "��ͥסַ��" << abs->personArray[i].m_Addr << endl;
		}
	}
	system("pause");
	system("cls");
}

int isExist(addressbook* abs , string name)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		if (abs->personArray[i].m_Name == name)
		{
			return i;
		}
	}
	return -1;
}

void deletePerson(addressbook * abs)
{
	cout << "��������Ҫɾ������ϵ�ˣ�" << endl;
	string name;
	cin >> name;
	int ret = isExist(abs, name);
	if (ret != -1)
	{
		for (int i = ret; i < abs->m_Size; i++)
		{
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_Size--;
		cout << "ɾ���ɹ�" << endl;
	}
	else
	{
		cout << "����ϵ�˲�����" << endl;
	}
	system("pause");
	system("cls");
}

void findPerson(addressbook* abs)
{
	cout << "��������Ҫ���ҵ���ϵ��" << endl;
	string name;
	cin >> name;
	int ret = isExist(abs, name);
	if (ret != -1)
	{
		cout << "������" << abs->personArray[ret].m_Name << "\t" << "�Ա�" << (abs->personArray[ret].m_Sex == 1 ? "��" : "Ů") << "\t" << "���䣺"
			<< abs->personArray[ret].m_Age << "\t" << "��ϵ�绰��" << abs->personArray[ret].m_Phone << "\t" << "��ͥסַ��" << abs->personArray[ret].m_Addr << endl;
	}
	else
	{
		cout << "����ϵ�˲�����" << endl;
	}
	system("pause");
	system("cls");
}

void modifyPerson(addressbook * abs)
{
	cout << "��������Ҫ�޸ĵ���ϵ��" << endl;
	string name;
	cin >> name;
	int ret = isExist(abs , name);
	if (ret != -1)
	{
		cout << "������������" << endl;
		string n_name;
		cin >> n_name;
		abs->personArray[ret].m_Name = n_name;

		cout << "�������Ա�" << endl;
		cout << "1 -- ��" << endl;
		cout << "2 -- Ů" << endl;
		int sex;

		while (true)
		{
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[ret].m_Sex = sex;
				break;
			}

			cout << "������ı���������������룺" << endl;
			cin.clear();//�޸�������
			cin.ignore();//ȡ��������������е��ַ�
		}


		cout << "���������䣺" << endl;
		int age;
		while (true)
		{
			cin >> age;
			if (sex < 150 || sex > 0)
			{
				abs->personArray[ret].m_Age = age;
				break;
			}
			cout << "��������ȷ�����䣺" << endl;
			cin.clear();
			cin.ignore();
		}

		cout << "��������ϵ�绰��" << endl;
		string phone;
		cin >> phone;
		abs->personArray[ret].m_Phone = phone;

		cout << "�������ͥ��ַ��" << endl;
		string address;
		cin >> address;
		abs->personArray[ret].m_Addr = address;

		cout << "�޸ĳɹ�" << endl;
	}
	else
	{
		cout << "����ϵ�˲�����" << endl;
	}
	system("pause");
	system("cls");
}

void cleanPerson(addressbook* abs)
{
	cout << "��ȷ��Ҫ���ͨѶ¼����պ����ݽ��޷��ָ�" << endl;
	cout << "1 -- ��" << endl;
	cout << "2 -- ��" << endl;
	int sur = 0;
	while (true)
	{
		cin >> sur;
		if (sur == 1 || sur == 2)
		{
			switch (sur)
			{
			case 1:
				abs->m_Size = 0;
				cout << "ͨѶ¼�����" << endl;
				break;
			case 2:
				break;
			}
			break;
		}

		cout << "������ı���������������룺" << endl;
		cin.clear();
		cin.ignore();
	}
	
	system("pause");
	system("cls");

}

int main()
{
	string name;
	int select = 0;
	addressbook abs;
	abs.m_Size = 0;

	while (true)
	{
		showMenu();
		cin >> select;

		switch (select)
		{
		case 1:
			addPerson(&abs);
			break;
		case 2:
			showPerson(&abs);
			break;
		case 3:
			deletePerson(&abs);
			break;
		case 4:
			findPerson(&abs);
			break;
		case 5:
			modifyPerson(&abs);
			break;
		case 6:
			cleanPerson(&abs);
			break;
		case 0:
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "��ѡ�����й���" << endl;
			system("pause");
			system("cls");
		}

	}


	system("pause");

	return 0;
}