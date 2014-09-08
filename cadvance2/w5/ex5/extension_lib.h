#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"

#define MAXLENGTH 100
#define MAXSIZE 1000

typedef struct _String {
	char content[MAXLENGTH];
} String;

void insertionSort(String *array, int n);
void exch(String *a, int i, int j);
String* mallocStringStruct(int amount);
void printArray(String *a, int amount);
int solve(FILE *f_domain, FILE *f_user, FILE *fout1, FILE *fout2);
void printToFile(FILE *f, char *pattern, String *array, int amount);
int getTheNumberOfRowInFile(FILE *f);
int genEmailList(String *emailList, int amount, FILE *f_domain, FILE *f_user);
void sort(String *a, int l, int r);
int removeDuplicatedEmail(String* result, String* emailList, int amount);
String* cloneArray(String *src, int amount);
int myCompare(void const* x, void const* y);

#endif