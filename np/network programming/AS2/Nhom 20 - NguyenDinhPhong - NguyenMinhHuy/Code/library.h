#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//thu vien Btree
#include"bc.h"         //tep khai bao ten cac ham cua Btree
#include"bt.h"
#include"btree.h"

#define BACKLOG 3 //maximum client

int allControl[BACKLOG];   //kiem soat clientID nao ket noi toi
int player_ing;
int role_ans[BACKLOG];

#define PLAY 2
#define REGISTER 1
#define EXIT 0

#define PLAYING 1
#define DONE -1

#define SUCCESS 5
#define FAILED -1


#define FOUND 4
#define WRONG_PASS -3
#define NOT_FOUND -7

#define YES 1
#define NO -6

#define LIMITED 3
#define EMPTINESS -5

//struct account
typedef struct account
{
	char user[50];
	char pass[50];
}account;

typedef struct step
{
    int position;
    char way;
}step;

// struct cau hoi
typedef struct question_{
    int IDQuestion;
    char ques[100];
    char ans1[100];
    char ans2[100];
    char ans3[100];
    char ans4[100];
    int ans;
} question;

question quesArr[15];


//struct data
typedef struct data
{
	int flag;		// flag = 0 : play , flag = 1 : login,
					//flag =3 : dang ki; flag = 4 faile; flag = 5 success
	step play;
	account object;
	char message[100];
	int result;
	int role;
	question document;
}data;

//doc file cau hoi
int readQues( char *fileName);

//search account by user, return 1 = ok, 0 = not exist
int searchAccount(account object);

//add new account
void addAccount(account object);

int searchSocket(int socketID);
void clearSocketData(int socketID);
int isLimited(void);
void creatSocketData(int socketID);

void 	initMemory();
#endif // LIBRARY_H_INCLUDED
