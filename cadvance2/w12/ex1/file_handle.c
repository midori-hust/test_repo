#include "file_handle.h"

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
	rewind(f);
	printf("Save file successfully\n");
}

void loadFromFile(FILE *f, char *pattern, String *array, int amount) {
	int i;

	rewind(f);
	for(i = 0; i < amount; i++) {
		fprintf(f, pattern, array[i].content);
	}
	rewind(f);
	printf("Save file successfully\n");
}