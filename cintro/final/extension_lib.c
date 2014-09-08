#include "extension_lib.h"

int solve() {
	Game personList[MAXSIZE];
	int numberOfPerson;
  	int choice;
  	char guessStr[MAXSIZE];
  	int option1Choose = 0;

  	while(1) {
      	choice = menu();

      	switch(choice) {
	        case 1:
    	    printf("You choose option %d\n", choice);
        	numberOfPerson = option1(personList, guessStr);
        	printf("\nThe player list:\n");
        	printPersonList(personList, numberOfPerson);
        	option1Choose = 1;
        	continue;
        	case 2:
        	printf("You choose option %d\n", choice);
        	if(!option1Choose) {
        		printf("Please choose option 1 first!\n");
        		continue;
        	}
        	option2(personList, numberOfPerson, guessStr);
        	continue;
        	case 3:
        	printf("You choose option %d\n", choice);
        	if(!option1Choose) {
        		printf("Please choose option 1 first!\n");
        		continue;
        	}
        	option3(personList, numberOfPerson);
	        continue;
        	case 4:
        	printf("You choose option %d\n", choice);
        	printf("Bye bye\n");
        	break;
        	default:
        	printf("It is not an option\n");
        	continue;
        }
      	break;
    }
	return 0;
}

int option1(Game *personList, char *guessStr) {
	int numberOfPerson;
	int i, j;

	printf("Please enter the number of people\n");
	numberOfPerson = getIntBetween(1, 4);

	printf("Please enter the string\n");
	handleString(guessStr);

	for(i = 0; i < numberOfPerson; i++) {
		printf("Person #%d\n", i + 1);
		printf("Please enter the name:\n");
		getString(personList[i].name);
		printf("How old is he (she)?\n");
		personList[i].age = getIntBetween(1, 100);

		for(j = 0; j < 4; j++) {
			personList[i].score[j] = 0;
		}
	}

	return numberOfPerson;
}

void handleString(char *str) {
	int i, length;

	do {
		getString(str);
		length = strlen(str);
		if(length < 20 || length > 40) {
			printf("Please enter a string which has length between 20 and 40\n");
		}

		if(hasSpace(str)) {
			printf("Please enter a non-space string\n");
		}
	} while(length < 20 || length > 40 || hasSpace(str));

	for(i = 0; i < strlen(str); i++) {
		str[i] = tolower(str[i]);
	}
}

int hasSpace(char *str) {
	int i;

	for(i = 0; i < strlen(str); i++) {
		if(str[i] == ' ') {
			return 1;
		}
	}

	return 0;
}

void printPersonList(Game *personList, int amount) {
	int i;

	printf("%-20s%-20s\n", "Full name", "Age");

	for(i = 0; i < amount; i++) {
		printf("%-20s%-20d\n", personList[i].name, personList[i].age);
	}
}

void option2(Game *personList, int amount, char *guessStr) {
	char displayString[MAXSIZE];
	char guessChar;
	char guessString[MAXSIZE];
	int i, j;

	makeDisplayString(displayString, strlen(guessStr));

	for(i = 0; i < amount; i++) {
		printf("Person #%d: %s\n", i + 1, personList[i].name);
		for(j = 0; j < 4; j++) {
			printf("Turn %d\n", j + 1);
			printf("Please enter your guess letter:\n");
			guessChar = getChar();
			updateScore(personList, i, j, updateDisplayString(guessStr, displayString, guessChar));
			printf("The current string:\n\t%s\n", displayString);
		}

		printf("Please enter the guess string:\n");
		getString(guessString);

		if(strcmp(guessString, guessStr) == 0) {
			personList[i].score[4] += 20;
			printf("Congratulation! You win!!!!\n");
		} else {
			printf("Better luck next time!\n");
		}

		makeDisplayString(displayString, strlen(guessStr));
	}

	displayResult(personList, amount);
}

char getChar() {
	char res;

	while(scanf("%c", &res) != 1) {
		printf("Please enter again!\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	res = tolower(res);

	return res;
}

void makeDisplayString(char *displayString, int length) {
	int i;

	for(i = 0; i < length; i++) {
		displayString[i] = '*';
	}
	displayString[i] = '\0';
}

int updateDisplayString(char *guessStr, char *displayString, char updateChar) {
	int i;
	int counter = 0;

	for(i = 0; i < strlen(displayString); i++) {
		if(guessStr[i] == updateChar && displayString[i] != updateChar) {
			displayString[i] = updateChar;
			counter++;
		}
	}

	return counter;
}

void updateScore(Game *personList, int index, int turn, int score) {
	personList[index].score[turn] = score;
	personList[index].score[4] += score;
}

void displayResult(Game *personList, int amount) {
	int i;

	printf("\n\tThe result\n");
	printf("%-20s%-6s%-6s%-6s%-6s%-10s\n", "Name", "L1", "L2", "L3", "L4", "Result");
	for(i = 0; i < amount; i++) {
		printf("%-20s%-6d%-6d%-6d%-6d%-10d\n", personList[i].name, personList[i].score[0], personList[i].score[1], personList[i].score[2],
			personList[i].score[3], personList[i].score[4]);
	}
	printf("\n");
}

void option3(Game *personList, int amount) {
	qsort(personList, amount, sizeof(Game), personCompare);
	displayRanking(personList, amount);
}

void displayRanking(Game *personList, int amount) {
	int i;

	printf("Ranking:\n");
	printf("%-5s%-20s%-10s\n", "#", "Full name", "Result");
	for(i = 0; i < amount; i++) {
		printf("%-5d%-20s%-10d\n", i + 1, personList[amount - i - 1].name, personList[amount - i - 1].score[4]);
	}
}

int personCompare(const void* a, const void* b) {
	Game *x = (Game*)a;
	Game *y = (Game*)b;

	return x->score[4] - y->score[4];
}