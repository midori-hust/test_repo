#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"
#include "generic_lib.h"
#include "file_handle.h"
#include "symbol_table.h"

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
void getTableData(FILE *f, SymbolTable *table);
void findWords(SymbolTable *table);
int getIpValue();
int myPow(int a, int b);

/* Compare functions */
Entry makeIpToCountryEntry(void *key, void *value);
int compareIpToCountryEntry(void *a, void *b);

#endif