#include "core.h"
#include "serverManager.h"
#include "serverCore.h"
#include "common.h"
#include "question.h"
#include "message.h"
#include "defineMessage.h"
#include "socketaction.h"
#include "command.h"
#include "sqlite3.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
 * Client                                                   Server/
 * |--------------------Connect---------------------------->Server/-<--------  |
 * 		success	|---------------Login---------------------->Server/            |
 * 					success|waiting-------------------------------/            |
 * 							|<-------------request as player----Server/        |
 * 							|------------request new question---->Server/<--|  |
 * 							|<--------question-----------------Server/      |  |
 * 							|---------complete-notify---------->Server/     |  |
 * 							|<--------count-down--------------->Server/     |  |
 * 							|----Start--Game-in--limit time-----------/     |  |
 * 							|------User answer----------------->Server/     |  |
 * 							|<-----Result-----------------------Server/     |  |
 * 								Success|-------------------------------------  |
 * 								Failure|----------------------------------------
 */
const char* StateName[] = 
{
	"STOP",
	"WAITING CONNECT",
	"PLAYING AND WAITING MAINPLAYER",
	"PLAYING AND WAITING NEW QUESTION",
	"PLAYING AND WAITING QUESTION COMPLETE",
	"PLAYING AND WAITING USERANSWER"
};

void init(Server *new, Monitor *monitor,ServerManager *manager, Question question)
{
	new -> serverSock = createTCPServerSocket(NULL);
	new -> currentQuestion = question;
	new -> monitor = monitor;
	new -> manager = manager;
	new -> run = run;
	new -> requestProcessing = requestProcessing;
	new -> commandProcessing = commandProcessing;
	new -> disconnect = disconnect;
	new -> viewStatus = viewStatus;
	(new -> monitor) -> addFD(new -> monitor, 0);
	(new -> monitor) -> addFD(new -> monitor,new -> serverSock);
	//n_player_answer <= n_fetch_question_complete <= n_player_accept <= n_player < n_ready <= n_connect
	new -> db =createDbAction("game_question.db"); 
	char *zERR;
	new -> db . assignStatement(&new -> db,LOGIN_STATEMENT);
	int erroCode = sqlite3_prepare_v2((new -> db) . dbObj , LOGIN_STATEMENT,100,&new -> loginStatement,&zERR);
	if (erroCode != SQLITE_OK)
	{
		printf("Error : %s\n",sqlite3_errmsg((new -> db) . dbObj));
	}
	erroCode = sqlite3_prepare_v2((new -> db) . dbObj, QUERY_QUESTION, 100, &new -> queryQuestionStatement,&zERR);
	if (erroCode != SQLITE_OK)
	{
		printf("Error : %s\n",sqlite3_errmsg((new -> db) . dbObj));
	}
	new -> currentQuestion = createQuestion(&new -> db);
	new -> userdata = createUserData(&new -> db);
	
	new -> n_connect = 0;
	new -> n_ready = 0;
	new -> n_player = 0;
	new -> n_player_fetch_complete = 0;
	new -> n_player_request_new = 0;
	new -> n_player_answer = 0;
	new -> mainPlayer = 0;
	new -> n_question = 0;
	new -> hasQuestionLevel = FALSE;
	new -> stop = FALSE;
	new -> playing  = FALSE;
	new -> state = WAITING_CONNECT;
}

