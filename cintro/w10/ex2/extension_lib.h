#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"

#define MAXSIZE 100
#define SIZE 100
#define TEMPSIZE 50

enum {
	JAN = 0,
	FEB = 1,
	MAR = 2,
	APR = 3,
	MAY = 4,
	JUN = 5,
	JUL = 6,
	AUG = 7,
	SEP = 8,
	OCT = 9,
	NOV = 10,
	DEC = 11,
};

typedef struct _Weather {
	float rainFall;
	float highTemp;
	float lowTemp;
	float averageTemp;
} Weather;


int solve();
void getData(Weather *list, int amount);
void displayData(Weather *list, int amount);
void sortArray(Weather *list, int amount);

void myPrintFrame(char *month, float rainFall, float highTemp, float lowTemp, float averageTemp);
float avg(float a, float b);
char* monthToString(int month);

#endif