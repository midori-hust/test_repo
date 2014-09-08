#include "extension_lib.h"

int solve() {
	Fractions listFraction[SIZE];
	int n, i;

	printf("Please enter the number of elements:\n");
	n = getInt();

	getInput(listFraction, n);

	printf("The list of fractions:\n");
	printArray(listFraction, n);

	for(i = 0; i < n; i++) {
		reverseFraction(&listFraction[i]);
	}

	printf("\nThe list of fraction after reversing\n");
	printArray(listFraction, n);

	return 0;
}

void getInput(Fractions *listFraction, int amount) {
	if(amount <= 0) {
		return;
	}

	int i;
	printf("Please enter the list:\n");

	for(i = 0; i < amount; i++) {
		printf("Fraction %d:\n", i + 1);
		printf("Please enter the numerator:\n");
		listFraction[i].numerator = getInt();
		printf("Please enter the denominator:\n");
		do {
			listFraction[i].denominator = getInt();
			if(listFraction[i].denominator == 0) {
				printf("Please enter the denominator again, because the denominator must not be equal to 0\n");
			}
		} while(listFraction[i].denominator == 0);
	}
}

void reverseFraction(Fractions *frac) {
	int temp;

	if(frac->numerator != 0) {
		temp = frac->numerator;
		frac->numerator = frac->denominator;
		frac->denominator = temp;
		return;
	}

	printf("Can not reverse the fraction %d / %d\n", frac->numerator, frac->denominator);
}

int factCompare(Fractions a, Fractions b) {
	return a.numerator * b.denominator - a.denominator * b.numerator;
}

void printArray(Fractions *listFraction, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("Fraction %d: %d / %d\n", i + 1, listFraction[i].numerator, listFraction[i].denominator);
	}
}