void freeServer(Server *server)
{
	
}
void reStartGame(Server *new)
{
	printf("Server is restart\n");
	new -> monitor -> resetMonitor(new -> monitor, new -> serverSock);
	new -> manager -> resetManager(new -> manager);
	//n_player_answer <= n_fetch_question_complete <= n_player_accept <= n_player < n_ready <= n_connect
	new -> n_connect = 0;
	new -> n_ready = 0;
	new -> n_player = 0;
	new -> n_player_fetch_complete = 0;
	new -> n_player_request_new = 0;
	new -> n_player_answer = 0;
	new -> mainPlayer = 0;
	new -> n_question = 0;
	new -> hasQuestionLevel = FALSE;
	new -> stop = FALSE;
	new -> playing  = FALSE;
	new -> state = WAITING_CONNECT;
}
void disconnect(Server *server, int fd)
{
	if (server -> manager -> connectionState[fd] > NOT_CONNECT)
	{
		if (server -> manager -> connectionState[fd] == CONNECT_NOT_READY)
		{
			server -> n_connect--;
		}
		else
		if (server -> manager -> connectionState[fd] == READY_NOT_PLAYER)
		{
			server -> n_ready--;
			server -> n_connect--;
		}
		else
		if (server -> manager -> connectionState[fd] == ASK_PLAYER_NOT_ACCEPT)
		{
			server -> n_player--;
			server -> n_ready--;
			server -> n_connect--;
		}
		else
		if (server -> manager -> connectionState[fd] == PLAYER)
		{
			server -> n_player--;
			server -> n_connect--;
			server -> n_ready--;
		}
		printf("Remove %d from Manager\n",fd);
		server -> manager -> removeConnection(server ->manager, fd);
		printf("Remove %d from Monitor\n",fd);
		server -> monitor -> removeFD(server -> monitor, fd);
		printf("Close socket %d\n",fd);
		close(fd);
	}
}

void emptyList(int *list, int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		list[i] = -1;
	}
}

void viewStatus(Server *server)
{
	int i = 0;
	int n_connected_not_ready =0;
	int n_ready_not_player =0;
	int n_ask_player_not_accept =0;
	int n_player= 0;
	int n_player_not_fetch_question =0;
	int n_fetch_question_incomplete =0;
	int n_fetch_question_complete =0;
	int n_player_not_count_down =0 ;
	int n_count_down_not_answer =0;
	int n_answered = 0;
	int n_correct = 0;
	int n_wrong = 0;
	int n_help_1 = 0;
	int n_help_2 = 0;
	int n_help_3 = 0;
	int n_help_4 = 0;
	
	for (i = 0; i <= server -> monitor -> fd_max ;i++)
	{
		
		int conS = server -> manager -> connectionState[i];
		n_connected_not_ready += (conS == CONNECT_NOT_READY);
		n_ready_not_player += (conS == READY_NOT_PLAYER);
		n_ask_player_not_accept += (conS == ASK_PLAYER_NOT_ACCEPT);
		n_player += (conS == PLAYER);
		int t = (conS == PLAYER);
		int playerS = server -> manager -> playerState[i];
		n_player_not_fetch_question += ((playerS == NOT_FETCH_QUESTION) && t);
		n_fetch_question_incomplete += ((playerS == FETCH_QUESTION_NOT_COMPLETE) && t);
		n_fetch_question_complete += ((playerS == FETCH_QUESTION_COMPLETE)&& t);
		n_player_not_count_down += ((playerS == NOT_COUNTDOWN)&& t);
		n_count_down_not_answer += ((playerS == COUNTDOWN_NOT_ANSWER)&& t);
		n_answered += ((playerS == ANSWERED)&& t);
		t = ((playerS == ANSWERED) && t);
		int answerS = server -> manager -> answerState[i];
		n_correct += ((answerS == CORRECT) && t);
		n_wrong += (( answerS == WRONG) && t);
		n_help_1 += (answerS == HELP_1) && t;
		n_help_2 += (answerS == HELP_2) && t;
		n_help_3 += (answerS == HELP_3) && t;
		n_help_4 += (answerS == HELP_4) && t;
	}
	printf("Connection state :\n");
	printf("\tNumber of sockets in connect but not ready state : %d\n",n_connected_not_ready);
	printf("\tNumber of sockets in ready but not player state : %d\n",n_ready_not_player);
	printf("\tNumber of sockets in ask player but not accept : %d\n",n_ask_player_not_accept);
	printf("\tNumber of sockets in player state : %d\n",n_player);
	printf("Player state\n");
	printf("\tNumber of sockets in player but not fetch question : %d\n",n_player_not_fetch_question);
	printf("\tNumber of sockets in player fetch question incomplete : %d\n",n_fetch_question_incomplete);
	printf("\tNumber of sockets in player and fetch question complete : %d\n",n_fetch_question_complete);
	printf("\tNumber of sockets in player but not count down : %d\n",n_player_not_count_down);
	printf("\tNumber of sockets in count down but not answer : %d\n",n_count_down_not_answer);
	printf("\tNumber of sockets in answered state : %d\n",n_answered);
	printf("Answer state \n");
	printf("\tNumber of sockets in correct answer : %d\n",n_correct);
	printf("\tNumber of sockets in wrong state : %d\n",n_wrong);
	printf("\tNumber of sockets in help 1 state : %d\n",n_help_1);
	printf("\tNumber of socket in help 2 state : %d\n",n_help_2);
	printf("\tNumber of sockets in help 3 state : %d\n",n_help_3);
	printf("\tNumber of sockets in help 4 state : %d\n",n_help_4);
}

