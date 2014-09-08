#include "extension_lib.h"

int solve() {
	PhoneBook *book = NULL;
	int i, n;
	char *temp;

	printf("Please enter the size of the phone book: \n");
	while((n = getInt()) <= 0) {
		printf("Please enter the positive number\n");
	}

	if((temp = myMalloc(sizeof(char), n)) == NULL) {
		return 1;
	}

	book = createPhoneBook();
	for(i = 0; i < n; i++) {
		sprintf(temp, "%s%d", "blah blah", i);
		addPhoneNumber(i, temp, book);
	}
	
	printf("The phone book list: \n");
	for(i = 0; i < n; i++) {
		printf("%s\n", getPhoneNumber(i, book));
	}

	dropPhoneBook(book);
	return 0;
}