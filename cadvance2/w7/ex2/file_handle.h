#ifndef __FILE_HANDLE_H__
#define __FILE_HANDLE_H__

#include "my_input_lib.h"

#define MAXLENGTH 100

typedef struct _String {
	char content[MAXLENGTH];
} String;

int getTheNumberOfRowInFile(FILE *f);
void printToFile(FILE *f, char *pattern, String *array, int amount);
void loadFromFile(FILE *f, char *pattern, String *array, int amount);

#endif