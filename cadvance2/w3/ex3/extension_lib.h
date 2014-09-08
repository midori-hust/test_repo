#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"

#define MAXLENGTH 100

typedef struct _String {
	char content[MAXLENGTH];
} String;

void insertionSort(String *array, int n);
void exch(String *a, int i, int j);
String* mallocStringStruct(int amount);
void printArray(String *a, int amount);
int solve(FILE *f);
void printToFile(FILE *f, char *pattern, String *array, int amount);
int getTheNumberOfRowInFile(FILE *f);

#endif