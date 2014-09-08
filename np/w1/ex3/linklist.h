#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 100

typedef struct _elementType {
  int id;
  char name[MAXLENGTH];
  float grade;
} elementType;

typedef struct node {
  elementType element;
  struct node* next;
} node;

node* cur;
node* root;

node *newNode(int id, char *name, float grade);
void insertTop(int id, char *name, float grade);
void insert(int id, char *name, float grade);
void displayList();
void deleteNode(int id);
node *searchNode(int id);
void freeList();
int menu();
void getStudentInfo(FILE *f);
void sortList();
void editGrade(int id, float newGrade);
int menu2();
void swap(elementType *a, elementType *b);

#endif
