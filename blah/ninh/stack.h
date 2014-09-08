#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100

typedef struct _Key {
	int square[MAXLENGTH][MAXLENGTH];
} Key;

typedef struct _Stack {
	Key storage[MAXLENGTH];
	int top;
} Stack;

Stack* makeStack();
void initialize(Stack *stack);
int isEmpty(Stack *stack);
int isFull(Stack *stack);
void push(Stack **stack, Key *item);
Key* pop(Stack **stack);
void printSquareContent(Key *item, int n);
void doSomething(Stack **stack, int n);
void tileSquare1(Key *item, int x, int y);
void tileSquare2(Key *item, int x, int y);
void tileSquare3(Key *item, int x, int y);
void tileSquare4(Key *item, int x, int y);

#endif
