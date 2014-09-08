#include "extension_lib.h"

int solve() {
	Jval *a;
	Jval searchItem;
	int result;
	int number;

	if((a = myMalloc(sizeof(Jval), SIZE)) == NULL) {
		return 1;
	}

	printf("Please enter the number which you want to find\n");
	number = getInt();
	searchItem = new_jval_i(number);

	generateArray(a, SIZE);
	printArrayJval(a, SIZE);

	if((result = seqSearchJval(a, SIZE, searchItem, compareJval)) != -1) {
		printf("Found %d at index %d\n", jval_i(searchItem), result);
	} else {
		printf("Not found!\n");
	}

	quickSort3WayJval(a, 0, SIZE - 1, compareJval);
	printArrayJval(a, SIZE);
	if((result = binarySearchJval(a, searchItem, 0, SIZE - 1, compareJval)) != -1) {
		printf("Found %d at index %d\n", jval_i(searchItem), result);
	} else {
		printf("Not found!\n");
	}

	free(a);
	return 0;
}

void generateArray(Jval *a, int amount) {
	int i;
	int temp;

	srand(time(NULL));
	for(i = 0; i < amount; i++) {
		temp = rand() % TEMPSIZE;
		a[i] = new_jval_i(temp);
	}
}

void printArrayJval(Jval *a, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("a[%d] = %d\n", i, jval_i(a[i]));
	}
}

/* Compare functions */

int compareJval(Jval *a, Jval *b) {
	int x = jval_i(*a);
	int y = jval_i(*b);

	return x - y;
}