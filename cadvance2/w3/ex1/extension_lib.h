#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"

#define MAXLENGTH 100
#define MAXSIZE 10000
#define MAX 10000
#define MINSIZE 10000

typedef struct _bigObj {
	int key;
	int content[MAXSIZE];
} BigObj;


BigObj* mallocBigObjStruct(int amount);
void genBigObjData(BigObj *bigObj, int amount);
void printListObj(BigObj *bigObj, int amount);
BigObj* clone(BigObj *source, int amount); // Not work
void selectionSort(BigObj *bigObj, int n);
void swap(BigObj *a, BigObj *b);
void quickSort(BigObj *bigObj, int left, int right);
int choosePivot(int left, int right);
int solve();
BigObj* extendList(BigObj *bigObj, int size, int new_size);
BigObj* mallocListObj(int amount);
int getTheNumberOfTimesExtending();

#endif