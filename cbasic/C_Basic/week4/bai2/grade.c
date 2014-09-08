/*
Viết chương trình sử dụng mảng động, đọc file bangdiem.txt rồi ghi ra file grade.dat(nhị phân – mảng cấu trúc sinh viên). Sau đó đọc lại file grade.dat và in bảng điểm ra màn hình.
*/

#include<stdio.h>
#include<stdlib.h>

//======================

typedef struct
{       
  int order;
  int id;
  char name[20];
  int mark;
}student;

//======================

int n_line(FILE *fin)
{
  char buff[80];
  int dem = 0;

  while(fgets(buff,80,fin) != NULL)
    dem++;
  rewind(fin);

  return dem;
}

//==================Ham chinh==================//

main()
{
  FILE *f1,*f2;
  student *a,*b;
  int i,n1,n2,n3;

  f1 = fopen("bangdiem.txt","r");
  n1 = n_line(f1);
  a = (student*)malloc(n1 * sizeof(student));  

  printf("\n\tChuong trinh bang diem sinh vien su dung mang dong\n");
  printf("\nDoc du lieu tu file bangdiem.txt.....");
  for(i = 0; i < n1 ; i++)
    fscanf(f1,"%d%d%s%d",&a[i].order,&a[i].id,a[i].name,&a[i].mark);
  fclose(f1);

  // Ghi dữ liệu mảng vào file grade.dat
  if((f2 = fopen("grade.dat","wb")) == NULL)
    printf("Cannot open file %s.\n","grade.dat");
  else 
    {
      n2 = fwrite(a,sizeof(student),n1,f2);
      fclose(f2);
    }
  printf("\n   Doc du lieu va ghi vao file grade.dat thanh cong!\n");

  // Doc dữ liệu mảng tu file grade.dat ra 1 mang moi
  b = (student*)malloc(n2 * sizeof(student));
  if((f2 = fopen("grade.dat","rb")) == NULL)
    printf("Cannot open file %s\n","grade.dat");
  else  
    {
      n3 = fread(b,sizeof(student),n2,f2);
      fclose(f2);
    }
  
  //In bang diem ra man hinh:
  printf("\nNhan Enter de hien thi ket qua....");
  getchar();
  printf("\nBang diem sinh vien:\n\n");
  for(i = 0; i < n3; i++)
    printf("%-3d%-10d%-20s%-3d\n",b[i].order,b[i].id,b[i].name,b[i].mark);

  free(a);
  free(b);
  return 0;
}


