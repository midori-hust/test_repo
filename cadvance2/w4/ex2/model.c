#include "model.h"

int generateData(Point *pointList, int amount, FILE *f) {
	int i;

	srand(time(NULL));
	for(i = 0; i < amount; i++) {
		pointList[i].row = rand() % MAX_RANDOM_RANGE;
		pointList[i].col = rand() % MAX_RANDOM_RANGE;
	}

	printToFile(f, "%d %d\n", pointList, amount);
	return 0;
}

int utilityFunct(int row, int col) {
	return row * 1000000 + col;
}

void sortByRow(Point *a, int l, int r) {
	// We choose the most right element as pivot
	if(r <= l)
		return;
	int i = l - 1, j = r;
	int p = l - 1, q = r;
	int k;

	while(1) {
		// while(a[++i].row < a[r].row); // Swap me
		i++;
		while(utilityFunct(a[i].row, a[i].col) < utilityFunct(a[r].row, a[r].col)) {
			i++;
		}
		j--;
		// while(a[r].row < a[--j].row)
		while(utilityFunct(a[r].row, a[r].col) < utilityFunct(a[j].row, a[j].col)) {
			if(j == l) {
				break;
			}
			j--;
		}

		if(i >= j) break; // Out of order

		exch(a, i, j);
		// if(a[i].row == a[r].row)
		if(utilityFunct(a[i].row, a[i].col) == utilityFunct(a[r].row, a[r].col)) {
			exch(a, ++p, i);
		}
		// if(a[j].row == a[r].row)
		if(utilityFunct(a[j].row, a[j].col) == utilityFunct(a[r].row, a[r].col)) {
			exch(a, --q, j);
		}
	}

	exch(a, i, r);
	j = i - 1;
	i = i + 1;
	
	for(k = l; k <= p; k++)
		exch(a, k, j--);
	for(k = r - 1; k >= q; k--)
		exch(a, k, i++);
	sortByRow(a, l, j);
	sortByRow(a, i, r);
}

void sortByCol(Point *a, int l, int r) {
	// We choose the most right element as pivot
	if(r <= l)
		return;
	int i = l - 1, j = r;
	int p = l - 1, q = r;
	int k;

	while(1) {
		i++;
		while(utilityFunct(a[i].col, a[i].row) < utilityFunct(a[r].col, a[r].row)) {
			i++;
		}
		j--;
		while(utilityFunct(a[r].col, a[r].row) < utilityFunct(a[j].col, a[j].row)) {
			if(j == l) {
				break;
			}
			j--;
		}

		if(i >= j) break; // Out of order

		exch(a, i, j);
		if(utilityFunct(a[i].col, a[i].row) == utilityFunct(a[r].col, a[r].row)) {
			exch(a, ++p, i);
		}
		if(utilityFunct(a[j].col, a[j].row) == utilityFunct(a[r].col, a[r].row)) {
			exch(a, --q, j);
		}
	}

	exch(a, i, r);
	j = i - 1;
	i = i + 1;
	
	for(k = l; k <= p; k++)
		exch(a, k, j--);
	for(k = r - 1; k >= q; k--)
		exch(a, k, i++);
	sortByCol(a, l, j);
	sortByCol(a, i, r);
}

void exch(Point *a, int i, int j) {
	int temp;

	temp = a[i].col;
	a[i].col = a[j].col;
	a[j].col = temp;

	temp = a[i].row;
	a[i].row = a[j].row;
	a[j].row = temp;
}

FrequencyList* getMaxCountByRow(Point *pointList, int amount) {
	int i;
	int maxCount = 0, oldPoint = -1, counter = 0;
	int value;
	FrequencyList *result = (FrequencyList*) malloc(sizeof(FrequencyList));

	for(i = 0; i < amount; i++) {
		if(pointList[i].row == oldPoint) {
			counter++;
		}
		else {
			oldPoint = pointList[i].row;
			counter = 1;
		}
		if(counter > maxCount) {
			maxCount = counter;
			value = pointList[i].row;
		}
	}
	result->value.row = value;
	result->value.col = value;
	result->frequency = maxCount;
	return result;
}

FrequencyList* getMaxCountByCol(Point *pointList, int amount) {
	int i;
	int maxCount = 0, oldPoint = -1, counter = 0;
	int value;
	FrequencyList *result = (FrequencyList*) malloc(sizeof(FrequencyList));

	for(i = 0; i < amount; i++) {
		if(pointList[i].col == oldPoint) {
			counter++;
		}
		else {
			oldPoint = pointList[i].col;
			counter = 1;
		}
		if(counter > maxCount) {
			maxCount = counter;
			value = pointList[i].col;
		}
	}
	result->value.col = value;
	result->value.row = value;
	result->frequency = maxCount;
	return result;
}

FrequencyList* getMaxCountByUtilityResult(Point *pointList, int amount) {
	int i;
	int maxCount = 0, oldUtilityResult = -1, counter = 0;
	int value;
	FrequencyList *result = (FrequencyList*) malloc(sizeof(FrequencyList));

	for(i = 0; i < amount; i++) {
		if(utilityFunct(pointList[i].row, pointList[i].col) == oldUtilityResult) {
			counter++;
		}
		else {
			oldUtilityResult = pointList[i].col;
			counter = 1;
		}
		if(counter > maxCount) {
			maxCount = counter;
			value = pointList[i].col;
		}
	}
	result->value.col = value;
	result->value.row = value;
	result->frequency = maxCount;
	return result;
}

void printPointListByRow(Point *pointList, int amount, int value) {
	int i;
	int counter = 0;

	while(getchar() != '\n');
	printf("Row %d\n", value);
	for(i = 0; i < amount; i++) {
		if(pointList[i].row == value) {
			printf("Point %d:\n\t(%d, %d)\n", i, pointList[i].col, pointList[i].row);
			counter++;
			if(counter % 25 == 0 && counter != 0) {
				printf("Do you want to see more 25 lines? (Y N)\n");
				if(getContinueRequest() == 'Y') {
					continue;
				} else {
					break;
				}
			}
		}
	}
}

void printPointListByCol(Point *pointList, int amount, int value) {
	int i;
	int counter = 0;

	while(getchar() != '\n');
	printf("Col %d\n", value);
	for(i = 0; i < amount; i++) {
		if(pointList[i].col == value) {
			printf("Point %d:\n\t(%d, %d)\n", i, pointList[i].col, pointList[i].row);
			counter++;
			if(counter % 25 == 0 && counter != 0) {
				printf("Do you want to see more 25 lines? (Y N)\n");
				if(getContinueRequest() == 'Y') {
					continue;
				} else {
					break;
				}
			}
		}
	}
}

void printPointListByUtilityResult(Point *pointList, int amount, int value) {
	int i;
	int counter = 0;

	while(getchar() != '\n');
	for(i = 0; i < amount; i++) {
		if(pointList[i].col == value) {
			printf("Point %d:\n\t(%d, %d)\n", i, pointList[i].col, pointList[i].row);
			counter++;
			if(counter % 25 == 0 && counter != 0) {
				printf("Do you want to see more 25 lines? (Y N)\n");
				if(getContinueRequest() == 'Y') {
					continue;
				} else {
					break;
				}
			}
		}
	}
}