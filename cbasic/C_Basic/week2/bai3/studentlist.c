/*
Viết chương trình đọc file student.dat gồm STT, họ tên sinh viên, MSSV. 
Nhập điểm cho từng sinh viên rồi in kết quả ra file bangdiem.txt và ra màn hình.
*/

#include<stdio.h>

//===========================

typedef struct student
{
  int order;
  int id;
  char name[100];
  int mark;
}student;

//===========================

int countLine(FILE *fin)
{
  int n = 0;
  char s[80];

  while(fgets(s,80,fin) != NULL)
    n++;
  rewind(fin);
  return n;
}

//===============Ham chinh=============//

main()
{
  FILE *fptr,*fout;
  char filename1[80] = "student.dat";
  char filename2[80] = "bangdiem.txt";
  int i,n = 0;
  student a[100];

  if((fptr = fopen(filename1,"r"))==NULL)
    printf("Khong the mo file %s!\n\n",filename1);
  else
    {
      n = countLine(fptr);

      for(i = 0; i < n; i++)
	fscanf(fptr,"%d%d%s",&a[i].order,&a[i].id,a[i].name);

      if((fout = fopen(filename2,"w")) == NULL)
	printf("Khong the mo file %s!\n\n",filename2);
      else
	{
	  printf("\n\tChuong trinh quan li diem sinh vien\n");

	  for(i = 0; i < n; i++)
	    { 
	      printf("\nNhap diem cho sinh vien %d:",a[i].order);
	      printf("\nHo ten: %s",a[i].name);
	      printf("\nMSSV: %d",a[i].id);
	      printf("\nDiem: ");scanf("%d",&a[i].mark);
	    }

	  printf("\n\tBang diem cua sinh vien:\n");

	  for(i = 0; i < n; i++)
	    { 
	      printf("%-3d%-10d%-15s%-5d\n",a[i].order,a[i].id,a[i].name,a[i].mark);
	      fprintf(fout,"%-3d%-10d%-15s%-5d\n",a[i].order,a[i].id,a[i].name,a[i].mark);
	    }
	}
      fclose(fptr);
      fclose(fout);
    }
  return 0;
}
