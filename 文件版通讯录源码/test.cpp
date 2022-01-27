#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"

void menu()
{
	printf("***               Contact                  ***\n");
	printf("***    1.add                      2.del    ***\n");
	printf("***    3.search                   4.modify ***\n");
	printf("***    5.show                     6.sort   ***\n");
	printf("***    7.save                     0.exit   ***\n");
	printf("**********************************************\n");
}

void test()
{
	int input = 0;
	struct Contact con;//创建通讯录
	InitContact(&con);//初始化通讯录
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case Exit:
			SaveContact(&con);//先保存再销毁
			//销毁通讯录，释放动态内存
			DestroyContact(&con);
			printf("退出通讯录\n");
			break;
		case Add:
			AddContact(&con);//添加联系人
			break;
		case Del:
			DelContact(&con);//删除指定联系人
			break;
		case Search:
			SearchContact(&con);//查找联系人
			break;
		case Modify:
			ModifyContact(&con);//修改联系人
			break;
		case Show:
			ShowContact(&con);//展示联系人
			break;
		case Sort:
			SortContact(&con);//按名字排序
			break;
		case Save:
			SaveContact(&con);//保存通讯录
			break;
		default:
			printf("选择错误，重新选择\n");
			break;
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}
