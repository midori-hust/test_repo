#include "lib.h"

int solve() {
	int choice;
	Result person[MAXLENGTH];
	int n;
	float guessingNum = -1;
	int case1 = 0;

	while(1) {
		switch(choice = menu()) {
			case 1:
			printf("You choose option %d\n", choice);
			do {
				printf("Please enter the guessing number:\n");
				guessingNum = getFloat();
				if(guessingNum < 1 || guessingNum > 100) {
					printf("Please enter another number!\n");
				}
			} while(guessingNum < 1 || guessingNum > 100);
			
			do {
				printf("Please enter the number of players\n");
				n = getInt();	
				if(n < 1 || n > 5) {
					printf("Please enter another number!\n");	
				}
			} while(n < 1 || n > 5);
			
			getPlayer(person, n);
			printPlayer(person, n);
			case1 = 1;
			continue;
			case 2:
			printf("You choose option %d\n", choice);
			if(!case1) {
				printf("Please choose case 1 first!\n");
				continue;
			}
			gameOn(person, n, guessingNum);
			printResult(person, n);
			continue;
			case 3:
			printf("You choose option %d\n", choice);
			if(!case1) {
				printf("Please choose case 1 first!\n");
				continue;
			}
			printRankingResult(person, n);
			continue;
			case 4:
			printf("You choose option %d\n", choice);
			if(!case1) {
				printf("Please choose case 1 first!\n");
				continue;
			}
			if(!findPerson(person, n)) {
				printf("Cannot find this person!\n");
			}
			continue;
			case 5:
			printf("You choose option %d\n", choice);
			break;
			default:
			printf("Invalid choice!\n");
			continue;
		}
		break;
	}

	return 0;
}

void getPlayer(Result *person, int amount) {
	int i, j;
	int spaceChecker = 0;
	String temp;

	for(i = 0; i < amount; i++) {
		do {
			printf("Player %d\n", i + 1);
			fgets(temp.content, MAXLENGTH, stdin);
			temp.content[strlen(temp.content) - 1] = '\0';

			for(j = 0; j < strlen(temp.content); j++) {
				if(temp.content[j] == ' ') {
					spaceChecker = 1;
					break;
				}
			}

			if(!spaceChecker) {
				printf("Please enter the name which have a space\n");
			}
		} while(!spaceChecker);

		strcpy(person[i].name.content, temp.content);
		for(j = 0; j < 5; j++) {
			person[i].suggest[j] = 0;
		}
		person[i].offset = 0;

		spaceChecker = 0;
	}
}

void gameOn(Result *person, int amount, int secretNumber) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("Player %s's turn\n", person[i].name.content);
		guessNumber(person, i, secretNumber);
	}
}

void guessNumber(Result *person, int playerIndex, int secretNumber) {
	int i;
	float guessNum;

	for(i = 0; i < 4; i++) {
		guessNum = getFloat();
		person[playerIndex].suggest[i] = guessNum;

		if(guessNum == secretNumber) {
			printf("Congratulation, you won!\n");
			person[playerIndex].offset = 0;
			return;
		}

		if(guessNum < secretNumber) {
			printf("This number is less than the secret number!\n");
		} else  {
			printf("This number is more than the secret number!\n");
		}
	}

	person[playerIndex].offset = myAbs((float)person[playerIndex].suggest[3] / 4.0 - 1);
}

void printPlayer(Result *person, int amount) {
	int i;

	printf("\n\n\tList players: \n");
	for(i = 0; i < amount; i++) {
		printf("Player %d\n", i + 1);
		printf("Name: %s\n", person[i].name.content);
	}	
}

void printResult(Result *person, int amount) {
	int i, j;

	printf("\n\tResult\n");
	printf("%20s%5s%5s%5s%5s\n", "Player's name", "1st", "2nd", "3rd", "4th");
	for(i = 0; i < amount; i++) {
		printf("%-20s", person[i].name.content);
		for(j = 0; j < 4; j++) {
			printf("%5.1f", person[i].suggest[j]);
		}
		printf("\n");
	}
	printf("\n");
}

void printRankingResult(Result *person, int amount) {
	int i, j, counter = 0;

	printf("\n\tResult!\n");
	printf("%-20s%-10s\n", "Player's name", "Offset");

	for(j = 0; j < 100; j++) {
		for(i = 0; i < amount; i++) {
			if(person[i].offset <= j && person[i].offset > j - 1) {
				counter++;
				printf("%-20s%-10f\n", person[i].name.content, person[i].offset);
			}
		}

		if(counter == amount) {
			return;
		}
	}
}

int findPerson(Result *person, int amount) {
	int i;
	String temp;
	float tempOffset;
	int flag = 0;

	printf("Please enter the name\n");
	fgets(temp.content, MAXLENGTH, stdin);
	temp.content[strlen(temp.content) - 1] = '\0';

	printf("Please enter the offset\n");
	tempOffset = getFloat();

	for(i = 0; i < amount; i++) {
		if(strstr(person[i].name.content, temp.content) != NULL) {
			if(person[i].offset <= tempOffset) {
				printf("Found! Player %s who has offset %f\n", person[i].name.content, person[i].offset);
				flag = 1;
			}
		}
	}

	return flag;
}

/**/

float myAbs(float number) {
	return number < 0 ? 0 - number : number;
}

int getInt() {
	int result;

	while(scanf("%d", &result) != 1) {
		printf("Invalid input! Please try again\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	return result;
}

float getFloat() {
	float result;

	while(scanf("%f", &result) != 1) {
		printf("Invalid input! Please try again\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	return result;
}

int menu() {
	int choice;

	printf("\tMENU\n");
	printf("1. Setup game\n");
	printf("2. Game on\n");
	printf("3. Ranking\n");
	printf("4. Find person\n");
	printf("5. Exit program\n");

	do {
		printf("What do you want?\n");
		choice = getInt();
		if(choice < 1 || choice > 5) {
			printf("Please enter the number in [1, 5]\n");
		}
	} while(choice < 1 || choice > 5);

	return choice;
}