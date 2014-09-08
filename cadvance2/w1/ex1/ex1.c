#include "MergeSort.h"

int main() {
	int *array;
	int i;
	FILE *f, *fResult;
	char filename[50] = "Random.txt";
	char filename1[50] = "Result.txt";

	if((f = fopen(filename, "r+")) == NULL) {
		printf("Cannot open file %s\n", filename);
		return 1;
	}

	if((fResult = fopen(filename1, "w+")) == NULL) {
		printf("Cannot open file %s\n", filename1);
		return 1;
	}

	array = (int*) malloc((MAXLENGTH+1)*sizeof(int));
	if(array == NULL) {
		printf("Cannot allocate memory\n");
		return 1;
	}

	srand(time(NULL));
	for(i=0; i < MAXLENGTH; i++) {
		array[i] = rand() % 100 + 1;
		fprintf(f, "%d\n", array[i]);
	}

	mergeSort(array, 0, MAXLENGTH - 1);

	for(i=0; i < MAXLENGTH; i++) {
		fprintf(fResult, "%d\n", array[i]);
	}
	
	free(array);
	fclose(f);
	fclose(fResult);
	return 0;
}
