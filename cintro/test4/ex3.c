#include <stdio.h>

int getInt();

int main() {
	int n;

	printf("Please enter the positive number:\n");
	while((n = getInt()) < 1) {
		printf("Please enter a positive number\n");
	}

	printf("The sum is %d\n", sumCalculate(n));

	return 0;
}

int sumCalculate(int n) {
	int i;
	int sum = 0;

	for(i = 1; i < n; i++) {
		if(n % i == 0)
			sum += i;
	}
	
	return sum;
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