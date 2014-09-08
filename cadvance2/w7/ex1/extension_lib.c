#include "extension_lib.h"

void printArray(String *a, int amount) {
	int i;

	while(getchar() != '\n');
	for(i = 0; i < amount; i++) {
		printf("%s\n", a[i].content);
		if(i % 25 == 0 && i != 0) {
			printf("Do you want to see more 25 lines? (Y N)\n");
			if(getContinueRequest() == 'Y') {
				continue;
			} else {
				break;
			}
		}

	}
}

int solve(FILE *f_domain, FILE *f_user, FILE *fout1, FILE *fout2) {
	String *emailList, *result, *emailListAfterRemoveDup;
	int rows;
	int choice;
	int case1Flag = 0, case3Flag = 0;

	int iResult, counter, *resultEmailIndexes;

	if((emailList = myMalloc(sizeof(String), MAXSIZE)) == NULL) {
		return 1;
	}

	if((emailListAfterRemoveDup = myMalloc(sizeof(String), MAXSIZE)) == NULL) {
		return 1;
	}	

  	while(1) {
      choice = menu();

      switch(choice) {
        case 1:
        printf("You choose option %d\n", choice);
        if(case1Flag) {
        	printf("You've just choosen this option!\n");
        	continue;
        }
        if(!genEmailList(emailList, MAXSIZE, f_domain, f_user)) {
			return 1;
		}
		printToFile(fout1, "%s\n", emailList, MAXSIZE);
		printArray(emailList, MAXSIZE);
		case1Flag = 1;
        continue;
        
        case 2:
        printf("You choose option %d\n", choice);
        if(!case1Flag) {
        	printf("There is no email in the list. Please choose option 1 first to generate the list of emails!\n");
        	continue;
        }
        iResult = findMax(emailList, sizeof(String), MAXSIZE, compareMaxEmail);
        printf("The longest length and the most alphabetic email is %s\n", emailList[iResult].content);

        iResult = findMax(emailList, sizeof(String), MAXSIZE, compareMinEmail);
        printf("The longest length and the most alphabetic email is %s\n", emailList[iResult].content);
        continue;

        case 3:
        printf("You choose option %d\n", choice);
        if(!case1Flag) {
        	printf("There is no email in the list. Please choose option 1 first to generate the list of emails!\n");
        	continue;
        }
        printf("The most duplicated email is ");
        result = (String*)findMaxSizeOfDuplicateSet(emailList, sizeof(String), MAXSIZE, myStringCompare);
        printf("%s\n", result->content);
        if((resultEmailIndexes = findMaxDuplicateSet(emailList, sizeof(String), MAXSIZE, &counter, result, myStringCompare)) == NULL) {
        	printf("Cannot find the most duplicated email\n");
        } else {
        	printf("with %d duplicated emails\n", counter);
        }
        case3Flag = 1;
        continue;

        case 4:
        printf("You choose option %d\n", choice);
        if(!case1Flag) {
        	printf("There is no email in the list. Please choose option 1 first to generate the list of emails!\n");
        	continue;
        }
        heapSort(emailList, sizeof(String), MAXSIZE, myStringCompare);
        printf("Heap sort's done\n");
        printf("After sorting emails list\n");
        printArray(emailList, MAXSIZE);
        continue;

        case 5:
        printf("You choose option %d\n", choice);
        if(!case1Flag) {
        	printf("There is no email in the list. Please choose option 1 first to generate the list of emails!\n");
        	continue;
        }
        reverseArray(emailList, sizeof(String), MAXSIZE);
        printf("After reversing emails list\n");
		printArray(emailList, MAXSIZE);
        continue;

        case 6:
        printf("You choose option %d\n", choice);
        if(case1Flag) {
	        printToFile(fout1, "%s\n", emailList, MAXSIZE);
	        printf("Print emails list before removing duplicated emails: Done\n");
	        printf("Removing duplicated emails\n");
			rows = removeDuplicatedEmail(emailListAfterRemoveDup, emailList, MAXSIZE);
			printf("Removing successfully\n");
			printToFile(fout2, "%s\n", emailListAfterRemoveDup, rows);
			printf("Print emails list after removing duplicated emails: Done\n");
        }
        
        if(case3Flag) {
			free(result);
        }
		free(emailListAfterRemoveDup);
	    free(emailList);
        printf("Bye bye\n");
        break;

        default:
        printf("It is not an option\n");
        continue;
      }
      break;
    }

	// sort(emailList, 0, MAXSIZE - 1);
	// q3sort(emailList, sizeof(String), 0, MAXSIZE - 1, myStringCompare);
	return 0;
}

