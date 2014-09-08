#ifndef __GENERIC_LIB_H__
#define __GENERIC_LIB_H__

#include <stdio.h>
#include <stdlib.h>

#include "my_input_lib.h"

/* Generic function */
void printList(void *a, size_t total, char *pattern, void (*printPattern)(void* buf, char *pattern, size_t total));
int findMax(void *buf, size_t size, size_t total, int (*compare)(void const*, void const*));
void reverseArray(void *buf, size_t size, size_t total);
void mySort(void *buf, size_t size, size_t total, int (*compare)(void const *, void const *));
void q3sort(void *buf, size_t size, int l, int r, int (*compare)(void const *, void const *));
void exch(void *buf, int i, int j, size_t size);
void* findMaxSizeOfDuplicateSet(void *buf, size_t size, size_t total, int (*compare)(void const *a, void const *b));
int* findMaxDuplicateSet(void *buf, size_t size, size_t total, int *counter, 
	void const *maxNumber, int (*compare)(void const *a, void const *b));

#endif