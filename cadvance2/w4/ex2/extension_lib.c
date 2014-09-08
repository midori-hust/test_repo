#include "extension_lib.h"

int solve(FILE *f) {
	Point *pointList = NULL;
	int choice;
	int n = MAXSIZE;
	int flag = 0;

  	while(1) {
      switch(choice = menu()) {
        case 1:
        printf("You choose option %d\n", choice);
        if((pointList = mallocPointStruct(n)) == NULL) {
        	return 1;
        }
        generateData(pointList, n, f);
        printf("Generate data successfully\n");
        flag = 1;
        // printPointList(pointList, n); // Debugging
        continue;
        case 2:
        printf("You choose option %d\n", choice);
        if(!flag) {
        	printf("Please choose option 1 first!\n");
        	continue;
        }
        findTheBiggestLinearPointsSet(pointList, n);
        continue;
        case 3:
        printf("You choose option %d\n", choice);
        if(!flag) {
        	printf("Please choose option 1 first!\n");
        	continue;
        }
        findTheBiggestPointsSet(pointList, n);
        continue;
        case 4:
        printf("You choose option %d\n", choice);
        if(!flag) {
        	printf("Please choose option 1 first!\n");
        	continue;
        }
        n = loadFromFile(f, "%d %d\n", pointList);
        printf("Reload data successfully\n");
        continue;
        case 5:
        printf("You choose option %d\n", choice);
        printf("Bye bye\n");
        if(pointList != NULL)
        	free(pointList);
        break;
        default:
        printf("It is not an option\n");
        continue;
      }
      break;
  }
  return 0;
}

void findTheBiggestLinearPointsSet(Point *pointList, int amount) {
	int maxCount = 0;
	FrequencyList *byRow, *byCol;

	sort(pointList, 0, amount - 1, BY_ROW);
	byRow = getMaxCountPointSet(pointList, amount, BY_ROW);
	sort(pointList, 0, amount - 1, BY_COL);
	byCol = getMaxCountPointSet(pointList, amount, BY_COL);
	printf("By col: %d, by row: %d\n", byCol->frequency, byRow->frequency);

	if(byCol->frequency < byRow->frequency) {
		printPointListType(pointList, amount, byRow->value.row, BY_ROW);
		printf("The biggest linear points set: row = %d, frequency = %d", byRow->value.row, byRow->frequency);
	}
	else if(byRow->frequency < byCol->frequency) {
		printPointListType(pointList, amount, byCol->value.col, BY_COL);
		printf("The biggest linear points set: col = %d, frequency = %d", byCol->value.col, byCol->frequency);
	}
	else {
		printPointListType(pointList, amount, byRow->value.row, BY_ROW);
		printPointListType(pointList, amount, byCol->value.col, BY_COL);
		printf("The biggest linear points set: col = %d, frequency = %d", byCol->value.col, byCol->frequency);
		printf(" and row = %d, frequency = %d", byRow->value.row, byRow->frequency);
	}
	
	free(byCol);
	free(byRow);
}

void findTheBiggestPointsSet(Point *pointList, int amount) {
	FrequencyList *point = (FrequencyList*) malloc(sizeof(FrequencyList));

	sort(pointList, 0, amount - 1, BY_COL);
	// printPointList(pointList, amount);
	point = getMaxCountPointSet(pointList, amount, BY_UTILITY);
	printf("The biggest points set: (%d, %d) frequency = %d\n", point->value.col, point->value.row, point->frequency);
	printPointListType(pointList, amount, utilityFunct(point->value.row, point->value.col), BY_UTILITY);

	free(point);
}