#ifndef __FILE_HANDLE_H__
#define __FILE_HANDLE_H__

#include <time.h>
#include "my_input_lib.h"

#define MAX_RANDOM_RANGE 50
#define MAXSIZE 10000
#define MAXLENGTH 100

enum SortType {
	BY_ROW,
	BY_COL,
	BY_UTILITY,
};

typedef struct _Point {
	int row;
	int col;
} Point;

void printToFile(FILE *f, char *pattern, Point *pointList, int amount);
int loadFromFile(FILE *f, char *pattern, Point *pointList);
int getTheNumberOfRowInFile(FILE *f);
Point* mallocPointStruct(int amount);

#endif