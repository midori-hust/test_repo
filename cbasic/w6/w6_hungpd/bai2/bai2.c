/* Bai 2: */
/* Viet chuong trinh tim kiem gan dung: */
/* -Tao 1 file van ban torng do moi dong la 1 xau co do dai <= 30 ky tu */
/* -Viet chuong trinh thuc hien cong viec sau: */
/* +Nhap tu ban phim 1 tu can tim */
/* +Hien thi ra man hinh cac xau trong file chua tu nay */
/*   Vi du: tu nhap vao la computer. */
/*   Cac tu thoa man nhu computer, computers, supercomputer... */


#include<stdio.h>
#include<string.h>

#define MAXLENGTH 100

int main()
{
  char str[MAXLENGTH];
  char read[MAXLENGTH];
  char *ptr;
  FILE *f;
  char filename[] = "test.txt";
  int flag = 0;

  if((f = fopen(filename, "r")) == NULL)
    {
      printf("Khong mo duoc file %s!\n", filename);
      return 1;
    }
 
  printf("Hay nhap vao tu ban can tim: "); gets(str);
  printf("Danh sach cac tu gan dung voi tu ban can tim:\n");
  while(1)
    {
      fgets(read, MAXLENGTH, f);
      if(feof(f)) break;
      if((ptr = strstr(read, str)) != NULL) 
	{
	  printf("%s", read);
	  flag = 1;
	}
    }

  if(flag == 0) printf("Khong co tu nao gan dung voi tu ban can tim!\n");
  printf("--------------------------------------------\n");
  printf("The end.\nBye bye!\n");

  fclose(f);
  return 0;
}
