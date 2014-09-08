#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"
#include "generic_lib.h"
#include "file_handle.h"

#define MAXSIZE 1000

void printArray(String *a, int amount);
int solve(FILE *f_domain, FILE *f_user, FILE *fout1, FILE *fout2);
int genEmailList(String *emailList, int amount, FILE *f_domain, FILE *f_user);
int removeDuplicatedEmail(String* result, String* emailList, int amount);

/* Compare function */
int myIntCompare(void const* a, void const* b);
int myStringCompare(void const* a, void const* b);
// int compareStudent(void const *a, void const *b);
int compareMaxEmail(void const* a, void const*b);
int compareMinEmail(void const* a, void const*b);
int utilityFunction(const String* a);
int mySearch(void *buf, int size, int total, void *item, int (*compare)(void const*, void const*));
void myPrintPattern(void *buf, char *pattern, size_t total);
int findMinCompare(void const* x, void const* y);
int findMaxCompare(void const* x, void const* y);

#endif