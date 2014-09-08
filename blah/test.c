#include <stdio.h>
#include <ctype.h>

int main()
{
  int a, b, max, min;
  char c;
  
  printf("Hay nhap vao 2 so nguyen: \n" );
  printf("So thu nhat: ");
  
  while(scanf("%d", &a) != 1) {
    printf("Ban da nhap ky tu khong phai so, xin vui long nhap lai so thu nhat!\n");
    while(getchar() != '\n');
  }

  printf("So thu hai: ");
  while(scanf("%d", &b) != 1) {
    printf("Ban da nhap ky tu khong phai so, xin vui long nhap lai so thu hai!\n");
    while(getchar() != '\n');
  }

  max = a<b ? b : a;
  min = a<b ? a : b;
  printf("So %d lon hon\n", max);
  printf("So %d nho hon\n", min);

  while(getchar() != '\n');
  printf("Ban hay nhap vao 1 chu cai: \n" );
  scanf("%c", &c);
  while(getchar() != '\n');

  while(!isalpha(c)) {
    printf("Ban khong nhap vao 1 chu cai. Xin vui long nhap lai\n");
    scanf("%c", &c);
  }

  if(islower(c))
    c = toupper(c);

  printf("Chu cai sau khi duoc viet hoa: %c\n", c);

  return 0;
}
