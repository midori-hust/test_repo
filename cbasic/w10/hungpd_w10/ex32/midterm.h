#ifndef __MIDTERM_H__
#define __MIDTERM_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100

struct product_info
{
  int id;
  char name[MAXLENGTH];
  char decription[MAXLENGTH];
};

typedef struct product_info ProductInfo;

char menu();
int BinarySearch(ProductInfo *productList, int id, int n);

#endif
