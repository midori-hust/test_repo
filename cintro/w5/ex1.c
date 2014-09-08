#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100
#define SIZE 7

void getGroupInput(int *a, int amount);
int getInt();
void printList(int *a, int amount);
int allStudent(int *a, int amount);
int* findMax(int *a, int amount, int *counter);
int* findMin(int *a, int amount, int *counter);
int* findSmallGroup(int *a, int amount, int *counter);
int* findBigGroup(int *a, int amount, int *counter);
int* findAverageGroup(int *a, int amount, int *counter);

int main() {
	int n;
	int i;
	int *a, *result;
	int counter;

	if((a = (int*) malloc((SIZE + 1) * sizeof(int))) == NULL) {
		printf("Cannot allocated memory\n");
		return 1;
	}

	getGroupInput(a, SIZE);
	printList(a, SIZE);

	result = findMin(a, SIZE, &counter);
	printf("\nThe list of groups which have the least number of students\n");
	for(i = 0; i < counter; i++) {
		printf("Group %d: %d student(s)\n", result[i] + 1, a[result[i]]);
	}

	result = findMax(a, SIZE, &counter);
	printf("\nThe list of groups which have the most number of students\n");
	for(i = 0; i < counter; i++) {
		printf("Group %d: %d student(s)\n", result[i] + 1, a[result[i]]);
	}

	result = findSmallGroup(a, SIZE, &counter);
	printf("\nThe list of groups which have the number of students less than average\n");
	for(i = 0; i < counter; i++) {
		printf("Group %d: %d student(s)\n", result[i] + 1, a[result[i]]);
	}

	result = findBigGroup(a, SIZE, &counter);
	printf("\nThe list of groups which have the number of students more than average\n");
	for(i = 0; i < counter; i++) {
		printf("Group %d: %d student(s)\n", result[i] + 1, a[result[i]]);
	}

	result = findAverageGroup(a, SIZE, &counter);
	if(counter == 0) {
		printf("There is no group which has the average number of students\n");
	} else {
		printf("\nThe list of groups which have the average number of students\n");
		for(i = 0; i < counter; i++) {
			printf("Group %d: %d student(s)\n", result[i] + 1, a[result[i]]);
		}	
	}

	free(a);
	free(result);
	return 0;
}

void getGroupInput(int *a, int amount) {
	int i;

	if(a == NULL) {
		return;
	}
	printf("Please enter the number of students in each group: \n");

	for(i = 0; i < amount; i++) {
		printf("Group %d: ", i + 1);
		a[i] = getInt();
	}

}

int getInt() {
	int result;

	while(scanf("%d", &result) != 1) {
		printf("Invalid input! Please enter again: ");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	return result;
}

void printList(int *a, int amount) {
	int i;

	printf("\nThe list of students: \n");
	for(i = 0; i < amount; i++) {
		printf("Group %d: %d student(s)\n", i + 1, a[i]);
	}
}

int allStudent(int *a, int amount) {
	int i, result = 0;

	for(i = 0; i < amount; i++) {
		result += a[i];
	}

	return result;
}

int* findMax(int *a, int amount, int *counter) {
	int i;
	int *result;
	int max = a[0];
	*counter = 0;

	if((result = (int*) malloc((SIZE + 1) * sizeof(int))) == NULL) {
		printf("Cannot allocated memory\n");
		return NULL;
	}

	for(i = 0; i < amount; i++) {
		if(max < a[i]) {
			max = a[i];
		}
	}

	for(i = 0; i < amount; i++) {
		if(max == a[i]) {
			result[(*counter)++] = i;
		}
	}
	return result;
}

int* findMin(int *a, int amount, int *counter) {
	int i;
	int *result;
	int max = a[0];
	*counter = 0;

	if((result = (int*) malloc((SIZE + 1) * sizeof(int))) == NULL) {
		printf("Cannot allocated memory\n");
		return NULL;
	}

	for(i = 0; i < amount; i++) {
		if(max > a[i]) {
			max = a[i];
		}
	}

	for(i = 0; i < amount; i++) {
		if(max == a[i]) {
			result[(*counter)++] = i;
		}
	}
	return result;
}

int* findSmallGroup(int *a, int amount, int *counter) {
	int *result;
	int i;
	*counter = 0;

	if((result = (int*) malloc((SIZE + 1) * sizeof(int))) == NULL) {
		printf("Cannot allocated memory\n");
		return NULL;
	}

	for(i = 0; i < amount; i++) {
		if(a[i] < allStudent(a, amount) / amount) {
			result[(*counter)++] = i;
		}
	}
	return result;
}

int* findBigGroup(int *a, int amount, int *counter) {
	int *result;
	int i;
	*counter = 0;

	if((result = (int*) malloc((SIZE + 1) * sizeof(int))) == NULL) {
		printf("Cannot allocated memory\n");
		return NULL;
	}

	for(i = 0; i < amount; i++) {
		if(a[i] > allStudent(a, amount) / amount) {
			result[(*counter)++] = i;
		}
	}
	return result;
}

int* findAverageGroup(int *a, int amount, int *counter) {
	int *result;
	int i;
	*counter = 0;

	if((result = (int*) malloc((SIZE + 1) * sizeof(int))) == NULL) {
		printf("Cannot allocated memory\n");
		return NULL;
	}

	for(i = 0; i < amount; i++) {
		if(a[i] == allStudent(a, amount) / amount) {
			result[(*counter)++] = i;
		}
	}
	return result;
}