#include "mlibrary.h"
int readQuestionFile(char* fileName) {

	char line[200], *s1, *s2, *s3, *s4, *s5, *s6, *s7;
	int i = 0, m;
	int j, k = 0;
	FILE *f;
	f = fopen(fileName, "r+b");
	if (f == NULL ) {
		perror("read file");
		return 0;
	} else {
		for (i = 0; i <= MAX_LEVEL; i++) {
			for (j = 0; j < NUMBERS_PER_QUES; j++) {
				if (fgets(line, 200, f) != NULL ) {
					//printf("The element [%d][%d]\n", i, j);
					s1 = strtok(line, ":");
					questLib[i][j].IDQuestion = atoi(s1);
					s2 = strtok(NULL, ":");
					strcpy(questLib[i][j].ques, s2);
					s3 = strtok(NULL, ":");
					strcpy(questLib[i][j].answerList[0], s3);
					s4 = strtok(NULL, ":");
					strcpy(questLib[i][j].answerList[1], s4);
					s5 = strtok(NULL, ":");
					strcpy(questLib[i][j].answerList[2], s5);
					s6 = strtok(NULL, ":");
					strcpy(questLib[i][j].answerList[3], s6);
					s7 = strtok(NULL, ":");
					questLib[i][j].ans = atoi(s7);
					k++;
//					printf("%s ?\n", questLib[i][j].ques);
//					for (m = 0; m < 4; m++) {
//						printf("%s\n", questLib[i][j].answerList[m]);
//					}
				} else {
					return k;
				}

			}
		}

		return i;
	}

}
/* this method used when the user first connected to the server */
void initializeCandidateData(CandidateData *toCandidateData) {
	toCandidateData->ansTime = 0;
}

/*this method used when the player first start the game, set all the field to start point */
void initializeMainPlayerData(MainPlayerData *toMainPlayerData) {
	int i = 0;
	toMainPlayerData->status = PLAYING;
	strcpy(toMainPlayerData->message, MAIN_PLAYER_BEGIN);
	toMainPlayerData->help_choice = HELP_CHOICES;/* have full helps */
	toMainPlayerData->level = 1;
	for (i = 0; i < 4; i++) {
		toMainPlayerData->selectionStatus[i] = AVAILABLE;
	}
}

/* add a client whose Id is clientId to the clientList,
 * return 1 if client has been added successfully
 * return 0 if the client list is full
 */
int addClient(int clientId) {
	int i = 0;
	for (i = 0; i < BACKLOG; i++) {
		if (clientInfo[i].status == EMPTY) {
			clientInfo[i].id = clientId;
			clientInfo[i].status = CONNECTED;
			printf("Client id %d has been added successfully !\n", clientId);
			return 1; /* client has been add to client list */
		}
	}
	return 0; /* the client list is full ! so return fail because the client cannot be added to client list */
}

/*initialize the client list with 6 available rooms
 *
 */
void initializeClientList() {
	int i;
	for (i = 0; i < BACKLOG; i++) {
		clientInfo[i].status = EMPTY;
		clientInfo[i].id = UNDEFINED;
		clientInfo[i].quick_answer = UNDEFINED;
		clientInfo[i].ansTime = MAX_TIME_ANSWER;
	}
}

/*check whether the client list has been full with 6 clients
 *
 */
int isClientListFull() {
	int i;
	for (i = 0; i < BACKLOG; i++) {
		if (clientInfo[i].status == EMPTY)
			return 0; /* the client list isn't full, still has room for clients */
	}
	return 1; /* the client list has been full of 6 clients already */
}

/*display the message to candidates */
void displayCandidateMessage(CandidateData toCandidateData) {
	printf("%s", toCandidateData.message);
}
/*display candidate message on win mode */
//void displayCandidateMessageOnWin(CandidateData toCandidateData) {
//	printw("%s", toCandidateData.message);
//}
/* display the message to main player */
void displayPlayerMessage(MainPlayerData exchangeData) {
	printf("%s", exchangeData.message);
}

