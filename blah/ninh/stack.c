#include "stack.h"

Stack* makeStack() {
  Stack *newStack;

  newStack = (Stack*) malloc(sizeof(Stack));
  return newStack;
}

void initialize(Stack *stack) {
  stack->top = 0;
}

int isEmpty(Stack *stack) {
  return stack->top == 0;
}

int isFull(Stack *stack) {
  return stack->top == MAXLENGTH;
}

void push(Stack **stack, Key *item) {
  if(isFull(*stack)) 
    printf("Stack overflow.\n");
  else {
    (*stack)->storage[(*stack)->top++] = *item;
  }
}

Key* pop(Stack **stack) {
  if(isEmpty(*stack)) {
      printf("Stack underflow.\n");
      return NULL;
  }
  else 
    return &(*stack)->storage[--(*stack)->top];
}

void printSquareContent(Key *item, int n) {
  int i, j;

  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
      printf(" %d ", item->square[i][j]);
    }
    printf("\n");
  }
}

void doSomething(Stack **stack, int n) {
  int i, j;

}

/*
* | +| +|
* | +|  |
*/
void tileSquare1(Key *item, int x, int y) {

}

/*
* | +| +|
* |  | +|
*/
void tileSquare2(Key *item, int x, int y) {
  
}

/*
* | +|  |
* | +| +|
*/
void tileSquare3(Key *item, int x, int y) {
  
}

/*
* |  | +|
* | +| +|
*/
void tileSquare4(Key *item, int x, int y) {
  
}