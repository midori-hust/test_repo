#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>
#include <ctype.h>

#include "my_input_lib.h"

#define MAXSIZE 100
#define SIZE 100
#define TEMPSIZE 50

typedef struct _Game {
	char name[MAXSIZE];
	int age;
	int score[MAXSIZE];
} Game;

int solve();
int option1(Game *personList, char *guessStr);
void option2(Game *personList, int amount, char *guessStr);
void option3(Game *personList, int amount);

void handleString(char *str);
int hasSpace(char *str);

void printPersonList(Game *personList, int amount);
int updateDisplayString(char *guessStr, char *displayString, char updateChar);
void updateScore(Game *personList, int index, int turn, int score);
void makeDisplayString(char *displayString, int length);
void displayResult(Game *personList, int amount);
void displayRanking(Game *personList, int amount);
char getChar();
int personCompare(const void* a, const void* b);

#endif