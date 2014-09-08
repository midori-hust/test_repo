#include "command.h"
#include <string.h>
int isListCommand(char *command)
{
	return (!strcmp(command,"list") || !strcmp(command,"LIST"));
}
int isNewSessionCommand(char *command)
{
	return (!strcmp(command,"NEW")||!strcmp(command,"new"));
}
int isCloseServerCommand(char *command)
{
	return (!strcmp(command,"exit") || !strcmp(command,"EXIT") || !strcmp(command,"quit") || !strcmp(command,"QUIT"));
}

int isConnectCommand(char *command)
{
	return (!strcmp(command,"connect") || (!strcmp(command,"CONNECT")));
}

int isLoginCommand(char *command)
{
	return (!strcmp(command,"login") || (!strcmp(command,"LOGIN")));
}

int isLogoutCommand(char *command)
{
	return (!strcmp(command,"logout") || (!strcmp(command,"LOGOUT")));
}
int isStatusCommand(char *command)
{
	return (!strcmp(command,"status") || (!strcmp(command,"STATUS")));
}

int isStartCommand(char *command)
{
	return (!strcmp(command,"start") || (!strcmp(command,"START")));
}

int isStateCommand(char *command)
{
	return (!strcmp(command,"state") || (!strcmp(command,"STATE")));
}
