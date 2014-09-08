#include "extension_lib.h"

int stringCompare(void const*x, void const *y) {
	const String *a = (const String*)x;
	const String *b = (const String*)y;

	return strcmp(a->content, b->content);
}

String* mallocStringStruct(int amount) {
	String *result;
	if((result = (String*) malloc((amount + 1) * sizeof(String))) == NULL) {
		printf("Cannot allocated memory\n");
		return NULL;
	}
	return result;
}

void printArray(String *array, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("a[%d]\t%s\n", i, array[i].content);
	}
}

int test(int input) {
	return input * 2;
}

int solve() {
	String *array;
	int i;
	
	if((array = mallocStringStruct(10)) == NULL) {
		return 1;
	}

	printf("Enter 10 input string: \n");
	for(i = 0; i < 10; i++) {
		fgets(array[i].content, MAXLENGTH, stdin);
		array[i].content[strlen(array[i].content) - 1] = '\0';
	}

	qsort(array, 10, sizeof(String), stringCompare);

	printf("After sorting: \n");
	printArray(array, 10);


	free(array);
	return 0;
}