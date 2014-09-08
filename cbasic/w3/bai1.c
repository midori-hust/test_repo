/* Viet chuong trinh cho phep: */
/* -Nhap tu ban phim xau ki tu str */
/* -Nhap tu ban phim 2 so nguyen a, b */
/* -Nhap tu ban phim ky tu ch */
/* -Ghi ra file demo.txt theo dinh dang */
/*   +Dong 1: ghi ra a <dau cach> ky tu ch <dau cach> b */
/*   +Dong 2: ghi ra xau str */
/* -Khi ket thuc chuong trinh, mo file demo.txt de xem ket qua */



#include <stdio.h>

#define MAXLENGTH 100

int main()
{
  char str[MAXLENGTH];
  int a, b;
  char ch;
  FILE *f1;
  char filename[] = "demo.txt";

  if((f1 = fopen(filename, "w")) == NULL)
    {
      printf("Khong mo duoc file %s!\n", filename);
      return 1;
    }
  
  
  printf("Hay nhap xau ky tu str: "); gets(str);
  printf("Hay nhap vao 2 so nguyen:\nSo nguyen a: "); scanf("%d", &a);
  printf("So nguyen b: "); scanf("%d", &b);
  char ch1 = getchar(); //Clear cache
  printf("Hay nhap 1 ky tu ch: "); ch = getchar(); 
  fprintf(f1, "%d %c %d\n", a, ch, b);
  fputs(str, f1);
  
  fclose(f1);
  return 0;
  
}