void sendMessage(Server *server,  Message *message, int fd)
{
	char *msgStr = message -> toString(message);
	printf("Send String : %s\n",msgStr);
	int send_status = sendData(fd,msgStr,strlen(msgStr));
	if (send_status == -1)
	{
		server -> disconnect(server,fd);
	}
	free(msgStr);
}

void sendAskPlayer(Server *server)
{
	int i = 0;
	Message askPlayerMessage = createMessage(2);
	askPlayerMessage . setParameter(&askPlayerMessage,"type","ASKPLAYER");
	askPlayerMessage . setParameter(&askPlayerMessage,"playertype","PLAYER");
	for (i = 1; i <= server -> monitor ->fd_max;i++)
	{
		if (server -> manager -> connectionState[i] == READY_NOT_PLAYER)
		{
			server -> manager -> raiseConnectionState(server -> manager , i, ASK_PLAYER_NOT_ACCEPT);
			sendMessage(server, &askPlayerMessage,i);
		}
	}
	askPlayerMessage . freeAll(&askPlayerMessage);
	server -> state = PLAYING_WAITING_NEW_QUESTION;
}

void getQuestion(Question *question)
{
	question -> loadQuestion(question,0);
}

void packQuestionMessage(Message *questionMessage, Question *question)
{
	questionMessage -> setParameter(questionMessage,"type","QUESTION");
	questionMessage -> setParameter(questionMessage,"questiontype",question -> type);
	questionMessage -> setParameter(questionMessage,"level",question -> level);
	questionMessage -> setParameter(questionMessage,"content",question -> content);
	questionMessage -> setParameter(questionMessage,"A_ANS",question -> a_ans);
	questionMessage -> setParameter(questionMessage,"B_ANS",question -> b_ans);
	questionMessage -> setParameter(questionMessage,"C_ANS",question -> c_ans);
	questionMessage -> setParameter(questionMessage,"D_ANS",question -> d_ans);
}

void sendQuestion(Server *server)
{
	int i = 0;
	printf("Send question\n");
	server -> n_question++;
	server -> db . setPrepareStatement(&server -> db, server -> queryQuestionStatement);
	getQuestion(&server -> currentQuestion);
	Message questionMessage = createMessage(8);
	packQuestionMessage(&questionMessage,&server -> currentQuestion);
	
	for (i = 1 ;i <= server -> monitor -> fd_max;i++)
	{
		if (
			(server -> manager -> connectionState[i] == PLAYER) &&
			(server -> manager -> playerState[i] == NOT_FETCH_QUESTION)
			)
			{
				server -> manager -> raisePlayerState (server -> manager, i, FETCH_QUESTION_NOT_COMPLETE);
				sendMessage(server, &questionMessage, i);
			}
	}
	questionMessage . freeAll (&questionMessage);
	server -> state = PLAYING_WAITING_QUESTION_COMPLETE;
}

