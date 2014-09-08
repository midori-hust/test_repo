#include "extension_lib.h"

int intCompare(void const* x, void const *y) {
	int m, n;
	m = *((int*)x);
	n = *((int*)y);

	if(m == n)
		return 0;

	return m > n ? -1 : 1;
}

int floatCompare(void const* x, void const *y) {
	float m, n;
	m = *((float*)x);
	n = *((float*)y);

	if(m == n)
		return 0;

	return m > n ? 1 : -1;
}

void genData(int* array, int amount) {
	int i;

	srand(time(NULL));
	for(i = 0; i < amount; i++) {
		array[i] = rand() % MAXSIZE;
	}
}

void genFloatData(float* array, int amount) {
	int i;

	srand(time(NULL));
	for(i = 0; i < amount; i++) {
		array[i] = (float)(rand() % MAXSIZE) / (rand() % MAXSIZE + 1);
	}
}

int* mallocInt(int amount) {
	int *result;
	if((result = (int*) malloc((amount + 1) * sizeof(int))) == NULL) {
		printf("Cannot allocated memory\n");
		return NULL;
	}
}

float* mallocFloat(int amount) {
	float *result;
	if((result = (float*) malloc((amount + 1) * sizeof(float))) == NULL) {
		printf("Cannot allocated memory\n");
		return NULL;
	}
}

void printArray(int *array, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("a[%d]\t%d\n", i, array[i]);
	}
}

void printFloatArray(float *array, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("a[%d]\t%f\n", i, array[i]);
	}
}

int solve() {
	float *array;

	if((array = mallocFloat(MAXSIZE)) == NULL) {
		return 1;
	}

	genFloatData(array, MAXSIZE);
	qsort(array, MAXSIZE, sizeof(float), floatCompare);

	printf("After sorting: \n");
	printFloatArray(array, MAXSIZE);

	free(array);
	return 0;
}