#include <stdio.h>

double square(double a);

int main() {
	double num = 0.0, sqr = 0.0;

	printf("Please enter the number\n");
	scanf("%lf", &num);

	printf("Square of %g is %g\n", num, square(num));

	return 0;
}

double square(double a) {
	return a * a;
}