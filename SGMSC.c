#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// 全局变量
MYSQL *con;
MYSQL_RES *res;
MYSQL_ROW row;

// 菜单
int menu() {
    int n;
    system("cls"); // 清屏
    printf("运动会管理系统\n");
    printf("----------------\n");
    printf("1.【各学院-各项】分数总览\n");
    printf("2.【各学院-男女】总分总览\n");
    printf("3.学院总分名次查询\n");
    printf("4.【各项目】运动员排名查询\n");
    printf("5.运动员信息录入\n");
    printf("6.项目成绩录入\n");
    printf("7.结束程序\n");
    printf("请输入所需功能前的序号: ");
    scanf("%d", &n);

    while (n < 1 || n > 7) {
        printf("请重新输入所需功能前的序号，eg:1\n");
        scanf("%d", &n);
    }

    return n;
}

// 1.【各学院-各项】分数总览
void scoreAcademy(MYSQL *con) {
    system("cls"); // 清屏
    printf("【各学院-各项】分数总览\n");
    printf("----------------\n");

    const char *query = "SELECT a.academy_name, e.event_name, SUM(r.score) AS total_score "
                        "FROM registration r "
                        "JOIN students s ON r.student_id = s.student_id "
                        "JOIN academy a ON r.academy_id = a.academy_id "
                        "JOIN events e ON r.event_id = e.event_id "
                        "GROUP BY a.academy_name, e.event_name "
                        "ORDER BY a.academy_name, e.event_name";

    if (mysql_query(con, query)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return;
    }

    res = mysql_store_result(con);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return;
    }

    printf("学院\t项目\t总分\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
    }

    mysql_free_result(res);

    int temp;
    printf("返回请输入1\n");
    scanf("%d", &temp);
}

// 2.【各学院-男女】总分总览
void scoreGender(MYSQL *con) {
    system("cls"); // 清屏
    printf("【各学院-男女】总分总览\n");
    printf("----------------\n");

    const char *query = "SELECT a.academy_name, SUM(r.score) AS total_score, "
                        "SUM(CASE WHEN s.gender = 'male' THEN r.score ELSE 0 END) AS total_male_score, "
                        "SUM(CASE WHEN s.gender = 'female' THEN r.score ELSE 0 END) AS total_female_score "
                        "FROM registration r "
                        "JOIN students s ON r.student_id = s.student_id "
                        "JOIN academy a ON r.academy_id = a.academy_id "
                        "GROUP BY a.academy_name";

    if (mysql_query(con, query)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return;
    }

    res = mysql_store_result(con);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return;
    }

    printf("学院\t总分\t男子总分\t女子总分\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3]);
    }

    mysql_free_result(res);

    int temp;
    printf("返回请输入1\n");
    scanf("%d", &temp);
}

// 3.学院总分名次查询
void rankAcademy(MYSQL *con) {
    system("cls"); // 清屏
    printf("学院总分名次查询\n");
    printf("----------------\n");

    const char *query = "SELECT a.academy_name, SUM(r.score) AS total_score "
                        "FROM registration r "
                        "JOIN academy a ON r.academy_id = a.academy_id "
                        "GROUP BY a.academy_name "
                        "ORDER BY total_score DESC";

    if (mysql_query(con, query)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return;
    }

    res = mysql_store_result(con);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return;
    }

    printf("学院\t总分\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%s\t%s\n", row[0], row[1]);
    }

    mysql_free_result(res);

    int temp;
    printf("返回请输入1\n");
    scanf("%d", &temp);
}

// 4.【各项目】运动员排名查询
void rankAthlete(MYSQL *con) {
    system("cls"); // 清屏
    printf("【各项目】运动员排名查询\n");
    printf("----------------\n");
    printf("请输入录入项目序号\n");
    printf("1.100m 2.200m 3.跳远 4.跳高\n");

    char event_id[10];
    scanf("%s", event_id);

    char query[256];
    snprintf(query, sizeof(query), "SELECT s.student_name, r.score "
                                   "FROM registration r "
                                   "JOIN students s ON r.student_id = s.student_id "
                                   "WHERE r.event_id = %s "
                                   "ORDER BY score DESC", event_id);

    if (mysql_query(con, query)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return;
    }

    res = mysql_store_result(con);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return;
    }

    printf("姓名\t分数\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%s\t%s\n", row[0], row[1]);
    }

    mysql_free_result(res);

    int temp;
    printf("返回请输入1\n");
    scanf("%d", &temp);
}