/*display the question */
void displayQuestion(Question question) {
	printf("Question : %s ?\n", question.ques);
	printf("A.%-25sB.%-25s\n", question.answerList[0], question.answerList[1]);
	printf("C.%-25sD.%-25s\n", question.answerList[2], question.answerList[3]);
}

void displayQuesWithFtyFty(MainPlayerData *mpd) {
	int i = 0;
	printf(">>>>50-50<<<<\n");
	printf("Question : %s ?\n", mpd->ques.ques);
	for (i = 0; i < 4; i++) {
		if (mpd->selectionStatus[i] == AVAILABLE) {
			switch (i) {
			case 0:
				printf("A.%-20s\n", mpd->ques.answerList[i]);
				break;
			case 1:
				printf("B.%-20s\n", mpd->ques.answerList[i]);
				break;
			case 2:
				printf("C.%-20s\n", mpd->ques.answerList[i]);
				break;
			case 3:
				printf("D.%-20s\n", mpd->ques.answerList[i]);
				break;
			default:
				break;
			}
		}
	}

}
/*display the question on win (this method is uses specially to take time spent answering quick ques */
void displayQuickQuestion(Question question) {
	printf("Question : %s ?\n", question.ques);
	printf("A.%-20sB.%-20s\n", question.answerList[0], question.answerList[1]);
	printf("C.%-20sD.%-20s\n", question.answerList[2], question.answerList[3]);
	printf(">>Your choice :");
}

StatusType getClientStatus(int id) {
	int i;
	for (i = 0; i < BACKLOG; i++) {
		if (clientInfo[i].id == id)
			return clientInfo[i].status;
	}
	//printf("Cann't get the client status !\n");
	return UNKNOWN;
}

void setCompetition(int index) {
	clientInfo[index].status = COMPETING;

}
void setClientStatus(int id, StatusType status, char name[]) {
	int i;
	for (i = 0; i < BACKLOG; i++) {
		if (clientInfo[i].id == id) {
			clientInfo[i].status = status;
			strcpy(clientInfo[i].clientName, name);
			return;
		}
	}
	printf("Cannot set the client status !\n");
}

void copyQuestion(Question *target, Question source) {
	int i = 0;
	strcpy(target->ques, source.ques);
	for (i = 0; i < 4; i++) {
		strcpy(target->answerList[i], source.answerList[i]);
	}
	target->ans = source.ans;
	target->IDQuestion = source.IDQuestion;
}

void createCashPrizeList() {
	strcpy(cashPrizeList[0], "0");
	strcpy(cashPrizeList[1], "200.000");
	strcpy(cashPrizeList[2], "400.000");
	strcpy(cashPrizeList[3], "600.000");
	strcpy(cashPrizeList[4], "1.000.000");
	strcpy(cashPrizeList[5], "2.000.000");
	strcpy(cashPrizeList[6], "4.000.000");
	strcpy(cashPrizeList[7], "6.000.000");
	strcpy(cashPrizeList[8], "10.000.000");
	strcpy(cashPrizeList[9], "14.000.000");
	strcpy(cashPrizeList[10], "22.000.000");
	strcpy(cashPrizeList[11], "30.000.000");
	strcpy(cashPrizeList[12], "40.000.000");
	strcpy(cashPrizeList[13], "60.000.000");
	strcpy(cashPrizeList[14], "85.000.000");
	strcpy(cashPrizeList[15], "150.000.000");
}

int getNumberOfClient() {
	int i;
	int numberOfClient = 0;
	for (i = 0; i < BACKLOG; i++) {
		if (clientInfo[i].status != EMPTY) {
			numberOfClient++;
		}
	}
	return numberOfClient;
}

