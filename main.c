/*
 * 本代码优点：
 * 使用linux内核代码规范形式
 * 注释完整，代码严谨
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <memory.h>
#include <math.h>

struct cookie   // 保存当前用户登陆信息
{
    char username[55];
};
struct userinfo   // 保存所有用户完整信息
{
    char username[55], password[55];
    char age[10];
    int status; // 状态1:账号注册成功， 0:账号待通过
    char sex[10]; // male or female
    char contact[55];
};
struct bookinfo // 保存所有图书信息
{
    char bookNum[55], bookName[55], author[55]; // 书号，书名，作者名
    char publishingHouse[55], publicshingTime[55]; // 出版社，出版时间
    char bookPrice[55]; // 该书的价格
};
struct booklend // 保存所有借书信息
{
    char userName[55];
    char bookNum[55];
    char startTime[55];
};
int WIDTH = 41; // 用户界面宽度
int OpWidth = 12; // 用户操作宽度
int UserNum = 0, BookNum = 0, LendNum = 0; // 用户总数, 图书总数，借阅总数
int i, j, k; // 提前定义循环变量
char BORDER[] = { '#', '*', '+', '@', '`', '-', '='}; // 边框随机字符
char OpLine = '-', BorderLeft = '|';
typedef struct cookie COOKIE;
typedef struct userinfo USERINFO;
typedef struct bookinfo BOOKINFO;
typedef struct booklend BOOKLEND;
COOKIE userCookie; // 登录信息
USERINFO USER[5000], CurrentUser; // 用户信息结构体数组
BOOKINFO BOOK[5000]; // 图书信息结构体数组
BOOKLEND LEND[5000]; // 借书信息结构体数组

/* 功能函数模块 */
char RandomNumber(char str[], int n); // 返回随机数函数
int ChooseVerify(int minNumber, int maxNumber); // 选择验证函数
void loginVerify(char username[]); // 登录验证函数
void BackgroundColor(); // 背景色函数
void SystemOp(char str[]); // 控制台操作函数
int StringMatch(char pStr[], char qStr[]); // 字符串模糊匹配函数
void BookPrintf(int id); // 图书信息输出函数
long Timestamp(char time[]); // 简易时间戳函数

void index(); // 主页函数
void login(); // 登录函数
void UserRegister();// 用户注册函数
void MainMenu(); // 主菜单函数

/* 图书管理系统主模块 */
void InformationEntry(); // 图书信息录入函数
void InformationBrowsing(); // 图书信息浏览函数
void InformationInquiry(); // 图书信息查询函数
void InformationDelete(); // 图书信息删除函数
void InformationModify(); // 图书信息修改函数
void AccountManage(); // 用户账号管理函数

/* 图书馆借书系统主模块 */
void BookLend(); // 借阅图书
void BookLendStatus(); // 图书借阅状态
void BookReturn(); // 图书归还

int main()
{
    // 实现随机背景色
    BackgroundColor();
    // 实现用户或者管理员登录
    index();
    // 进入主菜单
    MainMenu();
    return 0;
}

/// 主页
void index()
{
    SystemOp("cls");
    int chooseNumber;
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));

    printf("ESC键退出系统 / Tab键切换背景色\n");
    printf("\n\n\n\t\t\t\t欢迎来到图书馆！\n\n");
    printf("\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    printf("\t%c", '1');
    for( i = 0; i < OpWidth; i++ )
        printf("%c", OpLine);
    printf("管理员登录 \t|\n");
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    printf("\t%c", '2');
    for( i = 0; i < OpWidth; i++ )
        printf("%c", OpLine);
    printf("借阅者登录 \t|\n");
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c", BorderLeft);

    chooseNumber = ChooseVerify(1, 2);

    if(chooseNumber == 0)
    {
        SystemOp("exit");
        exit(0);
    }
    else if(chooseNumber >= 1 && chooseNumber <= 2)
    {
        login(chooseNumber);
    }
}

/// 登录函数（管理员登录和用户登录， 用户可注册和直接登录）
void login(int chooseNumber)
{
    SystemOp("cls");
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));
    int userChooseNumber, fileFlag, fileNum;
    char fileStr[55], username[55];

    // 从文件读取数据，保存到结构体中
    FILE *fp = NULL;
    fp = fopen("userinfo.txt", "a+");
    fileFlag = 0, fileNum = 0;
    while(!feof(fp))
    {
        if(fgets(fileStr, 55, fp)!=NULL)
        {
            fileStr[strlen(fileStr)-1]='\0'; // 去除字符串末尾\n
            switch(fileFlag)
            {
            case 0:
                strcpy(USER[fileNum].username, fileStr);
                break;
            case 1:
                strcpy(USER[fileNum].password, fileStr);
                break;
            case 2:
                strcpy(USER[fileNum].age, fileStr);
                break;
            case 3:
                USER[fileNum].status = fileStr[0] - '0';
                break;
            case 4:
                strcpy(USER[fileNum].sex, fileStr);
                break;
            case 5:
                strcpy(USER[fileNum].contact, fileStr);
                break;
            }
        }
        fileFlag++;
        if(fileFlag >= 6)
        {
            fileFlag = 0;
            fileNum++;
        }
    }
    UserNum = fileNum;
    fclose(fp);

    printf("\n\n\n\t\t\t\t请登录|图书馆！\n\n");
    printf("\t\tESC键返回首页->\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    switch(chooseNumber)
    {
    case 1:
    {
        // 管理员登录
        printf("\t管理员 :\tadmin\t\t%c\n", BorderLeft);
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf("%c", borderChar);
        printf("%c\n", BorderLeft);

        loginVerify("admin");
    }
    break;
    case 2:   // 借阅者登录
    {
        fflush(stdin);
        printf("\t借阅者登录\t\t\t%c\n", BorderLeft);
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '1');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("新用户注册 \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '2');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("直接登陆\t \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf("%c", borderChar);
        printf("%c\n", BorderLeft);

        userChooseNumber = ChooseVerify(1, 2);

        fflush(stdin);
        if(userChooseNumber == 1)   // 新用户注册
        {
            // 注册函数
            UserRegister();
        }
        else if(userChooseNumber == 2)     // 直接登陆
        {
            printf("\n\n\t\t");
            for( i = 0; i < WIDTH; i++ )
                printf("%c", borderChar);
            printf("\n\t\t\t你的用户名：");
            gets(username);
            loginVerify(username);
        }
        else if(userChooseNumber == 0)     // ESC
        {
            index();
            return;
        }
    }
    break;
    }
}

