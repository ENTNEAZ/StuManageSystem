#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
	int year;
	int month;
	int day;
};
struct Stu {
	int id;//学号 
	char name[15];//姓名 
	char sex[5]; //性别 
	char field[30];//专业 
	struct Date birthday;//出生日期 
	char address[100];//家庭地址 
	float E_grade;//英语入学成绩 
	struct Stu* next;
};

//有新生来报到，要逐个录入其信息，
//如：学生姓名，性别，专业，出生日期，家庭地址，英语入学成绩。
//要求设计链表类来实现，并统计学生人数。文本界面为：
//1. 新增学生信息 
//2. 删除学生信息
//3. 导入学生信息（已经保存于的文件信息）
//4. 学生信息搜索（按姓名）
//5. 学生信息统计（按专业或性别或年龄---年龄要自动计算）
//6. 按英语成绩排序
//7. 学生信息保存
//8. 退出

struct Stu* head = (struct Stu*)malloc(sizeof(struct Stu));
struct Stu* p, * q;
struct Stu* last;

void menu();//菜单 
void add();//新增学生信息
void search();//学生信息搜索(按姓名) 
void change();//修改学生信息（好像没要求写，自己加的） 
void del();//删除学生信息
void searchall();//学生信息统计（按专业或性别或年龄---年龄要自动计算） 
void sort();//排序 
void save();//学生信息保存 
bool isExist(int id,bool output);

void menu() {
	int userChoice;
	while (true) {
		system("cls");
		printf("----------------------------学生基本信息管理系统----------------------------\n");
		printf("\n");
		printf("\n");
		printf("                            新增学生信息输入 1 \n");
		printf("                            查询学生信息输入 2 \n");
		printf("                            修改学生信息输入 3 \n");
		printf("                            删除学生信息输入 4 \n");
		printf("                            浏览全部信息输入 5 \n");
		printf("                            学生成绩排序输入 6 \n");
		printf("                            学生信息储存输入 7 \n");
		printf("                            保存并安全退出   8 \n");
		printf("-----------------------------------------------------------------------------\n");
		scanf("%d", &userChoice);
		switch (userChoice)
		{
		case 1:
			add();
			break;
		case 2:
			search();
			break;
		case 3:
			change();
			break;
		case 4:
			del();
			break;
		case 5:
			searchall();
			break;
		case 6:
			sort();
			break;
		case 7:
			save();
			break;
		case 8:
			printf("退出");
		default:
			printf("重新输入\n");
		}
	}
}

void add()//增加 
{
	int id;
	struct Stu* toAdd;
	printf("输入id：");
	scanf("%d", &id);
	if (isExist(id, true)) {
		add();//已经存在此人 递归再次输入
	}
	

	if (last == head)
		toAdd = head;
	else
		toAdd = (struct Stu*)malloc(sizeof(struct Stu));
		
	toAdd->id = id;
	printf("输入姓名: ");
	scanf("%s", &toAdd->name);
	printf("输入性别: ");
	scanf("%s", &toAdd->sex);
	printf("输入专业: ");
	scanf("%s", &toAdd ->field);
	printf("输入出生日期: ");
	scanf("%d", &toAdd->birthday);
	printf("输入家庭地址: ");
	scanf("%s", &toAdd->address);
	printf("输入英语入学成绩：");
	scanf("%f", &toAdd->E_grade);
	toAdd->next = NULL;
	last->next = toAdd;
	last = toAdd;
	return;
}

bool isExist(int id,bool output = false)//查重 output为是否输出已经存在的信息
{
	struct Stu* item = head;
	if (item->id == id)
	{
		if (output) {
			printf("id: %d   姓名: %s   性别: %s   专业: %s   \n", item->id, item->name, item->sex, item->field);
			printf("学号已存在，请重新输入\n");
			printf("\n");
		}
		return true;
	}
	while (item->next != NULL)
	{
		if (item->id == id)
		{
			if (output) {
				printf("id: %d   姓名: %s   性别: %s   专业: %s   \n", item->id, item->name,item->sex, item->field);
				printf("学号已存在，请重新输入\n");
				printf("\n");
			}
			return true;
		}
		else
			item = item -> next;
	}
	return false;
}

void search()//查询 
{
	char iname[15];
	printf("输入要查询学生的id:");
	scanf("%s", &iname);
	p = head;
	while (p != NULL)
	{
		if (p->name == iname)
		{
			printf("id: %d   姓名: %s   性别: %s   专业: %s   出生日期: %s   家庭地址: %s   英语入学成绩: %f\n", p->id, p->name, p->sex, p->field, p->birthday, p->address, p->E_grade);
			menu();
		}
	}
	printf("查无此人,请重新输入\n");
	search();
}

void change()//修改 
{
	int i;
	printf("输入要修改学生的id:");
	scanf("%d", &i);
	p = head;
	while (p != NULL)
	{
		if (p->id == i)
		{
			printf("开始修改\n");
			printf("输入学号:");
			scanf("%d", &p->id);
			printf("输入姓名:");
			scanf("%s", &p->name);
			printf("输入性别:");
			scanf("%s", &p->sex);
			printf("输入专业:");
			scanf("%s", &p->field);
			printf("输入出生日期:");
			scanf("%d", &p->birthday);
			printf("输入家庭地址:");
			scanf("%s", &p->address);
			printf("输入英语入学成绩:");
			scanf("%f", &p->E_grade);
			printf("-----------------------------------------------");
			printf("\n");
			printf("修改后结果为\n");
			printf("id: %d   姓名: %s   性别: %s   专业: %s   出生日期: %s   家庭地址: %s   英语入学成绩: %f\n", p->id, p->name, p->sex, p->field, p->birthday, p->address, p->E_grade);
			menu();
		}
		else
		{
			q = p;
			p = p->next;
		}
	}
	printf("id不存在！请重新输入:");
	change();
}

void del()//删除 
{
	int i;
	printf("输入要删除学生的id:");
	scanf("%d", &i);
	p = head;
	while (p != NULL)
	{
		if (p->id == i)
		{
			printf("id: %d   姓名: %s   性别: %s   专业: %s   出生日期: %s   家庭地址: %s   英语入学成绩: %f\n", p->id, p->name, p->sex, p->field, p->birthday, p->address, p->E_grade);
			q->next = p->next;
			p->next = NULL;
			printf("该学生信息已删除\n");
			menu();
		}
		else
		{
			q = p;
			p = p->next;
		}
	}
	printf("id不存在！请重新输入:");
	del();
}

void searchall()
{

}

void sort()
{

}

void save()
{

}

int main(int argc, char* argv[]) {
	head->next = NULL;//head 的 next 设为NULL
	last = head;//last指向最后一个元素
	menu();
	//system(pause);
	return 0;
}
