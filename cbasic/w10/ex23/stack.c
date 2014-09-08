#include "stack.h"

void initialize()
{
  top = 0;
}

int empty()
{
  return top == 0;
}

int full()
{
  return top == MAXLENGTH;
}

void push(StudentInfo *item)
{
  if(full()) printf("Stack overflow.\n");
  else stack[top++] = *item;
}

int pop(StudentInfo *item)
{
  if(empty())
    {
      printf("Stack underflow.\n");
      return 0;
    }
  *item = stack[--top];
  return 1;
}
