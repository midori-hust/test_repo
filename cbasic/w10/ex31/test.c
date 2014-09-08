
#include "midterm.h"

int main()
{
  StudentInfo buffer;
  StudentInfo studentList[MAXLENGTH];
  int id;
  char name[MAXLENGTH];
  float mark;
  char ch2;
  int i = 0;
  int flag = 0;
  int j;
  int result;

  FILE *f;
  char filename[MAXLENGTH] = "student.dat";

  if ((f = fopen(filename, "w+b")) == NULL)
    {
      printf("Khong mo duoc file %s.\n", filename);
      return 1;
    }

  char ch;
  while(1)
    {
      ch = menu();
      switch(ch)
	{
	case '1':
	  printf("Ban chon %c.\n", ch);
	  while(1)
	    {
	      printf("Nhap vao ban phim thong tin cua 1 sinh vien (nhap '###' de ket thuc viec nhap):\n");
	      printf("Ten sinh vien: ");	    
	      gets(name);
	      name[strlen(name)] = '\0';
	      if(strcmp(name, "###") == 0) break;
	      if(strlen(name) > 30)
		{
		  printf("Nhap vao khong thanh cong. Ban da nhap ten sinh vien qua 30 ky tu.\n");
		  continue;
		}
	      printf("Ma so sinh vien: ");
	      if(scanf("%d", &id) == 0)
		{
		  while((ch2 = getchar()) != '\n');
		  printf("Nhap vao khong thanh cong. Ban da nhap MSSV sai (phai nhap so nguyen).\n");
		  continue;
		}
	      printf("Diem thi cua sinh vien: ");
	      while(1)
		{
		  if(scanf("%f", &mark) == 0)
		    {
		      while((ch2 = getchar()) != '\n');
		      printf("Nhap vao khong thanh cong. Ban da nhap diem sai (phai nhap so thuc trong khoang tu 0 toi 10).\n");	    
		      continue;
		    }
		  if((mark<0) || (mark>10))
		    {
		      printf("Nhap vao khong thanh cong. Ban da nhap diem sai (phai nhap so thuc trong khoang tu 0 toi 10).\n");	    
		      continue;
		    }
		  while((ch2 = getchar()) != '\n');
		  break;
		}
	      buffer.id = id;
	      strcpy(buffer.name,name);
	      buffer.mark = mark;
	      fwrite(&buffer, 1, sizeof(StudentInfo), f);
	    }
	  rewind(f);
	  continue;

	case '2':
	  printf("Ban chon %c.\n", ch);
 	  printf("Danh sach cac phan tu trong file: \n");
	  while(1)
	    {
	      fread(&buffer, 1, sizeof(StudentInfo), f);
	      if(feof(f)) break;
	      studentList[i] = buffer;
	      i++;
	      flag = 1;
	    }
	
	  if(flag == 0) 
	    {
	      printf("File trong!\n");
	    }
	  else
	    {
	      for(j=0; j<i; j++)
		{
		  printf("%s\n%d\t%f\n\n", studentList[j].name, studentList[j].id, studentList[j].mark);
		}
	      flag = 0;
	    }
	  rewind(f);
	  continue;

	case '3':
	  printf("Ban chon %c.\n", ch);
	  sortStudentList(studentList, i);

	  for(j=0; j<i; j++)
	    {
	      printf("%s\n%d\t%f\n\n", studentList[j].name, studentList[j].id, studentList[j].mark);
	    }
	  continue;

	case '4':
	  printf("Ban chon %c.\n", ch);
	  printf("Hay nhap vao MSSV ma ban can tim: ");
	  if(scanf("%d", &id) != 0)
	    {
	      while((ch2 = getchar()) != '\n');
	      result = BinarySearch(studentList, id, i);
	      if(result == -1) printf("Khong tim thay!\n");
	      else
		{
		  printf("Sinh vien ma ban can tim:\nTen: %s\nMSSV: %d\nDiem: %f\n", studentList[result].name, studentList[result].id, studentList[result].mark);
		}
	    }
	  else
	    {
	      while((ch2 = getchar()) != '\n');
	      printf("Ban da nhap sai ID.\n");
	    }
	  continue;

	case '5':
	  printf("Ban chon %c.\n", ch);
	  printf("Chuong trinh ket thuc!\n");
	  break;

	default:
	  printf("Ban da chon sai lua chon, xin vui long chon lai!\n");
	  continue;
	}
      break;
    }

  fclose(f);
  return 0;
}
