#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"

#define MAXSIZE 100
#define SIZE 100
#define TEMPSIZE 50

typedef struct _String {
	char content[MAXSIZE];
} String;

typedef struct _question {
	char question[MAXSIZE];
	char option1[MAXSIZE];
	char option2[MAXSIZE];
	char option3[MAXSIZE];
	int answer;
} Question;

int solve();

void makeQuestion(Question *questionList, int amount);
void getQuestion(Question *questionList, int index);
void getString(char *str);
void printQuestion(Question *questionList, int index);
void swap(char *a, char *b);

void option1(Question *questionList, int amount);
void option2(Question *questionList, int amount);
void option3(Question *questionList, int amount);

int getQuestionIndex(int amount);
char* getAnswer(Question *questionList, int amount, int index, int option);
void getQuestionSet(Question *questionList, int amount, int *questionSet, int sizeOfSet);
void gameOn(Question *questionList, int amount, int *questionsSet, int sizeOfSet, char *playerName);
void printResult(Question *questionList, int amount, int *questionsSet, int sizeOfSet, char *playerName, int *answerList);

#endif