/// 用户注册函数（用于新用户注册，指向文件userinfo.txt）
void UserRegister()
{
    SystemOp("cls");
    int usernameFlag = 0;
    char Password[55], rePassword[55];
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));
    USERINFO newUser; // 创建新用户
    FILE *fp = NULL; // 打开文件 userinfo.txt
    fp = fopen("userinfo.txt", "a+");

    printf("\n\n\n\t\t\t   新用户注册 | 图书馆\n\n");
    printf("\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    printf("\t用户名 ：");
    gets(newUser.username);
    // 验证用户名是否重复
    while(usernameFlag == 0)
    {
        usernameFlag = 1; // 初始化flag
        for(i = 0; i < UserNum; i++)
        {
            if(strcmp(USER[i].username, newUser.username) == 0)
            {
                usernameFlag = 0;
            }
        }
        if(usernameFlag == 0)   // 表示用户名重复
        {
            printf("\t\t%c\t用户名重复，请重新输入：\n", BorderLeft);
            printf("\t\t%c\t用户名 ：", BorderLeft);
            gets(newUser.username);
        }
        else
        {
            break;
        }
    }
    printf("\t\t%c\t密码 ：", BorderLeft);
    gets(Password);
    printf("\t\t%c\t重复密码 ：", BorderLeft);
    gets(rePassword);
    // 验证密码是否一致
    while(strcmp(Password, rePassword) != 0)
    {
        printf("\t\t%c\t密码不一致，请重新输入：\n", BorderLeft);
        printf("\t\t%c\t密码 ：", BorderLeft);
        gets(Password);
        printf("\t\t%c\t重复密码 ：", BorderLeft);
        gets(rePassword);
    }
    // 密码一致
    strcpy(newUser.password, Password);
    printf("\t\t%c\t年龄 ：", BorderLeft);
    gets(newUser.age);
    printf("\t\t%c\t性别(male or female) ：", BorderLeft);
    gets(newUser.sex);
    printf("\t\t%c\t联系方式 ：", BorderLeft);
    gets(newUser.contact);


    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    printf("\t注册成功！按ESC键返回； \t|\n");
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n", BorderLeft);

    newUser.status = 0; // 表示需管理员同意后使用

    fputs(newUser.username, fp);
    fputs("\n", fp);
    fputs(newUser.password, fp);
    fputs("\n", fp);
    fputs(newUser.age, fp);
    fputs("\n", fp);
    fputs("0", fp);
    fputs("\n", fp);
    fputs(newUser.sex, fp);
    fputs("\n", fp);
    fputs(newUser.contact, fp);
    fputs("\n", fp);

    fclose(fp); // 关闭文件

    if(getch() == 27)
    {
        login(2);
    }
    return;
}

