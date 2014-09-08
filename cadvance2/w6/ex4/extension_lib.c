#include "extension_lib.h"

void* myMalloc(int size, int total) {
	char *result;

	if((result = (char*) malloc((total + 1) * size * sizeof(char))) == NULL) {
		printf("Cannot allocated memory\n");
		return NULL;
	}

	return result;
}

void printArray(String *a, int amount) {
	int i;

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
	String *emailList, *result;
	int rows;


	if((emailList = myMalloc(sizeof(String), MAXSIZE)) == NULL) {
		return 1;
	}

	if((result = myMalloc(sizeof(String), MAXSIZE)) == NULL) {
		return 1;
	}

	if(!genEmailList(emailList, MAXSIZE, f_domain, f_user)) {
		return 1;
	}

	// sort(emailList, 0, MAXSIZE - 1);
	q3sort(emailList, sizeof(String), 0, MAXSIZE - 1, myCompare);
	printToFile(fout1, "%s\n", emailList, MAXSIZE);
	printf("Sort successfully\n");
	printf("The email list before removing duplicated emails: \n");
	printArray(emailList, MAXSIZE); // Debugging

	rows = removeDuplicatedEmail(result, emailList, MAXSIZE);

	// printArray(result, rows); // Debugging
	printToFile(fout2, "%s\n", result, rows);
	printf("Print to file successfully\n");
	
	free(emailList);
	free(result);
	return 0;
}

int getTheNumberOfRowInFile(FILE *f) {
	int row = 0;
	char str[MAX_BUFF_LENGTH];

	while(fscanf(f, "%s", str) != EOF) {
		row++;
	}
	rewind(f);

	return row;
}

void printToFile(FILE *f, char *pattern, String *array, int amount) {
	int i;

	rewind(f);
	for(i = 0; i < amount; i++) {
		fprintf(f, pattern, array[i].content);
	}
	rewind(f);
	printf("Save file successfully\n");
}

void loadFromFile(FILE *f, char *pattern, String *array, int amount) {
	int i;

	rewind(f);
	for(i = 0; i < amount; i++) {
		fprintf(f, pattern, array[i].content);
	}
	rewind(f);
	printf("Save file successfully\n");
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

void q3sort(void *buf, size_t size, int l, int r, int (*compare)(void const *, void const *)) {
	if(r <= l)
		return;
	int i = l - 1, j = r;
	int p = l - 1, q = r;
	int k;

	while(1) {
		i++;
		while(compare((char*)buf + size * i, (char*)buf + size * r) < 0) { // Swap me
			i++;
		}
		j--;
		while(compare((char*)buf + size * r, (char*)buf + size * j) < 0) {
			if(j == l) {
				break;
			}
			j--;
		}

		if(i >= j) break; // Out of order

		exch(buf, i, j, size);
		if(compare((char*)buf + size * i, (char*)buf + size * r) == 0) {
			exch(buf, ++p, i, size);
		}
		if(compare((char*)buf + size * j, (char*)buf + size * r) == 0) {
			exch(buf, --q, j, size);
		}
	}

	exch(buf, i, r, size);
	j = i - 1;
	i = i + 1;
	
	for(k = l; k <= p; k++)
		exch(buf, k, j--, size);
	for(k = r - 1; k >= q; k--)
		exch(buf, k, i++, size);
	q3sort(buf, size, l, j, compare);
	q3sort(buf, size, i, r, compare);
}

void exch(void *buf, int i, int j, size_t size) {
	char* temp;

	if((temp = myMalloc(sizeof(char), size)) == NULL) {
		return;
	}

	memcpy(temp, buf + i * size, size);
	memcpy(buf + i * size, buf + j * size, size);
	memcpy(buf + j * size, temp, size);
}

int myCompare(void const* x, void const* y) {
	const String* a = (const String*)x;
	const String* b = (const String*)y;

	return strcmp(a->content, b->content);
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