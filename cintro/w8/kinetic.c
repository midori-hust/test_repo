#include <stdio.h>

float kineticCalculate(float m, float v);

int main() {
	float m, v;

	printf("Enter m:\n");
	scanf("%f", &m);
	while(getchar() != '\n');
	printf("Enter v:\n");
	scanf("%f", &v);

	printf("The kinetic energy: ke = m * v^2 / 2 = %f\n", kineticCalculate(m, v));

	return 0;
}

float kineticCalculate(float m, float v) {
	return (m * v * v) / 2.0;
}