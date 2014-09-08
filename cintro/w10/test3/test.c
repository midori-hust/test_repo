#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void displayArray(int *array, int amount);
void sort(int *array, int amount);
int intCompare(const void* a, const void* b);

int main() {
	int b[100];
	int i;

	srand(time(NULL));
	for(i = 0; i < 40; i++) {
		b[i] = rand() % 100;
	}

	printf("Before sorting\n");
	displayArray(b, 40);
	sort(b, 40);
	printf("After sorting\n");
	displayArray(b, 40);

	return 0;
}

void displayArray(int *array, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("%d\n", array[i]);
	}
}

void sort(int *array, int amount) {
	qsort(array, amount, sizeof(int), intCompare);
}

int intCompare(const void* a, const void* b) {
	int *x = (int*)a;
	int *y = (int*)b;

	return *x - *y;
}