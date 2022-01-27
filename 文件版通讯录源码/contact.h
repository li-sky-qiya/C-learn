#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

//#define MAX 1000
#define DEFAULT_SZ 3//初始容量
#define INCREASE_SZ 2//每次增加容量

#define MAX_NAME 20
#define MAX_SEX 5
#define MAX_TELE 12
#define MAX_ADDR 30

enum Option
{
	Exit,
	Add,
	Del,
	Search,
	Modify,
	Show,
	Sort,
	Save
};

struct PeoInfo//信息
{
	char name[MAX_NAME];//姓名
	int age;//年龄
	char sex[MAX_SEX];//性别
	char tele[MAX_TELE];//电话
	char addr[MAX_ADDR];//住址
};

struct Contact//通讯录类型
{
	struct PeoInfo *data;
	int size;//记录当前已有信息数
	int capacity;//当前通讯录的最大容量
};

void InitContact(struct Contact* ps);
void AddContact(struct Contact* ps);
void ShowContact(const struct Contact* ps);
void DelContact(struct Contact* ps);
void SearchContact(const struct Contact* ps);
void ModifyContact(struct Contact* ps);
void SortContact(struct Contact* ps);
void DestroyContact(struct Contact* ps);
void SaveContact(struct Contact* ps);
void LoadContact(struct Contact* ps);
