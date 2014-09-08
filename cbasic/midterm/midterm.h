#ifndef __MIDTERM_H__
#define __MIDTERM_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100

typedef struct busInfo
{
  int id;
  char name[MAXLENGTH];
} BusInfo;


char menu();
void sortBusID(BusInfo *busList, int n);
void swap(BusInfo *bus1, BusInfo *bus2);

#endif
