#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"

#define MAXLENGTH 100
#define MAXSIZE 1000

typedef struct _record  {
	char product[MAXLENGTH];
	float price;
} Record;

int solve();
int recordCompare(void const*x, void const *y);
Record* mallocRecord(int amount);
void printArray(Record *array, int amount);

#endif