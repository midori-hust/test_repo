#include <stdio.h>

#define PI 3.142

int main() {
	double r;
	r = 5.678;
	printf("Radius = %f\n", r);
	printf("Circle's circumference = %f\n", 2.0 * PI * r);
	printf("Circle's area = %f\n", PI * r * r);
	printf("Sphere's area = %f\n", 4.0 * PI * r * r);
	printf("phere's volume = %f\n", 4.0 / 3.0 * PI * r * r * r);

	return 0;
}