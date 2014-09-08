/* Cau 23: Doc noi dung cua tep "sinhvien.dat" trong cau 20 va luu */
/* vao 1 stack cai dat bang mang. Sau do doc lan luot cac phan tu */
/* cua stack va luu vao file "sinhvien2.dat". Nhu vay thong tin  */
/* sinh vien trong file sinhvien.dat se duoc in theo thu tu nguoc  */
/* lai trong file sinhvien2.dat */


#include "stack.h"

StudentInfo stack[MAXLENGTH];
int top = 0;

int main()
{
  StudentInfo *buffer;
  int result;
  
  FILE *f1;
  char filename1[MAXLENGTH] = "student.dat";
  
  if ((f1 = fopen(filename1, "rb")) == NULL)
    {
      printf("Khong mo duoc file %s.\n", filename1);
      return 1;
    }

  FILE *f2;
  char filename2[MAXLENGTH] = "student2.dat";
  
  if ((f2 = fopen(filename2, "wb")) == NULL)
    {
      printf("Khong mo duoc file %s.\n", filename2);
      return 1;
    }

  initialize();
  while(1)
    {
      fread(buffer, 1, sizeof(StudentInfo), f1);
      if(feof(f1)) break;
      printf("\nTen sinh vien: %s\nMSSV: %d\nDiem: %f\n", buffer->name, buffer->id, buffer->mark);
      push(buffer);
    }
  printf("\nLuu sinh vien voi thu tu dao nguoc: \n");
  while(1)
    {
      result = pop(buffer);
      if(result == 0) break;
      printf("\nTen sinh vien: %s\nMSSV: %d\nDiem: %f\n", buffer->name, buffer->id, buffer->mark);
      fwrite(buffer, 1, sizeof(StudentInfo), f2);
    }


  fclose(f1);
  fclose(f2);
  return 0;
}
