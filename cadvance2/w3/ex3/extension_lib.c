#include "extension_lib.h"

#define MAXSIZE 100000

void insertionSort(String *array, int n) {
	int i, j;

	for(i = 1; i < n; i++) {
		j = i;
		while ((j > 0) && strcmp(array[j-1].content, array[j].content) > 0) {
			exch(array, j, j-1);
			j--;
		}
	}
}

void exch(String *a, int i, int j) {
	String *temp;

	temp = (String*) malloc(sizeof(String));

	strcpy(temp->content, a[i].content);
	strcpy(a[i].content, a[j].content);
	strcpy(a[j].content, temp->content);
	free(temp);
}

String* mallocStringStruct(int amount) {
  String *str;

  if((str = (String*) malloc((amount + 1) * sizeof(String))) == NULL) {
    printf("Cannot allocated memory\n");
    return NULL;
  }
  return str;
}

void printArray(String *a, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("%s\n", a[i].content);
	}
}

int solve(FILE *f) {
	String *array;
	char str[MAX_BUFF_LENGTH];
	int n = 0;

	if((array = mallocStringStruct(getTheNumberOfRowInFile(f))) == NULL) {
		return 1;
	}

	while(fscanf(f, "%s", str) != EOF) {
		strcpy(array[n++].content, str);
	}

	do {
		printf("Enter the string you wanna insert to dictionary: \n");
		fgets(str, MAX_BUFF_LENGTH, stdin);
		str[strlen(str) - 1] = '\0';
		strcpy(array[n++].content, str);
		
		insertionSort(array, n);

		printf("Do you want to continue? (Y N)\n");
	} while(getContinueRequest() != 'N');

	printToFile(f, "%s\n", array, n);

	free(array);
	return 0;
}

int getTheNumberOfRowInFile(FILE *f) {
	int row = 0;
	char str[MAX_BUFF_LENGTH];

	while(fscanf(f, "%s", str) != EOF) {
		row++;
	}
	rewind(f);

	return row;
}

void printToFile(FILE *f, char *pattern, String *array, int amount) {
	int i;

	rewind(f);
	for(i = 0; i < amount; i++) {
		fprintf(f, pattern, array[i].content);
	}
	printf("Save file successfully\n");
}