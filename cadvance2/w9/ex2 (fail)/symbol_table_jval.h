#ifndef __SYMBOL_TABLE_JVAL_H__
#define __SYMBOL_TABLE_JVAL_H__

#include "my_input_lib.h"
#include "my_jval_util.h"
#include "jval.h"
#include "generic_lib.h"

#define INITIAL_SIZE 1000
#define INCREMENTAL_SIZE 1000

typedef struct _Entry {
	Jval key;
	Jval value;
} Entry;

typedef struct _SymbolTable {
	Entry *entries;
	int total;
	int size;
	Entry (*makeNode)(Jval, Jval);
	int (*compare)(Jval*, Jval*);
} SymbolTable;

/* API */
void addEntry(Jval key, Jval value, SymbolTable *table);
Jval getEntry(Jval key, SymbolTable const *table);
SymbolTable* createSymbolTable(Entry (*makeNode)(Jval, Jval), int (*compare)(Jval*, Jval*));
void dropSymbolTable(SymbolTable *table);
void reallocEntry(SymbolTable *table);


/* Private */
void q3sortJval(SymbolTable *table, int l, int r);
int compareInTableJval(SymbolTable *table, Jval *a, Jval *b);

#endif