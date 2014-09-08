#include <stdio.h>

int getInt();
void printTriangle(int n);
void anotherPrintTriangle(int n);

int main() {
	int n;

	printf("Please enter the size of the triangle:\n");
	while((n = getInt()) <= 0) {
		printf("Invalid input! Please enter the positive number!\n");
	}

	//printTriangle(n);
	anotherPrintTriangle(n);
	return 0;
}

int getInt() {
	int result;

	while(scanf("%d", &result) != 1) {
		printf("Invalid input! Please try again!\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	return result;
}

void printTriangle(int n) {
	int i, j;
	int counter = 1;

	for(i = 0; i < n; i++) {
		for(j = 0; j < n + counter - 1; j++) {
			if(j >= (n - counter)) {
				printf("*");
			} else {
				printf(" ");
			}
		}
		counter++;
		printf("\n");
	}
}

void anotherPrintTriangle(int n) {
	int i, j;
	int counter = 1;

	for(i = 0; i < n; i++) {
		for(j = 0; j < n + counter - 1; j++) {
			if(j >= (n - counter)) {

				if((j - n + counter) % 2 == 0)
					printf("*");
				else
					printf(" ");

			} else {
				printf(" ");
			}
		}
		counter++;
		printf("\n");
	}	
}