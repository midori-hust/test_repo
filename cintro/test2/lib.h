#ifndef __LIB_H__
#define __LIB_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100

typedef struct _String {
	char content[MAXLENGTH];
} String;

typedef struct _Result {
	String id;
	String name;
	String className;
	float score[5];
	float average;
} Result;

int solve();
void getStudentInformation(Result *person, int *currentIndex);
void searching(Result *person, int amount);
int searchByName(Result *person, int amount);
int searchByClass(Result *person, int amount);
int searchByAverage(Result *person, int amount);
void findScholashipStudent(Result *person, int amount);
int hasFailSubject(Result *person, int studentIndex);
void fixGrade(Result *person, int amount);
int fix(Result *person, int amount, String id, int subjectIndex, float newGrade);
void deleteStudent(Result *person, int *amount);

void calculateAverage(Result *person, int studentIndex);
void printStudentList(Result *person, int amount);

float myAbs(float number);
int getInt();
float getFloat();
int menu();
int subMenu();

#endif