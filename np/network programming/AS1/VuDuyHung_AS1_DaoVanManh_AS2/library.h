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

#define BACKLOG 5 //maximum client

#define CAPACITY_GAME 14	// array of game

int all[BACKLOG][CAPACITY_GAME];
int allControl[BACKLOG];   //kiem soat clientID nao ket noi toi
FILE *logArray[BACKLOG];
char fileName[BACKLOG][100];

//#define PLAY 0
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

#define QUIT_GAME 10

#define SEND_LOG 11
//#define XPLAY 1;


//struct account
typedef struct account
{
	char user[50];
	char pass[50];
}account;

//struct nuoc choi
typedef struct step
{
    int position;      // position : 1->11
    char way;            // l = left or r = right
}step;

//struct data
typedef struct data
{
	int flag;		// flag = 0 : play , flag = 1 : login, flag = 2 : truyen file log,
					//flag =3 : dang ki; flag = 4 faile; flag = 5 success
	step play;
	account object;
	char message[100];
}data;

// khoi tao file log
void initFileLog(int socketIndex, data buf, char *address_client);

//in so do ban choi
void printMap(int *info);

//ghi so do ban choi vao log
void fprintMap(int *info, FILE *fp);

//lua chon nuoc choi
step choice(int *info);

//may tinh dua ra nuoc choi
step calculator(int *info);

//du doan so quan an duoc
int predict(int *info,step tmp);

//thuc hien nuoc di
int play(int *info,step tmp);
//return so quan an duoc

//kiem tra xem co an duoc o trong tiep theo ko
int checkContinue(int *info, step tmp);

//ghi file log
void logGame(int socketIndex, step tmp);

//quit game
void quitGame(int *info, FILE *fp);

//check exit game
int checkExit(int socketIndex);
// reutrn 0= not exit, 1 = exit

//search account by user, return 1 = ok, 0 = not exist
int searchAccount(account object);

//add new account
void addAccount(account object);
//clear buffer
//void clear(void);

int searchSocket(int socketID);
void clearSocketData(int socketID);
int isLimited(void);
void creatSocketData(int socketID);

void 	initMemory();
#endif // LIBRARY_H_INCLUDED
