#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <memory.h>

struct cookie   // ���浱ǰ�û���½��Ϣ
{
    char username[55];
};
struct userinfo   // ���������û�������Ϣ
{
    char username[55], password[55];
    char age[10];
    int status; // ״̬1:�˺�ע��ɹ��� 0:�˺Ŵ�ͨ��
    char sex[10]; // male or female
    char contact[55];
};
struct bookinfo // ��������ͼ����Ϣ
{
    char bookNum[55], bookName[55], author[55]; // ��ţ�������������
    char publishingHouse[55], publicshingTime[55]; // �����磬����ʱ��
    char bookPrice[55]; // ����ļ۸�
};
int WIDTH = 41; // �û�������
int OpWidth = 12; // �û��������
int UserNum = 0, BookNum = 0; // �û�����, ͼ������
int i, j, k; // ��ǰ����ѭ������
char BORDER[] = { '#', '*', '+', '@', '`', '-', '='}; // �߿�����ַ�
char OpLine = '-', BorderLeft = '|';
typedef struct cookie COOKIE;
typedef struct userinfo USERINFO;
typedef struct bookinfo BOOKINFO;
COOKIE userCookie; // ��¼��Ϣ
USERINFO USER[5000], CurrentUser; // �û���Ϣ�ṹ������
BOOKINFO BOOK[5000]; // ͼ����Ϣ�ṹ������

char RandomNumber(char str[], int n); // �������������
int ChooseVerify(int minNumber, int maxNumber); // ѡ����֤����
void loginVerify(char username[]); // ��¼��֤����
void BackgroundColor(); // ����ɫ����
void SystemOp(char str[]); // ����̨��������

void index(); // ��ҳ����
void login(); // ��¼����
void UserRegister();// �û�ע�ắ��
void MainMenu(); // ���˵�����
/* ͼ�����ϵͳ��ģ�� */
void InformationEntry(); // ͼ����Ϣ¼�뺯��
void InformationBrowsing(); // ͼ����Ϣ�������
void InformationInquiry(); // ͼ����Ϣ��ѯ����
void InformationDelete(); // ͼ����Ϣɾ������
void InformationModify(); // ͼ����Ϣ�޸ĺ���


int main()
{
    // ʵ���������ɫ
    BackgroundColor();
    // ʵ���û����߹���Ա��¼
    index();
    // �������˵�
    MainMenu();
    return 0;
}

/// ��ҳ
void index()
{
    SystemOp("cls");
    int chooseNumber;
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));

    printf("ESC���˳�ϵͳ / Tab���л�����ɫ\n");
    printf("\n\n\n\t\t\t\t��ӭ����ͼ��ݣ�\n\n");
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
    printf("����Ա��¼ \t|\n");
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    printf("\t%c", '2');
    for( i = 0; i < OpWidth; i++ )
        printf("%c", OpLine);
    printf("�����ߵ�¼ \t|\n");
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

