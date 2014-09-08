#include "extension_lib.h"

int solve(FILE *f) {
	SymbolTable *table = NULL;
	int i;
	
	table = createSymbolTable(makeDomainEntry, compareDomainEntry);
	getTableData(f, table);
	do {
		findWords(table);
		printf("Do you want to continue?\n");
	} while(getContinueRequest() != 'N');

	dropSymbolTable(table);
	return 0;
}

void getTableData(FILE *f, SymbolTable *table) {
	String *word;

	if((word = myMalloc(sizeof(String), 1)) == NULL) {
		return;
	}

	rewind(f);
	while(fscanf(f, "%s\n", word->content) != EOF) {
		if(strcmp(word->content, "") == 0)
			continue;
		addEntry(word, word, table);
	}
	rewind(f);
}

void findWords(SymbolTable *table) {
	char *request, *respond, *rest;
	String token[SIZE];

	if((request = myMalloc(sizeof(char), TEMPSIZE)) == NULL) {
		return;
	}

	if((respond = myMalloc(sizeof(char), TEMPSIZE)) == NULL) {
		return;
	}

	printf("Please enter the domain name which you want to access: \n");
	fgets(request, SIZE, stdin);
	request[strlen(request) - 1] = '\0';

	if((respond = getEntry(request, table)) != NULL) {
		printf("You can not access this domain name. It is blocked\n");
	} else {
		printf("You can access this domain name.\n");
	}

	free(request);
	free(respond);
}

/* Compare functions */
Entry makeDomainEntry(void *wordKey, void *wordValue) {
	Entry result;
	String *key = (String*)wordKey;
	String *value = (String*)wordValue;

	result.key = myMalloc(sizeof(String), 1);
	memcpy(result.key, key, sizeof(String));
	result.value = myMalloc(sizeof(String), 1);
	memcpy(result.value, value, sizeof(String));

	return result;
}

int compareDomainEntry(void *a, void *b) {
	String *x = (String*)a;
	String *y = (String*)b;

	return strcmp(x->content, y->content);
}