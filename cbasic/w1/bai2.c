/* Cau 2: Viet chuong trinh nhap vao mot mang so tu nhien. Hay in ra man hinh: */
/* - Dong 1: gom cac so le, tong cong co bao nhieu so le. */
/* - Dong 2: gom cac so chan, tong cong co bao nhieu so chan. */

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 100

int main()
{
  int n, i, j=0, k=0;
  int a[MAXLENGTH], b[MAXLENGTH], c[MAXLENGTH];

  printf("Hay nhap so phan tu cua mang: "); scanf("%d", &n);
  if((n>MAXLENGTH)||(n<0))
    {
      printf("Ban da nhap so qua lon, hoac khong nhap so vao. Chuong trinh se tu dong thoat!");
      return 1;
    }
  else
    {
      printf("Hay nhap lan luot cac phan tu cua mang: \n");
      for(i=0; i<n; i++)
	{
	  printf("\tPhan tu thu %d la: ", i+1); scanf("%d", &a[i]);
	  if(a[i]%2 == 0)
	    {
	      b[j] = a[i];
	      j++;
	    }
	  else 
	    {
	      c[k] = a[i];
	      k++;
	    }
	}
      printf("Co %d so le, bao gom: ", k);
      for(i=0; i<k; i++) printf(" %d ", c[i]);
      printf("\n");
      printf("Co %d so chan, bao gom: ", j);
      for(i=0; i<j; i++) printf(" %d ", b[i]);
      printf("\n");
      return 0;
    }
}
