#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"
#include "file_handle.h"
#include "symbol_table.h"

#define MAXSIZE 1000
#define SIZE 100
#define TEMPSIZE 50

int solve(FILE *f);
void getTableData(FILE *f, SymbolTable *table);
void findWords(SymbolTable *table);

/* Compare functions */
Entry makeDictionaryEntry(Jval *wordKey, Jval *wordValue);
int compareDictionaryEntry(Jval *a, Jval *b);

#endif