void sendCountDown(Server *server)
{
	Message countDown = createMessage(2);
	countDown . setParameter (&countDown,"type","COUNTDOWN");
	countDown . setParameter (&countDown,"time","10");
	int i;
	for (i = 0; i <= server -> monitor -> fd_max;i++)
	{
		if (
			(server -> manager -> connectionState[i] == PLAYER) &&
			(server -> manager -> playerState[i] == FETCH_QUESTION_COMPLETE)
			)
			{
				server -> manager -> raisePlayerState(server -> manager , i, COUNTDOWN_NOT_ANSWER);
				sendMessage(server, &countDown, i);
			}
	}
	countDown . freeAll (&countDown);
	server -> state = PLAYING_WAITING_USERANSWER;
}

void sendResult(Server *server)
{
	int i;
	Message correctAnswer = createMessage(2);
	
	correctAnswer . setParameter (&correctAnswer,"type","USERANSWER");
	correctAnswer . setParameter (&correctAnswer,"status","CORRECT");
	
	
	Message incorrectAnswer = createMessage(2);
	
	incorrectAnswer . setParameter (&incorrectAnswer,"type","USERANSWER");
	incorrectAnswer . setParameter (&incorrectAnswer,"status","WRONG");
	
	
	Message helpAnswer = createMessage(2);
	
	helpAnswer . setParameter (&helpAnswer,"type","USERANSWER");
	helpAnswer . setParameter (&helpAnswer,"status","ACCEPT");
	for ( i = 1; i <= server -> monitor -> fd_max ;i++)
	{
		if 
			(
			(server -> manager -> connectionState[i] == PLAYER) &&
			(server -> manager -> playerState[i] == ANSWERED)
			)
			{
				if (server -> manager -> answerState[i] == CORRECT)
				{
					server -> manager -> raisePlayerState(server -> manager , i, NOT_FETCH_QUESTION);
					sendMessage(server, &correctAnswer ,i);
				}
				else
				if (server -> manager -> answerState[i] == WRONG)
				{
					server -> manager -> raisePlayerState(server -> manager, i, NONE_PLAYER);
					server -> manager -> raiseAnswerState(server -> manager, i, NONE_ANSWER);
					//server -> manager -> raiseConnectionState(server -> manager, i, CONNECT_NOT_READY);
					sendMessage(server, &incorrectAnswer , i);
				}
				else
				{
					server -> manager -> raisePlayerState(server -> manager , i, NOT_FETCH_QUESTION);
					sendMessage(server, &helpAnswer , i);
				}
			}
	}
	correctAnswer . freeAll(&correctAnswer);
	incorrectAnswer . freeAll(&incorrectAnswer);
	helpAnswer . freeAll(&helpAnswer);
}

void CheckServer(Server *server)
{
	if (server -> playing)
	{
		if (server -> n_player == 0)
		{
			printf("All of player is wrong\n");
			reStartGame(server);
		}
		else
		if (server -> n_player == 1)
		{
			if (server -> manager -> answerState[server -> mainPlayer] == CORRECT)
			{
				printf("Congratuation !! You won 1 Billion USD\n");
				reStartGame(server);
			}
		}
		else
		if (server -> state == PLAYING_WAITING_QUESTION_COMPLETE)
		{
			if (server -> n_player_fetch_complete == server -> n_player)
			{
				sendCountDown(server);
			}
		}
		else
		if (server -> state == PLAYING_WAITING_USERANSWER)
		{
			if (server -> n_player_answer == server -> n_player)
			{
				sendResult(server);//
				startNewQuestion(server);//
			}
		}
		else
		if (server -> state == PLAYING_WAITING_NEW_QUESTION)
		{
			if (server -> n_player_request_new == server -> n_player)
			{
				sendAskQuestionLevel(server);
			}
		}
		else
		if (server -> state == PLAYING_WAITING_MAINPLAYER)
		{
			if (server -> hasQuestionLevel)
			{
				sendQuestion(server);
			}
		}
	}
	else
	{
		printf("Server is waiting connection\n");
	}
}

