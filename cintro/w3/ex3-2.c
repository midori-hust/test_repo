#include <stdio.h>

#define PI 3.1415

int main() {
	float radius;

	printf("Please enter the radius of the circle: \n");
	while(scanf("%f", &radius) != 1) {
		printf("Invalid input! Please enter again!\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	printf("R = %f\n", radius);
	printf("P = %f\n", 2 * radius * PI);
	printf("S = %f\n", radius * radius * PI);

	return 0;
}