int readyToStart() {
	int i = 0;
	for (i = 0; i < BACKLOG; i++) {
		if (clientInfo[i].status != WAITING) {
			return 0;
		}
	}

	return 1;
}
void removeClient(int clientId) {
	int i = 0;
	for (i = 0; i < BACKLOG; i++) {
		if (clientInfo[i].id == clientId) {
			clientInfo[i].id = UNDEFINED;
			clientInfo[i].status = EMPTY;
			return;
		}
	}
}
void printClientList() {
	int i = 0;
	printf("====CLIENT LIST====\n");
	for (i = 0; i < BACKLOG; i++) {
		printf("id : %d\tstatus : ", clientInfo[i].id);
		toString(clientInfo[i].status);
	}
}
void printClientsAnswerList() {
	int i = 0;
	printf("====CLIENT LIST====\n");
	for (i = 0; i < BACKLOG; i++) {
		printf("Name : %s\tid : %d\tstatus : ", clientInfo[i].clientName,
				clientInfo[i].id);
		toString(clientInfo[i].status);
		printf("Answer : %d\tTime : %.3f(s)\n", clientInfo[i].quick_answer,
				clientInfo[i].ansTime);
	}
}
void printClientStatus(int clientId) {
	int i;
	for (i = 0; i < BACKLOG; i++) {
		if (clientInfo[i].id == clientId) {
			printf("id : %d\tstatus : ", clientInfo[i].id);
			toString(clientInfo[i].status);
			printf("Answer : %d\tTime : %.3f(s)\n", clientInfo[i].quick_answer,
					clientInfo[i].ansTime);
			return;
		}
	}
	//printf("Can't get the status of client %d !\n", clientId);
}

void toString(StatusType clientStatus) {
	char status[40];
	switch (clientStatus) {
	case UNKNOWN:
		strcpy(status, "UNKNOWN");
		break;
	case EMPTY:
		strcpy(status, "EMPTY");
		break;
	case CONNECTED:
		strcpy(status, "CONNECTED");
		break;
	case JOINING:
		strcpy(status, "JOINING");
		break;
	case COMPETING:
		strcpy(status, "COMPETING");
		break;
	case PLAYING:
		strcpy(status, "PLAYING");
		break;
	case FINISHED:
		strcpy(status, "FINISHED");
		break;
	case WAITING:
		strcpy(status, "WAITING");
		break;
	default:
		strcpy(status, "ERROR");
		break;
	}
	printf("%s\n", status);
}

int timeval_subtract(struct timeval *result, struct timeval *t2,
		struct timeval *t1) {
	long int diff = (t2->tv_usec + 1000000 * t2->tv_sec)
			- (t1->tv_usec + 1000000 * t1->tv_sec);
	result->tv_sec = diff / 1000000;
	result->tv_usec = diff % 1000000;

	return (diff < 0);
}

void compete(CandidateData* cd, Question ques) {
//	WINDOW *w;
	struct timeval tvBegin, tvEnd, tvDiff;
	char c;
//	w = initscr();
//	FILE *file_id = fopen("/dev/tty", "r+");
//	SCREEN *termref = newterm(NULL, stdout, stdin);
	gettimeofday(&tvBegin, NULL );
	displayCandidateMessage(*cd);
	displayQuickQuestion(ques);
	//timeout(MAX_TIME_ANSWER);
	c = getchar();
	gettimeofday(&tvEnd, NULL );
	//delscreen(termref);
//	endwin();
	//doupdate();
//	refresh();
	timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
	cd->answer = handleQuickQuestion(c);
	cd->ansTime = (float) tvDiff.tv_sec + (float) tvDiff.tv_usec / 1000000;
	printf("Finished in about : %.3f(s)!\n", cd->ansTime);

}

int handleAnswer(char c) {
	switch (c) {
	case 'A':
	case 'a':
	case '1':
		return 1;
	case 'B':
	case 'b':
	case '2':
		return 2;
	case 'C':
	case 'c':
	case '3':
		return 3;
	case 'D':
	case 'd':
	case '4':
		return 4;
	case 'h':
	case 'H':
		return HELP_MODE;
	case 'l':
	case 'L':
		return END;

	default:
		printf("Wrong Input ! Please type your choice again !\n");
		printf(
				"\n>>Your choice (press 'H' to get help or 'L' to leave the game): ");
		while (getchar() != '\n')
			;
		return handleAnswer(getchar());
	}
}

