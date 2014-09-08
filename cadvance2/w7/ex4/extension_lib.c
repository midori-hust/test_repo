#include "extension_lib.h"

int solve(FILE *f) {
	SymbolTable *table = NULL;
	int i;
	
	table = createSymbolTable(makeDnsEntry, compareIp);
	getTableData(f, table);
	findDNS(table);

	dropSymbolTable(table);
	return 0;
}

void getTableData(FILE *f, SymbolTable *table) {
	String *ip, *dns;

	if((ip = myMalloc(sizeof(String), 1)) == NULL) {
		return;
	}

	if((dns = myMalloc(sizeof(String), 1)) == NULL) {
		return;
	}

	rewind(f);
	while(fscanf(f, "%[^,],", dns->content) != EOF) {
		fscanf(f, "%s\n", ip->content);
		addEntry(ip, dns, table);
	}
	rewind(f);
}

void findDNS(SymbolTable *table) {
	char *request, *respond;

	if((request = myMalloc(sizeof(char), TEMPSIZE)) == NULL) {
		return;
	}

	if((respond = myMalloc(sizeof(char), TEMPSIZE)) == NULL) {
		return;
	}

	printf("Please enter the IP which you want to find DNS: \n");
	fgets(request, SIZE, stdin);
	request[strlen(request) - 1] = '\0';
	printf("%s\n", request);

	if((respond = getEntry(request, table)) == NULL) {
		printf("Cannot find this IP\n");
	} else {
		printf("The domain %s is match with IP %s\n", respond, request);
	}
}

/* Compare functions */
Entry makeDnsEntry(void *ip, void *dns) {
	Entry result;
	String *key = (String*)ip;
	String *value = (String*)dns;

	result.key = myMalloc(sizeof(String), 1);
	memcpy(result.key, key, sizeof(String));
	result.value = myMalloc(sizeof(String), 1);
	memcpy(result.value, value, sizeof(String));

	return result;
}

int compareIp(void *a, void *b) {
	String *x = (String*)a;
	String *y = (String*)b;

	return strcmp(x->content, y->content);
}