#include <stdio.h>

int main() {
	int x, y;

	printf("Enter the input 1: \n");
	scanf("%d", &x);
	while(getchar() != '\n');
	printf("Enter the input 2: \n");
	scanf("%d", &y);
	while(getchar() != '\n');

	printf("x = %d\n", x);
	printf("y = %d\n", y);

	return 0;
}