#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <memory.h>

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

int WIDTH = 41; // 用户界面宽度
int OpWidth = 12; // 用户操作宽度
int UserNum = 0; // 用户总数
int i, j, k;
char BORDER[] = { '#', '*', '+', '@', '`', '-', '='}; // 边框随机字符
char OpLine = '-', BorderLeft = '|';
typedef struct cookie COOKIE;
typedef struct userinfo USERINFO;
COOKIE userCookie; // 登录信息
USERINFO USER[5000], CurrentUser; // 用户信息结构体数组

char RandomNumber(char str[], int n); // 返回随机数函数
int ChooseVerify(int minNumber, int maxNumber); // 选择验证函数
void loginVerify(char username[]); // 登录验证函数
void BackgroundColor(); // 背景色函数
void SystemOp(char str[]); // 控制台操作函数

void index(); // 主页函数
void login(); // 登录函数
void UserRegister();// 用户注册函数
void MainMenu(); // 主菜单函数


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

    printf("ESC键退出系统\n");
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

    return;
}

/// 登录函数
void login(int chooseNumber)
{
    SystemOp("cls");
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));
    int backStatus, userChooseNumber, fileFlag, fileNum;
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
    return;
}

/// 用户注册函数
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
            printf("\t\t%c\t用户名重复，请重新输入：\n");
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
        printf("\t\t%c\t密码不一致，请重新输入：\n");
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

/// 主菜单函数
void MainMenu()
{
    SystemOp("cls");
    int chooseNumber;
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));
    printf("欢迎你，%s！\n", userCookie.username);

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
            case 0: memset(&userCookie, 0, sizeof(COOKIE)); index(); break; // 退出系统，清除cookie,返回主页
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
    }
}

/// 配置函数
char RandomNumber(char str[], int n) // 返回随机数函数
{
    int randomChar;

    srand(time(NULL));
    randomChar = str[rand()%n];

    return randomChar;
}

int ChooseVerify(int minNumber, int maxNumber) // 选择验证函数
{
    int chooseNumber;
    char inputChar;
    printf("\n\t\tPlease Enter Choose: ");

    inputChar = getch();
    if(inputChar == 27)
    {
        return 0;
    }
    else
    {
        chooseNumber = inputChar - '0';
    }
    if( chooseNumber >= minNumber && chooseNumber <= maxNumber )
    {
        printf("\t\t Input Success.");
    }
    else
    {
        printf("\t\t Input Error!\n");
        chooseNumber = ChooseVerify(minNumber, maxNumber);
    }
    return chooseNumber;
}

void loginVerify(char username[]) // 登录验证函数
{
    int status;
    char password[55];

    printf("\t\t\t请输入密码 :  ", BorderLeft);
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
    return;
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
