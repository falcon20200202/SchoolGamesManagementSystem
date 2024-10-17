// sport.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<mysql/mysql.h>
//
//// 初始化并连接到 MySQL 数据库
//MYSQL* connect_db() {
//	MYSQL* conn = mysql_init(NULL);
//
//	if (conn == NULL) {
//		fprintf(stderr, "mysql_init() failed\n");
//		return NULL;
//	}
//
//	if (mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0) == NULL) {
//		fprintf(stderr, "mysql_real_connect() failed\n");
//		mysql_close(conn);
//		return NULL;
//	}
//
//	return conn;
//}
//
//void create_table(MYSQL* conn) {
//	const char* query = "CREATE TABLE IF NOT EXISTS athletes ("
//		"id INT AUTO_INCREMENT PRIMARY KEY, "
//		"name VARCHAR(100), "
//		"age INT, "
//		"gender ENUM('M', 'F'), "
//		"event VARCHAR(100), "
//		"result FLOAT)";
//
//	if (mysql_query(conn, query)) {
//		fprintf(stderr, "Table creation failed: %s\n", mysql_error(conn));
//	}
//	else {
//		printf("Table created successfully!\n");
//	}
//}



int menu();
void Sum();
void sort();
void csh();//1
void xyskzl();//2
void gxyxxzf();//3
void gxyzfmccx();//4

void gxyzfcx();//5
void gxmhjydyxxxxg();//6
void Add(); //6
int convert(int i);//6

struct Athlete
{
	int num;  //序号
	char project[500];  //项目
	int ranking;  //名次
	int score;  //分数
};//Ma[10]={{01,1100,1},{02,"tiaoyuan",1},},Wo[10];


struct collage
{
	int num;
	char name[300];  //学院名称
	struct Athlete Ma[10];
	struct Athlete Wo[10];
	int sum;
	int sumM;
	int sumW;
};

struct collage Class[6] =
{
	{1,"dianzigongcheng",
			{{1,"1100",1,7},{3,"跳远",1,7}},
			{{2,"1100",1,7},{4,"跳远",1,7}}
	},
	{2,"chuanbo",
			{{5,"1100",3,3},{7,"跳远",2,5}},
			{{6,"1100",3,3},{8,"跳远",2,5}}
	},
	{3,"shengmingkexue",
			{{9,"1100",2,5},{11,"跳远",5,1}},
			{{10,"1100",2,5},{12,"跳远",5,1}}
	},
	{4,"jidiangongcheng",
			{{13,"1100",4,2},{15,"跳远",4,2}},
			{{14,"1100",4,2},{16,"跳远",4,2}}
	},
	{5,"zhonge",
			{{17,"1100",6,0},{19,"跳远",3,3}},
			{{18,"1100",6,0},{20,"跳远",3,3}}
	},
	{6,"shuxue",
			{{21,"1100",5,1},{23,"跳远",6,0}},
			{{22,"1100",5,1},{24,"跳远",6,0}}
	}

};


int N; //参赛院系总数
int M; //参赛男子总数
int W; //参赛女子总数
int JM = 2; //每个学院的男运动员
int JW = 2; //每个学院的女运动员

//char a[6][300]={"dianzigongcheng","chuanbo","shengmingkexue","jidiangongcheng","zhonge","shuxue"};
//int	b[6]={Class[0].sum,Class[1].sum,Class[2].sum,Class[3].sum,Class[4].sum,Class[5].sum};




void main(int argc, char* argv[])
{


	int n = 1, i, j; //n是功能序号

	for (; n > 0 && n < 7;)
	{


		n = menu();
		switch (n)
		{
		case 1:csh(); break;
		case 2:xyskzl(); break;
		case 3:gxyxxzf(); break;
		case 4:gxyzfmccx(); break;
		case 5:gxyzfcx(); break;
		case 6:gxmhjydyxxxxg(); break;
		}


	}

}

//////////////////////菜单//////////////////
int menu()   //菜单
{
	int n;
	system("cls"); //清屏
	printf("运动会管理系统\n");
	printf("----------------\n");
	printf("1.初始化\n");
	printf("2.学院赛况总览\n");
	printf("3.各学院详细总分\n");
	printf("4.各学院总分名次查询\n");
	printf("5.各学院总分查询\n");
	printf("6.各项目获奖运动员信息修改\n");
	printf("7.结束程序\n");

	printf("请输入所需功能前的序号:");
	scanf_s("%d", &n);
	for (; n < 0 && n>7;)  //填入菜单最后一项数字
	{
		printf("请重新输入所需功能前的序号，eg:1");
		scanf_s("%d", &n);
	}

	return n;
}

//////////////////初始化1////////////////
void csh()
{
	printf("请输入参赛院系总数：");
	scanf_s("%d", &N);
	printf("\n");
	printf("请输入参赛男子总数：");
	scanf_s("%d", &N);
	printf("\n");
	printf("请输入参赛女子总数：");
	scanf_s("%d", &N);
	printf("\n");

}

//////////////学院赛况总览2/////////////////
void xyskzl()
{
	int i, j;
	for (i = 0; i < 6; i++)
	{
		printf("%s\n", Class[i].name);
		for (j = 0; j < (JM); j++)
		{
			printf("\t%s\n\t%d\t%d\n\t%d\t%d\n", Class[i].Ma[j].project, Class[i].Ma[j].num, Class[i].Ma[j].score, Class[i].Wo[j].num, Class[i].Wo[j].score);
		}

	}
	printf("返回请按1\n");

	scanf_s("%d", &i);
}


