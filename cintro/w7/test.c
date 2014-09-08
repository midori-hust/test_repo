#include <stdio.h>

int getInt();

int main() {
	int n;

	do {
		printf("Please enter the number in range [0, 10]\n");
		n = getInt();
		if(n < 0 || n > 10) {
			printf("Please enter another number\n");
		}
	} while(n < 0 || n > 10);

	printf("The number which you've just entered is %d\n", n);

	return 0;
}

int getInt() {
	int result;

	while(scanf("%d", &result) != 1) {
		printf("Invalid input! Please try again\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	return result;
}