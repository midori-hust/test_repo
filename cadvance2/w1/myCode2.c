#include "myLib.h"

int main() {
	int n, i, zeroQuantity = 0, counter = 0;
	float *a;
	float temp, avg, posSum = 0, negSum = 0, x;

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

	printf("The array:\n");
	printArray(a, n);
	for (i = 0; i < n; i++) {
		if (a[i] < 0) {
			negSum += a[i];
			counter++;
		} else if (a[i] > 0) {
			posSum += a[i];
		} else {
			zeroQuantity++;
		}
	}

	if (counter == 0) {
		printf("This array has no negative numbers\n");
	} else {
		printf("The average of negative numbers in this array is %f\n", negSum/counter);
	}
	printf("Sum of positive numbers in this array is %f\n", posSum);
	printf("The quantity of 0 in this array: %d\n", zeroQuantity);


	printf("Enter x from keyboard ");
	x = getFloat();
	searchPosition(a, n, x);

	free(a);
	return 0;
}