/// 主菜单函数（图书管理系统菜单 和 图书借书系统菜单）
void MainMenu()
{
    SystemOp("cls");
    int chooseNumber, fileFlag, fileNum;
    char fileStr[55];
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));
    printf("欢迎你，%s！", userCookie.username);

    // 从文件读取数据，保存到结构体中
    FILE *fp = NULL;
    fp = fopen("bookinfo.txt", "a+");
    fileFlag = 0, fileNum = 0;
    while(!feof(fp))
    {
        if(fgets(fileStr, 55, fp)!=NULL)
        {
            fileStr[strlen(fileStr)-1]='\0'; // 去除字符串末尾\n
            switch(fileFlag)
            {
            case 0:
                strcpy(BOOK[fileNum].bookNum, fileStr);
                break;
            case 1:
                strcpy(BOOK[fileNum].bookName, fileStr);
                break;
            case 2:
                strcpy(BOOK[fileNum].author, fileStr);
                break;
            case 3:
                strcpy(BOOK[fileNum].publishingHouse, fileStr);
                break;
            case 4:
                strcpy(BOOK[fileNum].publicshingTime, fileStr);
                break;
            case 5:
                strcpy(BOOK[fileNum].bookPrice, fileStr);
                break;
            }
        }
        fileFlag++;
        if(fileFlag >= 6)
        {
            fileFlag = 0;
            fileNum++;
        }
    }
    BookNum = fileNum;
    fclose(fp);

    FILE *fp2 = NULL;
    fp2 = fopen("booklend.txt", "a+");
    fileFlag = 0, fileNum = 0;
    while(!feof(fp2))
    {
        if(fgets(fileStr, 55, fp2)!=NULL)
        {
            fileStr[strlen(fileStr)-1]='\0'; // 去除字符串末尾\n
            switch(fileFlag)
            {
            case 0:
                strcpy(LEND[fileNum].userName, fileStr);
                break;
            case 1:
                strcpy(LEND[fileNum].bookNum, fileStr);
                break;
            case 2:
                strcpy(LEND[fileNum].startTime, fileStr);
                break;
            }
        }
        fileFlag++;
        if(fileFlag >= 3)
        {
            fileFlag = 0;
            fileNum++;
        }
    }
    LendNum = fileNum;
    fclose(fp2);

    if(strcmp(userCookie.username, "admin") == 0)   // 管理员登录状态
    {
        printf("\n\n\n\t\t\t\t图书信息管理系统\n\n");
        printf("\n\t\t");
        for( i = 0; i < WIDTH; i++ )
            printf("%c", borderChar);
        printf("\n\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '1');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("图书信息录入 \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '2');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("图书信息浏览 \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '3');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("图书信息查询 \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '4');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("图书信息删除 \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '5');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("图书信息修改 \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '6');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("用户账号管理 \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%s", "ESC");
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("退出 \t\t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf("%c", borderChar);
        printf("%c", BorderLeft);

        chooseNumber = ChooseVerify(1, 6);

        switch(chooseNumber)
        {
        case 0:
            memset(&userCookie, 0, sizeof(COOKIE));
            index();
            break; // 退出系统，清除cookie,返回主页
        case 1:
            InformationEntry();
            break; // 信息录入
        case 2:
            InformationBrowsing();
            break; // 信息浏览
        case 3:
            InformationInquiry();
            break; // 信息查询
        case 4:
            InformationDelete();
            break; // 信息删除
        case 5:
            InformationModify();
            break; // 信息修改
        case 6:
            AccountManage();
            break; // 用户账号管理
        }
    }
    else     // 借阅者登录状态
    {
        printf("\n\n\n\t\t\t\t图书馆借书系统\n\n");
        printf("\n\t\t");
        for( i = 0; i < WIDTH; i++ )
            printf("%c", borderChar);
        printf("\n\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '1');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("查阅图书 \t\t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '2');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("借阅图书 \t\t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '3');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("图书借阅状态 \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '4');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("图书归还 \t\t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%s", "ESC");
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("退出 \t\t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf("%c", borderChar);
        printf("%c", BorderLeft);

        chooseNumber = ChooseVerify(1, 4);

        switch(chooseNumber)
        {
        case 0:
            memset(&userCookie, 0, sizeof(COOKIE));
            index();
            break; // 退出系统，清除cookie,返回主页
        case 1:
            InformationInquiry();
            break; // 查阅图书
        case 2:
            BookLend();
            break; // 借阅图书
        case 3:
            BookLendStatus();
            break; // 图书借阅状态
        case 4:
            BookReturn();
            break; // 图书归还
        }
    }
}

/// 图书管理系统主模块（录入、浏览、查询、删除、修改，账户管理）
void InformationEntry() // 图书信息录入函数
{
    SystemOp("cls");
    fflush(stdin);
    int chooseNumber, bookNumFlag;
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));

    BOOKINFO NewBook; // 创建新的图书信息
    FILE *fp = NULL; // 打开文件 bookinfo.txt
    fp = fopen("bookinfo.txt", "a+");

    printf("\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c\t\t图书信息录入 \t\t%c\n", BorderLeft, BorderLeft, BorderLeft);
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);

    printf("%c\n\t\t%c\t请输入您的书籍的书号：", BorderLeft, BorderLeft);
    bookNumFlag = 0;
    gets(NewBook.bookNum);
    while(bookNumFlag == 0)
    {
        bookNumFlag = 1;
        for(i = 0; i < BookNum; i++)
        {
            if( strcmp(BOOK[i].bookNum, NewBook.bookNum) == 1 )
            {
                bookNumFlag = 0;
                break;
            }
        }
        printf("\t\t%c  该书号已存在，请重新输入!", BorderLeft);
        printf("%c\n\t\t%c\t请输入您的书籍的书号：", BorderLeft, BorderLeft);
        gets(NewBook.bookNum);
    }

    printf("\t\t%c\t请输入书名：", BorderLeft);
    gets(NewBook.bookName);
    printf("\t\t%c\t请输入作者名：", BorderLeft);
    gets(NewBook.author);
    printf("\t\t%c\t请输入出版社：", BorderLeft);
    gets(NewBook.publishingHouse);
    printf("\t\t%c\t请输入出版时间(时间格式:YYYY-mm-dd)：", BorderLeft);
    gets(NewBook.publicshingTime);
    while(NewBook.publicshingTime[4] != '-' && NewBook.publicshingTime[7] != '-')
    {
        printf("\t\t%c时间格式错误！请重新输入", BorderLeft);
        printf("\t\t%c\t请输入出版时间(时间格式:YYYY-mm-dd)：", BorderLeft);
        gets(NewBook.publicshingTime);
    }
    printf("\t\t%c\t请输入该书的价格：", BorderLeft);
    gets(NewBook.bookPrice);
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n", BorderLeft);

    // 图书信息录入文件
    fputs(NewBook.bookNum, fp);
    fputs("\n", fp);
    fputs(NewBook.bookName, fp);
    fputs("\n", fp);
    fputs(NewBook.author, fp);
    fputs("\n", fp);
    fputs(NewBook.publishingHouse, fp);
    fputs("\n", fp);
    fputs(NewBook.publicshingTime, fp);
    fputs("\n", fp);
    fputs(NewBook.bookPrice, fp);
    fputs("\n", fp);

    fclose(fp); // 关闭文件

    printf("\t\t《%s》信息录入完成，是否继续录入?(0 退出| 1 继续)", NewBook.bookName);

    chooseNumber = ChooseVerify(0, 1);
    switch(chooseNumber)
    {
    case 0:
        MainMenu();
        break; // 退出
    case 1:
        InformationEntry();
        break; // 继续
    }
    return;
}

void InformationBrowsing() // 图书信息浏览函数
{
    SystemOp("cls");
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));

    printf("\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c\t  ***图书信息浏览*** \t\t%c\n", BorderLeft, BorderLeft, BorderLeft);
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n", BorderLeft);

    // 输出所有的图书信息
    for(j = 0; j < BookNum; j++)
    {
        printf("\n\t\t");
        for( i = 0; i < WIDTH; i++ )
            printf("%c", borderChar);
        printf("\n\t\t%cid:%03d%c", BorderLeft, j+1, BorderLeft);
        for( i = 0; i < WIDTH-9; i++ )
            printf(" ");
        printf("%c\n\t\t%c\t书号：%s \t\t%c\n", BorderLeft, BorderLeft, BOOK[j].bookNum, BorderLeft);
        printf("\t\t%c\t书名：%s \t\t%c\n", BorderLeft, BOOK[j].bookName, BorderLeft);
        printf("\t\t%c\t作者：%s \t\t%c\n", BorderLeft, BOOK[j].author, BorderLeft);
        printf("\t\t%c\t出版社：%s \t\t%c\n", BorderLeft, BOOK[j].publishingHouse, BorderLeft);
        printf("\t\t%c\t出版时间：%s \t\t%c\n", BorderLeft, BOOK[j].publicshingTime, BorderLeft);
        printf("\t\t%c\t价格：%s \t\t\t%c\n",BorderLeft, BOOK[j].bookPrice, BorderLeft);
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf("%c", borderChar);
        printf("%c\n", BorderLeft);
    }
    printf("\t\t按ESC键返回：");
    int chooseNumber = ChooseVerify(0, 0);
    if(chooseNumber == 0)
    {
        MainMenu(); // 返回主菜单函数
    }
}

