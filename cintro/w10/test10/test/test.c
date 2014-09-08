#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXLENGTH 100

void insertionSort(int *a, int sizeArray);
void gen(int *array, int amount);
void display(int *array, int amount);
void swap(int *a, int *b);

int main() {
	int array[MAXLENGTH];
	
	gen(array, MAXLENGTH);
	display(array, MAXLENGTH);
	insertionSort(array, MAXLENGTH);
	display(array, MAXLENGTH);

	return 0;
}

void display(int *array, int amount) {
	int i;

	printf("List of array:\n");
	for(i = 0; i < amount; i++) {
		printf("#%d: %d\n", i+1, array[i]);
	}
}

void gen(int *array, int amount) {
	int i;

	srand(time(NULL));

	for(i = 0; i < amount; i++) {
		array[i] = rand() % 20;
	}
}

void insertionSort(int *a, int sizeArray){
	int i, j;

	for(i=1; i< sizeArray; i++){
		for(j=i; j>0; j--){
			if(*(a+j-1) > *(a+j)){
				swap(a + j, a + j - 1);
			}
		}
	}
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}