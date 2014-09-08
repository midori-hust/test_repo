// gcc -c mlibrary.h -lcurses
//gcc -o server mserver.c mlibrary.c -lncurses
//gcc -o client mclient.c mlibrary.c -lncurses
// ./client localhost 10080
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "mlibrary.h"
#include <errno.h>

int main(int args, char *argv[]) {

	char message[100];
	MainPlayerData toPlayerData;
	CandidateData toCandidateData;
	StatusType status;
	fd_set allSocket;
	fd_set readfds;
	int fdmax, k, l;
	int n;
	int playerIndex;
	int mainPlayerSelected = 0;
	int clientId;
	int playerAnswer;
	int level;
	int numberOfClient = 0;
	int yes = 1;
	int readResult;
	int listener;
	int acceptSocket;
	struct sockaddr_in server, client;
	int sin_size;
	int socket_in_allSocket;
	int nbytes;
	int i, j;
	char clientName[40];
	initializeClientList();
	createCashPrizeList();
	sin_size = sizeof(struct sockaddr_in);
	FD_ZERO(&allSocket);
	FD_ZERO(&readfds);
	if (args < 2) {
		printf("Usage : %s <PORT>\n", argv[0]);
		exit(-1);
	}
	readResult = readQuestionFile("question.txt");
	if (readResult < 0) {
		printf("Can't load the questions !");
		exit(-1);
	}
	if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("socket() error!\n");
		exit(-1);
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server.sin_zero), 8);
	setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	if (bind(listener, (struct sockaddr*) &server, sizeof(struct sockaddr))
			== -1) {
		printf("bind() error!\n");
		exit(-1);
	}
	//listen
	if (listen(listener, 2) == -1) {
		perror("listen");
		exit(3);
	}
	FD_SET(listener, &allSocket);
	fdmax = listener;
	printf("\t<<<Gameshow GHE NONG - AI LA TRIEU PHU>>>\n");
	while (1) {

		readfds = allSocket;

		/* On error, -1 is returned, select() and pselect() return the number of file descriptors */
		if (mainPlayerSelected == 0) {
			if (select(fdmax + 1, &readfds, NULL, NULL, NULL ) == -1) {
				perror("select");
				printf("errno = %d.\n", errno);
				exit(4);
			}
		}

		for (i = 0; i <= fdmax; i++) {

			if (FD_ISSET(i, &readfds)) {
				//printf("isset i=%d\n", i);
				if (i == listener) {

					acceptSocket = accept(listener, (struct sockaddr*) &client,
							&sin_size);
					printf("Listener : %d accept %d\n", listener, acceptSocket);
					//in dia chi ip
					printf("\n client address %s\n",
							inet_ntoa(client.sin_addr));
					if (acceptSocket == -1) {
						perror("accept");

					} else if (isClientListFull()) {
						clientId = NULL_ID;
						send(acceptSocket, &clientId, sizeof clientId, 0);
						close(acceptSocket);
						//FD_CLR(acceptSocket, &allSocket);
					} else {
						FD_SET(acceptSocket, &allSocket);
						printf("Server connected with socket %d\n",
								acceptSocket);
						addClient(acceptSocket);
						clientId = acceptSocket;
						if (acceptSocket > fdmax) {
							fdmax = acceptSocket;
							//printf("Now fdmax is : %d\n", fdmax);
						}
						send(acceptSocket, &clientId, sizeof clientId, 0);
						numberOfClient = getNumberOfClient();
						printf("We're now having %d clients connected !\n",
								numberOfClient);
					}

				} else {
//					printf("i before switch = %d Fmax=%d\n", i, fdmax);
					switch_case: switch (getClientStatus(i)) {
					case CONNECTED:
						if ((nbytes = recv(i, &toCandidateData,
								sizeof toCandidateData, 0)) <= 0) {
							printf(
									"Server stopped connecting to client id %d\n",
									i);
							close(i);
							removeClient(i);
							printf("%d clients left !\n", getNumberOfClient());
							FD_CLR(i, &allSocket);
							break;
						} else {
							recv(i, clientName, sizeof clientName, 0);
							setClientStatus(i, WAITING, clientName);
							strcpy(message, "Welcome : ");
							strcat(message, clientName);
							strcat(message, "\n");
							strcpy(toCandidateData.message, message);
							toCandidateData.status = WAITING;
							send(i, &toCandidateData, sizeof toCandidateData,
									0);
							printClientList();
							/* check if have enough 6 clients, so we can start the game */
							if (readyToStart()) {
								printf("We can start the game !!\n");
								k = randomNumber(NUMBERS_PER_QUES);
								//send question to all the clients //
								for (j = 0; j < BACKLOG; j++) {
									setCompetition(j);
									copyQuestion(&(toCandidateData.question),
											questLib[0][k]);
									toCandidateData.ansTime = 0;
									toCandidateData.status = COMPETING;
									strcpy(toCandidateData.message,
											QUICK_QUESTION_MESSAGE);
									send(clientInfo[j].id, &toCandidateData,
											sizeof(CandidateData), 0);
								}
								//get the answer back from them //
								for (j = 0; j < BACKLOG; j++) {
									if (recv(clientInfo[j].id, &toCandidateData,
											sizeof toCandidateData, 0) <= 0) {
										printf(
												"Server stopped connecting to client id %d\n",
												i);
										close(i);
										removeClient(i);
										printf("%d clients left !\n",
												getNumberOfClient());
										FD_CLR(i, &allSocket);
									} else {
										clientInfo[j].quick_answer =
												toCandidateData.answer;
										clientInfo[j].ansTime =
												toCandidateData.ansTime;
									}
								}
								//printf("Sending question done!\n");
								printClientsAnswerList();
								//select the main player //
								playerIndex = selectMainPlayer(questLib[0][k],
										BACKLOG);
								printf(
										"Our answer for the quick question : %d\n",
										questLib[0][k].ans);
								printf("====MAIN PLAYER SELECTED : %s ====\n",
										clientInfo[playerIndex].clientName);
								printClientStatus(clientInfo[playerIndex].id);
								startGame(playerIndex);

								for (j = 0; j < BACKLOG; j++) {
									if (j != playerIndex) {
										strcpy(toCandidateData.message,
												JOINER_MESSAGE);
									} else {
										strcpy(toCandidateData.message,
												MAIN_PLAYER_SELECTED);
										strcpy(toPlayerData.name,
												clientInfo[j].clientName);
									}
									toCandidateData.status = getClientStatus(
											clientInfo[j].id);
									send(clientInfo[j].id, &toCandidateData,
											sizeof(CandidateData), 0);

								}
								printClientList();
								//printf("Current i = %d\n", i);
								i = clientInfo[playerIndex].id;
								mainPlayerSelected = 1;
								goto switch_case;
//								break;
							} else {
								sprintf(message,
										"We now have %d players online, please wait until we have more %d client(s) !\n",
										getNumberOfClient(),
										BACKLOG - getNumberOfClient());
								strcpy(toCandidateData.message, message);
								send(i, &toCandidateData,
										sizeof toCandidateData, 0);

							}
						}
						break;
					case JOINING:
						//printf("[JOINING] Current i = %d\n", i);
//						i = 0;
//						if (mainPlayerSelected == 1) {
//							if ((nbytes = recv(i, &toCandidateData,
//									sizeof toCandidateData, 0)) <= 0) {
//								printf(
//										"Server stopped connecting to client id %d\n",
//										i);
//								close(i);
//								removeClient(i);
//								printf("%d clients left !\n",
//										getNumberOfClient());
//								FD_CLR(i, &allSocket);
//								break;
//							}
//						}
						break;
					case PLAYING:
						mainPlayerSelected = 1;
						initializeMainPlayerData(&toPlayerData);
						level = 1;
						do {
							selectQuestion(level, &toPlayerData);
							send(clientInfo[playerIndex].id, &toPlayerData,
									sizeof toPlayerData, 0);
							for (n = 0; n < BACKLOG; n++) {
								if (clientInfo[n].status == JOINING) {
									send(clientInfo[n].id, &toPlayerData,
											sizeof toPlayerData, 0);
								}
							}
							if (recv(i, &playerAnswer, sizeof playerAnswer, 0)
									<= 0) {
								printf(
										"Server stopped connecting to client id %d\n",
										i);
								close(i);
								removeClient(i);
								printf("%d clients left !\n",
										getNumberOfClient());
								FD_CLR(i, &allSocket);
								gameFinish(&toPlayerData,END);
								for (n = 0; n < BACKLOG; n++) {
									if (clientInfo[n].status == JOINING) {
										toPlayerData.status = FINISHED;
										send(clientInfo[n].id, &toPlayerData,
												sizeof toPlayerData, 0);
										close(clientInfo[n].id);
										removeClient(clientInfo[n].id);
										FD_CLR(clientInfo[n].id, &allSocket);
									}
								}
								continue;
							}

							if (playerAnswer == RIGHT) {
								printf("Good job! The player gave a right answer!\n");
								increaseQuestion(&toPlayerData);
								//tra loi dung o cau hoi so 15
								if (level == MAX_LEVEL) {
									wonGame(&toPlayerData);
									send(i, &toPlayerData, sizeof toPlayerData,
											0);
									for (n = 0; n < BACKLOG; n++) {
										if (clientInfo[n].status == JOINING) {
											send(clientInfo[n].id,
													&toPlayerData,
													sizeof toPlayerData, 0);
											close(clientInfo[n].id);
											removeClient(clientInfo[n].id);
											FD_CLR(clientInfo[n].id,
													&allSocket);
										}
									}
									close(i);
									removeClient(i);
									FD_CLR(i, &allSocket);
									exit(1);
								}
								level = level + 1;
							} else {
								endGame(&toPlayerData, playerAnswer);
								gameFinish(&toPlayerData,playerAnswer);
								send(i, &toPlayerData, sizeof toPlayerData, 0);
								for (n = 0; n < BACKLOG; n++) {
									if (clientInfo[n].status == JOINING) {
										toPlayerData.status = FINISHED;
										send(clientInfo[n].id, &toPlayerData,
												sizeof toPlayerData, 0);
										close(clientInfo[n].id);
										removeClient(clientInfo[n].id);
										FD_CLR(clientInfo[n].id, &allSocket);
									}
								}
								close(i);
								removeClient(i);
								printf("%d clients left !\n",
										getNumberOfClient());
								FD_CLR(i, &allSocket);
							}
						} while (playerAnswer == RIGHT && level <= MAX_LEVEL);
						printf("The game of player : %s ended !\n",
								toPlayerData.name);
						exit(1);
						break;
					default:
						break;
					}

				}
			}

		}

	}
}