// 5.运动员信息录入
void enterGender(MYSQL *con) {
    int n;
    system("cls"); // 清屏
    printf("运动员信息录入\n");
    printf("----------------\n");
    printf("1.添加运动员\n");
    printf("2.删除运动员\n");
    printf("3.修改运动员信息\n");
    printf("4.查询所有运动员报名信息\n");
    printf("请输入所需功能前的序号: ");
    scanf("%d", &n);

    while (n < 1 || n > 4) {
        printf("请重新输入所需功能前的序号，eg:1\n");
        scanf("%d", &n);
    }

    // 1.添加运动员
    if (n == 1) {
        char student_name[50];
        char gender[10];
        char academy_id[10];
        char event_id[10];

        printf("请输入姓名: ");
        scanf("%s", student_name);
        printf("请输入性别(male/female): ");
        scanf("%s", gender);
        printf("请输入学院id(1.电子工程 2.传播 3.通信工程 4.机电工程 5.中俄 6.数学): ");
        scanf("%s", academy_id);
        printf("请输入项目序号(1.100m 2.200m 3.跳远 4.跳高): ");
        scanf("%s", event_id);

        char query[256];
        snprintf(query, sizeof(query), "INSERT INTO students (student_name, gender, academy_id) VALUES ('%s', '%s', '%s')", student_name, gender, academy_id);

        if (mysql_query(con, query)) {
            fprintf(stderr, "%s\n", mysql_error(con));
            return;
        }

        snprintf(query, sizeof(query), "SELECT LAST_INSERT_ID() AS id");
        mysql_query(con, query);
        res = mysql_store_result(con);
        row = mysql_fetch_row(res);
        int student_id = atoi(row[0]);
        mysql_free_result(res);

        snprintf(query, sizeof(query), "INSERT INTO registration (student_id, academy_id, event_id, score) VALUES (%d, '%s', '%s', '0')", student_id, academy_id, event_id);

        if (mysql_query(con, query)) {
            fprintf(stderr, "%s\n", mysql_error(con));
            return;
        }

        printf("添加成功！你的序号为：%d\n", student_id);
    }
    // 2.删除运动员
    else if (n == 2) {
        char num_athlete[10];
        printf("请输入运动员序号: ");
        scanf("%s", num_athlete);

        char query[256];
        snprintf(query, sizeof(query), "DELETE FROM registration WHERE student_id = %s", num_athlete);
        mysql_query(con, query);

        snprintf(query, sizeof(query), "DELETE FROM students WHERE student_id = %s", num_athlete);
        mysql_query(con, query);

        printf("删除成功\n");
    }
    // 3.修改运动员报名信息
    else if (n == 3) {
        char student_id[10];
        char event_id[10];

        printf("请输入运动员序号: ");
        scanf("%s", student_id);
        printf("请输入要修改为的项目序号(1.100m 2.200m 3.跳远 4.跳高): ");
        scanf("%s", event_id);

        char query[256];
        snprintf(query, sizeof(query), "UPDATE registration SET event_id = %s WHERE student_id = %s", event_id, student_id);

        if (mysql_query(con, query)) {
            fprintf(stderr, "%s\n", mysql_error(con));
            return;
        }

        printf("修改成功！\n");
    }
    // 4.查询所有运动员报名信息
    else {
        printf("查询所有运动员报名信息\n");

        const char *query = "SELECT registration.student_id, students.student_name, students.gender, events.event_name "
                            "FROM registration "
                            "JOIN students ON registration.student_id = students.student_id "
                            "JOIN events ON registration.event_id = events.event_id";

        if (mysql_query(con, query)) {
            fprintf(stderr, "%s\n", mysql_error(con));
            return;
        }

        res = mysql_store_result(con);
        if (res == NULL) {
            fprintf(stderr, "%s\n", mysql_error(con));
            return;
        }

        printf("序号\t姓名\t性别\t项目\n");
        while ((row = mysql_fetch_row(res))) {
            printf("%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3]);
        }

        mysql_free_result(res);
    }

    int temp;
    printf("返回请输入1\n");
    scanf("%d", &temp);
}

// 6.项目成绩录入
void enterScore(MYSQL *con) {
    char event_id[10];
    system("cls"); // 清屏
    printf("项目成绩录入\n");
    printf("----------------\n");
    printf("请输入录入项目序号(1.100m 2.200m 3.跳远 4.跳高): ");
    scanf("%s", event_id);

    char query[256];
    snprintf(query, sizeof(query), "SELECT registration.student_id FROM registration WHERE event_id = %s", event_id);

    if (mysql_query(con, query)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return;
    }

    printf("报名该项目的学生为：\n");
    res = mysql_store_result(con);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return;
    }

    while ((row = mysql_fetch_row(res))) {
        printf("%s\n", row[0]);
    }

    mysql_free_result(res);

    printf("请输入对应得分\n");

    res = mysql_store_result(con);
    while ((row = mysql_fetch_row(res))) {
        char score[10];
        printf("%s: ", row[0]);
        scanf("%s", score);

        snprintf(query, sizeof(query), "UPDATE registration SET score = %s WHERE student_id = %s", score, row[0]);

        if (mysql_query(con, query)) {
            fprintf(stderr, "%s\n", mysql_error(con));
            return;
        }
    }

    mysql_free_result(res);
    printf("录入成功！\n");

    int temp;
    printf("返回请输入1\n");
    scanf("%d", &temp);
}

// 主函数
int main() {
    // MySQL 初始化
    con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    // 连接数据库
    if (mysql_real_connect(con, "公网ip", "用户名", "密码", "codertest", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(con);
        return EXIT_FAILURE;
    }

    int n = 1;

    while (n > 0 && n < 7) {
        n = menu();
        switch (n) {
            case 1: scoreAcademy(con); break;
            case 2: scoreGender(con); break;
            case 3: rankAcademy(con); break;
            case 4: rankAthlete(con); break;
            case 5: enterGender(con); break;
            case 6: enterScore(con); break;
        }
    }

    mysql_close(con);
    return 0;
}
