#include "symbol_table.h"

void addEntry(Jval key, Jval value, SymbolTable *table) {
	Entry temp;
	int index;

	if(table->total == table->size) {
		reallocEntry(table);
	}

	temp = table->makeNode(&key, &value);

	if((index = binarySearchSymtab(temp, 0, table->total - 1, table)) >= 0) {
		printf("Boom\n");
		return;
	}

	memcpy((char*)table->entries + table->total * sizeof(Entry), &temp, sizeof(Entry));
	table->total++;
}

Jval getEntry(Jval key, SymbolTable const *table) {
	int i;

	for(i = 0; i < table->total; i++) {
		if(table->compare(&(table->entries[i].key), &key) == 0) {
			return table->entries[i].value;
		}
	}
	return JNULL;
}

SymbolTable* createSymbolTable(Entry (*makeNode)(Jval*, Jval*), int (*compare)(Jval*, Jval*)) {
	SymbolTable *result;

	if((result = myMalloc(sizeof(SymbolTable), 1)) == NULL) {
		return NULL;
	}

	if((result->entries = myMalloc(sizeof(SymbolTable), INITIAL_SIZE)) == NULL) {
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

void sortEntry(SymbolTable *table) {
	quickSortSymtab(0, table->total - 1, table);
}



// Private functions
int binarySearchSymtab(Entry item, int low, int high, SymbolTable const *table) {
	int mid = midPoint(low, high);
	int res;

	if(low > high) {
		return -1;
	}

	res = table->compare(&(table->entries[mid].key), &item.key);
	if(res > 0) {
		return binarySearchSymtab(item, low, mid - 1, table);
	}

	if(res < 0) {
		return binarySearchSymtab(item, mid + 1, high, table);
	}

	return mid;
}

void insertionSortSymtab(SymbolTable *table) {
	int i, j;

	for(i = 1; i < table->total; i++) {
		j = i;
		while ((j > 0) && table->compare(&table->entries[j-1].key, &table->entries[j].key) > 0) {
			exchangeEntry(table, j, j-1);
			j--;
		}
	}
}

void exchangeEntry(SymbolTable *table, int i, int j) {
	Entry temp;

	memcpy(&temp, (char*)table->entries + i * sizeof(Entry), sizeof(Entry));
	memcpy((char*)table->entries + i * sizeof(Entry), (char*)table->entries + j * sizeof(Entry), sizeof(Entry));
	memcpy((char*)table->entries + j * sizeof(Entry), &temp, sizeof(Entry));
}

void quickSortSymtab(int l, int r, SymbolTable *table) {
	if(r <= l)
		return;
	int i = l - 1, j = r;
	int p = l - 1, q = r;
	int k;

	while(1) {
		i++;
		while(table->compare(&table->entries[i].key, &table->entries[r].key) < 0) { // Swap me
			i++;
		}
		j--;
		while(table->compare(&table->entries[r].key, &table->entries[j].key) < 0) {
			if(j == l) {
				break;
			}
			j--;
		}

		if(i >= j) break; // Out of order

		exchangeEntry(table, i, j);
		if(table->compare(&table->entries[i].key, &table->entries[r].key) == 0) {
			exchangeEntry(table, ++p, i);
		}
		if(table->compare(&table->entries[j].key, &table->entries[r].key) == 0) {
			exchangeEntry(table, --q, j);
		}
	}

	exchangeEntry(table, i, r);
	j = i - 1;
	i = i + 1;
	
	for(k = l; k <= p; k++)
		exchangeEntry(table, k, j--);
	for(k = r - 1; k >= q; k--)
		exchangeEntry(table, k, i++);
	quickSortSymtab(l, j, table);
	quickSortSymtab(i, r, table);
}