#include <stdio.h>

int main()
{
  /*
  int a, b, c, d;
  a = 5;
  b = a ++;
  c = (a+6) - ++b;
  d = a++ + ++b -c;
  printf("\nA: %d\nB: %d\nC: %d\nD: %d\n", a, b, c, d);
  */
  /*  if(3+4/2 > 3 && 3<5 || 10<9)
      printf("abc\n");*/
  /*
  int a, b, c, d;
  a=5;
  c = (b = a+3) +7;
  d = (a=2) + (c=9);
  printf("\nA: %d\nB: %d\nC: %d\nD: %d\n", a, b, c, d);
  */

  int i=1;
  while(1)
    {
      printf("%d", i);
      i++;
      if(i%3 == 0) continue;
      printf("/");
      if(i%5 == 0) break;
    }

  return 0;
}
