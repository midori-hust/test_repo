#include <stdio.h>

#define MAXLENGTH 100

float calculateAveragePoint(float *pointList, int amount);
float findMaxGrade(float *pointList, int amount);
int getInt();
int getFloat();

int main() {
	int n, i;
	float pointList[MAXLENGTH];

	printf("Please enter the number of students:\n");
	while((n = getInt()) < 1) {
		printf("Please enter a positive number\n");
	}

	printf("Please enter the student point:\n");
	for(i = 0; i < n; i++) {
		printf("Student %d: ", i + 1);
		do {
			pointList[i] = getFloat();
			if(pointList[i] < 0 || pointList[i] > 10)
				printf("Invalid grade! Please try again!\n");
		} while(pointList[i] < 0 || pointList[i] > 10);
	}


	printf("The average point: %f\n", calculateAveragePoint(pointList, n));
	printf("The max point: %f\n", findMaxGrade(pointList, n));

	return 0;
}

float calculateAveragePoint(float *pointList, int amount) {
	float result = 0;
	int i;

	for(i = 0; i < amount; i++) {
		result += pointList[i];
	}

	return result / amount;
}

float findMaxGrade(float *pointList, int amount) {
	float result = 0;
	int i;

	for(i = 0; i < amount; i++) {
		if(pointList[i] > result) {
			result = pointList[i];
		}
	}

	return result;
}

int getInt() {
	int result;

	while(scanf("%d", &result) != 1) {
		printf("Invalid input! Please try again!\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	return result;
}

int getFloat() {
	float result;

	while(scanf("%f", &result) != 1) {
		printf("Invalid input! Please try again!\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	return result;
}