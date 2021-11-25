//有新生来报到，要逐个录入其信息，
//如：学生姓名，性别，专业，出生日期，家庭地址，英语入学成绩。
//要求设计链表来实现，并统计学生人数。文本界面为：
//1. 新增学生信息 
//2. 删除学生信息
//3. 导入学生信息（已经保存于的文件信息）
//4. 学生信息搜索（按姓名）
//5. 学生信息统计（按专业或性别或年龄---年龄要自动计算）
//6. 按英语成绩排序
//7. 学生信息保存
//8. 退出

//函数分布 
//main()
//		load()							默认自动导入信息 
//		menu()							进入菜单 	
//			0.	load()					手动导入信息 
//			1.	add()					新增 
//					isExist()			查重 
//					birthdayJudge()		出生日期判断 
//						isLeap()		闰年判断 
//					addRaw()			将信息加入链表 
//			2.	search()				搜索 
//			3.	change()				修改		
//					birthdayJudge()		出生日期格式判断 
//						isLeap()		闰年判断 
//					sexJudge()			性别格式判断
//			4.	del()					删除 
//					printStu()			打印学生信息
//			5.	searchAll()				信息统计（包含筛选打印和全部打印）
//					screenField()		按照指定专业打印信息
//						printStu() 		打印学生信息
//					screenSex()			按照指定性别打印信息
//						printStu() 		打印学生信息
//					screenAge()			按照指定年龄打印信息（年龄根据该学生信息中的年份自动计算）
//						printStu() 		打印学生信息
//			6.	sort()					按照英语成绩排序（采用冒泡循环）
//			7.	save()					将链表信息存入文件
//			8.	save()					将链表信息存入文件后返回主函数，结束程序 
			

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

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

struct Stu* head = NULL;
struct Stu* last = NULL;

void menu();				//菜单														
void load(bool output);		//导入学生信息												0.done
void add();					//新增学生信息												1.done 
void search();				//学生信息查询(按姓名)											2.done
void change();				//修改学生信息（好像没要求写，自己加的）							3.done
void del();					//删除学生信息												4.done
void searchAll();			//学生信息统计（按专业或性别或年龄---年龄要自动计算）				5.done
void sort(bool output);		//排序														6.done
void printAll();			//输出全部信息												7.done
void save(bool output);		//学生信息保存												8.done

void addRaw(int id, char name[], char sex[], char field[], int year, int month, int day, char address[], float E_grade);//赋值												
void printStu(struct Stu* stu);						//输出学生信息
void screenField();									//按照专业筛选学生
void screenSex();									//按照性别筛选学生
void screenAge();									//按照年龄筛选学生
void updateLast();									//更新last指针

bool isExist(int id,bool output);					//检查输入学号是否已存在
bool birthdayJudge(int year, int month, int day);	//判断输入的出生日期是否有误
bool isLeap(int year, int month, int day);			//月份为2时根据年份判断是否闰年，然后判断输入的出生日期是否有误
bool sexJudge(char sex[]);							//判断输入的性别是否为“男”或“女”


void menu() //菜单
{
	int userChoice;

	while (true) 
	{
		system("cls");//清屏

		cout << endl;
		cout << endl;
		cout << endl;
		cout << "----------------------------学生基本信息管理系统----------------------------" << endl;
		cout << endl;
		cout << endl;
		cout << "0.导入学生信息（默认已自动导入）" << endl;
		cout << "1.新增学生信息 " << endl;
		cout << "2.查询学生信息 " << endl;
		cout << "3.修改学生信息 " << endl;
		cout << "4.删除学生信息 " << endl;
		cout << "5.学生信息统计 " << endl;
		cout << "6.学生成绩排序 " << endl;
		cout << "7.学生信息总览 " << endl;
		cout << "8.学生信息储存 " << endl;
		cout << "9.保存并安全退出" << endl;
		cout << endl;
		cout << endl;
		cout << "使用注意事项" << endl;
		cout << "进行“增加”、“修改”、“删除”操作后，务必将信息储存，否则不会保存在文件内！" << endl;
		cout << endl;
		cout << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
		
		cout << "请输入序号：";
		cin >> userChoice;

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
			printAll();
			break;
		case 8:
			save(true);
			break;
		case 9:
			save(true);
			return;
			break;
		default:
			cout << "无法识别，请重新输入" << endl;
			system("pause");
		}
	}
}

