#include "extension_lib.h"

int solve() {
  	int choice;
  	Question *questionList;
  	int numberOfQuestion = 5;

  	if((questionList = myMalloc(sizeof(Question), SIZE)) == NULL) {
  		return 1;
  	}

  	makeQuestion(questionList, numberOfQuestion);

  	while(1) {
      	choice = menu();

	    switch(choice) {
	        case 1:
	        printf("You choose option %d\n", choice);
	        option1(questionList, numberOfQuestion);
	        continue;
	        case 2:
	        printf("You choose option %d\n", choice);
	        option2(questionList, numberOfQuestion);
	        continue;
	        case 3:
	        printf("You choose option %d\n", choice);
	        option3(questionList, numberOfQuestion);
	        continue;
	        case 4:
	        printf("You choose option %d\n", choice);
	        printf("Bye bye\n");
	        free(questionList);
	        break;
	        default:
	        printf("It is not an option\n");
	        continue;
	    }
      	break;
    }

	return 0;
}

void makeQuestion(Question *questionList, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("Question %d\n", i + 1);
		getQuestion(questionList, i);
	}
}

void getQuestion(Question *questionList, int index) {
	int temp;

	printf("Enter the question:\n");
	getString(questionList[index].question);
	printf("Enter the option 1:\n");
	getString(questionList[index].option1);
	printf("Enter the option 2:\n");
	getString(questionList[index].option2);
	printf("Enter the option 3:\n");
	getString(questionList[index].option3);
	printf("The correct answer is:\n");
	do {
		temp = getInt();
		if(temp < 1 || temp > 3) {
			printf("Something's wrong, we don't have option %d\nPlease enter the correct answer again!\n", temp);
		}
	} while(temp < 1 || temp > 3);

	questionList[index].answer = temp;
}

void getString(char *str) {
	fgets(str, MAXSIZE, stdin);
	str[strlen(str) - 1] = '\0';
}

void printQuestion(Question *questionList, int index) {
	printf("Question #%d: %s\n", index, questionList[index].question);
	printf("1. %s\n", questionList[index].option1);
	printf("2. %s\n", questionList[index].option2);
	printf("3. %s\n", questionList[index].option3);
}

void swap(char *a, char *b) {
	char temp[MAXSIZE];

	strcpy(temp, a);
	strcpy(a, b);
	strcpy(b, temp);
}

void option1(Question *questionList, int amount) {
	int index;

	printf("Please enter the question index:\n");
	index = getQuestionIndex(amount);

	printQuestion(questionList, index - 1);
}

void option2(Question *questionList, int amount) {
	int index;
	int newCorrect;

	printf("Please enter the question which you want to change the correct answer\n");
	index = getQuestionIndex(amount);

	printf("Please enter the new correct answer\n");
	do {
		newCorrect = getQuestionIndex(3);
		if(newCorrect == questionList[index - 1].answer) {
			printf("This is old correct answer. Please choos another option!\n");
		}
	} while(newCorrect == questionList[index - 1].answer);

	swap(getAnswer(questionList, amount, index - 1, questionList[index - 1].answer), getAnswer(questionList, amount, index - 1, newCorrect));
	questionList[index - 1].answer = newCorrect;
	printf("Change answer successfully\n");
}

void option3(Question *questionList, int amount) {
	String player[5];
	int i, j, k = 0;
	int questionsSet[5];
	int temp;

	printf("Please enter the information in form below\n");
	for(i = 0; i < 3; i++) {
		printf("Player %d\n", i + 1);
		printf("What is your name?\n");
		getString(player[i].content);

		printf("Please enter the set of 3 unique questions:\n");
		getQuestionSet(questionList, amount, questionsSet, 3);
	}

	for(i = 0; i < 3; i++) {
		gameOn(questionList, amount, questionsSet, 3, player[i].content);
	}
}

int getQuestionIndex(int amount) {
	int res;

	do {
		res = getInt();
		if(res < 1 || res > amount) {
			printf("This question does not exist. Please enter the question index again!\n");
		}
	} while(res < 1 || res > amount);	

	return res;
}

char* getAnswer(Question *questionList, int amount, int index, int option) {
	switch(option) {
		case 1:
		return questionList[index].option1;
		case 2:
		return questionList[index].option2;
		case 3:
		return questionList[index].option3;
	}

	return NULL;
}

void getQuestionSet(Question *questionList, int amount, int *questionsSet, int sizeOfSet) {
	int i, j = 0;
	int temp;

	while(1) {
		temp = getQuestionIndex(5);
		for(i = 0; i < j; i++) {
			if(temp == questionsSet[i]) {
				printf("Please enter this question again\n");
				continue;
			}
		}

		questionsSet[j++] = temp;
		if(j == sizeOfSet) {
			break;
		}
	}
}

void gameOn(Question *questionList, int amount, int *questionsSet, int sizeOfSet, char *playerName) {
	int i;
	int answerList[5];

	printf("Player %s's turn\n", playerName);

	for(i = 0; i < sizeOfSet; i++) {
		printf("Question %d:\n", i + 1);
		printf("%s\n", questionList[questionsSet[i]].question);
		printf("\tOption 1. %s\n", questionList[questionsSet[i]].option1);
		printf("\tOption 2. %s\n", questionList[questionsSet[i]].option2);
		printf("\tOption 3. %s\n", questionList[questionsSet[i]].option3);
		printf("And your final answer is:\n");
		answerList[i] = getQuestionIndex(3);
	}

	printResult(questionList, amount, questionsSet, sizeOfSet, playerName, answerList);
}

void printResult(Question *questionList, int amount, int *questionsSet, int sizeOfSet, char *playerName, int *answerList) {
	int i, j, total = 0;

	printf("\nPlay result:\n");
	printf("Player name: %s\n", playerName);
	printf("%-10s%-10s%-10s%-10s\n", "Question #", "Choice", "Correct", "Point");
	for(i = 0; i < sizeOfSet; i++) {
		printf("%-10d%-10d%-10d", questionsSet[i], answerList[i], questionList[questionsSet[i]].answer);
		if(answerList[i] == questionList[questionsSet[i]].answer) {
			total++;
			printf("%-10d\n", 1);
		} else {
			printf("%-10d\n", 0);
		}
	}

	printf("Total: %d\n\n", total);
}