/// ��¼����������Ա��¼���û���¼�� �û���ע���ֱ�ӵ�¼��
void login(int chooseNumber)
{
    SystemOp("cls");
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));
    int backStatus, userChooseNumber, fileFlag, fileNum;
    char fileStr[55], username[55];

    // ���ļ���ȡ���ݣ����浽�ṹ����
    FILE *fp = NULL;
    fp = fopen("userinfo.txt", "a+");
    fileFlag = 0, fileNum = 0;
    while(!feof(fp))
    {
        if(fgets(fileStr, 55, fp)!=NULL)
        {
            fileStr[strlen(fileStr)-1]='\0'; // ȥ���ַ���ĩβ\n
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

    printf("\n\n\n\t\t\t\t���¼|ͼ��ݣ�\n\n");
    printf("\t\tESC��������ҳ->\n\t\t");
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
        // ����Ա��¼
        printf("\t����Ա :\tadmin\t\t%c\n", BorderLeft);
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
    case 2:   // �����ߵ�¼
    {
        printf("\t�����ߵ�¼\t\t\t%c\n", BorderLeft);
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '1');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("���û�ע�� \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '2');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("ֱ�ӵ�½\t \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf("%c", borderChar);
        printf("%c\n", BorderLeft);

        userChooseNumber = ChooseVerify(1, 2);

        if(userChooseNumber == 1)   // ���û�ע��
        {
            // ע�ắ��
            UserRegister();
        }
        else if(userChooseNumber == 2)     // ֱ�ӵ�½
        {
            printf("\n\n\t\t");
            for( i = 0; i < WIDTH; i++ )
                printf("%c", borderChar);
            printf("\n\t\t\t����û�����");
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

/// �û�ע�ắ�����������û�ע�ᣬָ���ļ�userinfo.txt��
void UserRegister()
{
    SystemOp("cls");
    int usernameFlag = 0;
    char Password[55], rePassword[55];
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));
    USERINFO newUser; // �������û�
    FILE *fp = NULL; // ���ļ� userinfo.txt
    fp = fopen("userinfo.txt", "a+");

    printf("\n\n\n\t\t\t   ���û�ע�� | ͼ���\n\n");
    printf("\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    printf("\t�û��� ��");
    gets(newUser.username);
    // ��֤�û����Ƿ��ظ�
    while(usernameFlag == 0)
    {
        usernameFlag = 1; // ��ʼ��flag
        for(i = 0; i < UserNum; i++)
        {
            if(strcmp(USER[i].username, newUser.username) == 0)
            {
                usernameFlag = 0;
            }
        }
        if(usernameFlag == 0)   // ��ʾ�û����ظ�
        {
            printf("\t\t%c\t�û����ظ������������룺\n");
            printf("\t\t%c\t�û��� ��", BorderLeft);
            gets(newUser.username);
        }
        else
        {
            break;
        }
    }
    printf("\t\t%c\t���� ��", BorderLeft);
    gets(Password);
    printf("\t\t%c\t�ظ����� ��", BorderLeft);
    gets(rePassword);
    // ��֤�����Ƿ�һ��
    while(strcmp(Password, rePassword) != 0)
    {
        printf("\t\t%c\t���벻һ�£����������룺\n");
        printf("\t\t%c\t���� ��", BorderLeft);
        gets(Password);
        printf("\t\t%c\t�ظ����� ��", BorderLeft);
        gets(rePassword);
    }
    // ����һ��
    strcpy(newUser.password, Password);
    printf("\t\t%c\t���� ��", BorderLeft);
    gets(newUser.age);
    printf("\t\t%c\t�Ա�(male or female) ��", BorderLeft);
    gets(newUser.sex);
    printf("\t\t%c\t��ϵ��ʽ ��", BorderLeft);
    gets(newUser.contact);


    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    printf("\tע��ɹ�����ESC�����أ� \t|\n");
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n", BorderLeft);

    newUser.status = 0; // ��ʾ�����Աͬ���ʹ��

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

    fclose(fp); // �ر��ļ�

    if(getch() == 27)
    {
        login(2);
    }
    return;
}

/// ���˵�������ͼ�����ϵͳ�˵� �� ͼ�����ϵͳ�˵���
void MainMenu()
{
    SystemOp("cls");
    int chooseNumber, fileFlag, fileNum;
    char fileStr[55];
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));
    printf("��ӭ�㣬%s��\n", userCookie.username);

    // ���ļ���ȡ���ݣ����浽�ṹ����
    FILE *fp = NULL;
    fp = fopen("bookinfo.txt", "a+");
    fileFlag = 0, fileNum = 0;
    while(!feof(fp))
    {
        if(fgets(fileStr, 55, fp)!=NULL)
        {
            fileStr[strlen(fileStr)-1]='\0'; // ȥ���ַ���ĩβ\n
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

    if(strcmp(userCookie.username, "admin") == 0)   // ����Ա��¼״̬
    {
        printf("\n\n\n\t\t\t\tͼ����Ϣ����ϵͳ\n\n");
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
        printf("ͼ����Ϣ¼�� \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '2');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("ͼ����Ϣ��� \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '3');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("ͼ����Ϣ��ѯ \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '4');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("ͼ����Ϣɾ�� \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '5');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("ͼ����Ϣ�޸� \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%s", "ESC");
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("�˳� \t\t|\n");
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
            break; // �˳�ϵͳ�����cookie,������ҳ
        case 1:
            InformationEntry();
            break; // ��Ϣ¼��
        case 2:
            InformationBrowsing();
            break; // ��Ϣ���
        case 3:
            InformationInquiry();
            break; // ��Ϣ��ѯ
        case 4:
            InformationDelete();
            break; // ��Ϣɾ��
        case 5:
            InformationModify();
            break; // ��Ϣ�޸�
        }
    }
    else     // �����ߵ�¼״̬
    {
        printf("\n\n\n\t\t\t\tͼ��ݽ���ϵͳ\n\n");
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
        printf("����ͼ�� \t\t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '2');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("����ͼ�� \t\t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '3');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("ͼ�����״̬ \t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%c", '4');
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("ͼ��黹 \t\t|\n");
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        printf("\t%s", "ESC");
        for( i = 0; i < OpWidth; i++ )
            printf("%c", OpLine);
        printf("�˳� \t\t|\n");
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

/// ͼ�����ϵͳ��ģ�飨¼�롢�������ѯ��ɾ�����޸ģ�
void InformationEntry() // ͼ����Ϣ¼�뺯��
{
    SystemOp("cls");
    fflush(stdin);
    int chooseNumber;
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));

    BOOKINFO NewBook; // �����µ�ͼ����Ϣ
    FILE *fp = NULL; // ���ļ� bookinfo.txt
    fp = fopen("bookinfo.txt", "a+");

    printf("\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c\t\tͼ����Ϣ¼�� \t\t%c\n", BorderLeft, BorderLeft, BorderLeft);
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);

    printf("%c\n\t\t%c\t�����������鼮����ţ�", BorderLeft, BorderLeft);
    gets(NewBook.bookNum);
    printf("\t\t%c\t������������", BorderLeft);
    gets(NewBook.bookName);
    printf("\t\t%c\t��������������", BorderLeft);
    gets(NewBook.author);
    printf("\t\t%c\t����������磺", BorderLeft);
    gets(NewBook.publishingHouse);
    printf("\t\t%c\t���������ʱ�䣺", BorderLeft);
    gets(NewBook.publicshingTime);
    printf("\t\t%c\t���������ļ۸�", BorderLeft);
    gets(NewBook.bookPrice);
    printf("\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n", BorderLeft);

    // ͼ����Ϣ¼���ļ�
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

    fclose(fp); // �ر��ļ�

    printf("\t\t��%s����Ϣ¼����ɣ��Ƿ����¼��?(0 �˳�| 1 ����)", NewBook.bookName);

    chooseNumber = ChooseVerify(0, 1);
    switch(chooseNumber)
    {
    case 0:
        MainMenu();
        break; // �˳�
    case 1:
        InformationEntry();
        break; // ����
    }
    return;
}

void InformationBrowsing() // ͼ����Ϣ�������
{
    SystemOp("cls");
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));

    printf("\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c\t  ***ͼ����Ϣ���*** \t\t%c\n", BorderLeft, BorderLeft, BorderLeft);
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n", BorderLeft);

    // ������е�ͼ����Ϣ
    for(j = 0; j < BookNum; j++)
    {
        printf("\n\t\t");
        for( i = 0; i < WIDTH; i++ )
            printf("%c", borderChar);
        printf("\n\t\t%cid:%03d%c", BorderLeft, j+1, BorderLeft);
        for( i = 0; i < WIDTH-9; i++ )
            printf(" ");
        printf("%c\n\t\t%c\t��ţ�%s \t\t%c\n", BorderLeft, BorderLeft, BOOK[j].bookNum, BorderLeft);
        printf("\t\t%c\t������%s \t\t%c\n", BorderLeft, BOOK[j].bookName, BorderLeft);
        printf("\t\t%c\t���ߣ�%s \t\t%c\n", BorderLeft, BOOK[j].author, BorderLeft);
        printf("\t\t%c\t�����磺%s \t\t%c\n", BorderLeft, BOOK[j].publishingHouse, BorderLeft);
        printf("\t\t%c\t����ʱ�䣺%s \t\t%c\n", BorderLeft, BOOK[j].publicshingTime, BorderLeft);
        printf("\t\t%c\t�۸�%s \t\t\t%c\n",BorderLeft, BOOK[j].bookPrice, BorderLeft);
        printf("\t\t%c", BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf(" ");
        printf("%c\n\t\t%c", BorderLeft, BorderLeft);
        for( i = 0; i < WIDTH-2; i++ )
            printf("%c", borderChar);
        printf("%c\n", BorderLeft);
    }
    printf("\t\t��ESC�����أ�");
    int chooseNumber = ChooseVerify(0, 0);
    if(chooseNumber == 0) {
        MainMenu(); // �������˵�����
    }
}

