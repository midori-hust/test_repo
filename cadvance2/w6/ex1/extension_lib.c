#include "extension_lib.h"

int solve() {
	int a[10];
	int *b;
	int i;

	for(i = 0; i < 10; i++) {
		a[i] = i;
	}

	if((b = (int*) malloc(11 * sizeof(int))) == NULL) {
		printf("Cannot allocated memory\n");
		return 1;
	}

	printf("The source list: \n");
	printIntList(a, 10);
	memcpy(b, a, 10 * sizeof(int));
	printf("The destination list: \n");
	printIntList(b, 10);
	return 0;
}

void printIntList(int *a, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("a[%d] = %d\n", i, a[i]);
	}
}