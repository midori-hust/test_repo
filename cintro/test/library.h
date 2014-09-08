#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "my_input_lib.h"

#define MAXLENGTH 100

typedef struct _Result {
	char name[30];
	int point[5];
	int sumPoint;
} Result;

int solve();
void signUp(Result *athletic, int amount);
void gameOn(Result *athletic, int amount);
void printList(Result *athletic, int amount);
void printResult(Result *athletic, int amount);
void giveReward(Result *athletic, int amount);
void giveAward(int medal, Result *athletic, int position);
void findSuperSniper(Result *athletic, int amount);

#endif