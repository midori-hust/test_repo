#include "myLib.h"

int main() {
	int n, i, j;
	float *a, *sortArray;
	float temp;

	do {
		printf("Enter the numbers of elements (must be greater than zero and less than 10):\n");
		n = getInt();
	} while(n <= 0 || n >= 10);

	a = (float*) malloc ((n + 1) *sizeof(float));
	if(a == NULL) {
      printf("Memory allocation failed!\n");
      return 1;
    }

	printf("Enter the numbers:\n");
	for( i = 0; i < n; i++) {
		printf("a[%d] = ",i);
		a[i] = getFloat();
	}

	sortArray = cloneArray(a, n);
	printf("\n");
	mySort(sortArray, n, ASC);
	printf("This array after ASC sorting:\n");
	printArray(sortArray, n);

	sortArray = cloneArray(a, n);
	mySort(sortArray, n, DESC);
	printf("\n");
	printf("This array after DESC sorting:\n");
	printArray(sortArray, n);

	sortArray = cloneArray(a, n);
	printf("\n");
	mySort(sortArray, n, ASB_DESC);
	printf("This array after ASB_DESC sorting:\n");
	printArray(sortArray, n);

	printf("\n\nProgram's done. Free resources...\n");
	free(a);
	return 0;
}