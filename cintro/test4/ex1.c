#include <stdio.h>
#include <math.h>

int main() {
	int n, i;
	int sum = 0;

	printf("Please enter an integer which is greater than 2: \n");
	while((n = getInt()) <= 2) {
		printf("Please enter a greater-than-2 number\n");
	}

	for(i = 1; i < n; i++) {
		if(isPrimeNumber(i)) {
			sum += i;
		}
	}

	printf("The sum of the prime numbers list which are in range 0 to %d: %d\n", n, sum);
	return 0;
}

int isPrimeNumber(int n) {
	int i;

	if(n <= 0)
		return 0;

	for(i = 2; i <= (int)sqrt(n); i++) {
		if(n % i == 0) {
			return 0;
		}
	}
	return 1;
}


int getInt() {
	int result;

	while(scanf("%d", &result) != 1) {
		printf("Invalid input! Please enter again!\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	return result;
}