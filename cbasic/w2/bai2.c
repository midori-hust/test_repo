#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100

int main(int argc, char* argv[])
{
  double a, b;
  double p, s;

  a = atof(argv[1]);
  b = atof(argv[2]);
  printf("Chu vi hinh chu nhat co cac chieu la %f va %f la: %f\n", a, b, (a+b)*2);
  printf("Dien tich hinh chu nhat co cac chieu la %f va %f la: %f\n", a, b, a*b);
  return 0;
}
