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

char menu();
void sortStudentList(StudentInfo *studentList, int n);
void swap(StudentInfo *student1, StudentInfo *student2);
int BinarySearch(StudentInfo *studentList, int id, int n);

#endif
