#include <stdio.h>

int main() {
	int answer;

	printf("Your input is %d\n", getInput("Please enter your input "));

	return 0;
}

int getInput(char *msg) {
	int a;

	printf("%s", msg);
	scanf("%d", &a);

	return a;
}