void run(Server *server)
{
	int list[3];
	int count = 0;
	do
	{
		emptyList(list,3);
		count = server -> monitor ->getFirstReadyFDList(server ->monitor,list,CHECK_READY_READ,-1);
		if (count != -1)
		{	
			if (list[0] == 0)
			{
				server -> commandProcessing(server);
			}
			else
			if (list[0] > 0)
			{
				server -> requestProcessing(server,list[0]);
			}
			else
			{
				printf("List[0] < 0  unsupported\n");
				server -> stop = TRUE;
			}
			CheckServer(server);
		}
		else
		{
			server -> monitor -> displayError(server -> monitor);
			server -> stop = TRUE;
		}
	}
	while (!server -> stop);
}

int acceptConnection(int serverSock)
{
	struct sockaddr_in clientAddress;
	socklen_t len = sizeof (struct sockaddr_in);
	int newCon = accept(serverSock,(struct sockaddr*)&clientAddress,&len);
	return newCon;
}

void requestProcessing(Server *server, int fd)
{
	if (fd == server -> serverSock )
	{
		int newCon = acceptConnection(server -> serverSock);
		if (newCon != -1) 
		{
			printf("Accept new connection\n");
			server -> manager -> raiseConnectionState(server ->manager,newCon , CONNECT_NOT_READY);
			server -> monitor -> addFD(server -> monitor, newCon);
			server -> n_connect++;
		}
	}
	else
	{
		if (server -> state == WAITING_CONNECT)
		{
			waitingConnectionProcessing(server, fd);
		}
		else
		{
			playingProcessing(server,fd);
		}
	}
}	

void commandProcessing(Server *server)
{
	char command[100];
	gets(command);
	printf("Command : %s\n",command);
	if (isCloseServerCommand(command))
	{
		server -> stop = TRUE;
	}
	else
	if (isStatusCommand(command))
	{
		server -> viewStatus(server);
	}
	else
	if (isStartCommand(command))
	{
		startNewGame(server);
	}
	else
	if (isStateCommand(command))
	{
		viewServerState(server);
	}
	else
	{
		printf("Unknown command :\n");
	}
}

Message receiveMessage(Server *server, int fd)
{
	char msgStr[MAX_DATA_LEN];
	Message newMessage = createMessage(MAX_PARAM);
	int recv_status = receiveData(fd,msgStr,MAX_DATA_LEN);
	if (recv_status <= 0)
	{
		printf("Receive message :Close socket %d\n",fd);
		newMessage . setParameter(&newMessage,"type","CLOSE");
		return newMessage;
	}
	msgStr[recv_status] = 0;
	newMessage.parseString(&newMessage,msgStr);
	return newMessage;
}

void loginProcessing(Server *server, Message *loginMessage, int fd)
{
	char *username = loginMessage -> getParameter(loginMessage,"username");
	char *password = loginMessage -> getParameter(loginMessage,"password");
	Boolean loginFlags = FALSE;
	if ((username == NULL) || (password == NULL))
	{
		loginFlags = FALSE;
	}
	else
	{
		((server -> userdata) . db) -> setPrepareStatement((server -> userdata).db,server -> loginStatement);
		loginFlags = server -> userdata . checkUser(&server -> userdata, username, password);
	}
	free(username);
	free(password);
	Message responseMessage = createMessage(2);
	responseMessage.setParameter(&responseMessage,"type","LOGIN");
	if (loginFlags == FALSE) 
		responseMessage.setParameter(&responseMessage,"status","FAILURE");
	else
		responseMessage.setParameter(&responseMessage,"status","SUCCESS");
	if (loginFlags)
	{
		server -> manager -> raiseConnectionState (server -> manager , fd , READY_NOT_PLAYER);
		server -> n_ready++;
	}
	sendMessage(server, &responseMessage,fd );
	responseMessage.freeAll(&responseMessage);
}
/*
void connectionProcessing(Server *server, Message *message, int fd)
{
	if (server -> manager -> connectionState[fd] == NOT_CONNECT)
	server -> manager -> raiseConnectionState(server -> manager, fd, CONNECT_NOT_READY);
	message -> displayMessage(message);
}
*/
void waitingConnectionProcessing(Server *server, int fd)
{
	Message newMessage = receiveMessage(server, fd);
	if (isLoginRequest(&newMessage))
	{
		loginProcessing(server,&newMessage,fd);
	}
	else
	if (isClose(&newMessage))
	{
		server -> disconnect(server, fd);
	}
	else
	{
		printf("Unknown message from socket : %d\n",fd);
	}
	newMessage.freeAll(&newMessage);
}