void InformationInquiry() // ͼ����Ϣ��ѯ����
{
    SystemOp("cls");
    char borderChar = RandomNumber(BORDER, sizeof(BORDER)/sizeof(BORDER[0]));

    printf("\n\t\t");
    for( i = 0; i < WIDTH; i++ )
        printf("%c", borderChar);
    printf("\n\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c\t  ***ͼ����Ϣ��ѯ*** \t\t%c\n", BorderLeft, BorderLeft, BorderLeft);
    printf("\t\t%c", BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf(" ");
    printf("%c\n\t\t%c", BorderLeft, BorderLeft);
    for( i = 0; i < WIDTH-2; i++ )
        printf("%c", borderChar);
    printf("%c\n", BorderLeft);
}

void InformationDelete() // ͼ����Ϣɾ������
{

}

void InformationModify() // ͼ����Ϣ�޸ĺ���
{

}

/// ���ú���ģ��
char RandomNumber(char str[], int n) // �������������
{
    int randomChar;

    srand(time(NULL));
    randomChar = str[rand()%n];

    return randomChar;
}

int ChooseVerify(int minNumber, int maxNumber) // ѡ����֤������!��
{
    int chooseNumber;
    char inputChar;
    printf("\n\t\tPlease Enter Choose: ");

    inputChar = getch();
    if(inputChar == 27)
    {
        return 0;
    }
    else if(inputChar == 9)
    {
        BackgroundColor();
        printf("(����ɫ�л��ɹ�\1)");
        return ChooseVerify(minNumber, maxNumber);
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

void loginVerify(char username[]) // ��¼��֤����
{
    int status;
    char password[55];

    printf("\t\t\t���������� :  ", BorderLeft);
    char tempPassword[20]= {};
    tempPassword[0]=getch();
    if (tempPassword[0]==27)
    {
        // ESC ��������ҳ��return
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

    if(strcmp(username, "admin") == 0)   // ����Ա��¼
    {
        if(strcmp(password, "admin") == 0)
        {
            status = 200;

            // ����cookie
            strcpy(userCookie.username, "admin");
        }
        else
        {
            status = 400;

            printf("\t\t \t������󣬵�¼ʧ�ܡ�������\n");
            loginVerify(username);
        }
    }
    else     // �����ߵ�¼
    {
        for(i = 0; i < UserNum; i++)
        {
            if(strcmp(username, USER[i].username) == 0)
            {
                if(strcmp(password, USER[i].password) == 0)   // ������ȷ
                {
                    if(USER[i].status == 0)   // δ������Աͨ��
                    {
                        status = 403; // Ȩ�޲�����ֹ����
                        printf("\t\t \t��ȴ�����Աͬ���û�ע��!\n");
                        loginVerify(username);
                        return;
                    }
                    else
                    {
                        status = 200; // û������

                        // ����cookie
                        strcpy(userCookie.username, username);
                        // ¼����Ϣ
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
                    status = 400; // �������

                    printf("\t\t \t������󣬵�¼ʧ�ܡ�������\n");
                    loginVerify(username);
                    return;
                }
            }
        }
        if(status != 200 || status != 400)
        {
            status = 404; // �Ҳ���
            printf("\t\t \t�û������ڣ���¼ʧ�ܡ��밴ESC������ע��\n");
            loginVerify(username);
            return;
        }
    }
}

void BackgroundColor() // ����ɫ����
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

void SystemOp(char str[]) // ����̨��������
{
    system(str);
}