void InformationInquiry() // 图书信息查询函数
{
    SystemOp("cls");
    int chooseNumber, resultNumber = 0;
    char searcherStr[55];
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));

    printf("\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c\t  ***图书信息查询*** \t\t%c\n", BorderLeft, BorderLeft, BorderLeft);
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    printf("\t%c", '1');
    for( i = 0; i < OpWidth; i++ )
        printf("%c", OpLine);
    printf("根据书号查询 \t|\n");
    printf("\t\t%c", BorderLeft);
    printf("\t%c", '2');
    for( i = 0; i < OpWidth; i++ )
        printf("%c", OpLine);
    printf("根据书名查询 \t|\n");
    printf("\t\t%c", BorderLeft);
    printf("\t%c", '3');
    for( i = 0; i < OpWidth; i++ )
        printf("%c", OpLine);
    printf("根据作者查询 \t|\n");
    printf("\t\t%c", BorderLeft);
    printf("\t%c", '4');
    for( i = 0; i < OpWidth; i++ )
        printf("%c", OpLine);
    printf("根据出版社查询 \t|\n");
    printf("\t\t%c", BorderLeft);
    printf("\t%c", '5');
    for( i = 0; i < OpWidth; i++ )
        printf("%c", OpLine);
    printf("根据出版时间查询 \t|\n");
    printf("\t\t%c", BorderLeft);
    printf("\t%s", "ESC");
    for( i = 0; i < OpWidth-2; i++ )
        printf("%c", OpLine);
    printf(" 返回主菜单 \t|\n");
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n", BorderLeft);
    printf("\n\t\t");

    chooseNumber = ChooseVerify(1, 5);
    fflush(stdin);
    switch(chooseNumber)
    {
    case 0:
        MainMenu();
        break;
    case 1:
    {
        printf("\n\t%c 请输入想要查询的书号：", BorderLeft);
        gets(searcherStr);
        for(k = 0; k < BookNum; k++)
        {
            if(StringMatch(BOOK[k].bookNum, searcherStr) == 1)
                resultNumber++,
                             BookPrintf(k);
        }
    }
    break;
    case 2:
    {
        printf("\n\t%c 请输入想要查询的书名：", BorderLeft);
        gets(searcherStr);
        for(k = 0; k < BookNum; k++)
        {
            if(StringMatch(BOOK[k].bookName, searcherStr) == 1)
                resultNumber++,
                             BookPrintf(k);
        }
    }
    break;
    case 3:
    {
        printf("\n\t%c 请输入想要查询的作者名：", BorderLeft);
        gets(searcherStr);
        for(k = 0; k < BookNum; k++)
        {
            if(StringMatch(BOOK[k].author, searcherStr) == 1)
                resultNumber++,
                             BookPrintf(k);
        }
    }
    break;
    case 4:
    {
        printf("\n\t%c 请输入想要查询的出版社：", BorderLeft);
        gets(searcherStr);
        for(k = 0; k < BookNum; k++)
        {
            if(StringMatch(BOOK[k].publishingHouse, searcherStr) == 1)
                resultNumber++,
                             BookPrintf(k);
        }
    }
    break;
    case 5:
    {
        char startTime[55], endTime[55];
        printf("\n\t%c 请输入想要查询的时间段(时间格式:YYYY-mm-dd)", BorderLeft);
        printf("\n\t%c --开始时间：", BorderLeft);
        gets(startTime);
        while(startTime[4] != '-' && startTime[6] != '-')
        {
            printf("\t时间格式错误！请重新输入");
            printf("\n\t%c --开始时间：", BorderLeft);
            gets(startTime);
        }
        printf("\n\t%c --结束时间：", BorderLeft);
        gets(endTime);
        while(endTime[4] != '-' && endTime[6] != '-')
        {
            printf("\t时间格式错误！请重新输入");
            printf("\n\t%c --结束时间：", BorderLeft);
            gets(endTime);
        }
        for(k = 0; k < BookNum; k++)
        {
            if(Timestamp(startTime) <= Timestamp(BOOK[k].publicshingTime) && Timestamp(BOOK[k].publicshingTime) <= Timestamp(endTime))
                resultNumber++,
                             BookPrintf(k);
        }
    }
    break;
    }
    printf("\n\t%c 共查询到%d 本书。", BorderLeft, resultNumber);
    printf("\n\t%c 是否继续查询？(0 退出| 1 重新查询)：", BorderLeft);
    chooseNumber = ChooseVerify(0, 1);
    if(chooseNumber == 0)   // 退出
    {
        MainMenu(); // 返回主菜单
    }
    else if(chooseNumber == 1)     // 继续查询
    {
        InformationInquiry(); // 回调函数
        return;
    }
    return;
}

void InformationDelete() // 图书信息删除函数
{
    SystemOp("cls");
    int chooseNumber, resultNumber = 0, bookDeleteNum;
    char searcherStr[55];
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));
    BOOKINFO tempbook;

    printf("\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c\t  ***图书信息删除*** \t\t%c\n", BorderLeft, BorderLeft, BorderLeft);
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    printf("\t%c", '1');
    for( i = 0; i < OpWidth; i++ )
        printf("%c", OpLine);
    printf("根据书号查询图书 \t|\n");
    printf("\t\t%c", BorderLeft);
    printf("\t%s", "ESC");
    for( i = 0; i < OpWidth-2; i++ )
        printf("%c", OpLine);
    printf(" 返回主菜单 \t|\n");
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t|(请精确查找，查找结果为一本书时允许删除|\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n", BorderLeft);
    printf("\n\t\t");

    chooseNumber = ChooseVerify(1, 1);
    fflush(stdin);
    switch(chooseNumber)
    {
    case 0:
        MainMenu();
        break;
    case 1:
    {
        printf("\n\t%c 请输入想要查询的书号：", BorderLeft);
        gets(searcherStr);
        for(k = 0; k < BookNum; k++)
        {
            if(StringMatch(BOOK[k].bookNum, searcherStr) == 1)
            {
                bookDeleteNum = k;
                resultNumber++;
                BookPrintf(k);
            }
        }
    }
    break;
    }
    printf("\n\t%c 共查询到%d 本书。", BorderLeft, resultNumber);
    printf("\n\t%c |(请精确查找，查找结果为一本书时允许删除)", BorderLeft);
    if(resultNumber == 1)
    {
        printf("\n\t%c 是否删除《%s》？(0 取消| 1 确认)：", BorderLeft, BOOK[bookDeleteNum].bookName);
        chooseNumber = ChooseVerify(0, 1);
        if(chooseNumber == 0)   // 取消
        {
            InformationDelete(); // 返回信息删除函数
            return;
        }
        else if(chooseNumber == 1)     // 删除
        {
            tempbook = BOOK[BookNum-1];
            BOOK[BookNum-1] = BOOK[bookDeleteNum];
            BOOK[bookDeleteNum] = tempbook;
            BookNum--;
            // 重新写入文件
            FILE *fp = NULL; // 打开文件 bookinfo.txt
            fp = fopen("bookinfo.txt", "w+");
            for(i = 0; i < BookNum; i++)
            {
                fputs(BOOK[i].bookNum, fp);
                fputs("\n", fp);
                fputs(BOOK[i].bookName, fp);
                fputs("\n", fp);
                fputs(BOOK[i].author, fp);
                fputs("\n", fp);
                fputs(BOOK[i].publishingHouse, fp);
                fputs("\n", fp);
                fputs(BOOK[i].publicshingTime, fp);
                fputs("\n", fp);
                fputs(BOOK[i].bookPrice, fp);
                fputs("\n", fp);
            }
            fclose(fp); // 关闭文件
        }
        printf("\n\t%c 删除成功！", BorderLeft);
        printf("\n\t\t");
        for( i = 0; i < WIDTH; i++ )
            printf("%c", borderChar);
        printf("\n");
    }
    printf("\n\t%c 是否继续？(0 退出| 1 重新查询)：", BorderLeft);
    chooseNumber = ChooseVerify(0, 1);
    if(chooseNumber == 0)   // 退出
    {
        MainMenu(); // 返回主菜单
    }
    else if(chooseNumber == 1)     // 继续查询
    {
        InformationDelete(); // 回调函数
        return;
    }

    return;
}

