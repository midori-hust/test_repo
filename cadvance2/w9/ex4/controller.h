#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "my_input_lib.h"
#include "file_handle.h"
#include "my_jval_util.h"

#define TEMP_CONTROLLER_SIZE 100

enum TYPE {
	INTERGER = 1,
	STRING = 2,
	STRUCT = 3,
	NONE = 4,
};

typedef struct _TestStruct {
	int x;
	int y;
} TestStruct;

int createData(Jval *array, int type);
void sequentialSearchController(Jval *array, int amount, int type);
void sortController(Jval *array, int amount, int type);
void binarySearchController(Jval *array, int amount, int type);
void printController(Jval *array, int amount, int type);

void makeIntegerData(Jval *array, int amount);
void makeStringData(Jval *array, int amount);
void makeStructData(Jval *array, int amount);

void printIntJval(Jval *array, int amount);
void printStrJval(Jval *array, int amount);
void printStructJval(Jval *array, int amount);
void printJval(Jval *array, int amount, void (*printData)(Jval*));

int intCompare(Jval *a, Jval *b);
int strCompare(Jval *a, Jval *b);
int structCompare(Jval *a, Jval *b);

int utilityFunction(int x, int y);
Jval getStructJval();

#endif