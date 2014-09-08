/* Vi du: Nhap vao 1 mang va in ra gia tri dao nguoc cua mang do */


#include <stdio.h>
#include <string.h>

#define MAXLENGTH 100

void nhapMang(int *ptr, int num)
{
  int i;

  /* Get the numbers from the user */
  for(i=0; i<num; i++)
    {
      printf("Phan tu thu %d: ", i+1);
      scanf("%d", ptr+i);
    }

}

void inNguoc(int *ptr, int num)
{
  int i;
  for(i=num-1; i>=0; i--) printf("%5d", ptr[i]);
  printf("\n");
}


int main()
{
  int n;
  int A[MAXLENGTH];

  printf("Nhap so phan tu trong day: "); scanf("%d", &n);
  printf("Nhap cac phan tu trong day:\n");

  nhapMang(A,n);
  printf("Day so sau khi dao lai:\n");
  inNguoc(A,n);
  return 0;
}
