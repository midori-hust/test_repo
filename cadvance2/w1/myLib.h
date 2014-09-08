#ifndef __MYLIB_H__
#define __MYLIB_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100

enum Sort { 
	ASC,
	DESC,
	ASB_DESC,
	 };

float* mySort(float *a, int n, int extension);
float* ascSort(float *a, int n);
float* descSort(float *a, int n);
float* abs_descSort(float *a, int n);
void printArray(float *a, int n);
void swap(float *a, float *b);
float* cloneArray(float *a, int n);
int getInt();
float getFloat();
void searchPosition(float *a, int n, float key);
int menu();

#endif
