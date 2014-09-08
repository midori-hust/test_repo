#include "serverManager.h"
ServerManager newServerManager()
{
	ServerManager newServer;
	newServer.removeConnection = removeConnection;
	newServer.raiseAnswerState = raiseAnswerState;
	newServer.raiseConnectionState = raiseConnectionState;
	newServer.raisePlayerState = raisePlayerState;
	newServer.resetManager = resetManager;
	int i = 0;
	for (i = 0; i < FD_SETSIZE ;i++)
	{
		newServer.connectionState[i] = NOT_CONNECT;
		newServer.playerState[i] = NONE_PLAYER;
		newServer.answerState[i] = NONE_ANSWER;
	}
	return newServer;
}

void resetManager(ServerManager *newServer)
{
	int i = 0;
	for (i = 1; i < FD_SETSIZE ;i++)
	{
		newServer -> connectionState[i] = NOT_CONNECT;
		newServer -> playerState[i] = NONE_PLAYER;
		newServer -> answerState[i] = NONE_ANSWER;
	}
}
void removeConnection(ServerManager *self, int fd)
{
	self -> raiseConnectionState(self,fd,NOT_CONNECT);
	self -> raisePlayerState(self,fd,NONE_PLAYER);
	self -> raiseAnswerState(self,fd, NONE_ANSWER);
}

void raiseConnectionState(ServerManager *self, int fd, ConnectionState newState)
{
	self -> connectionState[fd] = newState;
}

void raisePlayerState(ServerManager *self, int fd, PlayerState newState)
{
	self -> playerState[fd] = newState;
}

void raiseAnswerState(ServerManager *self, int fd, AnswerState newState)
{
	self -> answerState[fd] = newState;
}
