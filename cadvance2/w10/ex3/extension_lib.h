#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"
#include "file_handle.h"
#include "jrb.h"
#include "jval.h"

#define MAXSIZE 1000
#define SIZE 100
#define TEMPSIZE 50

typedef struct _Key {
	unsigned int upperBound;
	unsigned int lowerBound;
} Key;

typedef struct _Value {
	String code1;
	String code2;
	String nationName;
} Value;

int solve(FILE *f);
JRB getTableData(FILE *f);
void findWords(JRB tree);
int getIpValue();
int myPow(int a, int b);

/* Compare functions */
int compareIpToCountryEntry(Jval a, Jval b);

#endif