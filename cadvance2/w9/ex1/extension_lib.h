#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"
#include "generic_lib.h"
#include "file_handle.h"
#include "symbol_table.h"
#include "my_jval_util.h"
// #include "jval.h"

#define MAXSIZE 1000
#define SIZE 100
#define TEMPSIZE 50

int solve();
void generateArray(Jval *a, int amount);
void printArrayJval(Jval *a, int amount);

int compareJval(Jval *a, Jval *b);

#endif