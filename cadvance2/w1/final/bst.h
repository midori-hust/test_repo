#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLENGTH 100

typedef struct _Key {
  char name[MAXLENGTH];
  int point;
} Key;

typedef struct _Node {
  Key content;
  struct _Node *left, *right;
} Node;

int static counter = 0;

Node* Search(char *key, Node* Root);
void InsertNode(Key *key, Node** Root);
void display(Node *Root);
void freeTree(Node *Root);
int menu();
int getInt();
void genResultFile(FILE *f, Node* Root);
Node* searchForRelegated(int point, Node* Root);
void DeleteNode(Key *key, Node **Root);
Key DeleteMin(Node **Root);

#endif
