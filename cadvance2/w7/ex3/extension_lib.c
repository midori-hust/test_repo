#include "extension_lib.h"

#define SIZE 5

int solve() {
	SymbolTable *table = NULL;
	int i, n;
	char *temp;

	printf("Please enter the size of the phone book:\n");
	while((n = getInt()) <= 0) {
		printf("Please enter the positive number\n");
	}

	if((temp = myMalloc(sizeof(char), n)) == NULL) {
		return 1;
	}

	table = createSymbolTable(makePhoneBook, comparePhone);

	for(i = 0; i < n; i++) {
		sprintf(temp, "%s%d", "blah blah", i);
		addEntry(&i, temp, table);
	}

	printf("The list of the phone number: \n");
	for(i = 0; i < n; i++) {
		if((temp = getEntry(&i, table)) == NULL) {
			printf("Null entry\n");
			continue;
		}
		printf("Phone: %i, name: %s\n", i, (char*)getEntry(&i, table));
	}

	free(temp);
	dropSymbolTable(table);
	return 0;
}

Entry makePhoneBook(void *number, void *name) {
	Entry result;
	int *key = (int*)number;
	String *value = (String*)name;

	result.key = myMalloc(sizeof(int), 1);
	memcpy(result.key, key, sizeof(int));
	result.value = myMalloc(sizeof(String), 1);
	memcpy(result.value, value, sizeof(String));

	return result;
}

int comparePhone(void *a, void *b) {
	int *x = (int*)a;
	int *y = (int*)b;

	if(*x == *y)
		return 0;

	return *x > *y ? 1 : -1;
}