#include "core.h"
#include "game_config.h"
#include "clientCore.h"
#include "socketaction.h"
#include "command.h"
#include "message.h"
#include "defineMessage.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

const char* ConnectionStateName[] =
{
	"NOT CONNECT",
	"CONNECT NOT READY",
	"READY NOT PLAYER",
	"ASK PLAYER NOT ACCEPT",
	"PLAYER"
};
const char* PlayerStateName[] = 
{
	"NOT FETCH QUESTION",
	"FETCH QUESTION NOT COMPLETE",
	"FETCH QUESTION COMPLETE",
	"NOT COUNT DOWN",
	"COUNT DOWN NOT ANSWER",
	"ANSWERED"
};
const char* AnswerStateName[] = 
{
	"CORRECT",
	"WRONG",
	"HELP 1",
	"HELP 2",
	"HELP 3",
	"HELP 4"
};

Client newClient(Monitor *monitor, Boolean enableCommand)
{
	Client newClient;
	newClient.stop = FALSE;
	newClient.playing = FALSE;
	newClient.isMainPlayer = FALSE;
	newClient.con_state = NOT_CONNECT;
	newClient.player_state = NOT_FETCH_QUESTION;
	newClient.ans_state = CORRECT;
	newClient.n_question = 0;
	newClient.monitor = monitor;
	newClient.commandProcessing = commandProcessing;
	newClient.requestProcessing = requestProcessing;
	newClient.run = run;
	newClient.disconnect = disconnect;
	newClient.connectServer = connectServer;
	newClient.loginToServer = loginToServer;
	newClient.logoutServer = logoutServer;
	newClient.viewStatus = viewStatus;
	if (enableCommand) (newClient.monitor) -> addFD(newClient.monitor,0);
	return newClient;
}

void viewStatus(Client *client)
{
	printf("Connection state : %s\n",ConnectionStateName[client -> con_state]);
	printf("Player state : %s\n",PlayerStateName[client -> player_state]);
	printf("Answer state : %s\n",AnswerStateName[client -> ans_state]);
}

void logoutServer(Client *self)
{
	if (self -> con_state >= READY_NOT_PLAYER)
	{
		self -> con_state = CONNECT_NOT_READY;
		self -> player_state = NOT_FETCH_QUESTION;
		self -> ans_state = CORRECT;
		printf("Logout successfully\n");
	}
	else
	{
		printf("You not login\n");
	}
}

void connectServer(Client *self)
{
	if ((self -> clientSock > 0) && (self -> con_state >= READY_NOT_PLAYER))
	{
		printf("You logged on, please logout this account\n");
		return;
	}
	int clientSock = createRemoteConnection(NULL);
	if (clientSock != -1)
	{
		if (self -> clientSock > 0)
		{
			self -> disconnect(self, self -> clientSock);
		}
		printf("Connected\n");
		printf("Add %d to Monitor\n",clientSock);
		self -> clientSock = clientSock;
		self -> monitor -> addFD(self -> monitor, clientSock);
		self -> con_state = CONNECT_NOT_READY;
	}
}

void disconnect(Client *client, int fd)
{
	printf("Server disconnect\n");
	client -> monitor -> removeFD (client -> monitor,fd);
	client -> con_state = NOT_CONNECT;
	client -> player_state = NOT_FETCH_QUESTION;
	client -> ans_state = CORRECT;
	close(fd);
}

void emptyList(int *list, int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		list[i] = -1;
	}
}

void CheckClient(Client *client)
{
	if (client -> con_state == NOT_CONNECT)
	{
		printf("Disconnect\n");
		client -> stop = TRUE;
	}
}

void run(Client *client)
{
	int list[3];
	int check = -1;
	do
	{
		emptyList(list,3);
		check = client -> monitor ->getFirstReadyFDList(client -> monitor , list , CHECK_READY_READ ,-1);
		if (check == -1)
		{
			client -> stop = TRUE;
		}
		else
		{
			if (list[0] ==0)
			{
				commandProcessing(client);
			}
			else
			if (list[0] > 0)
			{
				requestProcessing(client,list[0]);
			}
			CheckClient(client);
		}
	}
	while (!client -> stop);
}
void sendMessage(Client *self,  Message *message, int fd)
{
	char *msgStr = message -> toString(message);
	int send_status = sendData(fd,msgStr,strlen(msgStr));
	if (send_status == -1)
	{
		self -> disconnect(self,fd);
	}
	free(msgStr);
}

