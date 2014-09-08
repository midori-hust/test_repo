#include "myLib.h"

float* mySort(float *a, int n, int extension) {
	switch (extension) {
		case ASC:
		return ascSort(a, n);
		break;
		case DESC:
		return descSort(a, n);
		break;
		case ASB_DESC:
		return abs_descSort(a, n);
		break;
		default:
		break;
	}
}

float* ascSort(float *a, int n) {
	int i, j;

	for( i=0; i < n; i++) {
		for(j=0; j < n-1; j++) {
			if(a[j] > a[j+1]) {
				swap(&a[j], &a[j+1]);
			}
		}
	}

	return a;
}

float* descSort(float *a, int n) {
	int i, j;

	for( i=0; i < n; i++) {
		for(j=0; j < n-1; j++) {
			if(a[j] < a[j+1]) {
				swap(&a[j], &a[j+1]);
			}
		}
	}

	return a;
}

float* abs_descSort(float *a, int n) {
	int i, j;

	for( i=0; i < n; i++) {
		for(j=0; j < n-1; j++) {
			if(abs(a[j]) > abs(a[j+1])) {
				swap(&a[j], &a[j+1]);
			}
		}
	}

	return a;
}

void printArray(float *a, int n) {
	int i;
	for(i = 0; i<n; i++) {
		printf("a[%d] = %f\n", i, a[i]);
	}	
}

void swap(float *a, float *b) {
	float temp = *a;
	*a = *b;
	*b = temp;
}

float* cloneArray(float *a, int n) {
	float *result;
	int i;

	result = (float*) malloc((n+1) *sizeof(float));
	if(result == NULL) {
      printf("Memory allocation failed!\n");
      return NULL;
    }

	for (i = 0; i < n; i++) {
		result[i] = a[i];
	}

	return result;
}

int getInt() {
	int result;

	while(scanf("%d",&result) != 1) {
		printf("This is not an integer number. Please retype the input: ");
		while(getchar() != '\n');
	}

	return result;
}

float getFloat() {
	float result;

	while(scanf("%f",&result) != 1) {
		printf("This is not a float number. Please retype the input: ");
		while(getchar() != '\n');
	}

	return result;
}

void searchPosition(float *a, int n, float key) {
	int i, isFound = 0;

	for (i = 0; i < n; i++) {
		if (a[i] == key) {
			printf("Found: a[%d] = %f\n", i, key);
			isFound = 1;
		}
	}

	if (!isFound) {
		printf("Not found %f in this array\n", key);
	}
}

int menu() {
    int option;

    printf("\n\t\tMENU\n");
    printf("\t1. Make tree \n");
    printf("\t2. Result\n");
    printf("\t3. Search\n");
    printf("\t4. Disqualify\n");
    printf("\t5. Make file\n");
    printf("\t6. Exit program\n");
    printf("\nWhich option would you like to choose?\n");

    do {
    	option = getInt();
    	if (option < 0 || option > 6) {
    		printf("Invalid option! Please choose again!\n");
    	}
    } while (option < 0 || option > 6);

    return option;
}