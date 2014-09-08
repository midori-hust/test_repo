/* Tao file demo.dat va ghi nhung noi dung sau */
/* -Nhap tu ban phim xau ky tu str */
/* -Nhap tu ban phim 2 so nguyen a, b */
/* -Nhap tu ban phim ky tu ch */
/* -Ghi ra file theo dinh dang */
/*   +Dong 1: ghi a, roi den ch, roi den b */
/*   +Dong 2: ghi xau str */
/*   -Xau khi ket thuc chuong trinh, mo file demo.dat de xem ket qua */
/*   -Sau do doc lai du lieu file vao lai cac bien a, b, ch, str.  */
/* Hien thi cac bien nay ra man hinh. */

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 100

typedef struct blah
{
  int a;
  int b;
  char ch;
  char str[MAXLENGTH];
} blah;


int main()
{
  int a, b;
  char str[MAXLENGTH];
  char ch;
  blah obj;
  blah obj1;


  /*  int a1, b1;
  char ch1; 
  char str1[MAXLENGTH];*/
  
  /*  FILE *f1;
  char filename[] = "demo.dat";

  if((f1 = fopen(filename, "w+")) == NULL)
    {
      printf("Khong mo duoc file %s!\n", filename);
      return 1;
    }

  printf("Hay nhap vao xau ky tu: "); gets(str);
  printf("Hay nhap vao 2 so nguyen:\nSo nguyen a: "); scanf("%d", &a);
  char ch1;
  while ((ch1 = getchar()) != '\n'); //Clear cache
  printf("So nguyen b: "); scanf("%d", &b);
  while ((ch1 = getchar()) != '\n'); //Clear cache
  printf("Hay nhap vao 1 ky tu: "); ch = getchar();
  obj.a = a;
  obj.b = b;
  obj.ch = ch;
  strcpy(obj.str, str);
  fwrite(&obj, 1, sizeof(obj), f1);
  fputs(str, f1);
  fclose(f1);
  */
  FILE *f2;
  char filename[] = "demo.dat";
  if((f2 = fopen(filename, "r+")) == NULL)
    {
      printf("Khong mo duoc file %s!\n", filename);
      return 1;
    }

  fread(&obj1, 1, sizeof(obj1), f2);
  printf("%d %c %d\n", obj1.a, obj1.ch, obj1.b);
  puts(obj1.str);
  
  fclose(f2);
  return 0;
}
