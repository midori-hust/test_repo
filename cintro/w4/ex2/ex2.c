#include <stdio.h>

int main() {
	double input;

	printf("Convert x km into y miles:\nx = ");
	while(scanf("%lf", &input) != 1) {
		printf("Please enter x again!\n");
		printf("x = ");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	printf("y = %lf miles\n", 0.621371 * input);

	return 0;
}