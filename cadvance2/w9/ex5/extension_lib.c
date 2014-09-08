#include "extension_lib.h"

int solve(FILE *f) {
	SymbolTable *table = NULL;
	int i;
	
	table = createSymbolTable(makeDictionaryEntry, compareDictionaryEntry);
	getTableData(f, table);
	do {
		findWords(table);
		printf("Do you want to continue?\n");
	} while(getContinueRequest() != 'N');

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
	Jval respond;

	if((request = myMalloc(sizeof(char), TEMPSIZE)) == NULL) {
		return;
	}

	printf("Please enter the domain name which you want to access: \n");
	fgets(request, SIZE, stdin);
	request[strlen(request) - 1] = '\0';

	respond = getEntry(new_jval_s(request), table);
	if(jval_s(respond) != jval_s(JNULL)) {
		printf("You can not access this domain name. It is blocked\n");
	} else {
		printf("You can access this domain name.\n");
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