int handleQuickQuestion(char c) {
	switch (c) {
	case 'A':
	case 'a':
	case '1':
		return 1;
	case 'B':
	case 'b':
	case '2':
		return 2;
	case 'C':
	case 'c':
	case '3':
		return 3;
	case 'D':
	case 'd':
	case '4':
		return 4;

	default:
		printf("Wrong Input ! Please type your choice again !\n");
		printf(">>Your choice : ");
		while (getchar() != '\n')
			;
		return handleAnswer(getchar());
	}
}
/*select the main player */
int selectMainPlayer(Question ques, int length) {
	int flag = 0;
	int i = 0;
	float minTime = MAX_TIME_ANSWER;
	int mainPlayer = UNDEFINED;
	int answer = ques.ans;
	for (i = 0; i < length; i++) {
		if (clientInfo[i].quick_answer == answer) {
			if (clientInfo[i].ansTime < minTime) {
				mainPlayer = i;
				minTime = clientInfo[i].ansTime;
				flag = 1;
			}
		}
	}
	if (flag == 1) {
		return mainPlayer;
	} else {
		for (i = 0; i < length; i++) {
			if (clientInfo[i].ansTime < minTime) {
				minTime = clientInfo[i].ansTime;
				mainPlayer = i;
			}
		}
		return mainPlayer;
	}
}
//set the player whose index passed is main player, others will be joining.

void startGame(int index) {
	int i = 0;
	for (i = 0; i < BACKLOG; i++) {
		if (clientInfo[i].status == COMPETING) {
			clientInfo[i].status = JOINING;
			clientInfo[i].ansTime = MAX_TIME_ANSWER;
			clientInfo[i].quick_answer = UNDEFINED;
		}
	}
	clientInfo[index].status = PLAYING;

}

void broadTheGame(MainPlayerData mpd) {

	printf("\nPLAYER'S NAME : %s\t", mpd.name);
	printf("PHAN THUONG HIEN TAI : %s (VND)\n\n", cashPrizeList[mpd.level - 1]);
	printf("\t\t>>>CAU HOI SO : %d<<<\n", mpd.level);
	displayQuestion(mpd.ques);

}

void helpHandler(MainPlayerData *mpd, int help_choice[]) {
	int i = 0;
	int choice;
	int prob, rand;
	int ans = mpd->ques.ans - 1; //ans can be 0 1 2 3
	int flag = 0;
	for (i = 0; i < HELP_CHOICES; i++) {
		if (help_choice[i] != INVALID) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		printf("You have used all the help choices!\n");
		return;
	}
	switch (mpd->help_choice) {
	case 0: //50/50
		if (help_choice[0] == INVALID) {
			printf("You have used this help !\n");
			return;
		} else {
			char c;
			fifty_fifty(mpd);
			displayQuesWithFtyFty(mpd);
			help_choice[0] = INVALID;
			return;
		}
	case 1: //phone
		if (help_choice[1] == INVALID) {
			printf("You have used this help !\n");
			return;
		} else {
			int i;
			printf("\t>>>Lua chon nguoi tro giup<<<\n");
			printf("\t1.Isaac Newton.\n");
			printf("\t2.Mark Zuckerberg.\n");
			printf("\t3.Barack Obama.\n");
			printf(">>>Your choice :");
			while (1) {
				if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 3) {
					break;
				} else {
					printf("Wrong input ! Please type your choice again !\n");
				}
			}
			switch (choice) {
			case 1: //chon Newton
				prob = randomNumber(100) + 1;
				if (prob >= 15) {
					printf("Answer of Newton : %c.%s\n",
							IntToChar(mpd->ques.ans),
							mpd->ques.answerList[ans]);
				} else {
					for (i = 0; i < 4; i++) {
						if (i != ans && mpd->selectionStatus[i] == AVAILABLE) {
							printf("Answer of Newton : %c.%s\n",
									IntToChar(i + 1), mpd->ques.answerList[i]);
							break;
						}
					}

				}
				help_choice[1] = INVALID;
				break;
			case 2: //chon Mark
				prob = randomNumber(100) + 1;
				if (prob >= 25) {
					printf("Answer of Mark Zuckerberg : %c.%s\n",
							IntToChar(mpd->ques.ans),
							mpd->ques.answerList[ans]);
				} else {
					for (i = 0; i < 4; i++) {
						if (i != ans && mpd->selectionStatus[i] == AVAILABLE) {
							printf("Answer of Mark Zuckerberg : %c.%s\n",
									IntToChar(i + 1), mpd->ques.answerList[i]);
							break;
						}
					}
				}
				help_choice[1] = INVALID;
				break;
			case 3: //chon Barack Obama
				prob = randomNumber(100) + 1;
				if (prob >= 20) {
					printf("Answer of Barack Obama : %c.%s\n",
							IntToChar(mpd->ques.ans),
							mpd->ques.answerList[ans]);
				} else {
					for (i = 0; i < 4; i++) {
						if (i != ans && mpd->selectionStatus[i] == AVAILABLE) {
							printf("Answer of Barack Obama : %c.%s\n",
									IntToChar(i + 1), mpd->ques.answerList[i]);
							break;
						}
					}
				}
				help_choice[1] = INVALID;
				break;
			}
			return;
		}
	case 2: //Ask the Audience
		if (help_choice[2] == INVALID) {
			printf("You have used this help !\n");

		} else {
			askTheAudience(mpd);
			help_choice[2] = INVALID;
		}
		break;

	default:
		return;
	}
}

