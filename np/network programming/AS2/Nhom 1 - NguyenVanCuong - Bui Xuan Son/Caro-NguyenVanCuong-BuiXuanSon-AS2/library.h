#ifndef _LIBRARY_H
#define _LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

#define MAXLINE 1000  // do dai toi da cua buffer
#define SERV_PORT 6789  // cong cua server
#define LISTENQ 20    // Queue for listening
#define ROOMSIZE 10
#define TABLESIZE 15
#define WINSIZE 5

// signal for game
#define SIGNAL_LOGIN            "login"
#define SIGNAL_LOGIN_OK         "login successful"
#define SIGNAL_REGISTER         "register"
#define SIGNAL_LOGIN_FALSE      "login false"
#define SIGNAL_START            "starting..."
#define SIGNAL_WAIT             "waitting..."
#define SIGNAL_GET_LIST_ROOM    "get list room"
#define SIGNAL_READY_PLAY       "ready play"
#define SIGNAL_QUIT             "quit"
#define SIGNAL_WIN              "you win!"
#define SIGNAL_LOOSE            "You loose"
#define SIGNAL_OUT_ROOM         "out room"
#define SIGNAL_GET_LOG_FILE     "get log file from server"
#define SIGNAL_OK               "ok"

//Color
#define BLACK  "\033[22;30m"
#define GREEN  "\033[22;31m"
#define RESET_COLOR "\e[m"
#define MAKE_GREEN "\e[32m"


/**
* Cau truc cho 1 phong choi
*/
typedef struct _player{
    int sockfd;
    int roomID;
    char mark; // O or X
    int wait; // 0 : isPlay, 1 : wait
}player;

typedef struct _room{
    player PlayerA ;
    player PlayerB ;
    int state;
    int table[TABLESIZE][TABLESIZE];
}room;
typedef struct _user{
    char username[100];
    char password[100];
}user;

/**
* Khoi tao ban choi. gan tat ca cac gia tri table[][] = 0
*/
void initTable(int table[TABLESIZE][TABLESIZE]);
/**
* Khoi tao phong choi gan cac gia tri mac dinh vao cac truong
*/
void initRoom(room *Room);
/**
* Lay ra 1 phong choi tu socket id
* Tra ve NULL neu ko tim thay phong choi tuong ung voi socket id
*/
room* getRoom(player Player[], int sockfd, room Room[]);
/**
* Kiem tra socket fd  trong 1 mang cac socket
*/
int checkIn(int *a, int fd);
/**
* Kiem tra xem da co user nao thang chua dua vao luat choi
*/
int checkWiner( int table[TABLESIZE][TABLESIZE], int xCross, int yCross, int flag);
/**
* thuc hien copy noi dung giua 2 table
*/
void copyTable( int A[TABLESIZE][TABLESIZE], int B[TABLESIZE][TABLESIZE]);
/**
* Thuc hien copy noi dung giua 2 phong choi
*/
void copyRoom(room *a, room *b);
/**
* Thuc hien copy giua 2 player
*/
void copyPlayer(player *A, player *B);
/**
* Doc file user.txt ghi vao 1 mang cac user
*/
int readFile(user *listUser);
/**
* So sanh giua 2 player xem co trung khop khong
*/
int compareUser(user u1, user u2);
/**
* Kiem tra dang nhap cua user
*/
int checkLogin(user *listUser,int n,  user u, char ListUsername[FD_SETSIZE][MAXLINE]);
/**
* Lay ra list cac phong trong, phong dang choi, phong dang cho.
*/
void getListRoomFree(room *Room, int *FullRoom, int *WaitingRoom, int *EmptyRoom);
/**
* Ma hoa noi dung cua danh sach cac phong choi. send cho user
*/
char * makeMessage(int *room);
/**
* Kiem tra su ton tai cua 1 player trong 1 list cac player
*/
int checkExistPlayer(player *Player, int sockfd);
/**
* Thuc hien in ra table tuong ung voi vi tri duoc nhap
*/
void drawTable(int table[TABLESIZE][TABLESIZE], int xCross, int yCross);
/**
* Danh dau vi tri duoc danh cua user vao table tuong ung.
*/
void signInTable(int table[TABLESIZE][TABLESIZE], char *message, int flag);
/**
* Kiem tra danh hop le
*/
int checkPlay(int table[TABLESIZE][TABLESIZE], char * message);
/**
* Ghi noi dung vao file log voi thong tin tuong ung
*/
void CreatFileLog( char *infoLog, char *filename);
/**
* Thuc hien in ra trang thai cua phong choi. Dung trong viec debug
*/
void printStateRoom(room *Room);
/**
* Thuc hien dang ki thong tin user len server.
*/
void registerUser (char username[], char  password[], char * filename);
/**
* Thuc hien cac buoc danh cua user
*/
int drawTable2(int table[TABLESIZE][TABLESIZE], int *xCross, int *yCross, int flag);
/**
* Ham bat phim
*/
int getch();
/**
* Ham xoa man hinh
*/
void clear();
/**
* Ham del file
*/
void delFile(char filename[]);
int checkExistUsername(char *username, char ListUsername[FD_SETSIZE][MAXLINE] );
int checkExistUsername2(char *username, user *listUser, int nUser);
#endif

