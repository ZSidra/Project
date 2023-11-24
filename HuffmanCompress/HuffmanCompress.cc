#include"HuffmanTree.hpp"
#include"FileCompressHuffman.h"

void menu()
{
	std::cout << "*******************************" << std::endl;
	std::cout << "*****    1.Huffmanѹ��    *****" << std::endl;
	std::cout << "*****    2.Huffman��ѹ    *****" << std::endl;
	std::cout << "*****    0.�˳�           *****" << std::endl;
	std::cout << "*******************************" << std::endl;
}

int inputInt()
{
	int num;
	while (true)
	{
		if (!(std::cin >> num))
		{
			std::cout << "������Ϸ��ַ���" << std::endl;
			std::cin.clear();
			std::cin.ignore(1024, '\n');
		}
		else
		{
			break;
		}
	}
	return num;
}

int main()
{
	int input = 0;
	while (1)
	{
		menu();
		input = inputInt();
		FileCompressHuffman fh;
		switch (input)
		{
		case 1:
			fh.getPath();
			fh.CompressFile();
			break;
		case 2:
			fh.getPath();
			fh.UNCCompressFile();
			break;
		case 0:
			exit(0);
			break;
		default:
			std::cout << "��������ȷ�Ĺ��ܱ�ţ�" << std::endl;
			break;
		}
		system("pause");
		system("cls");
	}
	
	

	return 0;
}