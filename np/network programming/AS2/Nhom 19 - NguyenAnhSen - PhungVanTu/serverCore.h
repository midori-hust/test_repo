#ifndef SERVER_CORE
#define SERVER_CORE
#include "core.h"
#include "serverManager.h"
#include "question.h"
#include "common.h"
#include "question.h"
#include "userdata.h"
#include "sqlite3.h"

#define LOGIN_STATEMENT "select * from user where username like ? and password like ?"
#define QUERY_QUESTION "select * from game_question where Types like ? and Level like ? and ID >= ?"

typedef enum 
{
	STOP,
	WAITING_CONNECT,
	PLAYING_WAITING_MAINPLAYER,
	PLAYING_WAITING_NEW_QUESTION,
	PLAYING_WAITING_QUESTION_COMPLETE,
	PLAYING_WAITING_USERANSWER,
}
ServerState;
typedef struct Server
{
	DbAction db;
	sqlite3_stmt *loginStatement;
	sqlite3_stmt *queryQuestionStatement;
	Boolean stop;
	Boolean playing;
	ServerState state;
	Monitor *monitor;
	ServerManager *manager;
	int serverSock;
	int mainPlayer;
	int n_player;
	int n_ready;
	int n_connect;
	int n_player_request_new;
	int n_player_fetch_complete;
	int n_player_answer;
	int n_question;
	Boolean hasQuestionLevel;
	Question currentQuestion;
	UserData userdata;
	void (*run)(struct Server *);
	void (*requestProcessing)(struct Server *, int fd);
	void (*commandProcessing)(struct Server *);
	void (*disconnect)(struct Server *, int fd);
	void (*viewStatus)(struct Server *);
}Server;

// Internal method
void run(Server *server);
void messageProcessing(Server *server, int fd);
void commandProcessing(Server *server);
void disconnect(Server *server, int fd);
void requestProcessing(Server *server, int fd);
void waitingConnectionProcessing(Server *, int);
void playingProcessing(Server *, int);
void viewStatus(Server *);
void viewServerState(Server *);
// Extern method
void init(Server *server, Monitor *monitor, ServerManager *manager, Question question);
void startNewQuestion(Server *);
void startNewGame(Server *);
void sendAskQuestionLevel(Server *);
void freeServer(Server *);
#endif