//////////////////各学院总分查询3//////////////////////
void gxyxxzf()
{
	int i, c[6], d[6], e[6];
	for (i = 0; i < 6; i++)
	{
		c[i] = Class[i].Ma[0].score + Class[i].Ma[1].score;
		d[i] = Class[i].Wo[0].score + Class[i].Wo[1].score;
		e[i] = c[i] + d[i];
	}
	for (i = 0; i < 6; i++)
	{
		printf("学院\t总分\t\t男子总分 女子总分\n");
		printf("%s\t%d\t%d\t%d\n", Class[i].name, e[i], c[i], d[i]);
	}
	printf("返回请输入1\n");
	scanf_s("%d", &i);
}


////////////////各学院总分名次查询4///////////
void gxyzfmccx()
{
	int temp, i, j;
	char a[6][20] = { "shuxue","zhonge","jidiangongcheng","chuanbo","shengmingkexue","dianzigongcheng" };

	int c[6], d[6], e[6];
	for (i = 0; i < 6; i++)
	{
		c[i] = Class[i].Ma[0].score + Class[i].Ma[1].score;
		d[i] = Class[i].Wo[0].score + Class[i].Wo[1].score;
		e[i] = c[i] + d[i];
	}

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6 - i; j++)
		{
			if (e[j] > e[j + 1])
			{
				temp = e[j]; e[j] = e[j + 1]; e[j + 1] = temp;
			}
		}
	}
	printf("学院     总分\n");
	for (i = 5; i > 0; i--)
	{
		printf("%s\t%d\n", a[i], e[i]);
	}
	printf("返回请输入1\n");
	scanf_s("%d", &i);
}



/////////////////各学院总分查询5/////////////
void gxyzfcx()
{
	int i, n;
	int c[6], d[6], e[6];
	for (i = 0; i < 6; i++)
	{
		c[i] = Class[i].Ma[0].score + Class[i].Ma[1].score;
		d[i] = Class[i].Wo[0].score + Class[i].Wo[1].score;
		e[i] = c[i] + d[i];
	}

	printf("1.电子工程\n2.传播\n3.生命科学\n4.机电工程\n5.中俄\6.数学\n7.返回\n");
	printf("请输入序号\n");
	scanf_s("%d", &n);
	for (; n > 0 && n < 7;)
	{
		switch (n)
		{
		case 1:printf("%s\t%d\n", Class[0].name, e[0]); break;
		case 2:printf("%s\t%d\n", Class[1].name, e[1]); break;
		case 3:printf("%s\t%d\n", Class[2].name, e[2]); break;
		case 4:printf("%s\t%d\n", Class[3].name, e[3]); break;
		case 5:printf("%s\t%d\n", Class[4].name, e[4]); break;
		case 6:printf("%s\t%d\n", Class[5].name, e[5]); break;
		}
		printf("1.电子工程\n2.传播\n3.生命科学\n4.机电工程\n5.中俄\6.数学\n7.返回\n");
		printf("请输入序号\n");
		scanf("%d", &n);
	}
}

///////////各项目获奖运动员信息修改6///////////////////

void gxmhjydyxxxxg()
{
	int n;
	printf("1.增添\n");
	printf("2.删除\n");
	printf("3.返回\n");
	printf("请输入所需功能前的序号：\n");
	scanf_s("%d", &n);
	for (; n < 1 && n>3;)
	{
		printf("请重新输入所需功能前的序号，eg:1");
		scanf_s("%d", &n);
	}
	switch (n)
	{
	case 1:Add(); break;
		//	case 2:Delete();break;
		//	case 3:Back();break;
	}
}


void Add()  //运动员信息输入
{
	int i, flag = 1;
	char c, col[200];

	for (; flag == 1;)
	{
		printf("请输入学院名称\n");
		scanf_s("%s", &col);
		if (!strcmp(col, "dianzigongcheng"))	i = 0;
		else if (!strcmp(col, "chuanbo")) i = 1;
		else if (!strcmp(col, "shengmingkexue")) i = 2;
		else if (!strcmp(col, "jidiangongcheng")) i = 3;
		else if (!strcmp(col, "zhonge")) i = 4;
		else i = 5;

		printf("请输入输入运动员性别('M'/'W'): \n");
		scanf_s("%s", &c);

		if (c == 'M')
		{
			printf("各信息之间用适当空格隔开\n");
			printf("序号 项目 名次\n");
			scanf_s("%d%s%d", &Class[i].Ma[JM].num, Class[i].Ma[JM].project, &c);
			Class[i].Ma[JM].score = convert(Class[i].Ma[JM].ranking);
			JM++;
		}
		else
		{
			printf("各信息之间用适当空格隔开\n");
			printf("序号 项目 名次\n");
			scanf_s("%d%s%d", &Class[i].Wo[JW].num, Class[i].Wo[JW].project, &Class[i].Wo[JW].ranking);
			Class[i].Wo[JW].score = convert(Class[i].Wo[JW].ranking);
			JW++;
		}

		printf("继续请按1，返回请按0\n");
		scanf_s("%d", &flag);

	}

}

int convert(int i)   //名次和分数转换
{
	switch (i)
	{
	case 1:return 7;
	case 2:return 5;
	case 3:return 3;
	case 4:return 2;
	case 5:return 1;
	}
}


void Sum()
{
	int i, j;
	for (i = 0; i < 6; i++)
	{
		Class[i].sum = 0; Class[i].sumM = 0; Class[i].sumW = 0;
		for (j = 0; j < (JM); j++)//男总分
		{
			Class[i].sumM += Class[i].Ma[j].score;
		}
		for (j = 0; j < (JW); j++)//女总分
		{
			Class[i].sumW += Class[i].Wo[j].score;
		}
		for (j = 0; j < ((JM)+(JW)); j++)//院总分
		{
			Class[i].sum = Class[i].sumM + Class[i].sumW;
		}
	}

}


