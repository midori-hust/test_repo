/* Cau 1: Viet chuong trinh thuc hien viec dao mot mang mot chieu  */
/* theo thu tu nguoc lai (luu y thuc hien dao tren mang, chu khong  */
/* don thuan la duyet theo thu tu nguoc lai)  */


#include <stdio.h>
#include <string.h>

#define MAXLENGTH 100

void swap(int *a, int *b)
{
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

int main()
{
  int i, n; 
  int a[MAXLENGTH]; 
  
  printf("Hay nhap so phan tu cua mang: "); scanf("%d", &n);
  if(n>MAXLENGTH) 
    {
      printf("Ban da khong nhap so vao, hoac nhap 1 so lon hon %d. Chuong trinh se thoat ra.\nXin vui long chay lai chuong trinh!\n", MAXLENGTH);
      return 1;
    }
  else
    {
      printf("Hay nhap lan luot cac phan tu cua mang: \n");
      for(i=0; i<n; i++)
	{
	  printf("\tPhan tu thu %d la: ", i+1); scanf("%d", &a[i]);
	}
      
      for(i=0; i<(n/2); i++) swap(&a[i], &a[n-1-i]);
      printf("Mang sau khi dao thu tu la: \n");
      for(i=0; i<n; i++) printf("\tPhan tu thu %d la: %d\n", i+1, a[i]);    
      return 0;
    }
}
