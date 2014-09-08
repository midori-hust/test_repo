#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"./libfdr/fields.h"
#include"./bt-3.0.1/inc/btree.h"

typedef struct{
  char word[40];
  char code[10];
  char mean[1000];
}dictsd;

char* coding(char* word);
void creat_btsoundex(BTA* btactSoundex);
