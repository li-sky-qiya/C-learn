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
	struct Contact con;//����ͨѶ¼
	InitContact(&con);//��ʼ��ͨѶ¼
	do
	{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case Exit:
			SaveContact(&con);//�ȱ���������
			//����ͨѶ¼���ͷŶ�̬�ڴ�
			DestroyContact(&con);
			printf("�˳�ͨѶ¼\n");
			break;
		case Add:
			AddContact(&con);//�����ϵ��
			break;
		case Del:
			DelContact(&con);//ɾ��ָ����ϵ��
			break;
		case Search:
			SearchContact(&con);//������ϵ��
			break;
		case Modify:
			ModifyContact(&con);//�޸���ϵ��
			break;
		case Show:
			ShowContact(&con);//չʾ��ϵ��
			break;
		case Sort:
			SortContact(&con);//����������
			break;
		case Save:
			SaveContact(&con);//����ͨѶ¼
			break;
		default:
			printf("ѡ���������ѡ��\n");
			break;
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}
