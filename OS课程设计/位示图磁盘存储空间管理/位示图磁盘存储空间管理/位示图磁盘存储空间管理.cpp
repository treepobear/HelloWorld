#include "pch.h"
#include<iostream>
using namespace std;

int BitMap[8][8];

void Print()
{
	cout << "-------当前磁盘存储存储位示图-------" << endl;
	cout << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << "\t    ";
		for (int j = 0; j < 8; j++)
		{
			cout << BitMap[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
}

void Assign()
{
	int request;//待分配的物理块数
	int free = 0;
	cout << "请输入你要分配的物理块数：";
	cin >> request;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			free++;
	if (request <= free)
	{
		cout << "分配成功！" << endl;
		cout << "分配的物理地址为：" << endl;
		cout << "柱面号\t" << "磁道号\t" << "物理记录号" << endl;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (request <= 0)
					break;
				if (BitMap[i][j] == 0)
				{
					BitMap[i][j] = 1;
					cout << i << "\t" << j / 4 << "\t" << j % 4 << endl;
					request--;
				}
			}
		}
	}
	else
		cout << "Sorry,没有足够的物理块进行分配!" << endl;

	cout << endl;
	Print();
}

void Recovery()
{
	int cylinder, track, record;
	cout << "请输入你想回收的物理地址：（柱面号、磁道号、物理记录号）" << endl;
	cin >> cylinder >> track >> record;
	int bytenum, position;
	bytenum = cylinder;//字节号
	position = track * 4 + record;//位号

	if (bytenum > 7 || position > 7)
	{
		cout << "输入的物理地址错误!" << endl;
		cout << endl;
		return;
	}

	BitMap[bytenum][position] = 0;
	cout << "回收成功！" << endl;
	cout << "回收字节号为:" << bytenum << "  回收的位号为:" << position << endl;
	cout << endl;

	Print();
}

int main()
{
	for (int i = 0; i < 8; i++)//位示图初始化
	{
		for (int k = 0; k < 8; k++)
			BitMap[i][k] = 0;
	}
	Print();
	int choice;
	while (true)
	{
		cout << "输入你要执行的操作： 1(分配) 2(回收)  -1(退出)" << endl;
		cin >> choice;
		if (choice == 1)
			Assign();
		else if (choice == 2)
			Recovery();
		else if (choice == -1)
			break;
	}
	getchar();
}
