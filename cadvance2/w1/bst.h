#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLENGTH 100


typedef struct Node {
  char name[MAXLENGTH];
  int point;
  struct Node *left, *right;
} Node;

Node* Search(char *key, Node* Root);
void InsertNode(char *key, Node** Root, int point);
void display(Node *Root);
void freeTree(Node *Root);
int menu();
int getInt();
void genResultFile(FILE *f, Node* Root);
void relegated(int point, Node* Root);
void DeleteNode(char *key, Node *Root);
char* DeleteMin(Node *Root);

#endif
