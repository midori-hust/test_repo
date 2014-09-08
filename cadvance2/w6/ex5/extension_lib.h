#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"

#define MAXLENGTH 100
#define MAXSIZE 10

typedef struct _Student {
	int id;
	char name[MAXLENGTH];
} Student;

int solve();
void genData(Student *a, int amount);
int* testFunction(int *amt);

/* Function pointers */
int myIntCompare(void const* a, void const* b);
int myStudentCompare(void const* a, void const* b);
int findMaxCompare(void const* x, void const* y);
int findMinCompare(void const* x, void const* y);
void myPrintPattern(void *buf, char *pattern, size_t total);
int compareStudent(void const *a, void const *b);

/* Generic functions */
void* myMalloc(int size, int total);
void exch(void *buf, int i, int j, size_t size);
int findMax(void *buf, size_t size, size_t total, int (*compare)(void const*, void const*));
void reverseArray(void *buf, size_t size, size_t total);
void printList(void *a, size_t total, char *pattern, void (*printPattern)(void* buf, char *pattern, size_t total));
int mySearch(void *buf, int size, int total, void *item, int (*compare)(void const*, void const*));
void q3sort(void *buf, size_t size, int l, int r, int (*compare)(void const *, void const *));
void mySort(void *buf, size_t size, size_t total, int (*compare)(void const *, void const *));
void* findMaxSizeOfDuplicateSet(void *buf, size_t size, size_t total, int (*compare)(void const *a, void const *b));
int* findMaxDuplicateSet(void *buf, size_t size, size_t total, int *counter, void const *maxNumber, int (*compare)(void const *a, void const *b));

#endif