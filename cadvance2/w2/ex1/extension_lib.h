#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXLENGTH 100

typedef struct _string {
	char content[MAXLENGTH];
} String;

typedef struct _mytime {
	int hour;
	int minute;
	int second;
} MyTime;

typedef struct _phonecall {
	String caller;
	String called;
	MyTime beginTime;
	int during;
} PhoneCall;

void randomPhoneNumber(String *array, int n);
void genPhoneCallData(String *array, int n, PhoneCall *phoneCall, int amount);
void selectionSort(PhoneCall *phoneCall, int n);
void swap(PhoneCall *a, PhoneCall *b);
PhoneCall* reverseList(PhoneCall phoneCall);
void printPhoneCallLog(PhoneCall *phoneCallList, int n);
void insertionSort(PhoneCall *phoneCall, int n);
int choosePivot(int left, int right);
void quickSort(PhoneCall *phoneCall, int left, int right);
int saveRunningTime(FILE *f, double quickSortTime, double insertionSortTime, double selectionSortTime, int amount);
int extendRecord(FILE *f, int amount, int percents, PhoneCall *phoneCallList);

#endif