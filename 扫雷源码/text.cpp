#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

void game()
{
	//雷的信息存储
	char mine[ROWS][COLS] = { 0 };
	//排查出的雷的信息
	char show[ROWS][COLS] = { 0 };
	int count = 0;
	int input1 = 0;
	//初始化
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	//打印棋盘
	DisplayBoard(mine, ROW, COL);
	printf("1.简单模式  2.一般模式  3.困难模式\n");
again:
	printf("请选择难度：>");
	scanf("%d", &input1);
	count = Level(input1);
	//布置雷
	if (count != 0)
	{
		SetMine(mine, ROW, COL, count);
		printf("游戏开始！\n");
	}
	else
	{
		goto again;
	}
	
	//扫雷
	FindMine(mine,show, ROW, COL,count);

}

void test()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("请选择：>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误，请重新选择\n");
			break;
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}