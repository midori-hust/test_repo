#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/select.h>
#include <unistd.h>
#include "mlibrary.h"

int main(int args, char *argv[]) {
	int isOnline = 1;
	struct hostent* he;
	struct sockaddr_in server;
	int sock_fd;
	int playerAnswer;
	int quesReceived = 0;
	int choice, i;
	int help_choice[HELP_CHOICES];
	int clientId = UNDEFINED;
	char clientName[40];
	char c;
	Question ques;
	StatusType clientStatus;
	MainPlayerData toPlayerData;
	CandidateData toCandidateData;
	createCashPrizeList();
	if (args != 3) {
		printf("Usage : %s <IP> <PORT>\n", argv[0]);
		exit(-1);
	}
	if ((he = gethostbyname(argv[1])) == NULL ) {
		printf("Cannot get the server !\n");
		exit(-1);
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr = *((struct in_addr*) he->h_addr);
	bzero(&(server.sin_zero), 8);
	// create a socket to server
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("Cannot create a socket !\n");
		exit(-1);
	}
	if (connect(sock_fd, (struct sockaddr*) &server, sizeof(struct sockaddr))
			== -1) {
		printf("error connect");
		exit(1);
	}
	recv(sock_fd, &clientId, sizeof clientId, 0);
	if (clientId == NULL_ID) {
		printf(CLIENT_FULL_MESSAGE);
		close(sock_fd);
		exit(-1);
	}
	//printf("Get the id  : %d\n", clientId);
	printf("=====WELCOME TO THE WHO WANT TO BE A MILLIONAIRE\n");
	printf("Enter your name : ");
	//get the user name
	gets(clientName);
	toCandidateData.status = CONNECTED;
	//send the data to server to let server know you name
	send(sock_fd, &toCandidateData, sizeof toCandidateData, 0);
	send(sock_fd, clientName, sizeof clientName, 0);
	// get the data back then display message for the first time join to game (this time a welcome message)
	recv(sock_fd, &toCandidateData, sizeof toCandidateData, 0);
	displayCandidateMessage(toCandidateData);
	clientStatus = toCandidateData.status;
	// print the client's status
//	printf("The client %d has status : ", clientId);
//	toString(clientStatus);
	//playerAnswer = RIGHT;
	/*handle data sent from server according to client role */
	while (isOnline) {
		switch (clientStatus) {
		case WAITING:
			recv(sock_fd, &toCandidateData, sizeof toCandidateData, 0);
			clientStatus = toCandidateData.status;
			if (clientStatus == WAITING) {
				displayCandidateMessage(toCandidateData);
			}
			copyQuestion(&ques, toCandidateData.question);

			break;
		case COMPETING:
			//displayCandidateMessage(toCandidateData);
			//displayQuestion(ques);
			compete(&toCandidateData, ques);
			printf("Waiting for result....!\n");
			sleep(1);
			//fflush(stdout);
			//endwin();
			// send answer to server //
			send(sock_fd, &toCandidateData, sizeof toCandidateData, 0);
			//receive the result and change the status of client according to result
			recv(sock_fd, &toCandidateData, sizeof toCandidateData, 0);
			displayAnswer(ques);
			sleep(1);
			displayCandidateMessage(toCandidateData);
			clientStatus = toCandidateData.status;
//			printf("The client %d has status : ", clientId);
//			toString(clientStatus);
			//fflush(stdout);
//			return 0;
//			 exit(0);
			break;
		case JOINING:
			ques = toPlayerData.ques;
			recv(sock_fd, &toPlayerData, sizeof toPlayerData, 0);

			if (quesReceived == 1) {
				displayAnswer(ques);
			}
			sleep(1);
			if (toPlayerData.status == FINISHED) {
				displayPlayerMessage(toPlayerData);
				exit(1);
			}
			broadTheGame(toPlayerData);
			quesReceived = 1;
			break;
		case PLAYING:
			//fflush(stdout);
			for (i = 0; i < HELP_CHOICES; i++) {
				help_choice[i] = AVAILABLE;
			}
			do {
				while (getchar() != '\n')
					;

				recv(sock_fd, &toPlayerData, sizeof toPlayerData, 0);
				if (toPlayerData.status == FINISHED) {
					displayPlayerMessage(toPlayerData);
					exit(1);
				}
				sleep(1);
				displayPlayerMessage(toPlayerData);
				sleep(1);
				broadTheGame(toPlayerData);
				printf(
						"\n>>Your choice (press 'H' to get help or 'L' to leave the game): ");
				c = getchar();
				choice = handleAnswer(c);
				//if the player has his own answer
				while (1) {
					if (choice != HELP_MODE) {//neu nguoi choi ko chon tro giup
						playerAnswer = checkAnswer(choice,
								toPlayerData.ques.ans);
						send(sock_fd, &playerAnswer, sizeof playerAnswer, 0);
						break;

					}
					//else if he needs help
					else { //xu ly tro giup
						helpMenu(&toPlayerData, help_choice);
						printf(
								"\n>>Your choice (press 'H' to get help or 'L' to leave the game): ");
						while (getchar() != '\n')
							;
						c = getchar();
						choice = handleAnswer(c);
					}
				}
			} while (playerAnswer == RIGHT);
			if (playerAnswer == WRONG || playerAnswer == END) {
				recv(sock_fd, &toPlayerData, sizeof toPlayerData, 0);
				sleep(1);
				displayAnswer(toPlayerData.ques);
				displayPlayerMessage(toPlayerData);
				isOnline = 0;
				clientStatus = FINISHED;
				close(sock_fd);
				exit(-1);
			}
			//fflush(stdout);
			break;
		default:
			printf("We will handle soon ...\n");
			break;
		}
		//fflush(stdout);
	}
	return 0;
}