void InformationModify() // 图书信息修改函数
{
    SystemOp("cls");
    int chooseNumber, resultNumber = 0, bookModifyNum;
    char searcherStr[55];
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));

    printf("\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c\t  ***图书信息修改*** \t\t%c\n", BorderLeft, BorderLeft, BorderLeft);
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    printf("\t%c", '1');
    for( i = 0; i < OpWidth; i++ )
        printf("%c", OpLine);
    printf("根据书号查询图书 \t|\n");
    printf("\t\t%c", BorderLeft);
    printf("\t%s", "ESC");
    for( i = 0; i < OpWidth-2; i++ )
        printf("%c", OpLine);
    printf(" 返回主菜单 \t|\n");
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t|(请精确查找，查找结果为一本书时修改信息|\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n", BorderLeft);
    printf("\n\t\t");

    chooseNumber = ChooseVerify(1, 1);
    fflush(stdin);
    switch(chooseNumber)
    {
    case 0:
        MainMenu();
        break;
    case 1:
    {
        printf("\n\t%c 请输入想要查询的书号：", BorderLeft);
        gets(searcherStr);
        for(k = 0; k < BookNum; k++)
        {
            if(StringMatch(BOOK[k].bookNum, searcherStr) == 1)
            {
                bookModifyNum = k;
                resultNumber++;
                BookPrintf(k);
            }
        }
    }
    break;
    }
    printf("\n\t%c 共查询到%d 本书。", BorderLeft, resultNumber);
    printf("\n\t%c |(请精确查找，查找结果为一本书时修改信息)", BorderLeft);
    if(resultNumber == 1)
    {
        printf("\n\t%c 是否修改《%s》该书信息？(0 取消| 1 确认)：", BorderLeft, BOOK[bookModifyNum].bookName);
        chooseNumber = ChooseVerify(0, 1);
        if(chooseNumber == 0)   // 取消
        {
            InformationModify(); // 返回信息修改函数
            return;
        }
        else if(chooseNumber == 1)     // 信息修改
        {
            fflush(stdin);
            printf("\n\n\t\t");
            for( i = 0; i < WIDTH; i++ )
                printf("%c", borderChar);
            printf("\n");
            printf("\t\t%c\t书号(%s)\n\t\t%c\n", BorderLeft, BOOK[bookModifyNum].bookNum, BorderLeft);
            // 获取修改信息
            printf("\t\t%c 你想修改的是？\n", BorderLeft);
            printf("\t\t%c <-1. 书名 ->\n", BorderLeft);
            printf("\t\t%c <-2. 作者名 ->\n", BorderLeft);
            printf("\t\t%c <-3. 出版社 ->\n", BorderLeft);
            printf("\t\t%c <-4. 出版时间 ->\n", BorderLeft);
            printf("\t\t%c <-5. 价格 ->\n", BorderLeft);
            chooseNumber = ChooseVerify(1, 5);
            switch(chooseNumber)
            {
            case 0:
            {
                InformationModify(); // 返回信息修改函数
                return;
            }
            break;
            case 1:
            {
                printf("\n\t\t%c\t书名(%s)：", BorderLeft, BOOK[bookModifyNum].bookName);
                gets(BOOK[bookModifyNum].bookName);
            }
            break;
            case 2:
            {
                printf("\n\t\t%c\t作者名(%s)：", BorderLeft, BOOK[bookModifyNum].author);
                gets(BOOK[bookModifyNum].author);
            }
            break;
            case 3:
            {
                printf("\n\t\t%c\t出版社(%s)：", BorderLeft, BOOK[bookModifyNum].publishingHouse);
                gets(BOOK[bookModifyNum].publishingHouse);
            }
            break;
            case 4:
            {
                printf("\n\t\t%c\t出版时间(%s)(格式:YYYY-mm-dd)：", BorderLeft, BOOK[bookModifyNum].publicshingTime);
                gets(BOOK[bookModifyNum].publicshingTime);
                while(BOOK[bookModifyNum].publicshingTime[4] != '-' && BOOK[bookModifyNum].publicshingTime[6] != '-')
                {
                    printf("\n\t\t%c时间格式错误！请重新输入", BorderLeft);
                    printf("\n\t\t%c\t出版时间(%s)(格式:YYYY-mm-dd)：", BorderLeft, BOOK[bookModifyNum].publicshingTime);
                    gets(BOOK[bookModifyNum].publicshingTime);
                }
            }
            break;
            case 5:
            {
                printf("\n\t\t%c\t价格(%s)：", BorderLeft, BOOK[bookModifyNum].bookPrice);
                gets(BOOK[bookModifyNum].bookPrice);
            }
            break;
            }
            // 重新写入文件
            FILE *fp = NULL; // 打开文件 bookinfo.txt
            fp = fopen("bookinfo.txt", "w+");
            for(i = 0; i < BookNum; i++)
            {
                fputs(BOOK[i].bookNum, fp);
                fputs("\n", fp);
                fputs(BOOK[i].bookName, fp);
                fputs("\n", fp);
                fputs(BOOK[i].author, fp);
                fputs("\n", fp);
                fputs(BOOK[i].publishingHouse, fp);
                fputs("\n", fp);
                fputs(BOOK[i].publicshingTime, fp);
                fputs("\n", fp);
                fputs(BOOK[i].bookPrice, fp);
                fputs("\n", fp);
            }
            fclose(fp); // 关闭文件
        }
        printf("\n\t%c 信息修改成功！", BorderLeft);
        printf("\n\t\t");
        for( i = 0; i < WIDTH; i++ )
            printf("%c", borderChar);
        printf("\n");
    }
    printf("\n\t%c 是否继续？(0 退出| 1 重新查询)：", BorderLeft);
    chooseNumber = ChooseVerify(0, 1);
    if(chooseNumber == 0)   // 退出
    {
        MainMenu(); // 返回主菜单
    }
    else if(chooseNumber == 1)     // 继续查询
    {
        InformationModify(); // 回调函数
        return;
    }

    return;
}

