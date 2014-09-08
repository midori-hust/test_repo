#include "extension_lib.h"

int solve() {
	Student *a;
	int i;
	Student searchEle;
	int iResult;
	
	Student *temp;
	int *resultSetPoint, counter;

	searchEle.id = 10;
	strcpy(searchEle.name, "Student10");

	if((a = myMalloc(sizeof(Student), MAXSIZE)) == NULL) {
		return 1;
	}

	// for(i = 0; i < MAXSIZE; i++) {
	// 	a[i].id = i + 1;
	// 	sprintf(a[i].name, "%s%d", "Student", i + 1);
	// }

	genData(a, MAXSIZE);


	if((iResult = mySearch(a, sizeof(Student), MAXSIZE, &searchEle, compareStudent)) == -1) {
		printf("Cannot find element %d\n", searchEle.id);
	} else {
		printf("The element %d is at index %d\n", searchEle.id, iResult);
	}

	iResult = findMax(a, sizeof(Student), MAXSIZE, findMaxCompare);
	printf("The greatest element is %d, at index %d\n", a[iResult].id, iResult);

	iResult = findMax(a, sizeof(Student), MAXSIZE, findMinCompare);
	printf("The lowest element is %d, at index %d\n", a[iResult].id, iResult);

	printf("Before reverse array\n");
	printList(a, MAXSIZE, "Student %d\n\tId: %d\n\tName: %s\n", myPrintPattern);

	// Reverse array

	reverseArray(a, sizeof(Student), MAXSIZE);
	printf("After reverse array:\n");
	printList(a, MAXSIZE, "Student %d\n\tId: %d\n\tName: %s\n", myPrintPattern);

	// mySort(a, sizeof(Student), MAXSIZE, myStudentCompare);
	temp = (Student*)findMaxSizeOfDuplicateSet(a, sizeof(Student), MAXSIZE, compareStudent);

	printf("The max size of duplicate is %s\n", temp->name);

	if((resultSetPoint = findMaxDuplicateSet(a, sizeof(Student), MAXSIZE, &counter, temp, myStudentCompare)) == NULL) {
		printf("Cannot find the max duplicate set point\n");
	} else {
		printf("The set of point at index:\n");
		for(i = 0; i < counter; i++) {
			printf("%d\t", resultSetPoint[i]);
			if((i + 1) % 5 == 0) {
				printf("\n");
			}
		}
		printf("\n");
	}
	
	free(resultSetPoint);
	free(temp);
	free(a);
	return 0;
}

void genData(Student *a, int amount) {
	int i;

	srand(time(NULL));
	for(i = 0; i < MAXSIZE; i++) {
		a[i].id = rand() % 100;
		sprintf(a[i].name, "%s%d", "Student", a[i].id);
	}
}

int myIntCompare(void const* a, void const* b) {
	const int* x = (const int*) a;
	const int* y = (const int*) b;

	if(*x == *y)
		return 0;

	return *x > *y ? 1 : -1;
}

int myStudentCompare(void const* a, void const* b) {
	const Student* x = (const Student*) a;
	const Student* y = (const Student*) b;

	return strcmp(x->name, y->name); // Find the student name
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

void myPrintPattern(void *buf, char *pattern, size_t total) {
	int i;
	Student *a = (Student*)buf;

	for(i = 0; i < total; i++) {
		printf(pattern, i, a[i].id, a[i].name);
	}
}

int findMinCompare(void const* x, void const* y) {
	const Student* a = (const Student*)x;
	const Student* b = (const Student*)y;

	if(a->id == b->id)
		return 0;

	return a->id > b->id ? 1 : -1;
}


int findMaxCompare(void const* x, void const* y) {
	const Student* a = (const Student*)x;
	const Student* b = (const Student*)y;

	if(a->id == b->id)
		return 0;

	return a->id > b->id ? -1 : 1;
}

int findMax(void *buf, size_t size, size_t total, int (*compare)(void const*, void const*)) {
	int i, res, iMax = 0;
	void* item;

	if(total == 0 || size < 0 || buf == NULL)
		return -1; // Cannot find the item element

	if((item = myMalloc(size, sizeof(char))) == NULL) {
		return -1;
	}

	memcpy(item, (char*)buf, size);

	for(i = 0; i < total; i++) {
		res = compare(item, (char*)buf + (size * i));
		if(res > 0) {
			memcpy(item, (char*)buf + (size * i), size);
			iMax = i;
		}
	}

	free(item);
	return iMax;
}

void reverseArray(void *buf, size_t size, size_t total) {
	int i;

	for(i = 0; i < total / 2; i++) {
		exch(buf, i, total - i - 1, size);
	}
}

void mySort(void *buf, size_t size, size_t total, int (*compare)(void const *, void const *)) {
	q3sort(buf, size, 0, total - 1, compare);
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

	free(temp);
}

int compareStudent(void const *a, void const *b) {
	const Student* x = (const Student*)a;
	const Student* y = (const Student*)b;

	if(x->id == y->id)
		return 0;

	return x->id > y->id ? 1 : -1;
}

void* findMaxSizeOfDuplicateSet(void *buf, size_t size, size_t total, int (*compare)(void const *a, void const *b)) {
	char *temp, *result;
	int counter = 0, i, maxCount = -1;

	if(total == 0 || size < 0 || buf == NULL)
		return NULL; // Cannot find the item element

	if((temp = myMalloc(size, total)) == NULL) {
		return NULL;
	}

	if((result = myMalloc(size, total)) == NULL) {
		return NULL;
	}

	mySort(buf, size, total, compare);

	memcpy(temp, buf, size);

	for(i = 0; i < total; i++) {
		if(compare(buf + i * size, temp) == 0) {
			counter++;
		} else {
			memcpy(temp, buf + i * size, size);
			counter = 1;
		}

		if(counter > maxCount) {
			maxCount = counter;
			memcpy(result, buf + i * size, size);
		}
	}

	free(temp);
	return result;
}

int* findMaxDuplicateSet(void *buf, size_t size, size_t total, int *counter, 
	void const *maxNumber, int (*compare)(void const *a, void const *b)) {

	int* result;
	int i;

	*counter = 0;

	if(total == 0 || size < 0 || buf == NULL)
		return NULL; // Cannot find the item element

	if((result = myMalloc(size, total)) == NULL)
		return NULL;

	mySort(buf, size, total, compare);

	for(i = 0; i < total; i++) {
		if(compare(buf + i * size, maxNumber) == 0) {
			result[(*counter)++] = i;
		}
	}

	return result;
}