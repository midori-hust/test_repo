#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"

#define MAXSIZE 100
#define SIZE 100
#define TEMPSIZE 50

/*
* Danh so thu tu cac chuc nang
*/
enum {
	BY_NAME = 0,
	BY_TOTAL = 1,
	PASS = 2,
};

typedef struct _Student {
	char id[SIZE];
	char name[SIZE];
	int math;
	int literature;
	int total;
} Student;

/*
* Cau truc xau tu dinh nghia
*/
typedef struct _String {
	char content[SIZE];
} String;

/*
* Ham main gia
*/
int solve();

/*
* Cac ham chinh
*/
void getData(Student *studentList, int amount);
int searchMenu();
int sortMenu();
void printList(Student *studentList, int amount);
void printFrame(Student student);
void search(Student *studentList, int amount, int option);
void sorting(Student *studentList, int amount, int option);

/*
* Cac ham lien quan toi chuc nang tim kiem
*/
void searchFunct(Student *studentList, int amount);
int searchByName(Student *studentList, int amount, char *name);
int searchByGrade(Student *studentList, int amount, int grade);
int searchPass(Student *studentList, int amount);

/*
* Cac ham lien quan toi chuc nang sap xep
*/
void sortFunct(Student *studentList, int amount);
void sortByName(Student *studentList, int amount);
void sortByTotal(Student *studentList, int amount);
int nameCompare(const void* a, const void* b);
int intCompare(const void* a, const void* b);
int split(char *str, char splitChar, String *listString);

#endif