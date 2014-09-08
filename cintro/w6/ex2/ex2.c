#include <stdio.h>

int getInt();

int main() {
	int n;

	printf("Please enter the degree Celsius:\n");
	


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