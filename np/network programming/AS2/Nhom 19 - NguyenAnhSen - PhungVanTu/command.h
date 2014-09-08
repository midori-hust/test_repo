#ifndef COMMAND
#define COMMAND
#define TRUE 1
#define FALSE 0
int isListCommand(char *);
int isNewSessionCommand(char *);
int isCloseServerCommand(char *);
int isConnectCommand(char *);
int isLoginCommand(char *);
int isLogoutCommand(char *);
int isStatusCommand(char *);
int isStartCommand(char *);
int isStateCommand(char *);
#endif
