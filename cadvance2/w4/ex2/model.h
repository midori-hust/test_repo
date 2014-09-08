#ifndef __MODEL_H__
#define __MODEL_H__

#include "my_input_lib.h"
#include "file_handle.h"


typedef struct _FrequencyList {
	Point value;
	int frequency;
} FrequencyList;

int generateData(Point *pointList, int amount, FILE *f);
int utilityFunct(int row, int col);
void sortByRow(Point *a, int l, int r);
void sortByCol(Point *a, int l, int r);
void exch(Point *a, int i, int j);
FrequencyList* getMaxCountByRow(Point *pointList, int amount);
FrequencyList* getMaxCountByCol(Point *pointList, int amount);
FrequencyList* getMaxCountByUtilityResult(Point *pointList, int amount);
void printPointListByRow(Point *pointList, int amount, int value);
void printPointListByCol(Point *pointList, int amount, int value);
void printPointListByUtilityResult(Point *pointList, int amount, int value);

#endif