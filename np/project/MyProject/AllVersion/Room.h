#ifndef __ROOM_H__
#define __ROOM_H__

#include <stdio.h>
#include <string.h>

#define MAX_ROOM_QUANTITY 10;

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

#endif