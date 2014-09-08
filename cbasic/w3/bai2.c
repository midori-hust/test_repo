/* Tiep theo bai tap da lam */
/* Mo file demo.txt */
/* -Doc noi dung dong 1 de hien thi a, b, ch */
/* -Doc xau co do dai toi da 20 ky tu o dong */
/* tiep theo va hien thi ra man hinh */

#include <stdio.h>

#define MAXLENGTH 100

int main()
{
  int a, b;
  char ch;
  char str[MAXLENGTH];

  FILE *f1;
  char filename[] = "demo.txt";

  if((f1 = fopen(filename, "r")) == NULL)
    {
      printf("Khong mo duoc file %s!\n", filename);
      return 1;
    }

  fscanf(f1, "%d %c %d\n", &a, &ch, &b);
  // fscanf(f1, "%s", str);
  fgets(str, 20, f1);
  //  puts(str);
  printf("%d %c %d\n%s\n", a, ch, b, str);

  fclose(f1);
  return 0;
}
