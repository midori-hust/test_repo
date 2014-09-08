#ifndef __MIDTERM_H__
#define __MIDTERM_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100

typedef struct prod_info
{
  int id;
  char name[MAXLENGTH];
  char description[MAXLENGTH];
  int price;
  int quantity;
} prodInfo;


char menu();
void nhapThongTin(FILE *f);

#endif
