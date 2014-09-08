#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include<stdio.h>
#include<stdlib.h>

typedef int elementType;

struct node
{
  elementType element;
  struct node* next;
  struct node* prev;
};


struct node* cur; 
struct node* root; 
struct node* sentinel;

typedef struct node * Node;

Node newNode(elementType data);
void insertAfter(Node current, Node new_item);
void insertBefore(Node current, Node new_item);
void append(Node new_item);
void prepend(Node new_item);
Node search(elementType element);
void displayList();
void deleteNode();

#endif
