#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

void game()
{
	//�׵���Ϣ�洢
	char mine[ROWS][COLS] = { 0 };
	//�Ų�����׵���Ϣ
	char show[ROWS][COLS] = { 0 };
	int count = 0;
	int input1 = 0;
	//��ʼ��
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	//��ӡ����
	DisplayBoard(mine, ROW, COL);
	printf("1.��ģʽ  2.һ��ģʽ  3.����ģʽ\n");
again:
	printf("��ѡ���Ѷȣ�>");
	scanf("%d", &input1);
	count = Level(input1);
	//������
	if (count != 0)
	{
		SetMine(mine, ROW, COL, count);
		printf("��Ϸ��ʼ��\n");
	}
	else
	{
		goto again;
	}
	
	//ɨ��
	FindMine(mine,show, ROW, COL,count);

}

void test()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("��ѡ��>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("ѡ�����������ѡ��\n");
			break;
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}