void AccountManage() // 用户账号管理函数
{
    SystemOp("cls");
    int chooseNumber;
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));

    printf("\n\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c\t", BorderLeft, BorderLeft);
    printf("\t用户账号管理系统 \t|\n");
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n\n", BorderLeft);
    printf("图书馆用户总数：%d\n", UserNum);
    for( i = 0; i < WIDTH+WIDTH/2; i++ )
        printf("%c", borderChar);
    printf("\n| 编号\t用户名\t密码\t性别\t年龄\t联系方式\t状态\n");
    for(i = 0; i < UserNum; i++)
    {
        printf("| %03d\t", i+1);
        printf("%s\t", USER[i].username);
        printf("%s\t", USER[i].password);
        printf("%s\t", USER[i].sex);
        printf("%s\t", USER[i].age);
        printf("%s\t", USER[i].contact);
        if(USER[i].status == 0)
            printf("未通过");
        else
            printf("已通过");
        printf("\n");
    }
    printf("\n");
    for( i = 0; i < WIDTH+WIDTH/2; i++ )
        printf("%c", borderChar);
    printf("\n按1进入账号操作, ESC键返回主菜单");
    chooseNumber = ChooseVerify(1, 1);
    if(chooseNumber == 0) // 返回主菜单
    {
        MainMenu();
        return;
    }
    printf("\n请输入想要操作的账号编号:");
    scanf("%d", &chooseNumber);
    chooseNumber--;
    if(USER[chooseNumber].status == 0)
    {
        int chooseNumber2;
        printf("\n该用户的状态是未通过，是否修改为通过？(1 是| 0 否)");
        chooseNumber2 = ChooseVerify(0, 1);
        switch(chooseNumber2)
        {
        case 0:  // 否,回调函数
        {
            AccountManage();
            return;
        }
        break;
        case 1:
        {
            // 修改用户信息,重新写入文件
            USER[chooseNumber].status = 1;
            FILE *fp = NULL; // 打开文件 userinfo.txt
            fp = fopen("userinfo.txt", "w+");
            for(i = 0; i < UserNum; i++)
            {
                fputs(USER[chooseNumber].username, fp);
                fputs("\n", fp);
                fputs(USER[chooseNumber].password, fp);
                fputs("\n", fp);
                fputs(USER[chooseNumber].age, fp);
                fputs("\n", fp);
                fputs("1", fp);
                fputs("\n", fp);
                fputs(USER[chooseNumber].sex, fp);
                fputs("\n", fp);
                fputs(USER[chooseNumber].contact, fp);
                fputs("\n", fp);
            }
            fclose(fp); // 关闭文件
            printf("\n修改成功！");
            printf("| 是否继续管理账号？（1 继续| 0 返回主菜单）");
            chooseNumber = ChooseVerify(0, 1);
            if(chooseNumber == 0)
            {
                MainMenu();
                return;
            }
            else
            {
                AccountManage();
                return;
            }
        }
        break;
        }
    }
    else
    {
        printf("\n该用户的状态是已通过!");
        printf("\n| 是否继续管理账号？（1 继续| 0 返回主菜单）");
        chooseNumber = ChooseVerify(0, 1);
        if(chooseNumber == 0)
        {
            MainMenu();
            return;
        }
        else
        {
            AccountManage();
            return;
        }
    }
    return;
}

