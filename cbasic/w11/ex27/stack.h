#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100


char stack[MAXLENGTH];
int top;


void initialize();
int empty();
int full();
void push(char *item);
int pop(char *item);

#endif
