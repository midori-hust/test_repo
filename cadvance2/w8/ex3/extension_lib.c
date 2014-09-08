#include "extension_lib.h"

int solve(FILE *f) {
	SymbolTable *table = NULL;
	int i;
	
	table = createSymbolTable(makeIpToCountryEntry, compareIpToCountryEntry);
	getTableData(f, table);
	do {
		findWords(table);
		printf("Do you want to continue?\n");
	} while(getContinueRequest() != 'N');

	dropSymbolTable(table);

	return 0;
}

void getTableData(FILE *f, SymbolTable *table) {
	Key *keyReader;
	Value *valueReader;
	int a, b;
	

	if((keyReader = myMalloc(sizeof(Key), 1)) == NULL) {
		return;
	}

	if((valueReader = myMalloc(sizeof(Value), 1)) == NULL) {
		return;
	}
	rewind(f);

	while(fscanf(f, "\"%u\",\"%u\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\"\n", &(keyReader->lowerBound), &(keyReader->upperBound)
		, valueReader->code1.content, valueReader->code2.content, valueReader->nationName.content) != EOF) {
		// printf("%u - %u - %s - %s - %s\n", keyReader->lowerBound, keyReader->upperBound, 
		// 	valueReader->code1.content, valueReader->code2.content, valueReader->nationName.content); // For debugging

		addEntry(keyReader, valueReader, table);
	}

	rewind(f);
	free(keyReader);
	free(valueReader);
}

void findWords(SymbolTable *table) {
	Key ipValue;
	Value *value;

	printf("Please enter the IP which you want to check: \n");
	ipValue.upperBound = getIpValue();
	ipValue.lowerBound = ipValue.upperBound;

	if((value = myMalloc(sizeof(Value), 1)) == NULL) {
		return;
	}

	if((value = getEntry(&ipValue, table)) == NULL) {
		printf("This IP is not in database\n");
		return;
	}

	printf("This IP is in nation %s (%s - %s)\n", value->nationName.content, value->code1.content, value->code2.content);
	printf("IP value: %u\n", ipValue.upperBound);
}

int getIpValue() {
	int a, b, c, d;

	while(scanf("%d.%d.%d.%d", &a, &b, &c, &d) != 4) {
		printf("Invalid input! Please enter an valid IP!\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	return a * myPow(255, 3) + b * myPow(255, 2) + c * myPow(255, 1) + d;
}

/* Compare functions */

Entry makeIpToCountryEntry(void *key, void *value) {
	Entry result;
	Key *tempKey = (Key*)key;
	Value *tempValue = (Value*)value;

	result.key = myMalloc(sizeof(Key), 1);
	memcpy(result.key, tempKey, sizeof(Key));
	result.value = myMalloc(sizeof(Value), 1);
	memcpy(result.value, tempValue, sizeof(Value));

	return result;
}

int compareIpToCountryEntry(void *a, void *b) {
	Key *entry = (Key*)a;
	Key *key = (Key*)b;

	if(entry->upperBound > key->upperBound && entry->lowerBound < key->upperBound)
		return 0;

	return 1;
}

int myPow(int a, int b) {
	int i;
	int result = 1;

	if(b == 0)
		return 1;

	for(i = 0; i < b; i++) {
		result *= a;
	}

	return result;
}