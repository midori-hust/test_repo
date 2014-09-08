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
	char *word;

	if((word = myMalloc(sizeof(char), SIZE)) == NULL) {
		return;
	}	

	rewind(f);
	while(fscanf(f, "%s\n", word) != EOF) {
		if(strcmp(word, "") == 0)
			continue;
		addEntry(new_jval_s(word), new_jval_s(word), table);
		if((word = myMalloc(sizeof(char), SIZE)) == NULL) {
			return;
		}
	}
	rewind(f);
	sortEntry(table);
}

void findWords(SymbolTable *table) {
	char *request, *rest, *token;
	char *ptr;
	Jval respond;

	if((request = myMalloc(sizeof(char), TEMPSIZE)) == NULL) {
		return;
	}

	ptr = request;
	printf("Please enter the string: \n");
	fgets(request, SIZE, stdin);
	request[strlen(request) - 1] = '\0';

	while((token = strtok_r(ptr, " ", &rest)) != NULL) {
		ptr = rest;
		respond = getEntry(new_jval_s(token), table);
		if(jval_s(respond) == jval_s(JNULL)) {
			printf("The word \"%s\" is not in the dictionary\n", token);
			continue;
		}
		printf("The word \"%s\" is in the dictionary\n", token);
	}

	free(request);
}

/* Compare functions */
Entry makeDictionaryEntry(Jval *wordKey, Jval *wordValue) {
	Entry result;

	result.key = *wordKey;
	result.value = *wordValue;

	return result;
}

int compareDictionaryEntry(Jval *a, Jval *b) {
	return strcmp(jval_s(*a), jval_s(*b));
}