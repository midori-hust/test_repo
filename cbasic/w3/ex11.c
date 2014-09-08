/* Tao mot file van ban lab1.txt voi noi dung tuy y. Sau do,  */
/* viet chuong trinh doc lan luot tung ky tu trong file tren  */
/* va ghi vao file moi co ten lab2.txt */

#include <stdio.h>

#define MAXLENGTH 100

int main()
{
  char c;
  FILE *f1, *f2;
  char filename1[] = "lab1.txt";
  char filename2[] = "lab2.txt";

  if((f1 = fopen(filename1, "r+")) == NULL)
    {
      printf("Cannot open file %s!\n", filename1);
      return 1;
    }
  if((f2 = fopen(filename2, "w+")) == NULL)
    {
      printf("Cannot open file %s!\n", filename1);
      return 1;
    }
  
  /*   do 
     { 
       c = getc(f1); 
       putc(c, f2); 
     } 
     while(c != EOF); */ //Code loi, co 2 ky hieu EOF trong file f2
   while((c = getc(f1)) != EOF) putc(c, f2); //Khong bi loi 2 EOF

  fclose(f1);
  fclose(f2);
  return 0;
}
