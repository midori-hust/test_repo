#ifndef __USER_H__
#define __USER_H__

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 100;
#define MAX_ROOM_QUANTITY 10;


typedef enum { 
	GAME_LOGIN,
	GAME_SIGN_UP,
	GAME_LOG_OUT
} GameStatus;

typedef enum  {
	ROOM_WAITING,
	ROOM_FULL,
	ROOM_EMPTY
} RoomState;

typedef struct _room
{
	int id;
	RoomState roomState;
	char whiteSidePlayer[MAXLENGTH];
	char blackSidePlayer[MAXLENGTH];
} Room;

typedef struct _roomList
{
	Room room;
	struct  _roomList *next;
} RoomList;

typedef enum  {
	CHESS_RESULT_IN_PROGRESS,
	CHESS_RESULT_WHITE_WON,
	CHESS_RESULT_BLACK_WON,
	CHESS_RESULT_DRAW
} ChessResult;

typedef enum {
	STT_ONLINE,
	STT_OFFLINE
} PlayerStatus;

typedef struct _player
{
	char name[MAXLENGTH];
	char password[MAXLENGTH];
	int win = 0;
	int draw = 0;
	int lose = 0;
	PlayerStatus status;
} Player;

typedef struct _playerList {
	Player playerInfo;
	struct _playerList *next;
} PlayerList;

int checkAcc(char acc[],int type,Player player[],int online);

#endif