/// 图书馆借书系统主模块
void BookLend() // 借阅图书
{
    SystemOp("cls");
    int chooseNumber, resultNumber = 0, bookLendNum;
    char searcherStr[55];
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));
    BOOKLEND newLend;

    printf("\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c\t  ***#借阅图书#*** \t\t%c\n", BorderLeft, BorderLeft, BorderLeft);
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    printf("\t%c", '1');
    for( i = 0; i < OpWidth; i++ )
        printf("%c", OpLine);
    printf("根据书号查询图书 \t|\n");
    printf("\t\t%c", BorderLeft);
    printf("\t%s", "ESC");
    for( i = 0; i < OpWidth-2; i++ )
        printf("%c", OpLine);
    printf(" 返回主菜单 \t|\n");
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t|(请精确查找，查找结果为一本书时允许借阅|\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n", BorderLeft);
    printf("\n\t\t");

    chooseNumber = ChooseVerify(1, 1);
    fflush(stdin);
    switch(chooseNumber)
    {
    case 0:
        MainMenu();
        break;
    case 1:
    {
        printf("\n\t%c 请输入想要查询的书号：", BorderLeft);
        gets(searcherStr);
        for(k = 0; k < BookNum; k++)
        {
            if(StringMatch(BOOK[k].bookNum, searcherStr) == 1)
            {
                bookLendNum = k;
                resultNumber++;
                BookPrintf(k);
            }
        }
    }
    break;
    }
    printf("\n\t%c 共查询到%d 本书。", BorderLeft, resultNumber);
    printf("\n\t%c |(请精确查找，查找结果为一本书时允许借阅)", BorderLeft);
    if(resultNumber == 1)
    {
        printf("\n\t%c 是否借阅《%s》？(0 取消| 1 确认)：\n", BorderLeft, BOOK[bookLendNum].bookName);
        chooseNumber = ChooseVerify(0, 1);
        if(chooseNumber == 0)   // 取消
        {
            BookLend(); // 返回图书借阅函数
            return;
        }
        else if(chooseNumber == 1)     // 允许用户借阅这本书
        {
            int lendFlag = 0;
            for(i = 0; i < LendNum; i++)
            {
                if(strcmp(LEND[i].userName, userCookie.username) == 0 && strcmp(LEND[i].bookNum, BOOK[bookLendNum].bookNum) == 0)
                    lendFlag = 1;
            }
            if(lendFlag == 1)
            {
                printf("\n\t%c 你已经借阅了这本书。\n", BorderLeft);
            }
            else
            {
                // 获取时间
                time_t t;
                struct tm * lt;
                char timeStr[55];
                time (&t);//获取Unix时间戳。
                lt = localtime (&t);//转为时间结构。
                timeStr[0] = (lt->tm_year+1900)/1000 + '0';
                timeStr[1] = (lt->tm_year+1900)/100%10 + '0';
                timeStr[2] = (lt->tm_year+1900)/10%10 + '0';
                timeStr[3] = (lt->tm_year+1900)%10 + '0';
                timeStr[4] = timeStr[7] = '-';
                timeStr[5] = (lt->tm_mon+1)/10 + '0';
                timeStr[6] = (lt->tm_mon+1)%10 + '0';
                timeStr[8] = (lt->tm_mday)/10 + '0';
                timeStr[9] = (lt->tm_mday)%10 + '0';
                timeStr[10] = '\0';
                strcpy(LEND[LendNum].startTime, timeStr);
                // 写入文件
                FILE *fp = NULL; // 打开文件 booklend.txt
                fp = fopen("booklend.txt", "a+");
                fputs(userCookie.username, fp);
                fputs("\n", fp);
                fputs(BOOK[bookLendNum].bookNum, fp);
                fputs("\n", fp);
                fputs(timeStr, fp);
                fputs("\n", fp);
                fclose(fp); // 关闭文件
                // 保存到结构体数组
                strcpy(LEND[LendNum].userName, userCookie.username);
                strcpy(LEND[LendNum].bookNum, BOOK[bookLendNum].bookNum);
                LendNum++;

                printf("\n\t%c 借阅成功！  借阅时间：%d-%d-%d %d:%d:%d", BorderLeft, lt->tm_year+1900, lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
                printf("\n\t\t");
            }
        }

    }
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n");

    printf("\n\t%c 是否继续？(0 退出| 1 借阅)：", BorderLeft);
    chooseNumber = ChooseVerify(0, 1);
    if(chooseNumber == 0)   // 退出
    {
        MainMenu(); // 返回主菜单
    }
    else if(chooseNumber == 1)     // 继续借阅
    {
        BookLend(); // 回调函数
        return;
    }
    return;
}

void BookLendStatus() // 图书借阅状态
{
    SystemOp("cls");
    int chooseNumber, lendNumber;
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));

    lendNumber = 0;
    for(i = 0; i < LendNum; i++)
    {
        if(strcmp(LEND[i].userName, userCookie.username) == 0)
            lendNumber++;
    }

    printf("\n\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c\t", BorderLeft, BorderLeft);
    printf("\t#图书借阅状态# \t\t|\n");
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n\n", BorderLeft);
    printf("已借阅图书：%d\n", lendNumber);
    for( i = 0; i < WIDTH+WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n| 书号\t书名\t\t作者\t\t出版社\t出版时间\t\t价格\n");
    // 获取时间
    time_t t;
    struct tm * lt;
    char timeStr[55];
    time (&t);//获取Unix时间戳。
    lt = localtime (&t);//转为时间结构。
    timeStr[0] = (lt->tm_year+1900)/1000 + '0';
    timeStr[1] = (lt->tm_year+1900)/100%10 + '0';
    timeStr[2] = (lt->tm_year+1900)/10%10 + '0';
    timeStr[3] = (lt->tm_year+1900)%10 + '0';
    timeStr[4] = timeStr[7] = '-';
    timeStr[5] = (lt->tm_mon+1)/10 + '0';
    timeStr[6] = (lt->tm_mon+1)%10 + '0';
    timeStr[8] = (lt->tm_mday)/10 + '0';
    timeStr[9] = (lt->tm_mday)%10 + '0';
    timeStr[10] = '\0';
    for(i = 0; i < LendNum; i++)
    {
        if(strcmp(LEND[i].userName, userCookie.username) == 0)
        {
            for(j = 0; j < BookNum; j++)
            {
                if(strcmp(LEND[i].bookNum, BOOK[j].bookNum) == 0)
                {
                    printf("| %s\t", BOOK[j].bookNum);
                    printf("%s\t", BOOK[j].bookName);
                    printf("%s\t", BOOK[j].author);
                    printf("%s\t", BOOK[j].publishingHouse);
                    printf("%s\t", BOOK[j].publicshingTime);
                    printf("%s\t", BOOK[j].bookPrice);
                    puts(timeStr);
                    printf("*%c*", LEND[i].startTime[9]);
                    LEND[i].startTime[10] = '\0';
                    int time1 = Timestamp(timeStr);
                    int time2 = Timestamp(LEND[i].startTime);
                    printf("\n<-已借阅：%d天->", time1- time2);
                }

            }
        }
    }
    printf("\n");
    for( i = 0; i < WIDTH+WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n ESC键返回主菜单");
    chooseNumber = ChooseVerify(0, 0);
    if(chooseNumber == 0) // 返回主菜单
    {
        MainMenu();
        return;
    }
    return;
}

void BookReturn() // 图书归还
{
    SystemOp("cls");
    int chooseNumber, lendNumber;
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));

    lendNumber = 0;
    for(i = 0; i < LendNum; i++)
    {
        if(strcmp(LEND[i].userName, userCookie.username) == 0)
            lendNumber++;
    }

    printf("\n\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c\t", BorderLeft, BorderLeft);
    printf("\t#图书归还系统# \t|\n");
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n\n", BorderLeft);
    printf("已借阅图书：%d\n", lendNumber);
    for( i = 0; i < WIDTH+WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n| 书号\t书名\t\t作者\t\t出版社\t出版时间\t\t价格\n");
    for(i = 0; i < LendNum; i++)
    {
        for(j = 0; j < BookNum; j++)
        {
            printf("| %s\t", BOOK[j].bookNum);
            printf("%s\t", BOOK[j].bookName);
            printf("%s\t", BOOK[j].author);
            printf("%s\t", BOOK[j].publishingHouse);
            printf("%s\t", BOOK[j].publicshingTime);
            printf("%s\t", BOOK[j].bookPrice);
        }
    }
    printf("\n");
    for( i = 0; i < WIDTH+WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n ESC键返回主菜单");
    chooseNumber = ChooseVerify(0, 0);
    if(chooseNumber == 0) // 返回主菜单
    {
        MainMenu();
        return;
    }
    return;
}

/// 功能函数模块
char RandomNumber(char str[], int n) // 返回随机数函数
{
    int randomChar;

    srand(time(NULL));
    randomChar = str[rand()%n];

    return randomChar;
}

int ChooseVerify(int minNumber, int maxNumber) // 选择验证函数（!）
{
    int chooseNumber;
    char inputChar;
    printf("\n\t\t输入您的选择: ");

    inputChar = getch();
    if(inputChar == 27)
    {
        return 0;
    }
    else if(inputChar == 9)
    {
        BackgroundColor();
        printf("(背景色切换成功\1)");
        return ChooseVerify(minNumber, maxNumber);
    }
    else
    {
        chooseNumber = inputChar - '0';
    }
    if( chooseNumber >= minNumber && chooseNumber <= maxNumber )
    {
        printf(" %d", chooseNumber);
    }
    else
    {
        printf("\tInput Error!\n");
        chooseNumber = ChooseVerify(minNumber, maxNumber);
    }
    return chooseNumber;
}

void loginVerify(char username[]) // 登录验证函数
{
    int status;
    char password[55];

    printf("\t\t\t请输入密码 :  ");
    char tempPassword[20]= {};
    tempPassword[0]=getch();
    if (tempPassword[0]==27)
    {
        // ESC 键返回主页，return
        index();
        return;
    }
    else
    {
        printf("%c", tempPassword[0]);
    }

    scanf("%s", password);
    strcat(tempPassword, password);
    strcpy(password, tempPassword);

    if(strcmp(username, "admin") == 0)   // 管理员登录
    {
        if(strcmp(password, "admin") == 0)
        {
            status = 200;

            // 创建cookie
            strcpy(userCookie.username, "admin");
        }
        else
        {
            status = 400;

            printf("\t\t \t密码错误，登录失败。请重试\n");
            loginVerify(username);
        }
    }
    else     // 借阅者登录
    {
        for(i = 0; i < UserNum; i++)
        {
            if(strcmp(username, USER[i].username) == 0)
            {
                if(strcmp(password, USER[i].password) == 0)   // 密码正确
                {
                    if(USER[i].status == 0)   // 未经管理员通过
                    {
                        status = 403; // 权限不够禁止访问
                        printf("\t\t \t请等待管理员同意用户注册!\n");
                        loginVerify(username);
                        return;
                    }
                    else
                    {
                        status = 200; // 没有问题

                        // 创建cookie
                        strcpy(userCookie.username, username);
                        // 录入信息
                        strcpy(CurrentUser.username, USER[i].username);
                        strcpy(CurrentUser.password, USER[i].password);
                        strcpy(CurrentUser.age, USER[i].age);
                        strcpy(CurrentUser.contact, USER[i].contact);
                        strcpy(CurrentUser.sex, USER[i].sex);
                        CurrentUser.status = USER[i].status;

                        return;
                    }
                }
                else
                {
                    status = 400; // 密码错误

                    printf("\t\t \t密码错误，登录失败。请重试\n");
                    loginVerify(username);
                    return;
                }
            }
        }
        if(status != 200 || status != 400)
        {
            status = 404; // 找不到
            printf("\t\t \t用户不存在，登录失败。请按ESC键返回注册\n");
            loginVerify(username);
            return;
        }
    }
}

void BackgroundColor() // 背景色函数
{
    char COLOR[20] = {};
    char randomColor;
    char colorString[20] = "color 00";
    for(i = 0; i < 16; i++)
    {
        if(i < 10)
        {
            COLOR[i] = i + '0';
        }
        else
        {
            COLOR[i] = i - 10 + 'a';
        }
    }
    randomColor =  RandomNumber(COLOR, sizeof(COLOR)/sizeof(COLOR[0]));
    colorString[6] = randomColor;
    SystemOp(colorString);
}

void SystemOp(char str[]) // 控制台操作函数
{
    system(str);
}

int StringMatch(char pStr[], char qStr[]) // 字符串模糊匹配函数
{
    int flag = 0; // 初始化flag;
    int pLen = strlen(pStr), qLen = strlen(qStr);
    if(pLen < qLen)   // 确保pStr长度大于qStr
    {
        return 0;
    }
    for(i = 0; i <= pLen-qLen; i++)
    {
        if(pStr[i] == qStr[0])
        {
            flag = 1;
            for(j = 0; j < qLen; j++)
            {
                if(pStr[i+j] != qStr[j])
                    flag = 0;
            }
        }
    }
    return flag;
}

void BookPrintf(int id) // 图书信息输出函数
{
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));
    printf("\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c\t书号：%s \t\t%c\n", BorderLeft, BorderLeft, BOOK[id].bookNum, BorderLeft);
    printf("\t\t%c\t书名：%s \t\t%c\n", BorderLeft, BOOK[id].bookName, BorderLeft);
    printf("\t\t%c\t作者：%s \t\t%c\n", BorderLeft, BOOK[id].author, BorderLeft);
    printf("\t\t%c\t出版社：%s \t\t%c\n", BorderLeft, BOOK[id].publishingHouse, BorderLeft);
    printf("\t\t%c\t出版时间：%s \t\t%c\n", BorderLeft, BOOK[id].publicshingTime, BorderLeft);
    printf("\t\t%c\t价格：%s \t\t\t%c\n",BorderLeft, BOOK[id].bookPrice, BorderLeft);
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n", BorderLeft);
}

long Timestamp(char time[]) // 简易时间戳函数
{
    /* 输入YYYY-mm-dd格式日期字符串2019-07-03
     * 转化成简易时间戳
     * 便于时间之间比较
     */
    int year, month, day;
    long timestamp = 0;
    int mday; // 2月是否闰月
    int months[13]= {0,31,28,31,30,31,30,31,31,30,31,30,31};
    // 转化成整型数据
    year = (time[0]-'0')*1000 + (time[1]-'0')*100 + (time[2]-'0')*10 + (time[3]-'0');
    month = (time[5]-'0')*10 + (time[6]-'0');
    day = (time[8]-'0')*10 + (time[9]-'0');
    // 转化为时间戳,以1800-01-01为基准
    for(i = 1800; i < year; i++)
    {
        if((i%4==0 && i%100!=0) ||i %400==0)
            timestamp += 366;
        else
            timestamp += 365;
    }
    if((year%4==0 && year%100!=0) || year%400==0)
        mday = 29;
    else
        mday = 28;
    months[2] = mday;
    for(i = 1; i < month; i++)
    {
        timestamp += months[i];
    }
    timestamp += day;

    return timestamp;
}
