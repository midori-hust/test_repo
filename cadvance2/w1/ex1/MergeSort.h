#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAXLENGTH 2000000

void mergeSort(int *a, int low, int high);
void selection(int *a, int n);
void swap(int *a, int *b);
void merge(int *a, int low, int mid, int high);
void bubbleSort(int *a, int n);
void quickSort(int *a, int left, int right);

#endif