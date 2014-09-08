#include "midterm.h"


char menu()
{
  char ch;
  printf("\t\tMENU\n\n");
  printf("1. Nhap thong tin.\n");
  printf("2. Doc du lieu tu file.\n");
  printf("3. Sap xep mang.\n");
  printf("4. Tim kiem sinh vien.\n");
  printf("5. Ket thuc.\n");
  printf("\tBan chon?\n");
  ch = getchar();
  char ch1;
  while((ch1 = getchar()) != '\n');
  printf("Processing...\n");
  return ch;
}

/*
void searchStudent(int id)
{
  StudentList *current;
  int flag = 0;

  printf("Ket qua tim kiem:\n");
  for(current = root; current != NULL; current = current->next)
    {
      if((current->info).id == id)
	{
	  printf("Sinh vien %s\nMSSV: %d\nDiem: %f\n", (current->info).name, (current->info).id, (current->info).mark);
	  flag = 1;
	}
    }
  if(flag == 0)
    {
      printf("Khong tim thay sinh vien can tim!\n");
    }
    }*/

void sortStudentList(StudentInfo *studentList, int n)
{
  int min;
  int i, j;
  for(i=0; i<n-1; i++)
    {
      min = i;
      for(j=i+1; j<n; j++)
	if(studentList[j].id < studentList[min].id) min = j;
      swap(&(studentList[min]), &(studentList[i]));
    }
}

void swap(StudentInfo *student1, StudentInfo *student2)
{
  StudentInfo temp = *student1;
  *student1 = *student2;
  *student2 = temp;
}

int BinarySearch(StudentInfo *studentList, int id, int n)
{
  int Low, Mid, High;
  Low = 0;
  High = n-1;
  while(Low <= High)
    {
      Mid = (Low + High)/2;
      if(studentList[Mid].id < id)
	Low = Mid + 1;
      else if(studentList[Mid].id > id)
	High = Mid - 1;
      else
	return Mid;
    }
  return -1;
}

