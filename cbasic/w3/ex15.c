/* Cau 15: */
/* Thong tin ve mot thi sinh bao gom: */
/* So bao danh (max 10 ky tu) */
/* Ho va ten (Max 30 ky tu) */
/* Diem thi (so thap phan) */
/* Hay viet chuong trinh nhap tu ban phim thong tin  */
/* cac thi sinh cho den khi nhap vao so bao danh la -1. */
/* Thong tin moi thi sinh duoc ghi ra file van ban  */
/* "thisinh.txt" (khong su dung mang de luu o buoc nay) */
/* Sau do, mo lai file de doc thong tin vao mang ts.  */
/* Hien thi mang ts ra man hinh, Tiep do duyet mang ts de  */
/* luu thong tin nhung thi sinh co diem thi >= 5 vao  */
/* file van ban "thisinh2.txt" */

#include<stdio.h>
#include<stdlib.h>

#define MAXLENGTH 100

typedef struct studentInfo
{
  int id;
  char name[31];
  float grade;
} studentInfo;


int main()
{
  studentInfo student[MAXLENGTH];
  FILE *f1, *f2;
  char filename1[] = "thisinh.txt";
  char filename2[] = "thisinh2.txt";

  if((f1 = fopen(filename1, "w+")) == NULL)
    {
      printf("Cannot open file %s", filename1);
      return 1;
    }
  if((f2 = fopen(filename2, "w+")) == NULL)
    {
      printf("Cannot open file %s", filename2);
      return 1;
    }

  int id;
  char name[31];
  float grade;
  int i = 0;
  printf("Hay nhap vao thong tin cac thi sinh (Muon ket thuc, hay nhap SBD la -1):\n");
  while(1)
    {
      printf("Thi sinh thu %i:\nSBD (Nhap so duong toi da 10 chu so): ", ++i); scanf("%d", &id);
      if(id == -1) break;
      if((id>9999999999) || (id<0))
	{
	  printf("Ban da nhap sai quy cach SBD, vui long tat may va di ngu neu ban khong hieu dong nay!");
	  continue;
	}
      char ch = getchar();
      printf("Ho va ten: "); gets(name);
      printf("Diem thi: "); scanf("%f", &grade);
      fprintf(f1, "%d\n%s\n%f\n", id, name, grade);
    }
 
  int j=0;
  fclose(f1);
  if((f1 = fopen(filename1, "r")) == NULL)
    {
      printf("Cannot open file %s", filename1);
      return 1;
      }

  while(!feof(f1))
    {
      fscanf(f1, "%d\n", &student[j].id);
      fgets(student[j].name,31,f1);
      fscanf(f1, "%f\n", &student[j].grade);
      j++;
    }
  //j now is size of array student
  printf("Danh sach cac thi sinh: \n");
  printf("SBD\tTen\n\tDiem\n");
  int k;
  fputs("Danh sach cac sinh vien diem lon hon 5:\n", f2);
  for(k=0; k<j; k++)
    {
      printf("%d\t%s\t%f\n", student[k].id, student[k].name, student[k].grade);
      if(student[k].grade>=5)
	{
	  fprintf(f2, "%d\t%s\t%f\n", student[k].id, student[k].name, student[k].grade);
	}
    }

  fclose(f1);
  fclose(f2);
  return 0;
}

