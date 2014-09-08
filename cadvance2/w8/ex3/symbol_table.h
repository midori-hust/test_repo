#ifndef __PHONE_LIB_H__
#define __PHONE_LIB_H__

#include "my_input_lib.h"

#define INITIAL_SIZE 1000
#define INCREMENTAL_SIZE 1000

typedef struct _Entry {
	void* key;
	void* value;
} Entry;

typedef struct _SymbolTable {
	Entry *entries;
	int total;
	int size;
	Entry (*makeNode)(void*, void*);
	int (*compare)(void*, void*);
} SymbolTable;

/* API */
void addEntry(void* key, void* value, SymbolTable *table);
void* getEntry(void* key, SymbolTable const *table);
SymbolTable* createSymbolTable(Entry (*makeNode)(void*, void*), int (*compare)(void*, void*));
void dropSymbolTable(SymbolTable *table);
void reallocEntry(SymbolTable *table);

#endif