int genEmailList(String *emailList, int amount, FILE *f_domain, FILE *f_user) {
	String *domainList, *userList;
	int i;
	int domainListSize = getTheNumberOfRowInFile(f_domain);
	int userListSize = getTheNumberOfRowInFile(f_user);

	if((domainList = myMalloc(sizeof(String), domainListSize)) == NULL)
		return 0;

	if((userList = myMalloc(sizeof(String), getTheNumberOfRowInFile(f_user))) == NULL)
		return 0;

	i = 0;
	while(fscanf(f_domain, "%s\n", domainList[i++].content) != EOF);
	
	i = 0;
	while(fscanf(f_user, "%s\n", userList[i++].content) != EOF);
	
	srand(time(NULL));

	for(i = 0; i < amount; i++) {
		sprintf(emailList[i].content, "%s@%s", userList[rand() % userListSize].content, domainList[rand() % domainListSize].content);
	}

	free(domainList);
	free(userList);
	return 1;
}

int removeDuplicatedEmail(String* result, String* emailList, int amount) {
	int i, n = 0;

	if(amount == 1)
		return 1;
	if(result == NULL)
		return -1;
	if(emailList == NULL)
		return -1;

	strcpy(result[n++].content, emailList[0].content);

	for(i = 1; i < amount; i++) {
		if(strcmp(emailList[i-1].content, emailList[i].content) != 0) {
			strcpy(result[n++].content, emailList[i].content);
		}
	}

	return n;
}

/* Compare functions */
int myIntCompare(void const* a, void const* b) {
	const int* x = (const int*) a;
	const int* y = (const int*) b;

	if(*x == *y)
		return 0;

	return *x > *y ? 1 : -1;
}

int myStringCompare(void const* a, void const* b) {
	const String* x = (const String*) a;
	const String* y = (const String*) b;

	return strcmp(x->content, y->content);
}

// int compareStudent(void const *a, void const *b) {
// 	const Student* x = (const Student*)a;
// 	const Student* y = (const Student*)b;

// 	if(x->id == y->id)
// 		return 0;

// 	return x->id > y->id ? 1 : -1;
// }

int compareMaxEmail(void const* a, void const*b) {
	const String* x = (const String*)a;
	const String* y = (const String*)b;

	if(utilityFunction(x) == utilityFunction(y))
		return 0;
	return utilityFunction(x) > utilityFunction(y) ? 1 : -1;
}

int compareMinEmail(void const* a, void const*b) {
	const String* x = (const String*)a;
	const String* y = (const String*)b;

	if(utilityFunction(x) == utilityFunction(y))
		return 0;
	return utilityFunction(x) > utilityFunction(y) ? -1 : 1;
}

int utilityFunction(const String* a) {
	return 1000000 * strlen(a->content) + a->content[0];
}

int mySearch(void *buf, int size, int total, void *item, int (*compare)(void const*, void const*)) {
	int i, res;

	if(total == 0 || size < 0 || buf == NULL)
		return -1; // Cannot find the item element

	for(i = 0; i < total; i++) {
		res = compare(item, (char*)buf + (size * i));
		if(res == 0)
			return i;
	}

	return -1;
}

void printList(void *a, size_t total, char *pattern, void (*printPattern)(void* buf, char *pattern, size_t total)) {
	printPattern(a, pattern, total);
}

// void myPrintPattern(void *buf, char *pattern, size_t total) {
// 	int i;
// 	Student *a = (Student*)buf;

// 	for(i = 0; i < total; i++) {
// 		printf(pattern, i, a[i].id, a[i].name);
// 	}
// }

// int findMinCompare(void const* x, void const* y) {
// 	const Student* a = (const Student*)x;
// 	const Student* b = (const Student*)y;

// 	if(a->id == b->id)
// 		return 0;

// 	return a->id > b->id ? 1 : -1;
// }


// int findMaxCompare(void const* x, void const* y) {
// 	const Student* a = (const Student*)x;
// 	const Student* b = (const Student*)y;

// 	if(a->id == b->id)
// 		return 0;

// 	return a->id > b->id ? -1 : 1;
// }
