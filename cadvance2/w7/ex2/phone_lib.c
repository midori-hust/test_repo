#include "phone_lib.h"

void addPhoneNumber(long number, char *name, PhoneBook *book) {
	int i;

	for(i = 0; i < book->total; i++) {
		if(book->entries[i].number == number) {
			strcpy(book->entries[i].name, name);
			return;
		}
	}

	if(book->total == book->size) {
		reallocPhoneBook(book);
	}
	book->entries[book->total].number = number;
	strcpy(book->entries[book->total++].name, name);
}

char* getPhoneNumber(long number, PhoneBook const *book) {
	int i;

	for(i = 0; i < book->total; i++) {
		if(book->entries[i].number == number) {
			return book->entries[i].name;
		}
	}

	return NULL;
}

PhoneBook* createPhoneBook() {
	PhoneBook *result;

	if((result = myMalloc(sizeof(PhoneBook), 1)) == NULL) {
		return NULL;
	}

	if((result->entries = myMalloc(sizeof(PhoneEntry), INITIAL_SIZE)) == NULL) {
		return NULL;
	}

	result->total = 0;
	result->size = INITIAL_SIZE;

	return result;
}

void dropPhoneBook(PhoneBook *book) {
	free(book->entries);
	free(book);
}

void reallocPhoneBook(PhoneBook *book) {
	if((book->entries = realloc(book->entries, (book->size + INCREMENTAL_SIZE) * sizeof(PhoneEntry))) == NULL) {
		return;
	}
	book->size += INCREMENTAL_SIZE;
}