/* loai di 2 dap an sai */
void fifty_fifty(MainPlayerData *mpd) {
	int ans = mpd->ques.ans - 1;
	if (ans % 2 == 0) {
		//dap an la so chan~, loai 2 dap an le
		mpd->selectionStatus[1] = INVALID;
		mpd->selectionStatus[3] = INVALID;
	} else {
		//dap an la so le, loai 2 dap an chan~.
		mpd->selectionStatus[0] = INVALID;
		mpd->selectionStatus[2] = INVALID;
	}

}
int randomNumber(int range) {
	srand((unsigned) time(NULL ));
	return (rand() % range);
}
//select a random question in a specified level
void selectQuestion(int level, MainPlayerData *mpd) {
	int ran = randomNumber(NUMBERS_PER_QUES);
	mpd->ques = questLib[level][ran];
}

//check answer of player  RIGHR or WRONG //
int checkAnswer(int playerAnswer, int answer) {

	if (playerAnswer == END) {
		return END;
	} else if (playerAnswer == answer) {
		return RIGHT;
	} else

		return WRONG;
}
/* take the next question when player have provided the right answer */
void increaseQuestion(MainPlayerData *mpd) {
	int i = 0;
	sprintf(mpd->message,
			">>>Chuc mung ! Ban da tra loi dung cau hoi so %d ! Hay den voi cau hoi tiep theo<<<\n",
			mpd->level);
	mpd->level = mpd->level + 1;
//	strcpy(mpd->message,MAIN_PLAYER_RIGHT_ANSWER);
}

void helpMenu(MainPlayerData *mpd, int help_choice[]) {
	printf(">>>HELP MENU<<<\n");
	printf("1.50-50\n");
	printf("2.Phone-a-friend.\n");
	printf("3.Ask the Audience.\n");
	printf(">>Your choice :");
	int choice;
	while (1) {
		if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 3) {
			break;
		}
		printf("Wrong input ! Please type your choice again !\n");
	}
	mpd->help_choice = choice - 1;
	helpHandler(mpd, help_choice);
}
void endGame(MainPlayerData *mpd, int choice) {
	int prizeLevel = 0;
	switch (choice) {
	case WRONG:
		if (mpd->level >= 10 && mpd->level <= 15) {
			prizeLevel = 10;
		} else if (mpd->level >= 5 && mpd->level <= 9) {
			prizeLevel = 5;
		} else {
			prizeLevel = 0;
		}
		sprintf(mpd->message,
				">>>Rat tiec ! Ban da tra loi sai ! Ban se ra ve voi so tien %s(VND)!\n",
				cashPrizeList[prizeLevel]);
		break;
	case END:
		prizeLevel = mpd->level - 1;
		sprintf(mpd->message,
				">>>Ban da quyet dinh dung cuoc choi! Ban se ra ve voi so tien %s(VND) !\n",
				cashPrizeList[prizeLevel]);
		break;
	default:
		prizeLevel = UNDEFINED;
		break;
	}
}
char IntToChar(int i) {
	switch (i) {
	case 1:
		return 'A';
	case 2:
		return 'B';
	case 3:
		return 'C';
	case 4:
		return 'D';
	}
}
void displayAnswer(Question ques) {
	int ans = ques.ans;
	printf("\nDap an cua chung toi la : %c.%s\n", IntToChar(ans),
			ques.answerList[ans - 1]);
}