void loginToServer(Client *client)
{
	if (client -> con_state <= NOT_CONNECT) 
	{
		printf("Please connect before\n");
		return;
	}
	if (client -> con_state >= READY_NOT_PLAYER)
	{
		printf("You've already logged on\n");
		return;
	}
	Message loginMessage = createMessage(3);
	loginMessage . setParameter(&loginMessage,"type","LOGIN");
	loginMessage . setParameter(&loginMessage,"username","abc");
	loginMessage . setParameter(&loginMessage,"password","1234");
	sendMessage(client, &loginMessage, client -> clientSock);
	loginMessage . freeAll(&loginMessage);
}

void commandProcessing(Client *self)
{
	char command[100];
	gets(command);
	if (isCloseServerCommand(command))
	{
		self -> stop = TRUE;
	}
	else
	if (isConnectCommand(command))
	{
		self -> connectServer(self);
	}
	if (isLoginCommand(command))
	{
		self -> loginToServer(self);
	}
	if (isLogoutCommand(command))
	{
		self -> logoutServer(self);
	}
	if (isStatusCommand(command))
	{
		self -> viewStatus (self);
	}
	else
	{
		printf("Unknown command\n");
	}
}

Message receiveMessage(Client *client, int fd)
{
	char msgStr[MAX_DATA_LEN];
	Message newMessage = createMessage(MAX_PARAM);
	
	int recv_status = receiveData(fd,msgStr,MAX_DATA_LEN);
	if (recv_status <= 0)
	{
		newMessage . setParameter(&newMessage,"type","CLOSE");
		
		return newMessage;
	}
	msgStr[recv_status] = 0;
	//printf("String : %s")
	newMessage.parseString(&newMessage,msgStr);
	return newMessage;
}

void loginProcessing(Client *client, Message *message, int fd)
{
	char *status = message -> getParameter(message, "status");
	Boolean check = (strcmp(status,"SUCCESS") == 0);
	free(status);
	if (check) client -> con_state = READY_NOT_PLAYER;
}

void fetchQuestionProcessing(Client *client, Message *message, int fd)
{
	client -> n_question++;
	char *level = message -> getParameter(message,"level");
	strcpy(client -> currentQuestion . level, level);
	char *type = message -> getParameter(message,"type");
	strcpy(client -> currentQuestion . type, type);
	char *content = message -> getParameter(message, "content");
	strcpy((client -> currentQuestion) . content, content);
	char *a_ans = message -> getParameter(message, "A_ANS");
	strcpy((client -> currentQuestion). a_ans , a_ans);
	char *b_ans = message -> getParameter(message, "B_ANS");
	strcpy((client -> currentQuestion). b_ans , b_ans);
	char *c_ans = message -> getParameter(message, "C_ANS");
	strcpy((client -> currentQuestion). c_ans , c_ans);
	char *d_ans = message -> getParameter(message, "D_ANS");
	strcpy((client -> currentQuestion). d_ans , d_ans);
	free(a_ans);
	free(b_ans);
	free(c_ans);
	if (d_ans != NULL) free(d_ans);	
	Message completeQuestion = createMessage(2);
	completeQuestion.setParameter(&completeQuestion,"type","QUESTION");
	completeQuestion.setParameter(&completeQuestion,"status","COMPLETE");
	sendMessage(client,&completeQuestion,fd);
}

void printAnswer(char name, char *ans)
{
	if (strlen(ans)>0)
	printf("%c) %s\n",name,ans);
}
void printQuestion(Question question)
{
	printf("Question : xxx, Type : %s, Level : %s\n",question.type, question.level);
	printf(LONGLINE);
	printf("Content : \n");
	printf("%s\n",question.content);
	printf(SHORTLINE);
	printf("Answer :\n");
	printAnswer('A',question . a_ans);
	printAnswer('B',question . b_ans);
	printAnswer('C',question . c_ans);
	printAnswer('D',question . d_ans);
	printf(LONGLINE);
}

void promtUserAnswer(Client *client)
{
	system("clear");
	printQuestion(client -> currentQuestion);
	client -> endAns[0] = 32;
	if (client -> isMainPlayer)
	getEndAnswer("Your answer",client -> endAns,20);
	else getEndAnswer("Your answer",client -> endAns,10);
}

