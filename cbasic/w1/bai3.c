/* Cau 3: Viet chuong trinh nhap tu ban phim 2 so nguyen n va m. */
/* Sau dp nhap n so nguyen luu vao mang a, nhap m so nguyen luu vao mang b. */
/* - Hien thi ra man hinh so luong cac phan tu chung cua 2 mang nay, va  */
/* danh sach cac phan tu do. */
/* - Sap xep mang a va b theo thu tu tang dan. Hien thi ket qua ra man hinh. */
/* - Tu 2 mang a va b, gop lai thanh mang c sao cho cac phan tu trong c */
/* theo thu tu tang dan. Hien thi c ra man hinh */


#include <stdio.h>

#define MAXLENGTH 100

void swap(int *a, int *b);
void *sapxeptang(int* a, int n);

int main()
{
  int n, m, i, j, k;
  int a[MAXLENGTH], b[MAXLENGTH], c[MAXLENGTH], d[MAXLENGTH];

  printf("Hay nhap so phan tu cua mang thu nhat: "); scanf("%d", &n);
  printf("Hay nhap so phan tu cua mang thu hai: "); scanf("%d", &m);
  if((n>MAXLENGTH) || (n<0))
    {
      printf("Ban da nhap 1 so qua lon, hoac nhap ky tu khac so. Chuong trinh se tu dong thoat ra!\n");
      return 1;
    }
  else
    {
      printf("\n\t\tMang thu nhat: \n");
      for(i=0; i<n; i++)
	{
	  printf("\tPhan tu thu %d la: ", i+1); scanf("%d", &a[i]);
	  if(i>0)
	    {	     
	      if(a[i] < a[i-1]) swap(&a[i], &a[i-1]); //Preparing	      
	    }
	}
      printf("\n\t\tMang thu hai: \n");
      for(i=0; i<m; i++)
	{
	  printf("\tPhan tu thu %d la: ", i+1); scanf("%d", &b[i]);
	  if(i>0)
	    {
	      if(b[i] < b[i-1]) swap(&b[i], &b[i-1]); //Preparing
	    }
	}
      sapxeptang(a, n);
      sapxeptang(b, m);
      
      
      
      
      //Find the members which both of the arrays have
      k=0;
      for(i=0; i<n; i++)
	{
	  for(j=0; j<m; j++)
	    {
	      if(a[i] == b[j]) 
		{
		  if(k>0)
		    {
		      if(a[i] != d[k-1])
			{
			  d[k] = a[i];
			  k++;
			}
		    }
		  else
		    {
		      d[k] = a[i];
		      k++;
		    }
		}
	    }
	}
      printf("Cac phan tu chung cua 2 mang gom: ");
      for(i=0; i<k; i++) printf(" %d ", d[i]); 
      printf("\n");      
      printf("Cac phan tu cua mang thu nhat gom: ");
      for(i=0; i<n; i++) printf(" %d ", a[i]);
      printf("\n");      
      printf("Cac phan tu cua mang thu hai gom: ");
      for(i=0; i<m; i++) printf(" %d ", b[i]);
      printf("\n");             

      //join a and b to c
      k=0;
      for(i=0; i<n; i++)
	{
	  c[k] = a[i];
	  k++;	   
	}
      for(j=0; j<m; j++)
	{
	  c[k] = b[j];
	  k++;
	}
      sapxeptang(c,k);
      printf("Cac phan tu cua mang gop giua mang thu nhat va mang thu hai gom: ");
      for(i=0; i<k; i++) printf(" %d ", c[i]);
      printf("\n"); 
    }
  return 0;
}



void swap(int *a, int *b)
{
  int temp; 
  temp = *a;
  *a = *b;
  *b = temp;
}

void *sapxeptang(int *a, int n)
{
  int i;
  for(i=0; i<n-1;)
    {
      if(a[i]>a[i+1])
	{
	  swap(&a[i], &a[i+1]);
	  i=0;
	}
      else i++;
    }
}
