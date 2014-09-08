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

node *newNode(elementType data);
void insertTop(node* root, node* new_item);
void insert(node* root, node* cur, node* new_item);
void displayList(node*root);
void deleteNode(node*root, node* cur);
node *getPrev(node* root, node* cur);

#endif
