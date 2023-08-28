#include"speechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech(); 

	this->createSpeaker();

	this->loadRecord();
}

void SpeechManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "***********   ��ӭ�μ��ݽ�����   ***********" << endl;
	cout << "***********    1.��ʼ�ݽ�����    ***********" << endl;
	cout << "***********    2.�鿴�����¼    ***********" << endl;
	cout << "***********    3.��ձ�����¼    ***********" << endl;
	cout << "***********    0.�˳���������    ***********" << endl;
	cout << "********************************************" << endl;
}

void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->V.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();
}

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";

	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		this->v1.push_back(i + 10001);

		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

void SpeechManager::startSpeech()
{
	//��һ�ֿ�ʼ����

	//��ǩ
	this->speechDraw();
	//����
	this->speechContest();
	//��ʾ�������
	this->showScore();
	//�ڶ��ֿ�ʼ����
	this->m_Index++;
	//��ǩ
	this->speechDraw();
	//����
	this->speechContest();
	//��ʾ���ս��
	this->showScore();
	//����������ļ���
	this->saveRecord();
	//����
	this->m_Index = 1;
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
	cout << "�������������" << endl;
}

void SpeechManager::speechDraw()
{
	cout << "��" << this->m_Index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "------------------------------" << endl;
	system("pause");
}

void SpeechManager::speechContest()
{
	cout << "-----------��" << this->m_Index << "�ֱ�����ʽ��ʼ��-----------" << endl;

	multimap<double, int , greater<double>>groupScore;

	int num = 0;

	vector<int>v_Src;
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / double(d.size());

		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		groupScore.insert(make_pair(avg, *it));

		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "ѡ�ֱ�ţ�" << it->second << "\t" << "������" << this->m_Speaker[it->second].m_Name << "\t" << "�ɼ���" <<this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back(it->second);
				}
				else
				{
					V.push_back(it->second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
		
	}
	cout << "-----------��" << this->m_Index << "�ֱ�������-----------" << endl;
	system("pause");
}

void SpeechManager::showScore()
{
	cout << "��" << this->m_Index << "�ֽ���ѡ����Ϣ���£�" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = V;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << "������" << this->m_Speaker[*it].m_Name << "�÷֣�" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->showMenu();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//��׷�ӵķ�ʽд�ļ�

	for (vector<int>::iterator it = V.begin(); it != V.end(); it++)

	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼����ɹ���" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "�ļ�Ϊ��" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "����Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;
	ifs.putback(ch);//�������ȡ�ĵ����ַ��Ż�
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;
		int pos = -1;//�鵽","λ�õı���
		int start = 0;
		

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		v.clear();
		index++;

	}
	ifs.close();
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty == true)
	{
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "��" << i + 1 << "��"
				<< "�ھ���ţ�" << this->m_Record[i][0] << "�÷֣�" << this->m_Record[i][1] << "\t"
				<< "�Ǿ���ţ�" << this->m_Record[i][2] << "�÷֣�" << this->m_Record[i][3] << "\t"
				<< "������ţ�" << this->m_Record[i][4] << "�÷֣�" << this->m_Record[i][5] << endl;
		}
	}
}

void SpeechManager::clearRecord()
{
	cout << "ȷ�����ȫ�����ݣ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.ȡ��" << endl;

	int choice;

	if (!(cin >> choice))
	{
		cout << "������Ϸ��ַ���" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
	}

	if (choice == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->initSpeech();

		this->createSpeaker();

		this->loadRecord();

		cout << "��ճɹ���" << endl;

		this->fileIsEmpty = true;
	}
	else
	{
		return;
	}
}

SpeechManager::~SpeechManager()
{

}