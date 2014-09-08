#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"

#define MAXLENGTH 100
#define MAXSIZE 1000

typedef struct _String {
	char content[MAXLENGTH];
} String;

void exch(void *buf, int i, int j, size_t size);
void q3sort(void *buf, size_t size, int l, int r, int (*compare)(void const *, void const *));
int myCompare(void const* x, void const* y);
void* myMalloc(int size, int total);
void printArray(String *a, int amount);
int solve(FILE *f_domain, FILE *f_user, FILE *fout1, FILE *fout2);
void printToFile(FILE *f, char *pattern, String *array, int amount);
int getTheNumberOfRowInFile(FILE *f);
int genEmailList(String *emailList, int amount, FILE *f_domain, FILE *f_user);
int removeDuplicatedEmail(String* result, String* emailList, int amount);

#endif