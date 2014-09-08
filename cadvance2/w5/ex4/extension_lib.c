#include "extension_lib.h"

void insertionSort(String *array, int n) {
	int i, j;

	for(i = 1; i < n; i++) {
		j = i;
		while ((j > 0) && strcmp(array[j-1].content, array[j].content) > 0) {
			exch(array, j, j-1);
			j--;
		}
	}
}

void exch(String *a, int i, int j) {
	String *temp;

	temp = (String*) malloc(sizeof(String));

	strcpy(temp->content, a[i].content);
	strcpy(a[i].content, a[j].content);
	strcpy(a[j].content, temp->content);
	free(temp);
}

String* mallocStringStruct(int amount) {
  String *str;

  if((str = (String*) malloc((amount + 1) * sizeof(String))) == NULL) {
    printf("Cannot allocated memory\n");
    return NULL;
  }
  return str;
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


	if((emailList = mallocStringStruct(MAXSIZE)) == NULL) {
		return 1;
	}

	if((result = mallocStringStruct(MAXSIZE)) == NULL) {
		return 1;
	}

	if(!genEmailList(emailList, MAXSIZE, f_domain, f_user)) {
		return 1;
	}

	sort(emailList, 0, MAXSIZE - 1);
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

	if((domainList = mallocStringStruct(domainListSize)) == NULL)
		return 0;

	if((userList = mallocStringStruct(getTheNumberOfRowInFile(f_user))) == NULL)
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

void sort(String *a, int l, int r) {
	// We choose the most right element as pivot

	if(r <= l)
		return;
	int i = l - 1, j = r;
	int p = l - 1, q = r;
	int k;

	while(1) {
		while(strcmp(a[++i].content, a[r].content) < 0); // Swap me
		while(strcmp(a[r].content, a[--j].content) < 0)
			if(j == l)
				break;

		if(i >= j) break; // Out of order

		exch(a, i, j);
		if(strcmp(a[i].content, a[r].content) == 0)
			exch(a, ++p, i);
		if(strcmp(a[j].content, a[r].content) == 0)
			exch(a, --q, j);
	}

	exch(a, i, r);
	j = i - 1;
	i = i + 1;
	
	for(k = l; k <= p; k++)
		exch(a, k, j--);
	for(k = r - 1; k >= q; k--)
		exch(a, k, i++);
	sort(a, l, j);
	sort(a, i, r);
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