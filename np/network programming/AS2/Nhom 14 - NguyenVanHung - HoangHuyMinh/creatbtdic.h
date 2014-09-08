#include<stdio.h>
#include<string.h>
#include"./libfdr/fields.h"
#include"./bt-3.0.1/inc/btree.h"
#include<stdlib.h>
#include<ctype.h>

typedef struct{
  char word[40];
  char mean[1000];
}dict;

void creat_btree(BTA *btact);
