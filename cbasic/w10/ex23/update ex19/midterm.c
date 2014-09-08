#include "midterm.h"


char menu()
{
  char ch;
  printf("\t\tMENU\n\n");
  printf("1. Nhan thong tin.\n");
  printf("2. Tim kiem.\n");
  printf("3. Xoa sinh vien.\n");
  printf("4. Hien thi danh sach sinh vien.\n");
  printf("5. Ket thuc.\n");
  printf("\tBan chon?\n");
  ch = getchar();
  char ch1;
  while((ch1 = getchar()) != '\n');
  printf("Processing...\n");
  return ch;
}

StudentList *newStudent(int id, char *name, float mark)
{
  StudentList *new;
  new = (StudentList*)malloc(sizeof(StudentList));
  strcpy((new->info).name, name);
  new->info.id = id;
  new->info.mark = mark;
  new->next = NULL;
  return new;
}

void insertTop(StudentList* new_item)
{
  if(root == NULL) root = new_item;
  else
    {
      new_item->next = root;
      root = new_item;
    }
}

void displayList()
{
  StudentList *current;
  printf("\nDanh sach sinh vien hien tai:\n");
  for(current = root; current != NULL; current = current->next)
    {
      printf("Ten sinh vien: %s\nMSSV: %d\nDiem: %f\n\n", (current->info).name, (current->info).id, (current->info).mark);
    }
}

void deleteStudent(int id)
{
  StudentList *current;
  StudentList *temp;
  int flag = 0;
  
  if(root == NULL)
    {
      printf("Danh sach trong.\n");
      return;
    }

  for(current = root; current != NULL; current = current->next)
    {
      if(current == root)
	{
	  if((root->info).id != id)
	    continue;
	  else
	    {
	      temp = root;
	      root = root->next;
	      free(temp);      
	      return;
	    }
	}

      if((current->next->info).id == id)
	{
	  temp = current->next;
	  current->next = temp->next;
	  free(temp);
	  printf("Xoa thanh cong.\n");
	  flag = 1;
	}
    }

  if(flag == 0)
    {
      printf("Khong tim thay sinh vien can xoa. Viec xoa that bai.\n");
    }
}

void freeList()
{
  StudentList *temp;

  while(root != NULL)
    {
      temp = root;
      root = root->next;
      free(temp);
    }
}

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
}

void saveFile(FILE *f)
{
  StudentList *current;
  for(current = root; current != NULL; current = current->next)
    {
      fwrite(&(current->info), 1, sizeof(StudentInfo), f);
    }
  return;
}
