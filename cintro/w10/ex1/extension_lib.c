#include "extension_lib.h"

int solve() {
	Weather monthWeather[12];

	getData(monthWeather, 12);
	displayData(monthWeather, 12);

	printf("\nAfter sort:\n");
	// sortArray(monthWeather, 12, weatherComapre);
	qsort(monthWeather, 12, sizeof(Weather), weatherComapre1);
	displayData(monthWeather, 12);

	return 0;
}

void getData(Weather *list, int amount) {
	int i;

	printf("Please enter weather data\n");

	for(i = 0; i < amount; i++) {
		printf("Month %d\n", i + 1);
		list[i].month = i;
		printf("Total rain fall:\n");
		list[i].rainFall = getFloat();

		printf("High temp:\n");
		list[i].highTemp = getFloat();
		printf("Low temp:\n");
		list[i].lowTemp = getFloat();

		list[i].averageTemp = avg(list[i].highTemp, list[i].lowTemp);
	}
}

void displayData(Weather *list, int amount) {
	int i;

	printf("%-10s%10s%10s%10s%10s\n", "Month", "Rain fall", "Highest", "Lowest", "Average");
	for(i = 0; i < amount; i++) {
		myPrintFrame(monthToString(list[i].month), list[i].rainFall, list[i].highTemp, list[i].lowTemp, list[i].averageTemp);
	}
}

float avg(float a, float b) {
	return (a + b) / 2;
}

void myPrintFrame(char *month, float rainFall, float highTemp, float lowTemp, float averageTemp) {
	printf("%-10s%10.2f%10.2f%10.2f%10.2f\n", month, rainFall, highTemp, lowTemp, averageTemp);
}

char* monthToString(int month) {
	char *res;

	if((res = (char*) malloc((SIZE + 1) * sizeof(char))) == NULL) {
		return NULL;
	}

	switch(month) {
		case JAN:
		strcpy(res, "January");
		break;
		case FEB:
		strcpy(res, "Febuary");
		break;
		case MAR:
		strcpy(res, "March");
		break;
		case APR:
		strcpy(res, "April");
		break;
		case MAY:
		strcpy(res, "May");
		break;
		case JUN:
		strcpy(res, "June");
		break;
		case JUL:
		strcpy(res, "July");
		break;
		case AUG:
		strcpy(res, "August");
		break;
		case SEP:
		strcpy(res, "September");
		break;
		case OCT:
		strcpy(res, "October");
		break;
		case NOV:
		strcpy(res, "November");
		break;
		case DEC:
		strcpy(res, "December");
		break;
		default:
		return NULL;
	}

	return res;
}

void sortArray(Weather *list, int amount, int (*compare)(Weather, Weather)) {
	int i, j;
	int iMin;

	for(j = 0; j < amount - 1; j++) {
		iMin = j;
		for(i = j + 1; i < amount; i++) {
			if(compare(list[i], list[iMin]) < 0)
				iMin = i;
		}

		if(iMin != j)
			swap(&list[j], &list[iMin]);
	}
}

void swap(Weather *a, Weather *b) {
	Weather temp;

	memcpy(&temp, a, sizeof(Weather));
	memcpy(a, b, sizeof(Weather));
	memcpy(b, &temp, sizeof(Weather));
}

int weatherComapre(Weather a, Weather b) {
	if(a.averageTemp > b.averageTemp) {
		return 1;
	}
	
	if(a.averageTemp < b.averageTemp) {
		return -1;
	}

	return 0;
}

int weatherComapre1(const void* a, const void* b) {
	Weather *x = (Weather*)a;
	Weather *y = (Weather*)b;

	if(x->averageTemp > y->averageTemp) {
		return 1;
	}
	
	if(x->averageTemp < y->averageTemp) {
		return -1;
	}

	return 0;
}