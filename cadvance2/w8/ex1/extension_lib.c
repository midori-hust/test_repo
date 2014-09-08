#include "extension_lib.h"

int solve(FILE *f) {
	SymbolTable *table = NULL;
	int i;
	
	table = createSymbolTable(makeDictionaryEntry, compareDictionaryEntry);
	getTableData(f, table);
	findWords(table);

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
	char *request, *respond, *rest, *token;
	char *ptr;

	if((request = myMalloc(sizeof(char), TEMPSIZE)) == NULL) {
		return;
	}

	if((respond = myMalloc(sizeof(char), TEMPSIZE)) == NULL) {
		return;
	}

	ptr = request;
	printf("Please enter the string: \n");
	fgets(request, SIZE, stdin);
	request[strlen(request) - 1] = '\0';

	while((token = strtok_r(ptr, " ", &rest)) != NULL) {
		ptr = rest;
		if((respond = getEntry(token, table)) == NULL) {
			printf("The word \"%s\" is not in the dictionary\n", token);
			continue;
		}
		printf("The word \"%s\" is in the dictionary\n", token);
	}

	free(request);
	free(respond);
}

/* Compare functions */
Entry makeDictionaryEntry(void *wordKey, void *wordValue) {
	Entry result;
	String *key = (String*)wordKey;
	String *value = (String*)wordValue;

	result.key = myMalloc(sizeof(String), 1);
	memcpy(result.key, key, sizeof(String));
	result.value = myMalloc(sizeof(String), 1);
	memcpy(result.value, value, sizeof(String));

	return result;
}

int compareDictionaryEntry(void *a, void *b) {
	String *x = (String*)a;
	String *y = (String*)b;

	return strcmp(x->content, y->content);
}