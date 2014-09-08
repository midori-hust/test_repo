#ifndef _STACK_H_
#define _STACK_H_

#define MAX 100

//==================

typedef struct
{
  ElmType array[MAX];
  int top;
}Stack;

//=========================

void newStack(Stack *stack) //Khoi tao stack
{
  (*stack).top = 0;
}

//=========================

int empty(Stack stack) //Kiem tra stack co rong khong
{
  return stack.top == 0;
}

//=========================

int full(Stack stack) //Kiem tra stack day chua
{
  return stack.top == MAX;
}

//=====================================

void push(Stack *stack, ElmType key) // Them phan tu vao dinh stack
{
  if(full(*stack))printf("Stack day\n");
  else 
    (*stack).array[(*stack).top++] = key;
}

//=======================================

ElmType pop(Stack *stack) // Lay phan tu o dinh stack
{
  if(empty(*stack))
    printf("Stack rong.\n");
  else 
    return (*stack).array[--(*stack).top];
}

//=======================================

ElmType top(Stack *stack) //Tra ve gia tri o dinh stack
{
  ElmType x;
  x = pop(stack);
  push(stack,x);
  return x;
}

//=======================================

#endif