void add()//增加 
{
	int id;

	cout << "输入学号：";
	cin >> id;

	if (isExist(id, true)) 
	{
		system("pause");
		return;//已经存在此人 返回菜单
	}
	else 
	{
		char name[15], sex[5], field[30], address[100];
		float E_grade;
		int year, month, day;

		cout << "输入姓名: ";
		cin >> name;

		cout << "输入性别: ";
		cin >> sex;

		cout << "输入专业: ";
		cin >> field;

		cout << "请输入出生年份: ";
		cin >> year;

		cout << "请输入出生月份: ";
		cin >> month;

		cout << "请输入出生日期: ";
		cin >> day;

		cout << "输入家庭地址: ";
		cin >> address;

		cout << "输入英语入学成绩：";
		cin >> E_grade;

		if (!birthdayJudge(year, month, day))
		{
			cout << "日期输入有误，返回至菜单" << endl;
			system("pause");
			return;
		}

		if (!sexJudge(sex))
		{
			cout << "性别输入不符实际，返回至菜单" << endl;
			system("pause");
			return;
		}

		addRaw(id, name, sex, field, year, month, day, address, E_grade);
		cout << "添加成功" << endl;
		system("pause");
		return;
	}
}

bool birthdayJudge(int year, int month, int day)
{
	time_t  t;
	time(&t);

	if (year <= localtime(&t)->tm_year + 1900 && month >= 1 && month <= 12 && day >= 1 && day <= 31)
	{
		switch (month)
		{
		case 4:
		case 6:
		case 9:
		case 11:
			if (day <= 30)//这些是小月
			{
				return true;
			}
			return false;
			break;
		case 2:
			return isLeap(year,month,day);//判断2月的天数输入是否有误
			break;
		default:
			return true;//这些月本来就有31天
		}
	}
	return false;//日期不在范围里
}

