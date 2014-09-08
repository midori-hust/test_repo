#ifndef __MY_INPUT_LIB_H__
#define __MY_INPUT_LIB_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFF_LENGTH 100

int getInt();
float getFloat();
void getString(char *str);
int getIntBetween(int lower, int upper);
int menu();
void handleMenu();
int getContinueRequest();
void* myMalloc(size_t size, size_t total);

#endif