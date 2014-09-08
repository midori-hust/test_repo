#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"

#define MAXLENGTH 100
#define MAXSIZE 1000

typedef struct _Student {
	int id;
	char name[MAXLENGTH];
} Student;

int solve();
int myIntCompare(void const* a, void const* b);
int myStudentCompare(void const* a, void const* b);
int mySearch(void *buf, int size, int total, void *item, int (*compare)(void const*, void const*));
void printIntList(int *a, int amount);
void* myMalloc(int size, int total);

#endif