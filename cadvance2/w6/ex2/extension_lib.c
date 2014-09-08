#include "extension_lib.h"

int solve() {
	int *a;
	int i;
	int searchEle = 725;

	if((a = mallocInt(MAXSIZE)) == NULL) {
		return 1;
	}

	for(i = 0; i < MAXSIZE; i++) {
		a[i] = i+1;
	}

	// printIntList(a, MAXSIZE);

	printf("The element %d is at index %d\n", searchEle, mySearch(a, sizeof(int), MAXSIZE, &searchEle, myIntCompare));

	return 0;
}

int myIntCompare(void const* a, void const* b) {
	const int* x = (const int*) a;
	const int* y = (const int*) b;

	if(*x == *y)
		return 0;

	return *x > *y ? 1 : -1;
}

int mySearch(void *buf, int size, int total, void *item, int (*compare)(void const*, void const*)) {
	int i, res;

	if(total == 0 || size < 0 || buf == NULL)
		return -1; // Cannot find the item element

	for(i = 0; i < total; i++) {
		res = compare(item, (char*)buf + (size * i));
		if(res == 0)
			return i;
	}

	return -1;
}

void printIntList(int *a, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("a[%d] = %d\n", i, a[i]);
	}
}

int* mallocInt(int amount) {
	int *result;

	if((result = (int*) malloc((amount + 1) * sizeof(int))) == NULL) {
		printf("Cannot allocated memory\n");
		return NULL;
	}

	return result;
}