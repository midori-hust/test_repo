#ifndef USERDATA
#define USERDATA
#define ACCEPT_USER 1
#define NOT_ACCEPT_USER 0
#include "dbaction.h"
typedef struct UserData
{
	DbAction *db;
	int (*checkUser)(struct UserData *, char*, char *);
}UserData;
int checkUser(UserData *,char* username, char *password);

UserData createUserData(DbAction *);
#endif
