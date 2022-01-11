#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2
#define EASY_COUNT ROW*COL/8
#define COMMON_COUNT ROW*COL/6
#define HARD_COUNT ROW*COL/4

void menu();
void game();
void InitBoard(char board[ROWS][COLS], int rows, int cols, char set);
void DisplayBoard(char board[ROWS][COLS], int row, int col);
int Level(int input1);
void SetMine(char board[ROWS][COLS], int row, int col, int count);
void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS],int row, int col,int count);