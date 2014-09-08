#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"

#define MAXLENGTH 100
#define MAXSIZE 1000

int intCompare(void const* x, void const *y);
int floatCompare(void const* x, void const *y);
void genData(int* array, int amount);
void genFloatData(float* array, int amount);
int* mallocInt(int amount);
float* mallocFloat(int amount);
int solve();
void printArray(int *array, int amount);
void printFloatArray(float *array, int amount);

#endif