#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"

static int Find_by_name(const struct Contact* ps, char name[MAX_NAME])
{
	//找到返回下标，找不到返回-1
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
		//增容
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
	//读取文件存放到通讯录中
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
	//初始可以存放 3 个人的信息
	if (ps->data == NULL)
	{
		return;
	}
	ps->size = 0;
	ps->capacity = DEFAULT_SZ;
	//把文件中已有的信息加载到通讯录中
	LoadContact(ps);
}

void AddContact(struct Contact* ps)
{
	int check = CheckCapacity(ps);//检测容量是否已满
	//满 则增容 成功返回1 失败返回0
	//不满 则不进行任何操作 返回1

	//增加数据
	if (1 == check)
	{
		printf("请输入名字：>");
		scanf("%s", ps->data[ps->size].name);
		printf("请输入年龄：>");
		scanf("%d", &(ps->data[ps->size].age));
		printf("请输入性别：>");
		scanf("%s", ps->data[ps->size].sex);
		printf("请输入电话：>");
		scanf("%s", ps->data[ps->size].tele);
		printf("请输入地址：>");
		scanf("%s", ps->data[ps->size].addr);

		ps->size++;
		printf("添加成功\n");
	}
	else
	{
		printf("扩容失败\n");
	}
}

void ShowContact(const struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("通讯录为空\n");
	}
	else
	{
		int i = 0;
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-20s\n", "名字", "年龄", "性别", "电话", "地址");
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
	printf("请输入要删除人的姓名:>");
	scanf("%s", name);
	//查找
	int pos = Find_by_name(ps,name);
	//删除
	if (pos == -1)
	{
		printf("该联系人不存在\n");
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
	printf("请输入查找联系人的姓名:>");
	scanf("%s", name);
	int pos = Find_by_name(ps, name);
	if (-1 == pos)
	{
		printf("该联系人不存在\n");
	}
	else
	{
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-20s\n", "名字", "年龄", "性别", "电话", "地址");
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
	printf("请输入修改联系人姓名:>");
	scanf("%s", name);
	int pos = Find_by_name(ps, name);
	if (-1 == pos)
	{
		printf("该联系人不存在\n");
	}
	else
	{
		printf("请输入名字：>");
		scanf("%s", ps->data[pos].name);
		printf("请输入年龄：>");
		scanf("%d", &(ps->data[pos].age));
		printf("请输入性别：>");
		scanf("%s", ps->data[pos].sex);
		printf("请输入电话：>");
		scanf("%s", ps->data[pos].tele);
		printf("请输入地址：>");
		scanf("%s", ps->data[pos].addr);

		printf("修改完成\n");
	}
}

void SortContact(struct Contact* ps)
{
	qsort(ps->data, ps->size, sizeof(ps->data[0]), comp_PeoInfo_by_name);
	printf("排序完成\n");
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
	//写通讯录中数据到文件中
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		fwrite(&ps->data[i], sizeof(struct PeoInfo), 1, pfWrite);
	}
	fclose(pfWrite);
	pfWrite = NULL;
	printf("保存成功\n");
}