#include "extension_lib.h"

int recordCompare(void const*x, void const *y) {
	const Record* a = (const Record*)x;
	const Record* b = (const Record*)y;

	if(strcmp(a->product, b->product) == 0) {
		if(a->price == b->price)
			return 0;
		return a->price > b->price ? 1 : -1;

	}
	return strcmp(a->product, b->product);
} // Swap the return value to sort DESC

int recordCompare1(void const*x, void const *y) {
	const Record* a = (const Record*)x;
	const Record* b = (const Record*)y;

	if(a->price == b->price) {
		return strcmp(a->product, b->product);
	}
	return a->price > b->price ? 1 : -1;
}

Record* mallocRecord(int amount) {
	Record *result;
	if((result = (Record*) malloc((amount + 1) * sizeof(Record))) == NULL) {
		printf("Cannot allocated memory\n");
		return NULL;
	}
	return result;
}

void printArray(Record *array, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("Record %d:\n\tProduct name: %s\n\tPrice: %f\n", i + 1, array[i].product, array[i].price);
	}
}

int solve() {
	Record *array;
	int i;
	
	if((array = mallocRecord(10)) == NULL) {
		return 1;
	}

	printf("Enter 10 input Record: \n");
	for(i = 0; i < 10; i++) {
		printf("Product's name: ");
		fgets(array[i].product, MAXLENGTH, stdin);
		array[i].product[strlen(array[i].product) - 1] = '\0';
		printf("Product's price: ");
		array[i].price = getFloat();
	}

	qsort(array, 10, sizeof(Record), recordCompare);

	printf("After sorting: \n");
	printArray(array, 10);

	// qsort(array, 10, sizeof(Record), recordCompare1);

	// printf("After sorting: \n");
	// printArray(array, 10);
	free(array);
	return 0;
}