void askTheAudience(MainPlayerData *mpd) {
	int i;
	int random[4];
	int ans = mpd->ques.ans - 1;
	Question question = mpd->ques;
	int flag = 0;
	for (i = 0; i < 4; i++) {
		if (mpd->selectionStatus[i] == INVALID) {
			flag = 1; //50-50 mode
			break;
		}
	}
	if (flag == 0) {
		random[ans] = randomNumber(20) + 50; //ti le cua cau tra loi dung luon tren 50%
		int remain = 100 - random[ans];
		switch (ans) {
		case 0:
			random[1] = randomNumber(remain / 3);
			random[2] = remain - (random[1] + randomNumber(remain * 11 / 20));
			random[3] = remain - (random[1] + random[2]);
			break;
		case 1:
			random[0] = randomNumber(remain / 3);
			random[2] = remain - (random[0] + randomNumber(remain * 11 / 20));
			random[3] = remain - (random[0] + random[2]);
			break;
		case 2:
			random[0] = randomNumber(remain / 3);
			random[1] = remain - (random[0] + randomNumber(remain * 11 / 20));
			random[3] = remain - (random[0] + random[1]);
			break;
		case 3:
			random[0] = randomNumber(remain / 3);
			random[1] = remain - (random[0] + randomNumber(remain * 11 / 20));
			random[2] = remain - (random[0] + random[1]);
			break;
		}
		printf("\t>>>Ask The Expert<<<\n");
		printf("A.%-25s : %d%%\nB.%-25s : %d%%\n", question.answerList[0],
				random[0], question.answerList[1], random[1]);
		printf("C.%-25s : %d%%\nD.%-25s : %d%%\n", question.answerList[2],
				random[2], question.answerList[3], random[3]);

	} else {
		int random[2];
		char c;
		random[0] = randomNumber(25) + 55;
		random[1] = 100 - random[0];
		for (i = 0; i < 4; i++) {
			if (mpd->selectionStatus[i] == AVAILABLE) {

				if (i == ans) {
					printf("%c.%-25s : %d%%\n", IntToChar(i + 1),
							mpd->ques.answerList[i], random[0]);
				} else {
					printf("%c.%-25s : %d%%\n", IntToChar(i + 1),
							mpd->ques.answerList[i], random[1]);
				}

			}
		}
	}
	return;
}
void wonGame(MainPlayerData *mpd) {
	sprintf(mpd->message,
			">>>Chuc mung! Ban da xuat sac vuot qua 15 cau hoi! Ban se ra ve voi so tien %s(VND)!<<<\n",
			cashPrizeList[MAX_LEVEL]);
			mpd->status==FINISHED;
}
void gameFinish(MainPlayerData *mpd, int choice) {
	int prizeLevel = 0;
	switch (choice) {
	case WRONG:
		if (mpd->level >= 10 && mpd->level <= 15) {
			prizeLevel = 10;
		} else if (mpd->level >= 5 && mpd->level <= 9) {
			prizeLevel = 5;
		} else {
			prizeLevel = 0;
		}
		sprintf(mpd->message,
				">>>Ban %s da ket thuc phan choi cua minh! Ban se ra ve voi so tien %s(VND)!\n",
				mpd->name, cashPrizeList[prizeLevel]);
		break;
	case END:
		prizeLevel = mpd->level - 1;
		sprintf(mpd->message,
				">>>Ban %s da ket thuc phan choi cua minh! Ban se ra ve voi so tien %s(VND)!\n",
				mpd->name, cashPrizeList[prizeLevel]);
		break;
	default:
		prizeLevel = UNDEFINED;
		break;
	}
}
