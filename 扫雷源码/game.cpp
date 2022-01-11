#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

void menu()
{
	printf("**********************************\n");
	printf("***1.��ʼ��Ϸ        0.�˳���Ϸ***\n");
	printf("**********************************\n");
}

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}

void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	//��ӡ�к�
	for (i = 0; i <= col; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);//��ӡ�к�
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

int Level(int input1)
{
	switch (input1)
	{
	case 1:
		return EASY_COUNT;
	case 2:
		return COMMON_COUNT;
	case 3:
		return HARD_COUNT;
	default:
		printf("����������������룺>\n");
		return 0;
	}
}

void SetMine(char board[ROWS][COLS], int row, int col, int count)
{
	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}

int GetMineCount(char mine[ROWS][COLS], int x, int y)
{
	return
		mine[x - 1][y] +
		mine[x - 1][y - 1] +
		mine[x - 1][y + 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] +
		mine[x][y + 1] +
		mine[x][y - 1] - 8 * '0';
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col,int count)
{
	int x = 0;
	int y = 0;
	int win = 0;
	while (win < row * col - count)
	{
		printf("�������Ų����꣺>");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (mine[x][y] == '1')
			{
				printf("���ź���������ˣ�\n");
				DisplayBoard(mine, row, col);
				break;
			}
			else
			{
				int count1 = GetMineCount(mine, x, y);
				show[x][y] = count1 + '0';
				DisplayBoard(show, row, col);
				win++;
			}
		}
		else
		{
			printf("����Ƿ������������룺\n");
		}
	}
	if (win == row * col - count)
	{
		printf("��ϲ�㣬���׳ɹ���\n");
		DisplayBoard(mine, row, col);
	}
}