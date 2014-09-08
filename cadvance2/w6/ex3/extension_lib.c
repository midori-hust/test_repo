#include "extension_lib.h"

int solve() {
	Student *a;
	int i;
	Student searchEle;

	searchEle.id = 256;
	strcpy(searchEle.name, "Student256");

	if((a = myMalloc(sizeof(Student), MAXSIZE)) == NULL) {
		return 1;
	}

	for(i = 0; i < MAXSIZE; i++) {
		a[i].id = i + 1;
		sprintf(a[i].name, "%s%d", "Student", i + 1);
	}

	printf("The element %d is at index %d\n", searchEle.id, mySearch(a, sizeof(Student), MAXSIZE, &searchEle, myStudentCompare));

	return 0;
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

	// if(x->id == y->id)
	// 	return 0;

	// return x->id > y->id ? 1 : -1;

	return strcmp(x->name, y->name);
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

void printIntList(int *a, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("a[%d] = %d\n", i, a[i]);
	}
}

void* myMalloc(int size, int total) {
	char *result;

	if((result = (char*) malloc((total + 1) * size * sizeof(char))) == NULL) {
		printf("Cannot allocated memory\n");
		return NULL;
	}

	return result;
}