#include "symbol_table_jval.h"

void addEntry(Jval key, Jval value, SymbolTable *table) {
	Entry temp;
	int i;

	if(table->total == table->size) {
		reallocEntry(table);
	}

	temp = table->makeNode(key, value);

	// TODO: searching

	memcpy((char*)table->entries + table->total * sizeof(Entry), &temp, sizeof(Entry));
	table->total++;

	// TODO: resort
}

Jval getEntry(Jval key, SymbolTable const *table) {
	int i;

	for(i = 0; i < table->total; i++) {
		if(table->compare(&table->entries[i].key, &key) == 0) {
			return table->entries[i].value;
		}
	}
	return JNULL;
}

SymbolTable* createSymbolTable(Entry (*makeNode)(Jval, Jval), int (*compare)(Jval*, Jval*)) {
	SymbolTable *result;

	if((result = myMalloc(sizeof(SymbolTable), 1)) == NULL) {
		return NULL;
	}

	if((result->entries = myMalloc(sizeof(Entry), INITIAL_SIZE)) == NULL) {
		return NULL;
	}

	result->total = 0;
	result->size = INITIAL_SIZE;
	result->makeNode = makeNode;
	result->compare = compare;

	return result;
}

void dropSymbolTable(SymbolTable *table) {
	free(table->entries);
	free(table);
}

void reallocEntry(SymbolTable *table) {
	if((table->entries = realloc(table->entries, (table->size + INCREMENTAL_SIZE + 1) * sizeof(Entry))) == NULL) {
		return;
	}

	table->size += INCREMENTAL_SIZE;
}