/*
void acceptPlayerProcessing(Server *server, Message *message, int fd)
{
	if (isAccept(message))
	{
		server -> manager ->raiseConnectionState(server -> manager, fd, PLAYER);
		if (fd == server -> mainPlayer)
		{
			//server -> state = PLAYING_WAITING_PLAYER_ACCEPT;
			sendAskPlayer(server);
		}
		server -> manager->raisePlayerState(server -> manager, fd, NOT_FETCH_QUESTION);
		server -> n_player_accept+=1;
	}
}
*/

void fetchQuestionCompleteProcessing(Server *server, Message *message, int fd)
{
	server -> manager -> raisePlayerState (server -> manager, fd, FETCH_QUESTION_COMPLETE);
	server -> n_player_fetch_complete ++;
}

int chooseMainPlayer(Server *server)
{
	return server -> monitor -> fd_max;
}

void sendAskQuestionLevel(Server *server)
{
	if (server -> mainPlayer == 0) server -> mainPlayer = chooseMainPlayer(server);
	Message askQuestion = createMessage(2);
	server -> currentQuestion . getQuestionType(&server -> currentQuestion);
	askQuestion . setParameter(&askQuestion,"type","ASKQUESTIONLEVEL");
	askQuestion . setParameter(&askQuestion,"questiontype",(server -> currentQuestion) .type);
	sendMessage(server, &askQuestion,server -> mainPlayer);
	if (server -> manager -> connectionState[server -> mainPlayer] > NOT_CONNECT)
	{
		server -> state = PLAYING_WAITING_MAINPLAYER;
	}
	askQuestion . freeAll(&askQuestion);
}

void askQuestionProcessing(Server *server, Message *message, int fd)
{
	server -> manager -> raisePlayerState(server -> manager , fd, NOT_FETCH_QUESTION);
	server -> manager -> raiseConnectionState(server -> manager , fd, PLAYER);
	server -> n_player_request_new++;
}

void userAnswerProcessing(Server *server, Message *message, int fd)
{
	char *answer = message -> getParameter(message, "correct");
	char *help = message -> getParameter(message,"help");

	int ans_flags = FALSE;

	server -> manager -> raisePlayerState(server -> manager, fd, ANSWERED);
	server -> n_player_answer++;

	if (!strcmp(answer,server -> currentQuestion.correct))
	{
		server -> manager -> raiseAnswerState(server -> manager, fd, CORRECT);
		ans_flags = TRUE;
	}
	else
	if (help == NULL)
	{
		server -> manager->raiseAnswerState(server -> manager,fd, WRONG);
		ans_flags = FALSE;
	}
	else
	{
		server -> manager -> raiseAnswerState(server -> manager, fd, CORRECT);
		ans_flags = TRUE;
	}
	if (answer != NULL)
	free(answer);
	if (help != NULL)
	free(help);
}

void closeProcessing(Server *server, Message *message, int fd)
{
	if (server -> mainPlayer == fd)
	{
		server -> mainPlayer = 0;
	}
	server -> disconnect(server,fd);
}

