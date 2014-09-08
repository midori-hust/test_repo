#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"

#define MAXSIZE 100
#define SIZE 100
#define TEMPSIZE 50

typedef struct _Data {
	int output[SIZE];
} Data;

int solve();

void getPrimeMultipleList(int num, int *output, int *size);
void getAllMultipleList(int *output, int size);
void printList(int *output, int amount);

#endif