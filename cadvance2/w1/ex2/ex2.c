#include "sort_lib.h"
#include "my_input_lib.h"
#include "extension_lib.h"
#include <time.h>

#define MAXSIZE 2000000

int main() {
	// FILE *f;
	// char filename[MAXLENGTH] = "gen_number.txt";

	int *array;
	int i;

	// if ((f = fopen(filename, "r+")) == NULL) {
	// 	printf("Cannot open file %s\n", filename);
	// 	return 1;
	// }

	array = (int*) malloc((MAXLENGTH+1) * sizeof(int));
	if(array == NULL) {
		printf("Cannot allocate memory\n");
		return 1;
	}

	srand(time(NULL));

	for(i = 0; i < MAXLENGTH; i++) {
		array[i] = rand() % 100 + 1;
		//fprintf(f, "%d\n", array[i]);
	}


	printArray(array, MAXLENGTH);

	quickSortMedian(array, 0, MAXLENGTH - 1);
	//mergeSort(array, 0, MAXLENGTH - 1);
	//selection(array, MAXLENGTH);
	//bubbleSort(array, MAXLENGTH);
	//insertionSort(array, MAXLENGTH);
	//quickSort(array, 0, MAXLENGTH - 1);

	printArray(array, MAXLENGTH);

	// fclose(f);
	free(array);
	return 0;
}