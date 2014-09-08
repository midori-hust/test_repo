/* Cau 12: */
/* Viet chuong trinh nhap tu ban phim N so thuc luu vao 1 mang */
/* (N<100 va N duoc nhap tu ban phim). Sau do ghi ra 1 file van  */
/* ban co dia chi la "float.txt" theo quy cach: dong dau tien  */
/* luu so luong cac so thuc, cac dong tiep theo luu cac so thuc,  */
/* moi so luu tren 1 dong. Doc lai tep van ban do va luu cac so  */
/* thuc lon hon 5 vao tep "float2.txt" theo quy cach giong nhu  */
/* tep "float.txt". Luu ma nguon chuong trinh voi ten file_1.c */

#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 100

int main()
{
  int n;
  float *a;
  FILE *f1, *f2;
  char filename1[] = "float.txt";
  char filename2[] = "float2.txt";

  if((f1 = fopen(filename1, "w+t")) == NULL)
    {
      printf("Cannot open file %s!\n", filename1);
      return 1;
    }
  if((f2 = fopen(filename2, "w+t")) == NULL)
    {
      printf("Cannot open file %s!\n", filename2);
      return 1;
    }

  printf("Hay nhap vao so nguyen N (so phan tu cua mang): "); scanf("%d", &n);
  fprintf(f1, "%d\n", n);

  a = (float*) malloc (n * sizeof(float)); //dung thu vien stdlib.h
  if(a == NULL)
    {
      printf("Cap phat bo nho that bai!\n");
      return 1;
    }

  int i;
  printf("Hay nhap vao lan luot cac phan tu cua mang:\n");
  for(i=0; i<n; i++)
    {
      printf("Phan tu thu %d: ", i+1); scanf("%f", &a[i]);
      fprintf(f1, "%f\n", a[i]);
    }

  rewind(f1);
  float b;
  fscanf(f1, "%f\n", &b);//Doc dong dau tien
  while(!feof(f1))
    {
      fscanf(f1, "%f\n", &b);
      if(b>5) fprintf(f2, "%f\n", b);
    }
  free(a);
  fclose(f1);
  fclose(f2);
  return 0;
}
