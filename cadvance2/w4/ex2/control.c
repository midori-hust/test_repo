#include "control.h"

void sort(Point *pointList, int l, int r, int type) {
	if(type == BY_ROW)
		sortByRow(pointList, l, r);
	if(type == BY_COL)
		sortByCol(pointList, l, r);
}

FrequencyList* getMaxCountPointSet(Point *pointList, int amount, int type) {
	if(type == BY_ROW)
		return getMaxCountByRow(pointList, amount);
	if(type == BY_COL)
		return getMaxCountByCol(pointList, amount);
	if(type == BY_UTILITY)
		return getMaxCountByUtilityResult(pointList, amount);
	return 0;
}

void printPointListType(Point *pointList, int amount, int value, int type) {
	if(type == BY_ROW)
		printPointListByRow(pointList, amount, value);
	if(type == BY_COL)
		printPointListByCol(pointList, amount, value);
	if(type == BY_UTILITY)
		printPointListByUtilityResult(pointList, amount, value);
}

void printPointList(Point *pointList, int amount) {
	int i;

	while(getchar() != '\n');
	for(i = 0; i < amount; i++) {
		printf("Point %d:\n\tx = %d\n\ty = %d\n", i, pointList[i].col, pointList[i].row);
		if(i % 25 == 0 && i != 0) {
			printf("Do you want to see more 25 lines? (Y N)\n");
			if(getContinueRequest() == 'Y') {
				continue;
			} else {
				break;
			}
		}
	}
}