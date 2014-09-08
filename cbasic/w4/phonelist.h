#ifndef __PHONELIST_H__
#define __PHONELIST_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLENGTH 100
typedef struct address
{
  char name[MAXLENGTH];
  int tel;
  char email[MAXLENGTH];
} Address;

typedef struct AddressList
{
  struct AddressList *next;
  Address addr;
} AddressList;

AddressList* root;
AddressList* cur;
AddressList* prev;

AddressList *newAddress(char *name, int tel, char *email);
void insertTop(AddressList* new_item);
void insert(AddressList* new_item);
void displayList();
void delete();
void deleteNumber(char *name);

#endif
