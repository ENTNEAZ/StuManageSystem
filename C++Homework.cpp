#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Date
{
	int year;
	int month;
	int day;
};

struct Stu {
	int id;						//学号 
	char name[15];				//姓名 
	char sex[5];				//性别 
	char field[30];				//专业 
	struct Date birthday;		//出生日期 
	char address[100];			//家庭地址 
	float E_grade;				//英语入学成绩 
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

struct Stu* head = NULL;
struct Stu* last = NULL;
//struct Stu* p, * q;


void menu();				//菜单														0.
void add();					//新增学生信息												1.done 
void del();					//删除学生信息												2.done
void load(bool output);		//导入学生信息												3.done
void search();				//学生信息搜索(按姓名)										4.done
void searchAll();			//学生信息统计（按专业或性别或年龄---年龄要自动计算）		5.done
void sort(bool output);		//排序														6.done
void save(bool output);		//学生信息保存												7.done
void change();				//修改学生信息（好像没要求写，自己加的）					8.done

void addRaw(int id, char name[], char sex[], char field[], int year, int month, int day, char address[], float E_grade);//赋值
bool isExist(int id,bool output);//检查输入学号是否已存在
void printStu(struct Stu* stu);//输出学生信息
void screenField();//按照专业筛选学生
void screenSex();//按照性别筛选学生
void screenAge();//按照年龄筛选学生
void printAll();//输出全部信息
bool birthdayJudge(int year, int month, int day, bool output);//判断输入的出生日期是否有误
bool isLeap(int year, int month, int day, bool output);//月份为2时根据年份判断是否闰年，然后判断输入的出生日期是否有误


void menu() //菜单
{
	int userChoice;
	while (true) {
		system("cls");//清屏
		printf("\n");
		printf("----------------------------学生基本信息管理系统----------------------------\n");
		printf("\n");
		printf("0.导入学生信息（默认已自动导入）\n");
		printf("1.新增学生信息 \n");
		printf("2.查询学生信息 \n");
		printf("3.修改学生信息 \n");
		printf("4.删除学生信息 \n");
		printf("5.学生信息统计 \n");
		printf("6.学生成绩排序 \n");
		printf("7.学生信息储存 \n");
		printf("8.保存并安全退出   \n");
		printf("\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("请输入序号：");
		scanf("%d", &userChoice);
		switch (userChoice)
		{
		case 0:
			load(true);
			break;
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
			searchAll();
			break;
		case 6:
			sort(true);
			break;
		case 7:
			save(true);
			break;
		case 8:
			save(true);
			return;
			break;
		default:
			printf("无法识别，请重新输入\n");
			system("pause");
		}
	}
}

void add()//增加 
{
	int id;
	printf("输入学号：");
	scanf("%d", &id);
	if (isExist(id, true)) {
		add();//已经存在此人 递归再次输入
	}
	else {
		char name[15], sex[5], field[30], birthday[20], address[100];
		float E_grade;
		int year, month, day;
		printf("输入姓名: ");
		scanf("%s", &name);
		printf("输入性别: ");
		scanf("%s", &sex);
		printf("输入专业: ");
		scanf("%s", &field);
		printf("请输入出生年份: ");
		scanf("%d", &year);
		printf("请输入出生月份: ");
		scanf("%d", &month);
		printf("请输入出生日期: ");
		scanf("%d", &day);
		printf("输入家庭地址: ");
		scanf("%s", &address);
		printf("输入英语入学成绩：");
		scanf("%f", &E_grade);
		system("pause");
	}
	if (birthdayJudge(year month, day, ture))
	{
		return;
	}
	addRaw(id, name, sex, field, year, month, day, address, E_grade);
	printf("添加成功！\n");
	return;
}

bool birthdayJudge(int year, int month, int day, bool output)
		if (year < localtime(&t)->tm_year + 1900 && month >= 1 && month <= 12 && day >= 1 && day <= 31)
		{
			switch (month)
			{
			case 4:
			case 6:
			case 9:
			case 11:
				if (day != 31)
				{
					return false;
				}
				return true;
				break;
			case 2:
				isLeap(year);//判断2月的天数输入是否有误
				break;
			default:
				return false;
			}
		}
		else
		{
			return false;
		}
}

bool isLeap(int year, int month, int day, bool output)//闰年判断（闰年2月29天，平年2月28天）
{
	int four;
	int hundred1;
	int hundred4;
	four = year % 4;
	hundred1 = year % 100;
	hundred4 = year % 400;
	if ((hundred4 == 0 ) || (four == 0 && hundred1 != 0))
	{
		if (day <= 29)
		{
			return false;
		}
		return true;
	}
	else
	{
		if (day <= 28)
		{
			return false;
		}
		return true;
	}
}

void addRaw(int id,char name[],char sex[],char field[],int year,int month,int day,char address[],float E_grade) //赋值
{
	struct Stu* toAdd = (struct Stu*)malloc(sizeof(struct Stu));

	toAdd->id = id;
	strcpy(toAdd->name, name);
	strcpy(toAdd->sex, sex);
	strcpy(toAdd->field, field);
	toAdd->birthday.year = year;
	toAdd->birthday.month = month;
	toAdd->birthday.day = day;
	strcpy(toAdd->address, address);
	toAdd->E_grade = E_grade;
	toAdd->next = NULL;

	if (head == NULL) {
		head = toAdd;
		last = head;//last指向最后一个元素
	}
	else {
		last->next = toAdd;
		last = last->next;
	}
	return;
}

bool isExist(int id, bool output = false)//查重 output为是否输出已经存在的信息
{
	if (head == NULL)
	{
		return false;
	}
	struct Stu* item = head;
	if (item->id == id)
	{
		if (output) {
			printf("学号: %d   姓名: %s   性别: %s   专业: %s   \n", item->id, item->name, item->sex, item->field);
			printf("学号已存在，请重新输入\n");
			printf("\n");
		}
		return true;
	}
	while (item != NULL)
	{
		if (item->id == id)
		{
			if (output) {
				printf("学号: %d   姓名: %s   性别: %s   专业: %s   \n", item->id, item->name, item->sex, item->field);
				printf("学号已存在，请重新输入\n");
				printf("\n");
			}
			return true;
		}
		else
			item = item->next;
	}
	return false;
}

void search()//查询 
{
	struct Stu* item = head;
	char inputName[15];
	printf("输入要查询学生的姓名:");
	scanf("%s", &inputName);
	inputName[14] = '\0';//防止用户输入过长 导致没有\0
	printf("下面是数据库内有关\"%s\"的信息\n\n", inputName);
	while (item != NULL)
	{
		if (strcmp(item->name, inputName) == 0)
		{
			printStu(item);
			//防止重名 继续执行
			item = item->next;
		}
		else {
			item = item->next;
		}
	}
	printf("\n以上是数据库内有关\"%s\"的信息\n", inputName);
	system("pause");
	return;
}

void change()//修改 
{
	struct Stu* item;
	int id;
	printf("输入要修改学生的学号:");
	scanf("%d", &id);
	item = head;
	while (item != NULL)
	{
		if (item->id == id)
		{
			printStu(item);
			printf("开始修改\n");
			printf("输入学号:");
			scanf("%d", &item->id);
			printf("输入姓名:");
			scanf("%s", &item->name);
			printf("输入性别:");
			scanf("%s", &item->sex);
			printf("输入专业:");
			scanf("%s", &item->field);
			printf("输入出生年份:");
			scanf("%d", &item->birthday.year);
			printf("输入出生月份:");
			scanf("%d", &item->birthday.month);
			printf("输入出生日期:");
			scanf("%d", &item->birthday.day);
			printf("输入家庭地址:");
			scanf("%s", &item->address);
			printf("输入英语入学成绩:");
			scanf("%f", &item->E_grade);
			printf("-----------------------------------------------");
			printf("\n");
			printf("修改后结果为\n");
			printStu(item);
			printf("\n");
			system("pause");
			return;
		}
		else
			item = item->next;
	}
	printf("学号不存在！返回至菜单\n");
	system("pause");
	return;
}

void del()//删除 
{
	int id;
	struct Stu* needToDel, * beforeDel;
	beforeDel = NULL;
	printf("输入要删除学生的学号:");
	scanf("%d", &id);
	needToDel = head;
	while (needToDel != NULL)
	{
		if (needToDel->id == id)
		{
			printStu(needToDel);
			if (beforeDel == NULL) 
			{
				head = needToDel->next;
				free(needToDel);
			}
			else {
				beforeDel->next = needToDel->next;
				free(needToDel);
			}
			printf("该学生信息已删除\n");
			system("pause");
			return;
		}
		else
		{
			beforeDel = needToDel;
			needToDel = needToDel->next;
		}
	}
	printf("学号不存在！返回至菜单:\n");
	system("pause");
	return;
}

void searchAll()//信息统计（筛选出制定专业或性别或年龄）
{
	int userChoice;
	while (true)
	{
		system("cls");
		printf("\n");
		printf("----------------------------学生信息统计系统----------------------------");
		printf("\n");
		printf("1.按照专业筛选\n");
		printf("2.按照性别筛选\n");
		printf("3.按照年龄筛选\n");
		printf("4.输出全部学生信息\n");
		printf("\n");
		printf("5.返回主菜单\n");
		printf("\n");
		printf("------------------------------------------------------------------------");
		printf("\n");
		printf("请输入序号:");
		scanf("%d", &userChoice);
		switch (userChoice)
		{
		case 1:
			screenField();
			break;
		case 2:
			screenSex();
			break;
		case 3:
			screenAge();
			break;
		case 4:
			printAll();
			break;
		case 5:
			return;
			break;
		default :
			printf("无法识别，请重新输入！\n");
			system("pause");
		}
	}
}

void screenField()//按照专业筛选出符合条件的学生
{
	struct Stu* item = head;
	char findField[30];
	int count = 0;
	findField[29] = '\0';
	printf("请输入要筛选出的专业：");
	scanf("%s", &findField);
	printf("\n以下是数据库中的信息：\n");
	while (item != NULL)
	{
		if (strcmp(item->field, findField) == 0)
		{
			printStu(item);
			count++;
		}
		item = item->next;
	}
	printf("\n");
	printf("符合条件的学生有%d个\n", count);
	printf("----------------------------------------------------------\n");
	system("pause");
	return;
}

void screenSex()//按照性别筛选出符合条件的学生
{
	struct Stu* item = head;
	char findSex[5];
	int count = 0;
	findSex[4] = '\0';
	printf("请输入要筛选出的性别：");
	scanf("%s", &findSex);
	printf("\n以下是数据库中的信息：\n");
	while (item != NULL)
	{
		if (strcmp(item->sex, findSex) == 0)
		{
			printStu(item);
			count++;
		}
		item = item->next;
	}
	printf("\n");
	printf("符合条件的学生有%d个\n", count);
	printf("----------------------------------------------------------\n");
	system("pause");
	return;
}

void screenAge()//按照年龄筛选出符合条件的学生
{
	struct Stu* item = head;
	int findAge;
	int count = 0;
	time_t  t;
	time(&t);
	printf("请输入要筛选出的年龄：");
	scanf("%d", &findAge);
	printf("\n以下是数据库中的信息：\n");
	while (item != NULL)
	{
		if ((localtime(&t)->tm_year + 1900)-item->birthday.year == findAge)
		{
			printStu(item);
			count++;
		}
		item = item->next;
	}
	printf("\n");
	printf("符合条件的学生有%d个\n", count);
	printf("----------------------------------------------------------\n");
	system("pause");
	return;
}

void printAll() {
	struct Stu* item = head;
	printf("以下是数据库中所有人的信息：\n");
	while (item != NULL) {
		printStu(item);
		item = item->next;
	}
	printf("\n");
	system("pause");
	return;
}

void sort(bool output = false)//按照英语成绩排序
{
	struct Stu* prePoint, * curPoint, * nextPoint, * end, * tempPoint;//pre前一项 cur当前项 next后一项 end控制循环次数(优化冒泡)
	end = NULL;
	prePoint = NULL;
	curPoint = head;
	if (curPoint == NULL || curPoint->next == NULL)
		return;//一个都没有或者就一个 干嘛欺骗我的感情
	//现在保证至少有两个了
	nextPoint = curPoint->next;//初始化三个指针 ; 
	while (head->next != end)
	{
		prePoint = NULL;
		curPoint = head;
		nextPoint = curPoint->next;
		for (; nextPoint != end; prePoint = prePoint == NULL?head:prePoint->next, curPoint = curPoint->next, nextPoint = nextPoint->next)
		{	//判断是否到达结束位置 ; 

			if (curPoint->E_grade < nextPoint->E_grade) //从大到小
			{
				if (prePoint != NULL) {
					prePoint->next = nextPoint;
					curPoint->next = nextPoint->next;
					nextPoint->next = curPoint;
				}	
				else //pre是NULL说明操作的是head
				{
					head = nextPoint;
					curPoint->next = nextPoint->next;
					head->next = curPoint;
				}
				tempPoint = curPoint;//此时nextPoint变前一项，curPoint变后一项  交换nextPoint, curPoint
				curPoint = nextPoint;
				nextPoint = tempPoint;
			}
		}
		end = curPoint;//一轮循环结束 最后一项已经排好 end提前一项 (冒泡原理)
	}
	if (output) {
		printf("排序成功，已按照英语成绩进行排序\n");
		system("pause");
	}
		
}


void load(bool output = false) //
{
	FILE* fp = NULL;
	char name[15], sex[5], field[30], birthday[20], address[100];
	float E_grade;
	int id, year, month, day;
	bool haveNext = true;
	fp = fopen("information.txt", "r");

	while (haveNext && fp != NULL)
	{
		fscanf(fp, "%d\n", &id);
		fscanf(fp, "%s\n", &name);
		fscanf(fp, "%s\n", &sex);
		fscanf(fp, "%s\n", &field);
		fscanf(fp, "%d\n", &year);
		fscanf(fp, "%d\n", &month);
		fscanf(fp, "%d\n", &day);
		fscanf(fp, "%s\n", &address);
		haveNext = (fscanf(fp, "%f\n", &E_grade) == -1)?false:true;//当返回-1时代表没有内容了
		if (haveNext)
			addRaw(id, name, sex, field, year, month, day, address, E_grade);
	}

	fp != NULL ? fclose(fp) : NULL;
	if (output) {
		printf("导入成功\n");
		system("pause");
	}
	return;
}

void save(bool output = false)//文件存放
{
	FILE* fp = NULL;
	struct Stu* item = head;
	fp = fopen("information.txt", "w");

	while (item != NULL && fp != NULL) 
	{
		fprintf(fp,"%d\n",item->id);
		fprintf(fp,"%s\n", item->name);
		fprintf(fp, "%s\n", item->sex);
		fprintf(fp,"%s\n", item->field);
		fprintf(fp, "%d\n", item->birthday.year);
		fprintf(fp, "%d\n", item->birthday.month);
		fprintf(fp, "%d\n", item->birthday.day);
		fprintf(fp, "%s\n", item->address);
		fprintf(fp, "%.1f\n", item->E_grade);

		item = item->next;
	}

	fp != NULL ? fclose(fp) : NULL;
	if (output) {
		printf("导出成功\n");
		system("pause");
	}
	return;
}

void printStu(struct Stu* stu) //输出学生信息
{
	printf("学号: %-10d姓名: %-10s性别: %-10s专业: %-15s出生日期: %-4d-%-2d-%-5d家庭地址: %-20s英语入学成绩: %.1f\n", stu->id, stu->name, stu->sex, stu->field, stu->birthday.year, stu->birthday.month, stu->birthday.day, stu->address, stu->E_grade);
	return;
}

int main(int argc, char* argv[]) {
	load();
	menu();
	//system("pause");
	return 0;
}
