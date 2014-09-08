#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"

#define MAXLENGTH 100
#define MAXSIZE 1000

typedef struct _String  {
	char content[MAXLENGTH];
} String;

int solve();
int stringCompare(void const*x, void const *y);
String* mallocStringStruct(int amount);
void printArray(String *array, int amount);

#endif