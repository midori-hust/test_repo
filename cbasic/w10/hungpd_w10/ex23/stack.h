#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100


struct student_info
{
  int id;
  char name[MAXLENGTH];
  float mark;
};

typedef struct student_info StudentInfo;

StudentInfo stack[MAXLENGTH];
int top;


void initialize();
int empty();
int full();
void push(StudentInfo *item);
int pop(StudentInfo *item);

#endif
