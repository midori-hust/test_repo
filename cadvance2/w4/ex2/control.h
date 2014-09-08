#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "model.h"

void printPointList(Point *pointList, int amount);
void sort(Point *pointList, int l, int r, int type);
FrequencyList* getMaxCountPointSet(Point *pointList, int amount, int type);
void printPointListType(Point *pointList, int amount, int value, int type);

#endif