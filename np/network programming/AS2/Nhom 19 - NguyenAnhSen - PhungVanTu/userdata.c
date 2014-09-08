#include"userdata.h"
#include <string.h>
UserData createUserData(DbAction *db)
{
	UserData userData;
	userData . checkUser = checkUser;
	userData .db = db;
	return userData;
}

int checkUser(UserData *userData, char *username, char *password)
{
	userData -> db -> resetParameter(userData -> db);
	userData -> db -> bindParameterString(userData -> db, 1, username);
	userData -> db -> bindParameterString(userData -> db, 2, password);
	userData -> db -> execute(userData -> db);
	if (userData -> db -> state == ROW_AVAIABLE)
	{
		return ACCEPT_USER;
	}
	else return NOT_ACCEPT_USER;
}
