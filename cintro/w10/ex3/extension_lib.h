#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"

#define MAXSIZE 100
#define SIZE 100
#define TEMPSIZE 50

typedef struct _Fractions {
	int numerator;
	int denominator;
} Fractions;

int solve();

void getInput(Fractions *listFraction, int amount);
void reverseFraction(Fractions *frac);
int factCompare(Fractions a, Fractions b);
void printArray(Fractions *listFraction, int amount);

#endif
