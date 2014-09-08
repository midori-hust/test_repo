#ifndef __PHONE_LIB_H__
#define __PHONE_LIB_H__

#include "my_input_lib.h"

#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 10

typedef struct _PhoneEntry {
	long number;
	char name[80];
} PhoneEntry;

typedef struct _PhoneBook {
	PhoneEntry *entries;
	int total;
	int size;
} PhoneBook;

/* API */
void addPhoneNumber(long number, char *name, PhoneBook *book);
char* getPhoneNumber(long number, PhoneBook const *book);
PhoneBook* createPhoneBook();
void dropPhoneBook(PhoneBook *book);
void reallocPhoneBook(PhoneBook *book);

#endif