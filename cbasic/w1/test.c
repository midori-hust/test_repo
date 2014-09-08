#include <stdio.h>
#include <string.h>

#define MAXLENGTH 100

//Tra ve phan ten cua mot xau ho va ten
char *timten(char* hoten)
{
  int i;
  i = strlen(hoten)-1;

  //Tim ky tu cuoi cung trong xau
  while (i>=0 && hoten[i] != ' ') i--;
  return hoten + i + 1;
}

int main()
{
  char hoten[MAXLENGTH];

  printf("Hay nhap vao xau ho va ten: ");
  gets(hoten);
  printf("Ten cua nguoi nay la: %s\n", timten(hoten));
  return 0;

}
