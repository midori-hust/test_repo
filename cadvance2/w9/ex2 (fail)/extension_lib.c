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
	Jval tempWord;

	if((word = myMalloc(sizeof(String), 1)) == NULL) {
		return;
	}

	rewind(f);
	while(fscanf(f, "%s\n", word->content) != EOF) {
		if(strcmp(word->content, "") == 0)
			continue;
		tempWord = new_jval_s(word->content);
		addEntry(tempWord, tempWord, table);
	}
	rewind(f);

	free(word);
}

void findWords(SymbolTable *table) {
	char *request, *rest, *token;
	char *ptr;
	Jval temp;
	Jval respond;

	if((request = myMalloc(sizeof(char), SIZE)) == NULL) {
		return;
	}

	ptr = request;
	printf("Please enter the string: \n");
	fgets(request, SIZE, stdin);
	request[strlen(request) - 1] = '\0';

	while((token = strtok_r(ptr, " ", &rest)) != NULL) {
		ptr = rest;
		temp = new_jval_s(token);

		respond = getEntry(temp, table);
		// if(jval_s(respond) == NULL) {
		if(jval_s(respond) == jval_s(JNULL)) {
			printf("The word \"%s\" is not in the dictionary\n", token);
			continue;
		}
		printf("The word \"%s\" is in the dictionary\n", token);
	}

	free(request);
}

/* Compare functions */
Entry makeDictionaryEntry(Jval key, Jval value) {
	Entry result;

	result.key = key;
	result.value = value;

	return result;
}

int compareDictionaryEntry(Jval *a, Jval *b) {
	char *x = jval_s(*a);
	char *y = jval_s(*b);

	return strcmp(x, y);
}