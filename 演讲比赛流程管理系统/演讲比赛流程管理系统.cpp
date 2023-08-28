#include<iostream>
#include<ctime>
#include"speechManager.h"
using namespace std;

int main()
{
	srand((unsigned int)time(NULL));

	SpeechManager sm;

	int choice = 0;

	while (true)
	{
		sm.showMenu();

		cout << "�����빦�ܱ�ţ�" << endl;
		if (!(cin >> choice))
		{
			cout << "������Ϸ��ַ���" << endl;
			cin.clear();
			cin.ignore(1024 , '\n');
		}

		switch (choice)
		{
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			cout << "��������ȷ�ı��!" << endl;
			break;
		}
		system("pause");
		system("cls");
	}

	system("pause");

	return 0;
}