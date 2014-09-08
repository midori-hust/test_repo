#ifndef __PHONE_LIB_H__
#define __PHONE_LIB_H__

#include "my_input_lib.h"
#include "my_jval_util.h"

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
	Entry (*makeNode)(Jval*, Jval*);
	int (*compare)(Jval*, Jval*);
} SymbolTable;

/* API */
void addEntry(Jval key, Jval value, SymbolTable *table);
Jval getEntry(Jval key, SymbolTable const *table);
SymbolTable* createSymbolTable(Entry (*makeNode)(Jval*, Jval*), int (*compare)(Jval*, Jval*));
void dropSymbolTable(SymbolTable *table);
void reallocEntry(SymbolTable *table);
void sortEntry(SymbolTable *table);

// Private
int binarySearchSymtab(Entry item, int low, int high, SymbolTable const *table);
void insertionSortSymtab(SymbolTable *table);
void exchangeEntry(SymbolTable *table, int i, int j);
void quickSortSymtab(int l, int r, SymbolTable *table);

#endif