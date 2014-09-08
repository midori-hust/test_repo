#ifndef __MIDTERM_H__
#define __MIDTERM_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100

struct student_info
{
  int id;
  char name[MAXLENGTH];
  float mark;
};

typedef struct student_info StudentInfo;

typedef struct _StudentList
{
  struct _StudentList *next;
  StudentInfo info;
} StudentList;

StudentList* root;
StudentList* cur;
StudentList* prev;


char menu();
StudentList *newStudent(int id, char *name, float mark);
void insertTop(StudentList* new_item);
void displayList();
void freeList();
void searchStudent(int id);
void deleteStudent(int id);


#endif