bool isLeap(int year, int month, int day)//闰年判断（闰年2月29天，平年2月28天）
{
	int four;
	int hundred1;
	int hundred4;

	four = year % 4;
	hundred1 = year % 100;
	hundred4 = year % 400;

	if ((hundred4 == 0 ) || (four == 0 && hundred1 != 0))//闰年（能被400整除或能被4整除但不能被100整除）
	{
		if (day <= 29)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else//平年
	{
		if (day <= 28)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool sexJudge(char sex[])//判断输入的性别是否为“男”或“女”
{
	if (strcmp(sex,"男") == 0 || strcmp(sex, "女") == 0)
	{
		return true;
	}
	return false;
}

void addRaw(int id,char name[],char sex[],char field[],int year,int month,int day,char address[],float E_grade) //赋值
{
	struct Stu* toAdd = new struct Stu;

	if (toAdd == NULL) {
		cout << "内存不足！无法添加" << endl;
		system("pause");
		return;
	}

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

	while (item != NULL)
	{
		if (item->id == id)
		{
			if (output) {
				cout << "学号 :  " << item->id << "姓名 :  " << item->name << "性别 :  " << item->sex << "专业 :  " << item->field << endl;
				cout << "学号已存在，请重新输入" << endl;
				cout << endl;
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

	cout << "输入要查询学生的姓名:";
	cin >> inputName;

	inputName[14] = '\0';//防止用户输入过长 导致没有\0
	cout << "下面是数据库内有关" << inputName << "的信息" << endl;
	cout << endl;

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
	cout << "以上是数据库内有关" << inputName << "的信息" << endl;
	cout << endl;
	system("pause");
	return;
}

void change()//修改 
{
	struct Stu* item;
	int id;
	cout << "输入要修改学生的学号:";
	cin >> id;

	item = head;

	while (item != NULL)
	{
		if (item->id == id)
		{
			printStu(item);
			cout << "开始修改" << endl;

			cout << "输入姓名: ";
			cin >> item->name;

			cout << "输入性别: ";
			cin >> item->sex;

			cout << "输入专业: ";
			cin >> item->field;

			cout << "请输入出生年份: ";
			cin >> item->birthday.year;

			cout << "请输入出生月份: ";
			cin >> item->birthday.month;

			cout << "请输入出生日期: ";
			cin >> item->birthday.day;

			cout << "输入家庭地址: ";
			cin >> item->address;

			cout << "输入英语入学成绩：";
			cin >> item->E_grade;

			cout << "-----------------------------------------------" << endl;

			if (birthdayJudge(item->birthday.year, item->birthday.month, item->birthday.day))
			{
				return;
			}
			cout << endl;

			cout << "修改后结果为" << endl;
			printStu(item);

			cout << endl;
			system("pause");
			return;
		}
		else
			item = item->next;
	}
	cout << "学号不存在！返回至菜单" << endl;
	system("pause");
	return;
}

void del()//删除 
{
	int id;
	struct Stu* needToDel, * beforeDel;
	beforeDel = NULL;

	cout << "输入要删除学生的学号:";
	cin >> id;

	needToDel = head;

	while (needToDel != NULL)
	{
		if (needToDel->id == id)
		{
			printStu(needToDel);
			if (needToDel == last) {
				last = beforeDel;//指向前面的
			}
			if (beforeDel == NULL) 
			{
				head = needToDel->next;
				delete needToDel;
			}
			else {
				beforeDel->next = needToDel->next;
				delete needToDel;
			}
			cout << "该学生信息已删除" << endl;
			system("pause");
			return;
		}
		else
		{
			beforeDel = needToDel;
			needToDel = needToDel->next;

		}
	}
	cout << "学号不存在！返回至菜单:" << endl;
	system("pause");
	return;
}

void searchAll()//信息统计（筛选出制定专业或性别或年龄）
{
	int userChoice;

	while (true)
	{
		system("cls");
		cout << endl;
		cout << "----------------------------学生信息统计系统----------------------------" << endl;
		cout << endl;
		cout << endl;
		cout << "1.按照专业筛选" << endl;
		cout << "2.按照性别筛选" << endl;
		cout << "3.按照年龄筛选" << endl;
		cout << "4.输出全部学生信息" << endl;
		cout << endl;
		cout << "5.返回主菜单" << endl;
		cout << endl;
		cout << endl;
		cout << "------------------------------------------------------------------------" <<endl;
		cout << endl;
		cout << endl;

		cout << "请输入序号:";
		cin >> userChoice;
			
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
			cout << "无法识别，请重新输入！" << endl;
			system("pause");
		}
	}
}

void screenField()//按照专业筛选出符合条件的学生
{
	struct Stu* item = head;
	char findField[30] = { 0 };
	int count = 0;
	findField[29] = '\0';

	cout << "请输入要筛选出的专业：" << endl;
	cin >> findField;

	cout << endl << "以下是数据库中的信息：" << endl;

	while (item != NULL)
	{
		if (strcmp(item->field, findField) == 0)
		{
			printStu(item);
			count++;
		}
		item = item->next;
	}

	cout << endl;
	cout << "符合条件的学生有" << count << "个" << endl;
	cout << "----------------------------------------------------------" << endl;
	system("pause");
	return;
}

void screenSex()//按照性别筛选出符合条件的学生
{
	struct Stu* item = head;
	char findSex[5] = {0};
	int count = 0;
	findSex[4] = '\0';

	cout << "请输入要筛选出的性别：";
	cin >> findSex;

	cout << endl << "以下是数据库中的信息：" << endl;

	while (item != NULL)
	{
		if (strcmp(item->sex, findSex) == 0)
		{
			printStu(item);
			count++;
		}
		item = item->next;
	}

	cout << endl;
	cout << "符合条件的学生有" << count << "个" << endl;
	cout << "----------------------------------------------------------" << endl;
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

	cout << "请输入要筛选出的年龄：";
	cin >> findAge;

	cout << endl << "以下是数据库中的信息：" << endl;

	while (item != NULL)
	{
		if ((localtime(&t)->tm_year + 1900)-item->birthday.year == findAge)
		{
			printStu(item);
			count++;
		}
		item = item->next;
	}

	cout << endl;
	cout << "符合条件的学生有" << count << "个" << endl;
	cout << "----------------------------------------------------------" << endl;
	system("pause");
	return;
}

void printAll() 
{
	struct Stu* item = head;
	cout << endl << "以下是数据库中所有人的信息：" << endl;

	while (item != NULL) 
	{
		printStu(item);
		item = item->next;
	}

	cout << endl;
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
	{
		cout << "排序成功，已按照英语成绩进行排序" << endl;
		system("pause");
		return;//一个都没有或者就一个
	}
		
	//至少有两个
	nextPoint = curPoint->next;//初始化三个指针 

	while (head->next != end)
	{
		prePoint = NULL;
		curPoint = head;
		nextPoint = curPoint->next;//结束for循环，对几个指针进行复位

		for (; nextPoint != end; prePoint = prePoint == NULL?head:prePoint->next, curPoint = curPoint->next, nextPoint = nextPoint->next)
		{	//判断是否到达结束位置 ; 

			if (curPoint->E_grade < nextPoint->E_grade) //从大到小
			{
				if (prePoint != NULL) 
				{
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

	if (output) 
	{
		cout << "排序成功，已按照英语成绩进行排序" << endl;
		system("pause");
	}
		
}

void printStu(struct Stu* stu) //输出学生信息
{
	cout << endl;
	cout << "学号:" << std::left << setw(12) << stu->id;
	cout << "姓名:" << std::left << setw(10) << stu->name;
	cout << "性别:" << std::left << setw(5) << stu->sex;
	cout << "专业:" << std::left << setw(15) << stu->field;
	cout << "出生日期:" << std::left << setw(4) << stu->birthday.year << "-" << std::right << setw(2) << stu->birthday.month << "-" << std::right << setw(2) << stu->birthday.day << std::right << setw(15);
	cout << "家庭地址:" << std::left << setw(24) << stu->address;
	cout << "英语入学成绩:" << std::left << setw(3) << stu->E_grade;
	cout << endl;
	cout << endl;
	cout << endl;

	return;
}

void load(bool output = false) //
{
	ifstream file;
	char name[15], sex[5], field[30], address[100];
	float E_grade;
	int id, year, month, day;
	bool haveNext = true;
	file.open("information.txt");

	while (file.good() && !(file.peek() == EOF))
	{
		file >> id;
		file.ignore();

		file.getline(name,15);
		file.getline(sex, 5);
		file.getline(field, 30);

		file >> year;
		file >> month;
		file >> day;
		file.ignore();

		file.getline(address, 100);
		file >> E_grade;
		file.ignore();

		addRaw(id, name, sex, field, year, month, day, address, E_grade);
	}
	file.close();

	if (output) 
	{
		cout << "导入成功" << endl;
		system("pause");
	}
	return;
}

void save(bool output = false)//文件存放
{
	ofstream file;
	struct Stu* item = head;
	file.open("information.txt");

	while (item != NULL && file.good()) 
	{
		file << item->id << endl;
		file << item->name << endl;
		file << item->sex << endl;
		file << item->field << endl;
		file << item->birthday.year << endl;
		file << item->birthday.month << endl;
		file << item->birthday.day << endl;
		file << item->address << endl;
		file << item->E_grade << endl;

		item = item->next;
	}

	file.close();

	if (output) 
	{
		cout << "导出成功" << endl;
		system("pause");
	}
	return;
}

void updateLast() {
	Stu* item = head;
	while (item->next != NULL)
	{
		item = item->next;
	}
	last = item;
}
int main(int argc, char* argv[]) 
{
	load();
	menu();
	return 0;
}