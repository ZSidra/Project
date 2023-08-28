#include"workerManager.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//�ļ�������
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ����ڣ���������
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����ݴ浽������
	this->init_Emp();
	ifs.close();
}

void WorkerManager::Show_Menu()
{
	cout << "***************************************" << endl;
	cout << "******* ��ӭʹ��ְ������ϵͳ! *******" << endl;
	cout << "***************************************" << endl;
	cout << "*********** 0.�˳�������� ***********" << endl;
	cout << "*********** 1.����ְ����Ϣ ***********" << endl;
	cout << "*********** 2.��ʾְ����Ϣ ***********" << endl;
	cout << "*********** 3.ɾ����ְְ�� ***********" << endl;
	cout << "*********** 4.�޸�ְ����Ϣ ***********" << endl;
	cout << "*********** 5.����ְ����Ϣ ***********" << endl;
	cout << "*********** 6.���ձ������ ***********" << endl;
	cout << "*********** 7.��������ĵ� ***********" << endl;
	cout << "***************************************" << endl;
}

void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::addEmp()
{
	cout << "���������Ա��������" << endl;
	int addNum = 0;
	while (true)
	{
		if (!(cin >> addNum))
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

	if (addNum > 0)
	{
		int newSize = this->m_EmpNum + addNum;
		Worker** newSpace = new Worker * [newSize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		for (int i = 0; i < addNum; i++)
		{
			int id;//ְ�����
			string name;//ְ������
			int dselect;//����ѡ��
			cout << "�������" << i + 1 << "����ְ����ţ�" << endl;
			while (true)
			{
				if (!(cin >> id))
				{
					cout << "������Ϸ��ַ���" << endl;
					cin.clear();
					cin.ignore(1024, '\n');
				}
				else if (this->isExist(id) != -1)
				{
					cout << "�ñ�ŵ�ְ���Ѵ���,���������룺" << endl;
					continue;
				}
				else
				{
					break;
				}
			}	
			cout << "�������" << i + 1 << "����ְ��������" << endl;
			cin >> name;
			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			while (true)
			{
				if (!(cin >> dselect))
				{
					cout << "������Ϸ��ַ���" << endl;
					cin.clear();
					cin.ignore(1024, '\n');
				}
				else if (dselect < 1 || dselect > 3)
				{
					cout << "��������ȷ����ţ�" << endl;
					continue;
				}
				else
				{
					break;
				}
			}

			Worker* worker = NULL;
			switch (dselect)
			{
			case 1:
				worker = new Employee(id , name , dselect);
				break;
			case 2:
				worker = new Manager(id, name, dselect);
				break;
			case 3:
				worker = new Boss(id, name, dselect);
				break;
			}
			newSpace[this->m_EmpNum + i] = worker;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;
		this->m_FileIsEmpty = false;

		this->save();
		cout << "�ɹ����" << addNum << "��ְ��" << endl;
	}
	else
	{
		cout << "������������" << endl;
	}
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << "\t" <<
			this->m_EmpArray[i]->m_Name << "\t" <<
			this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name >> dId)
	{
		num++;
	}
	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
}

void WorkerManager::showEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
}

void WorkerManager::delEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "������Ҫɾ����ְ����ţ�" << endl;
		int id = 0;
		while (true)
		{
			if (!(cin >> id))
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
		int index = this->isExist(id);
		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "ɾ���ɹ�" << endl;
			if (this->m_EmpNum == 0)
			{
				this->m_FileIsEmpty = true;
			}
		}
		else
		{
			cout << "��ְ��������" << endl;
		}
	}
}

int WorkerManager::isExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

bool WorkerManager::isExist(string name)
{
	bool flag = false;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Name == name)
		{
			this->m_EmpArray[i]->showInfo();
			flag = true;
		}
	}
	return flag;
}

void WorkerManager::modEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ����ţ�" << endl;
		int id = 0;
		while (true)
		{
			if (!(cin >> id))
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
		int index = this->isExist(id);
		int newid = 0;
		string name;
		int dId = 0;
		if (index != -1)
		{
			delete this->m_EmpArray[index];
			cout << "���޸�idΪ��" << index << "����ְ��id��" << endl;
			while (true)
			{
				if (!(cin >> newid))
				{
					cout << "������Ϸ��ַ���" << endl;
					cin.clear();
					cin.ignore(1024, '\n');
				}
				else if (this->isExist(newid) != -1)
				{
					cout << "�ñ�ŵ�ְ���Ѵ���,���������룺" << endl;
					continue;
				}
				else
				{
					break;
				}
			}
			cout << "������ְ��������" << endl;
			cin >> name;
			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			while (true)
			{
				if (!(cin >> dId))
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
			switch (dId)
			{
			case 1:
				this->m_EmpArray[index] = new Employee(newid, name, dId);
				break;
			case 2:
				this->m_EmpArray[index] = new Manager(newid, name, dId);
				break;
			case 3:
				this->m_EmpArray[index] = new Boss(newid, name, dId);
				break;
			}
			this->save();
			cout << "�޸ĳɹ�" << endl;
		}
		else
		{
			cout << "��ְ��������" << endl;
		}
	}
}

void WorkerManager::findEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		int select = 0;
		cout << "��ѡ����ҷ�ʽ��" << endl;
		cout << "1.����Ų���" << endl;
		cout << "2.����������" << endl;
		while (true)
		{
			if (!(cin >> select))
			{
				cout << "������Ϸ��ַ���" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			else if (select != 1 && select != 2)
			{
				cout << "��������ȷ����ţ�" << endl;
				continue;
			}
			else
			{
				break;
			}
		}
		
		if (select == 1)
		{
			int id = 0;
			cout << "��������ҵ�ְ����ţ�" << endl;
			while (true)
			{
				if (!(cin >> id))
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
			int index = this->isExist(id);
			if (index != -1)
			{
				this->m_EmpArray[index]->showInfo();
			}
			else
			{
				cout << "�ñ�ŵ�Ա��������" << endl;
			}
		}
		else
		{
			string name;
			cout << "��������ҵ�ְ��������" << endl;
			cin >> name;

			if(!this->isExist(name))
			{
				cout << "��������Ա��������" << endl;
			}
		}
	}
}

void WorkerManager::sortEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1.��������" << endl;
		cout << "2.��������" << endl;
		int select = 0;
		while (true)
		{
			if (!(cin >> select))
			{
				cout << "������Ϸ��ַ���" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			else if (select != 1 && select != 2)
			{
				cout << "��������ȷ����ţ�" << endl;
				continue;
			}
			else
			{
				break;
			}
		}
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minormax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)
				{
					if (this->m_EmpArray[minormax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minormax = j;
					}
				}
				else
				{
					if (this->m_EmpArray[minormax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minormax = j;
					}
				}
			}
			if (minormax != i)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minormax];
				this->m_EmpArray[minormax] = temp;
			}
		}
		cout << "����ɹ�" << endl;
		this->save();
	}
}

void WorkerManager::cleanFile()
{
	cout << "ȷ��Ҫ����ĵ������ݽ��޷��ָ�" << endl;
	cout << "1.��" << endl;
	cout << "2.��" << endl;
	int select = 0;
	while (true)
	{
		if (!(cin >> select))
		{
			cout << "������Ϸ��ַ���" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (select != 1 && select != 2)
		{
			cout << "��������ȷ����ţ�" << endl;
			continue;
		}
		else
		{
			break;
		}
	}
	if (select == 1)
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = NULL;
				}
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "���������" << endl;
	}
	else
	{
		return;
	}
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}
