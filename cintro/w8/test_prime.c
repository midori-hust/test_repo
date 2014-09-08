#include <stdio.h>

int isPrime(int number);

int main() {
	int i;
	int number;

	printf("Please enter 10 integer:\n");
	for(i = 0; i < 10; i++) {
		printf("a[%d]: ", i);
		scanf("%d", &number);
		while(getchar() != '\n');
		if(!isPrime(number)) {
			printf("This is a prime number\n");
		}
		else {
			printf("This is not a prime number\n");
		}
	}

	return 0;
}

int isPrime(int number) {
	int i;

	if(number <= 1) 
		return 0;

	for(i = 2; i <= number / 2; i++) {
		if(number % i == 0) 
			return 1;
	}

	return 0;
}