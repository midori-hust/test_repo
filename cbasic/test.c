#include<stdio.h>

int main()
{
  int a;
  printf("Hay nhap vao 1 so:"); scanf("%d",&a);
  switch(a)
    {
    case 0:
      printf("0");
    case 1:
      printf("1");
    case 2:
      printf("2");
    case 3:
      printf("3");
    case 4:
    case 5:
      printf("5");
      break;
    }
  return 0;

}
