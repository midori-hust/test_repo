#ifndef __SORT_LIB_H__
#define __SORT_LIB_H__

#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 100

void mergeSort(int *a, int low, int high);
void selection(int *a, int n);
void swap(int *a, int *b);
void merge(int *a, int low, int mid, int high);
void bubbleSort(int *a, int n);
void quickSort(int *a, int left, int right);
void quickSortMedian(int *a, int left, int right);
int median3(int *a, int left, int right);
void insertionSort(int *a, int n);
void printArray(int *a, int n);
int choosePivot(int left, int right);

#endif