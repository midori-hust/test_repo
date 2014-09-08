#ifndef CLIENT_CORE
#define CLIENT_CORE
#include "common.h"
#include "core.h"
#include "question.h"
#include "libterm.h"

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
	WRONG,
	CORRECT,
	HELP_1,
	HELP_2,
	HELP_3,
	HELP_4
};
typedef enum AnswerState AnswerState;
typedef struct Client
{
	Boolean stop;
	Boolean playing;
	int clientSock;
	Boolean isMainPlayer;
	Monitor *monitor;
	ConnectionState con_state;
	PlayerState player_state;
	AnswerState ans_state;
	Question currentQuestion;
	int n_question;
	char endAns[2];
	void (*connectServer)(struct Client *);
	void (*commandProcessing)(struct Client *);
	void (*requestProcessing)(struct Client*, int fd);
	void (*run)(struct Client *);
	void (*disconnect)(struct Client *, int fd);
	void (*loginToServer)(struct Client *);
	void (*logoutServer) (struct Client *);
	void (*viewStatus)(struct Client *);
}Client;
// Method
void commandProcessing(Client *);
void requestProcessing(Client *, int fd);
void disconnect(Client *, int);
void run(Client *);
void connectServer(Client *);
void loginToServer(Client *);
void logoutServer(Client *);
void viewStatus(Client *);
// External function
Client newClient(Monitor *, Boolean enableCommand);
#endif
