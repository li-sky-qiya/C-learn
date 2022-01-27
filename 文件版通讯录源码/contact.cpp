#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"

static int Find_by_name(const struct Contact* ps, char name[MAX_NAME])
{
	//�ҵ������±꣬�Ҳ�������-1
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (0 == strcmp(name, ps->data[i].name))
		{
			return i;
		}
	}
	return -1;
}

static int comp_PeoInfo_by_name(const void* e1, const void* e2)
{
	return strcmp(((struct PeoInfo*)e1)->name, ((struct PeoInfo*)e2)->name);
}

int CheckCapacity(struct Contact* ps)
{
	if (ps->size == ps->capacity)
	{
		//����
		struct PeoInfo* ptr = (struct PeoInfo*)realloc(ps->data, (ps->capacity + INCREASE_SZ) * sizeof(struct PeoInfo));
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += INCREASE_SZ;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 1;
	}
}

void LoadContact(struct Contact* ps)
{
	struct PeoInfo tmp = { 0 };
	FILE* pfRead = fopen("contact.dat", "rb");
	if (NULL == pfRead)
	{
		printf("LoadContact::%s\n", strerror(errno));
		return;
	}
	//��ȡ�ļ���ŵ�ͨѶ¼��
	while (fread(&tmp, sizeof(struct PeoInfo), 1, pfRead))
	{
		CheckCapacity(ps);
		ps->data[ps->size] = tmp;
		ps->size++;
	}
	fclose(pfRead);
	pfRead = NULL;
}

void InitContact(struct Contact* ps)
{
	ps->data = (struct PeoInfo*)malloc(DEFAULT_SZ * sizeof(struct PeoInfo));
	//��ʼ���Դ�� 3 ���˵���Ϣ
	if (ps->data == NULL)
	{
		return;
	}
	ps->size = 0;
	ps->capacity = DEFAULT_SZ;
	//���ļ������е���Ϣ���ص�ͨѶ¼��
	LoadContact(ps);
}

void AddContact(struct Contact* ps)
{
	int check = CheckCapacity(ps);//��������Ƿ�����
	//�� ������ �ɹ�����1 ʧ�ܷ���0
	//���� �򲻽����κβ��� ����1

	//��������
	if (1 == check)
	{
		printf("���������֣�>");
		scanf("%s", ps->data[ps->size].name);
		printf("���������䣺>");
		scanf("%d", &(ps->data[ps->size].age));
		printf("�������Ա�>");
		scanf("%s", ps->data[ps->size].sex);
		printf("������绰��>");
		scanf("%s", ps->data[ps->size].tele);
		printf("�������ַ��>");
		scanf("%s", ps->data[ps->size].addr);

		ps->size++;
		printf("��ӳɹ�\n");
	}
	else
	{
		printf("����ʧ��\n");
	}
}

void ShowContact(const struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
	}
	else
	{
		int i = 0;
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
		for (i = 0; i < ps->size; i++)
		{
			printf("%-20s\t%-4d\t%-5s\t%-12s\t%-20s\n",
				ps->data[i].name,
				ps->data[i].age,
				ps->data[i].sex,
				ps->data[i].tele,
				ps->data[i].addr
			);
		}
	}
}

void DelContact(struct Contact* ps)
{
	char name[MAX_NAME];
	printf("������Ҫɾ���˵�����:>");
	scanf("%s", name);
	//����
	int pos = Find_by_name(ps,name);
	//ɾ��
	if (pos == -1)
	{
		printf("����ϵ�˲�����\n");
	}
	else
	{
		int j = 0;
		for (j = pos; j < ps->size - 1; j++)
		{
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;
	}
}

void SearchContact(const struct Contact* ps)
{
	char name[MAX_NAME];
	printf("�����������ϵ�˵�����:>");
	scanf("%s", name);
	int pos = Find_by_name(ps, name);
	if (-1 == pos)
	{
		printf("����ϵ�˲�����\n");
	}
	else
	{
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
		printf("%-20s\t%-4d\t%-5s\t%-12s\t%-20s\n",
			ps->data[pos].name,
			ps->data[pos].age,
			ps->data[pos].sex,
			ps->data[pos].tele,
			ps->data[pos].addr
		);
	}
}

void ModifyContact(struct Contact* ps)
{
	char name[MAX_NAME];
	printf("�������޸���ϵ������:>");
	scanf("%s", name);
	int pos = Find_by_name(ps, name);
	if (-1 == pos)
	{
		printf("����ϵ�˲�����\n");
	}
	else
	{
		printf("���������֣�>");
		scanf("%s", ps->data[pos].name);
		printf("���������䣺>");
		scanf("%d", &(ps->data[pos].age));
		printf("�������Ա�>");
		scanf("%s", ps->data[pos].sex);
		printf("������绰��>");
		scanf("%s", ps->data[pos].tele);
		printf("�������ַ��>");
		scanf("%s", ps->data[pos].addr);

		printf("�޸����\n");
	}
}

void SortContact(struct Contact* ps)
{
	qsort(ps->data, ps->size, sizeof(ps->data[0]), comp_PeoInfo_by_name);
	printf("�������\n");
}

void DestroyContact(struct Contact* ps)
{
	free(ps->data);
	ps->data = NULL;
}

void SaveContact(struct Contact* ps)
{
	FILE* pfWrite = fopen("contact.dat", "wb");
	if (NULL == pfWrite)
	{
		printf("SaveContact::%s\n", strerror(errno));
		return;
	}
	//дͨѶ¼�����ݵ��ļ���
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		fwrite(&ps->data[i], sizeof(struct PeoInfo), 1, pfWrite);
	}
	fclose(pfWrite);
	pfWrite = NULL;
	printf("����ɹ�\n");
}