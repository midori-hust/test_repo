#include <stdio.h>

int main() {
	float det, detX, detY;
	float a1, b1, c1, a2, b2, c2;

	printf("\tax + by = c\n");
	printf("\ta'x + b'y = c'\n");
	printf("a = ");
	scanf("%f", &a1);
	while(getchar() != '\n');
	printf("b = ");
	scanf("%f", &b1);
	while(getchar() != '\n');
	printf("c = ");
	scanf("%f", &c1);
	while(getchar() != '\n');
	printf("a' = ");
	scanf("%f", &a2);
	while(getchar() != '\n');
	printf("b' = ");
	scanf("%f", &b2);
	while(getchar() != '\n');
	printf("c' = ");
	scanf("%f", &c2);
	while(getchar() != '\n');

	det = a1 * b2 - a2 * b1;
	if(det == 0) {
		if(a1 == a2) {
			printf("He phuong trinh co vo so nghiem thoa man %fx + %fy = %f\n", a1, b1, c1);
		} else {
			printf("He phuong trinh vo nghiem\n");
		}
		return 0;
	}

	detX = c1 * b2 - c2 * b1;
	detY = a1 * c2 - a2 * c1;

	printf("\nNghiem cua he phuong trinh: \n");
	printf("\tx = %f\n", detX / det);
	printf("\ty = %f\n", detY / det);

	return 0;
}