void sendUserAnswer(Client *client)
{
	Message userAns = createMessage(2);
	userAns . setParameter(&userAns,"type","USERANSWER");
	userAns . setParameter(&userAns,"correct",client -> endAns);
	sendMessage(client,&userAns,client -> clientSock);
}


void startCountDownProcessing(Client *client)
{
	client -> playing = TRUE;
	promtUserAnswer(client);
	sendUserAnswer(client);
}

void printQuestionLevel(Client *client)
{
	printf(LONGLINE);
	printf("Question type : %s\n",client -> currentQuestion.type);
	printf(SHORTLINE);
	printf("A) Hard\n");
	printf("B) Easy\n");
	printf(SHORTLINE);
}

void promtQuestionLevel(Client *client)
{
	printQuestionLevel(client);
	char quest_type[2];
	getEndAnswer("Question level",quest_type,20);
	if (!strcmp(quest_type,"A")) strcpy(client -> currentQuestion.level,"HARD");
	else strcpy(client -> currentQuestion . level, "EASY");
}

void askQuestionProcessing(Client *client, Message *message, int fd)
{
	char *questiontype = message -> getParameter(message,"questiontype");
	strcpy(client -> currentQuestion.type,questiontype);
	free(questiontype);
	promtQuestionLevel(client);
	message -> setParameter(message, "level",(client -> currentQuestion).level);
	sendMessage(client,message,fd);
}

void sendAskQuestion(Client *client)
{
	printf("Send ask question\n");
	Message askQuestion = createMessage(2);
	askQuestion . setParameter(&askQuestion,"type","ASKQUESTION");
	askQuestion . setParameter(&askQuestion,"status","ACCEPT");
	sendMessage(client,&askQuestion,client -> clientSock);
	askQuestion . freeAll(&askQuestion);
	client -> player_state = NOT_FETCH_QUESTION;
}

void resultProcessing(Client *client,Message *message)
{
	char *status = message -> getParameter(message,"status");
	client -> stop = !(strcmp(status,"WRONG"));
	if (client -> stop == FALSE)
	{
		sendAskQuestion(client);
		client -> ans_state = CORRECT;
	}
	else
	{
		client -> ans_state = CORRECT;
	}
	free(status);
}

void askPlayerProcessing(Client *client, Message *message, int fd)
{
	char *playerType = message -> getParameter(message,"playertype");
	Boolean isMainPlayer = !(strcmp(playerType,"MAINPLAYER"));
	free(playerType);
	client -> isMainPlayer = isMainPlayer;
	Message acceptPlayer = createMessage(2);
	acceptPlayer . setParameter(&acceptPlayer,"type","ASKQUESTION");
	acceptPlayer . setParameter(&acceptPlayer,"status","ACCEPT");
	sendMessage(client,&acceptPlayer,fd);
}

void unknownProcessing(Client *client,Message *message, int fd)
{
	printf("Unknown message\n");
	printf("From socket : %d\n",fd);
	message -> displayMessage(message);
}

void askQuestionLevelProcessing(Client *client, Message *message, int fd)
{
	char *questiontype = message -> getParameter(message,"questiontype");
	strcpy (client -> currentQuestion . type , questiontype);
	promtQuestionLevel(client);
	message -> setParameter(message, "level",(client -> currentQuestion).level);
	sendMessage(client,message,fd);
}

void requestProcessing(Client *self, int fd)
{
	Message message = receiveMessage(self,fd);
	if (isLoginRequest(&message))
	{
		loginProcessing(self,&message,fd);
	}
	else
	if (isQuestion(&message))
	{
		fetchQuestionProcessing(self,&message,fd);
	}
	else
	if (isCountDown(&message))
	{
		startCountDownProcessing(self);
	}
	else
	if (isUserAnswer(&message))
	{
		resultProcessing(self,&message);
	}
	else
	if (isAskQuestion(&message))
	{
		askQuestionProcessing(self,&message, fd);
	}
	else
	if (isAskPlayer(&message))
	{
		askPlayerProcessing(self,&message,fd);
	}
	else
	if (isAskQuestionLevel(&message))
	{
		askQuestionLevelProcessing(self,&message,fd);
	}
	else
	if (isClose(&message))
	{
		self -> disconnect(self, fd);
	}
	else
	{
		unknownProcessing(self,&message,fd);
	}
	message . freeAll(&message);
}
