#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 100

typedef int elementType;

typedef struct node {
  elementType element;
  struct node* next;
} node;

node* cur;
node* root;

node *newNode(elementType data);
void insertTop(elementType data);
void insert(elementType data);
void displayList();
void deleteNode();
node *searchNode(elementType data);
void freeList();

#endif
