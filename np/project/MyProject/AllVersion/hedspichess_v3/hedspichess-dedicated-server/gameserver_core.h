#ifndef __GAMESERVER_CORE_H__
#define __GAMESERVER_CORE_H__


extern void gameserver_core_init ();
extern int gameserver_core_loadUsers ();
extern int gameserver_core_signin (char *username, char *password, int sockfd);
extern int gameserver_core_signup (char *username, char *password);
extern int gameserver_core_getOtherUserSockfd (int sockfd);
extern void gameserver_core_initNewRoom (int sockfd1, int sockfd2);

#endif
