#include "extension_lib.h"

int solve() {
	int num;
	int output[SIZE], size = 0;
	int i;

	printf("Please enter the number:\n");
	num = getInt();

	getPrimeMultipleList(num, output, &size);
	getAllMultipleList(output, size);
	// printList(output, size);

	return 0;
}

void getPrimeMultipleList(int num, int *output, int *size) {
	int i;

	for(i = 2; i < num/2; i++) {
		if(!(num % i)) {
			output[(*size)++] = i;
			getPrimeMultipleList(num / i, output, size);
			return;
		}
	}

	output[(*size)++] = num;
}

void printList(int *output, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("\t%d\n", output[i]);
	}
}

void getAllMultipleList(int *output, int size) {
	int i;
	int res = 1;

	if(size == 0) {
		return;
	}

	for(i = 0; i < size; i++) {
		res *= output[i];
		printf("%d\n", res);	
	}

	getAllMultipleList(output + 1, size - 1);
}