/* Cau 4: Viet chuong trinh nhap 1 xau ky tu va kiem tra xem chuoi do */
/* co doi xung khong? */

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 100

int main()
{
  int i;
  char str[MAXLENGTH];

  printf("Hay nhap xau: "); gets(str);
  for(i=0; i<(strlen(str)/2); i++)
    {
      if(str[i] != str[strlen(str)-1-i])
	{
	  printf("Xau nay khong phai xau doi xung.\n");
	  return 1;
	}
    }
  printf("Xau nay la xau doi xung.\n");
  return 0;
}
