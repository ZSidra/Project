#pragma once
#include<iostream>
#include<vector>
#include<deque>
#include<map>
#include<algorithm>
#include<numeric>
#include<functional>
#include<fstream>
#include"speaker.h"
using namespace std;

class SpeechManager
{
public:
	SpeechManager();

	void showMenu();

	void exitSystem();

	void initSpeech();//��ʼ����������

	void createSpeaker();

	void startSpeech();//��ʼ����

	void speechDraw();//��ǩ

	void speechContest();//��������

	void showScore();//��ʾ�������

	void saveRecord();//�����¼

	void loadRecord();//��ȡ��¼

	void showRecord();

	void clearRecord();

	bool fileIsEmpty;//�ж��ļ��Ƿ�Ϊ��

	map<int, vector<string>>m_Record;//��������¼

	~SpeechManager();

	vector<int>v1;//�������ѡ�ֱ��

	vector<int>v2;//��Ž���ѡ�ֱ��

	vector<int>V;//���ʤ��ѡ�ֱ��

	map<int, Speaker>m_Speaker;//���ѡ�ֱ�źͶ�Ӧ��ѡ��

	int m_Index;//��������
};