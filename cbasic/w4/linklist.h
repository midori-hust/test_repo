#ifndef __LINKLIST_H__
//#define __LINKLIST_H__

#include<stdio.h>
#include<stdlib.h>

typedef int elementType;

typedef struct node
{
  elementType element;
  struct node* next;
} node;

node* cur; 
node* root; 
node* prev; 

node *newNode(elementType data);
void insertTop(node* new_item);
void insert(node* new_item);
void displayList();
void deleteNode();
node *getPrev();

#endif
