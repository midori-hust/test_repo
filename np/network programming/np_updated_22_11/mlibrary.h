#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
/* indicate that the question is used to select the main player */
#define QUICK_QUESTION -1
/* define the max level of the question, 15 means we have 15 question for a player to answer */
#define NULL_ID -10
/* define the client id that indicates the client can't join the game because there is no slot for him */
#define MAX_LEVEL 15
/* indicates that the connection is undefined */
#define UNDEFINED -1
/* the number of questions for a same level */
#define NUMBERS_PER_QUES 4
/*the number of help choices */
#define HELP_CHOICES 3
/*indicate the main player wants help */
#define HELP_MODE 5
/* the status of help choices : available or invalid (used for set in help[] array of data structure*/
#define INVALID -1
#define AVAILABLE 0
/* the total clients server can serve */
#define BACKLOG 3 /* 6 clients at a time server can serve */
#define OCCUPIED 1 /*Indicates the status of the client is connected to the server already */
#define MAX_TIME_ANSWER 30000 /* Time for candidates to give answer for the quick question -30s */
/* defining message to notify clients */
#define RIGHT 7 //right answer
#define WRONG 8	//wrong answer
#define END   9	//stop playing
#define CLIENT_FULL_MESSAGE "Sorry we have enough clients here !\n See you next time !\n"
#define QUICK_QUESTION_MESSAGE "Here is a quick question ! You need to give us an answer within 30 seconds !\n"
#define JOINER_MESSAGE "We have selected the main player ! You can watch the game starting now !\n"
#define MAIN_PLAYER_SELECTED "Congratulation ! You are the main player now !\n"
#define MAIN_PLAYER_BEGIN "==== Welcome you to the game ! Get ready ! ====\n"
#define MAIN_PLAYER_WRONG_ANSWER "Sorry ! Your selection is incorrect !\n"
/* the array contains list of cash prize corresponding to the question level */
char cashPrizeList[MAX_LEVEL+1][20];
/*status of clients */
typedef enum {
	EMPTY, CONNECTED, WAITING, COMPETING, JOINING, PLAYING, FINISHED, UNKNOWN
} StatusType;

/* Declaration of the array containing id and connection status of clients */
typedef struct _ClientInfo {
	int id; 	//is the integer of socket file descriptor
	StatusType status; //can be one of PLAYING, CONNECTED,COMPETING, FINISHED
	int quick_answer;
	float ansTime;
	char clientName[40];
} ClientInfo;
ClientInfo clientInfo[BACKLOG];

// structure of question
typedef struct _question {
	int IDQuestion;
	char ques[100];
	char answerList[4][40];
	int ans;
} Question;
Question questLib[MAX_LEVEL+1][NUMBERS_PER_QUES];

/* structure of data send to joiner of server (just a client, not the main player */
typedef struct _candidateData {
	StatusType status;
	char message[100];
	//Account user;
	Question question;
	float ansTime;
	int answer;
} CandidateData;

/* structure of data send between server and the main player  */

typedef struct _data {
	StatusType status;
	char message[100];
	Question ques; //Store data of a question
	int help_choice; //help = -1 : don't user have
//help =  0 : change question
//help =  1 : 50/50
//help =  2 : phone
//help =  3 : Unused

	int level; // Store the result of current-user ;
	char name[40]; //player's name
	int selectionStatus[4]; //status of 4 selections
} MainPlayerData;

/* create a cash prize list to the array of char[]*/
void createCashPrizeList();
/*read questions from the filename file to the array of question */
int readQuestionFile(char *filename);
void displayPlayerMessage(MainPlayerData toPlayerData);
void copyQuestion(Question *target, Question source);
void displayCandidateMessage(CandidateData toCandidateData);
void displayCandidateMessageOnWin(CandidateData toCandidateData);
void displayQuestion(Question question);
void displayQuickQuestion(Question question);

/* initialize the data for the main player */
void initializeMainPlayerData(MainPlayerData *toMainPlayerData);
/* initialize data for candidate */
void initializeCandidateData(CandidateData *toCandidateData);
void initializeClientList();
void removeClient(int clientId);
int addClient(int clientId);
int isClientListFull();

StatusType getClientStatus(int id);
void setClientStatus(int id, StatusType status, char name[]);
int getNumberOfClient();

int readyToStart();

void printClientList();
/*print  list of the clients' answer for quick question */
void printClientsAnswerList();
void printClientStatus(int clientId);
void toString(StatusType status);
void setCompetition();

/* calculate the time spent to answer of client */
int timeval_subtract(struct timeval *result, struct timeval *t2,
		struct timeval *t1);

/* handling selecting the main player */
void compete(CandidateData* cd, Question ques);
/* handle the answer of player or candidates */
int handleAnswer(char c);
int handleQuickQuestion(char c);
int selectMainPlayer(Question ques, int length);
/*set the player whose index is passed to be the main players, other players is joining */
void startGame(int index);
/*send data to all the viewer and main players (tuong thuat truc tiep game)*/
void broadTheGame(MainPlayerData mpd);

/* check if the main player's answer is right*/
int isRightAnswer(MainPlayerData mpd);
/* random a number */
int randomNumber(int range);
/* switch to help mode khi nguoi dung chon help */
void helpHandler(MainPlayerData *mpd,int help_choice[]);

void askTheAudience(MainPlayerData *mpd);

void fifty_fifty(MainPlayerData *mpd);
void displayQuesWithFtyFty(MainPlayerData *mpd);
void phoneToHelp(Question ques,int toPerson);

void selectQuestion(int level,MainPlayerData *mpd);

int checkAnswer(int playerAnswer,int answer);

void increaseQuestion(MainPlayerData *mpd);
/* help menu appears when player in help mode */
void helpMenu(MainPlayerData *mpd,int help_choice[]);
/* game end (when player made wrong answer or decided to leave the game */
void endGame(MainPlayerData *mpd,int choice);
char IntToChar(int i);
void displayAnswer(Question ques);

void wonGame(MainPlayerData *mpd);
void gameFinish(MainPlayerData *mpd,int choice);
