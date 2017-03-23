#include "stdafx.h"
#include <iostream>
#include "NJU.h"
#include "Wait.h"
#define passwd 10
using namespace std;

char *info_file_loc = "data\\info.nju";
char *user_file_loc = "data\\user.nju";
char *pw_file_loc  = "data\\pw.nju";
extern char new_username[MAX_ID_LENGTH];
extern char new_password[MAX_PASSWORD_LENGTH];
extern status *new_status;
/*控制台测试函数*/
/*int main()
{
	int choice = 1;
	if (choice == 1) {
		read_info();
		login();
		status *p = (status *)malloc(sizeof(status));
		read_status(p);
		free(p);
	}
	else if (choice == 0)
		logout();
	return 0;
}*/

/*文档是否为空*/
bool file_is_empty(char *filename)
{
	FILE *fp;
	char ch;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		exit(0);
	}
	ch = fgetc(fp);
	if (ch == EOF)
		return true;
	else
		return false;
}

/*登录系统*/
void login()
{
	WinExec("data\\login.exe", SW_HIDE);
}

/*登出系统*/
void logout()
{
	WinExec("data\\logout.exe", SW_HIDE);
}

/*更新用户后，修改用户名和密码*/
void save_user()
{
	fstream file(user_file_loc, ios::out);
	fstream file2(pw_file_loc, ios::out);
	fstream fp;
	fp.open(user_file_loc, fstream::in | fstream::out | fstream::app);
	fp << new_username << "\n";
	fp.close();

	fp.open(pw_file_loc, fstream::in | fstream::out | fstream::app);
	fp << new_password << "\n";
	fp.close();
	/*
	for (unsigned i = 0; i < strlen(new_password); ++i)
		fp << (char)(new_password[i] - (char)passwd);
	fp << "\n";
	fp.close();
	*/
}

/*从username.txt以及password.txt读取数据到内存*/
void read_info(char *&username, char *&password)
{
	/*
	char *username = (char *)malloc(MAX_ID_LENGTH * sizeof(char));
	char *password = (char *)malloc(MAX_PASSWORD_LENGTH * sizeof(char));
	free(username);
	free(password);
	*/

	ifstream fp;
	fp.open(user_file_loc, ios::binary);
	string line;
	getline(fp, line);
	strcpy(username, line.c_str()); 
	fp.close();	

	ifstream fp2;
	fp2.open(pw_file_loc, ios::binary);
	string line2;
	getline(fp2, line2);
	strcpy(password, line2.c_str());
	fp2.close();
	/*
	for (unsigned i = 0; i < strlen(password) - 1; ++i)
		password[i] += (char)passwd;
	
	strcpy(new_password, password);
	strcpy(new_username, username);
	*/
}

/*读取登录后网页返回信息并写入结构体*/
void read_status(status *&p)
{
	ifstream fp;
	fp.open(info_file_loc, ios::binary);

	string line;
	int i = 0;
	while (getline(fp, line))
	{
		bool finish = 0;
		switch (i) {
		case 0: p->successful = atoi(line.c_str()); break;
		case 1: p->device_amounts = atoi(line.c_str()); break;
		case 2: p->account_balance = (float)atoi(line.c_str()) / (float)1000; break;
		case 3: strcpy(p->username, line.c_str()); break;
		case 4: finish = 1; break;
		}
		++i;
		if (finish)
			break;
	}
	int time = atoi(line.c_str());
	p->hours = time / 3600;
	p->mins = (time - p->hours * 3600) / 60;
	//cout << p->successful << endl << p->account_balance << endl << p->device_amounts << endl << p->username << endl << p->hours << endl << p->mins << endl;
}

//清空状态数据
void clean_status()
{
	new_status->successful = 0;
}