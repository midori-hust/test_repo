#include "file_handle.h"

void printToFile(FILE *f, char *pattern, Point *pointList, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		fprintf(f, pattern, pointList[i].row, pointList[i].col);
	}
	rewind(f);
}

int loadFromFile(FILE *f, char *pattern, Point *pointList) {
	int i = 0;
	int temp1, temp2;

	if((pointList = mallocPointStruct(getTheNumberOfRowInFile(f))) == NULL) {
		return -1;
	}

	while(fscanf(f, "%d %d\n", &pointList[i].col, &pointList[i].row) != EOF) {
		i++;
	}
	rewind(f);
	return i;
}

int getTheNumberOfRowInFile(FILE *f) {
	int i = 0;
	int temp1, temp2;

	while(fscanf(f, "%d %d\n", &temp1, &temp2) != EOF) {
		i++;
	}
	rewind(f);
	return i;
}

Point* mallocPointStruct(int amount) {
  Point *pointList;

  if((pointList = (Point*) malloc((amount + 1) * sizeof(Point))) == NULL) {
    printf("Cannot allocated memory\n");
    return NULL;
  }
  return pointList;
}