void askQuestionLevelProcessing(Server *server, Message *message, int fd)
{
	char *questionLevel = message -> getParameter(message,"level");
	strcpy(server -> currentQuestion . level, questionLevel);
	if (!strcmp(questionLevel,"HARD")) server -> currentQuestion . levelID = HARD;
	else server -> currentQuestion . levelID  = EASY;
	if (questionLevel != NULL) free(questionLevel);
	server -> hasQuestionLevel = TRUE;
}

void playingProcessing(Server *server, int fd)
{
	Message newMessage = receiveMessage(server,fd);
	if (isAskQuestion(&newMessage)) // Message to notify that client ready to new question
	{
		askQuestionProcessing(server,&newMessage,fd);
	}
	else
	if (isQuestion(&newMessage)) // Messge to notify that client fetched completely question
	{
		fetchQuestionCompleteProcessing(server,&newMessage,fd);
	}
	else
	if (isUserAnswer(&newMessage)) // Message that contains answer of user for current question
	{
		userAnswerProcessing(server,&newMessage,fd);
	}
	else
	if (isAskQuestionLevel(&newMessage)) // Message for only main player, it contains new question's level
	{
		askQuestionLevelProcessing(server,&newMessage,fd);
	}
	else
	if (isClose(&newMessage)) // Message for error of parsing message from data string
	{
		closeProcessing(server,&newMessage,fd);
	}
	else
	{
		
		printf("Unknow message from socket : %d\n",fd);
		//connectionProcessing(server,&newMessage,fd);
	}
	newMessage.freeAll(&newMessage);
}

void sendAskMainPlayer(Server *server, int fd)
{
	server -> mainPlayer = fd;
	Message askMainPlayer = createMessage(2);
	askMainPlayer . setParameter(&askMainPlayer,"type","ASKPLAYER");
	askMainPlayer . setParameter(&askMainPlayer,"playertype","MAINPLAYER");
	sendMessage(server,&askMainPlayer,fd);
	askMainPlayer . freeAll(&askMainPlayer);
}

void sendMessageToList(Server *server, Message *message, int con_condition, int player_condition, int ans_condition)
{
	int i = 0;
	for (i = 0 ; i <= server -> monitor -> fd_max ;i++)
	{
		if (
			(server -> manager -> connectionState[i] == con_condition) &&
			(server -> manager -> playerState[i] == player_condition) &&
			(server -> manager -> answerState[i] == ans_condition)
			)
			{
				sendMessage(server , message, i);
			}
	}
}

void viewServerState(Server *server)
{
	printf("Server state : %s\n",StateName[server -> state]);
	printf("Main player : %d \n",server -> mainPlayer);
	printf("Number of connect : %d\n",server -> n_connect);
	printf("Number of ready : %d\n",server -> n_ready);
	printf("Number of players : %d\n",server -> n_player);
	printf("Number of players request new question: %d\n",server -> n_player_request_new);
	//printf("Number of players accept : %d\n",server -> n_player_accept);
	printf("Number of players fetch complete : %d\n",server -> n_player_fetch_complete);
	printf("Numner of players answer : %d\n",server -> n_player_answer);
}

void startNewGame(Server *server)
{
	server -> playing = TRUE;
	server -> n_question = 0;
	server -> mainPlayer = 0;
	startNewQuestion(server);
}

void startNewQuestion(Server *server)
{
	//server -> n_player_accept = 0;
	server -> n_player = server -> n_ready;
	server -> n_player_answer = 0; 
	server -> n_player_fetch_complete = 0;
	server -> n_player_request_new = 0;
	server -> hasQuestionLevel = FALSE;
	if (server -> n_question == 0)
	{
		sendAskPlayer(server);
	}
	server -> state = PLAYING_WAITING_NEW_QUESTION;
}

void AskMainPlayer(Server *server)
{
	if (server -> mainPlayer > 0)
	{
		printf("Main player is already\n");
		server -> state = PLAYING_WAITING_NEW_QUESTION;
	}
	else
	{
		//server -> state = PLAYING_WAITING_NEW_QUESTION;
		sendAskMainPlayer(server,server -> monitor -> fd_max);
		printf("Choosing main player\n");
	}
}
