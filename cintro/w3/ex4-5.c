#include <stdio.h>

int main() {
	int hour;

	printf("Enter the hours per week which the employee works\n");
	while(scanf("%d", &hour) != 1) {
		printf("Invalid input! Please enter again\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	if(hour < 40)
		printf("The salary: %d\n", hour * 25000);
	else {
		printf("The salary: %d\n", hour * 25000 + (hour - 40) * 40000);
	}

	return 0;
}