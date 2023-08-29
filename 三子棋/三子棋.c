#define _CRT_SECURE_NO_WARNINGS
#include"game.h"

void menu()
{
	printf("**********************\n");
	printf("******* 1.play *******\n");
	printf("******* 0.exit *******\n");
	printf("**********************\n");
	printf("����������ѡ��\n");
}

void game()
{

	//��������
	char board[ROW][COL] = { 0 };
	//���̳�ʼ��
	initBoard(board, ROW, COL);
	//��ӡ����
	displayBoard(board, ROW, COL);
	while (1)
	{
		//��Ҳ���
		playerMove(board, ROW, COL);
		displayBoard(board, ROW, COL);
		char ret = isWin(board, ROW, COL);
		//���Բ���
		computerMove(board, ROW, COL);
		displayBoard(board, ROW, COL);
		ret = isWin(board, ROW, COL);
		if (ret != 'c')
		{
			if (ret == 'o')
			{
				printf("���ʤ����\n");
			}
			else if (ret == 'x')
			{
				printf("����ʤ����\n");
			}
			else
			{
				printf("ƽ�֣�\n");
			}
			break;
		}
	}
}

int main()
{
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		system("cls");
		menu();
		scanf("%d", &input);
		switch(input)
		{
		case 1:
			game();
			break;
		case 0:
			break;
		default:
			printf("��������");
		}
		system("pause");
	} while (input);

	return 0;
}