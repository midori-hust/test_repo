#ifndef __MY_INPUT_LIB_H__
#define __MY_INPUT_LIB_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFF_LENGTH 100

int getInt();
float getFloat();
int menu();
FILE* openFile(char *filename, char *extension);
void handleMenu();
int getContinueRequest();
void* myMalloc(int size, int total);

#endif