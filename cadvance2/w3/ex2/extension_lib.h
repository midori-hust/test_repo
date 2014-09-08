#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"
#include "sort_lib.h"

#define MAXLENGTH 100
#define MAX 1000000
#define RANDOM_RANGE 10

void sort(int *a, int l, int r);
void exch(int *a, int i, int j);
void genTestData(int *a, int amount);
void printArray(int *a, int amount);
int* mallocIntArray(int amount);
int solve();
int choosePivot(int left, int right);
void quickSort(int *a, int left, int right);
void swap(int *a, int *b);
void quickSortMedian(int *a, int left, int right);
int median3(int *a, int left, int right);
void insertionSort(int *a, int n);
void quicksortViet(int a[], int l, int r);

#endif