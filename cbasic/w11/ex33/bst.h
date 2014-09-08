#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLENGTH 100

typedef struct Node
{
  char key[MAXLENGTH];
  int frequency;
  struct Node *left, *right;
} Node;

Node* Search(char *key, Node* Root);
void InsertNode(char *key, Node** Root);
void display(Node *Root);
void freeTree(Node *Root);

#endif
