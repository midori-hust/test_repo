#ifndef SERVER_MANAGER
#define SERVER_MANAGER
#include <sys/time.h>
#include <sys/types.h>// Define connection state
//NOT_CONNECT ->  CONNECT_NOT_READY -> READY_NOT_PLAYER -> 
enum ConnectionState
{
	NOT_CONNECT,
	CONNECT_NOT_READY,
	READY_NOT_PLAYER,
	ASK_PLAYER_NOT_ACCEPT,
	PLAYER
};
typedef enum ConnectionState ConnectionState;
enum  PlayerState
{
	NONE_PLAYER,
	NOT_FETCH_QUESTION,
	FETCH_QUESTION_NOT_COMPLETE,
	FETCH_QUESTION_COMPLETE,
	NOT_COUNTDOWN,
	COUNTDOWN_NOT_ANSWER,
	ANSWERED
};
typedef enum PlayerState PlayerState;
enum AnswerState
{
	NONE_ANSWER,
	WRONG,
	CORRECT,
	HELP_1,
	HELP_2,
	HELP_3,
	HELP_4
};
typedef enum AnswerState AnswerState;
typedef struct ServerManager
{
	int connectionState[FD_SETSIZE];
	int playerState[FD_SETSIZE];
	int answerState[FD_SETSIZE];
	void (*removeConnection)(struct ServerManager *manager, int fd);
	void (*raiseConnectionState)(struct ServerManager *manager, int fd, ConnectionState newState);
	void (*raisePlayerState)(struct ServerManager *manager, int fd, PlayerState newState);
	void (*raiseAnswerState)(struct ServerManager *manager, int fd, AnswerState newState);
	void (*resetManager)(struct ServerManager *);
}
ServerManager;
ServerManager newServerManager();
void removeConnection(ServerManager *self, int fd);
void raiseConnectionState(ServerManager *manager, int fd, ConnectionState newState);
void raisePlayerState(ServerManager *manager, int fd, PlayerState newState);
void raiseAnswerState(ServerManager *manager, int fd, AnswerState newState);
void resetManager(ServerManager *manager);
#endif
