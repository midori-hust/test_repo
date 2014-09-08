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

int split(char *str, char splitChar, String *listString) {
  int counter = 0;
  int i;
  char *ptr, *temp;

  if(str == NULL) {
    return -1;
  }

  temp = myMalloc(sizeof(String), 1);
  strcpy(temp, str);
  ptr = temp;

  for(i = 0; i <= strlen(str); i++) {
    if(temp[i] == splitChar || temp[i] == '\0') {
      temp[i] = '\0';
      strcpy(listString[counter++].content, ptr);
      ptr = temp + i + 1;
    }
  }

  return counter;
}
