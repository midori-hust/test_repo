#ifndef __LIB_H__
#define __LIB_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100

typedef struct _String {
	char content[MAXLENGTH];
} String;

typedef struct _Result {
	String name;
	float suggest[4];
	float offset;
} Result;

int solve();
void getPlayer(Result *person, int amount);
void gameOn(Result *person, int amount, int secretNumber);
void guessNumber(Result *person, int playerIndex, int secretNumber);
void printPlayer(Result *person, int amount);
void printResult(Result *person, int amount);
void printRankingResult(Result *person, int amount);
int findPerson(Result *person, int amount);


float myAbs(float number);
int getInt();
float getFloat();
int menu();

#endif