#include "extension_lib.h"

int solve(FILE *f) {
	JRB tree;
	JRB anotherTree;

	if((tree = getTableData(f)) == NULL) {
		return 1;
	}

	do {
		findWords(tree);
		printf("Do you want to continue?\n");
	} while(getContinueRequest() != 'N');

	jrb_free_tree(tree);

	return 0;

	// FOR DEBUGGING
	// jrb_traverse(anotherTree, tree) {
	// 	Key *key;
	// 	Value *value;

	// 	key = jval_v(anotherTree->key);
	// 	value = jval_v(anotherTree->val);
	// 	printf("%u - %u - %s - %s - %s\n", key->lowerBound, key->upperBound, 
	// 		value->code1.content, value->code2.content, value->nationName.content); // For debugging
	// }
}

JRB getTableData(FILE *f) {
	JRB tree;

	Key *keyReader;
	Value *valueReader;

	tree = make_jrb();

	if((keyReader = myMalloc(sizeof(Key), 1)) == NULL) {
		return NULL;
	}

	if((valueReader = myMalloc(sizeof(Value), 1)) == NULL) {
		return NULL;
	}
	rewind(f);

	while(fscanf(f, "\"%u\",\"%u\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\"\n", &(keyReader->lowerBound), &(keyReader->upperBound)
		, valueReader->code1.content, valueReader->code2.content, valueReader->nationName.content) != EOF) {

		// printf("%u - %u - %s - %s - %s\n", keyReader->lowerBound, keyReader->upperBound, 
		// 	valueReader->code1.content, valueReader->code2.content, valueReader->nationName.content); // For debugging

		(void) jrb_insert_gen(tree, new_jval_v(keyReader), new_jval_v(valueReader), compareIpToCountryEntry);

		if((keyReader = myMalloc(sizeof(Key), 1)) == NULL) {
			return NULL;
		}

		if((valueReader = myMalloc(sizeof(Value), 1)) == NULL) {
			return NULL;
		}
	}

	printf("Make tree successfully.\n");

	rewind(f);
	free(keyReader);
	free(valueReader);
	return tree;
}

void findWords(JRB tree) {
	Key ipValue;
	JRB res;
	Value *value;
	int *ipList;
	int n, i;

	printf("How many client access to the website?\n");
	while((n = getInt()) <= 0) {
		printf("Please enter the positive number!\n");
	}

	if((ipList = myMalloc(sizeof(int), n)) == NULL) {
		return;
	}
	
	for(i = 0; i < n; i++) {
		printf("Please enter the IP which you want to check: \n");
		printf("IP %d: ", i + 1);
		ipList[i] = getIpValue();
	}

	printf("\nSet language: \n");
	for(i = 0; i < n; i++) {
		ipValue.upperBound = ipList[i];
		ipValue.lowerBound = ipValue.upperBound;
		
		printf("IP %d:\n", i + 1);
		if((res = jrb_find_gen(tree, new_jval_v(&ipValue), compareIpToCountryEntry)) == NULL) {
			printf("IP value: %u\n", ipValue.upperBound);
			printf("This IP is not in database\n");
			printf("Set default language: US\n");
			continue;
		}

		value = jval_v(res->val);

		printf("IP value: %u\n", ipValue.upperBound);
		printf("This IP is from %s (%s - %s)\n", value->nationName.content, value->code1.content, value->code2.content);
		printf("Set language: %s\n", value->code2.content);
	}

	free(ipList);
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

int compareIpToCountryEntry(Jval a, Jval b) {
	Key *item1;
	item1 = jval_v(a);
	Key *item2;
	item2 = jval_v(b);

	// printf("%u %u - %u %u\n", item1->lowerBound, item1->upperBound, item2->lowerBound, item2->upperBound); // Debugging
	if(item1->upperBound < item2->lowerBound)
		return -1;
	if(item1->lowerBound > item2->upperBound)
		return 1;

	return 0;
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