#include "extension_lib.h"

int solve() {
	int n;
	int i;
	int *a;

	printf("Please enter the number of elements\n");
	n = getInt();

	if((a = (int*)malloc((n+1) * sizeof(int))) == NULL) {
		printf("Cannot allocated memory\n");
		return 1;
	}

	for(i = 0; i < n; i++) {
		printf("a[%d] = ", i);
		a[i] = getInt();
	}

	selection(a, n);

	printf("Enter the rank: \n");
	int rank = getInt();

	printf("Phan tu nho thu %d la %d\n", rank, findTheElement(a, n, rank));

	printf("\nThe list of the elements:\n");
	printIntList(a, n);

	return 0;
}

int* numberFilter(int *a, int amount) {
	int *b, i;
	int oldNum;
	int counter = 0;

	if((b = (int*) malloc((amount + 1) * sizeof(int))) == NULL) {
		return NULL;
	}

	if(amount <= 0) {
		return NULL;
	}

	oldNum = a[0];
	b[0] = a[0];

	for(i = 1; i < amount; i < amount) {
		if(oldNum != a[i]) {
			b[counter++] = a[i];
			oldNum = a[i];
		}
	}

}

int findTheElement(int *a, int amount, int rank) {
	int i, oldNum;
	int counter = 1;

	oldNum = a[0];
	for(i = 0; i < amount; i++) {
		if(oldNum != a[i]) {
			counter++;
			oldNum = a[i];
		}

		if(counter == rank)
			break;
	}

	if(i == amount) {
		return a[amount - 1];
	}
	return a[i];
}

void printIntList(int *a, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("a[%d] = %d\n", i, a[i]);
	}
}

void selection(int *a, int n) {
	int i, j;
	int iMin;

	for(j = 0; j < n - 1; j++) {
		iMin = j;
		for(i = j + 1; i < n; i++) {
			if(a[i] < a[iMin])
				iMin = i;
		}

		if(iMin != j)
			swap(&a[j], &a[iMin]);
	}
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}