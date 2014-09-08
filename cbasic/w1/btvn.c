/* Viet chuong trinh voi cac ham xu li xau duoc tao ra de lam cac viec sau: */
/* - Cat bo cac dau cach thua trong mot xau */
/* - Dem so tu hien co trong 1 xau */
/* - Dao nguoc thu tu cac ki tu hien co cua 1 xau */
/* - Tach mot xau ho va ten thanh 2 xau moi cho phan ho va phan ten */



#include <stdio.h>
#include <string.h>

#define MAXLENGTH 100
//----------------------------------------------------------------------
//Tra ve phan ten cua mot xau ho va ten
char *timten(char *hoten)
{
  int i;
  i = strlen(hoten)-1;

  //Tim ky tu cuoi cung trong xau
  while (i>=0 && hoten[i] != ' ') i--;
  if(i!=0)
    {
      hoten[i] = '\0';
    }
  return hoten + i + 1;
}

//Loai bo cac dau cach bang ham nay
char *chuanhoaxau(char *str)
{
  int i, k=0;
  int flag = 0;
  char str1[MAXLENGTH];
  for(i=0; i<strlen(str); i++)
    {
      if(str[i] != ' ')
	{
	  str[k] = str[i];
	  k++;
	  flag = 0;
	}
      else if(i == 0) //Ky tu cach dau tien
	{
	  flag = 1;
	  continue;
	}
      else if(flag == 0) //Ky tu cach khong phai dau tien, flag = 0
	{
	  str[k] = ' ';
	  k++;
	  flag = 1;
	}
      else continue; //Ky tu cach khong phai dau tien, flag = 1
    }

  if(str[k-1] == ' ') str[k-1] = '\0';
  else str[k] = '\0';
  return str;
}

//-------------------------------------------------------------------------
int main()
{
  char hoten[MAXLENGTH], daonguoc[MAXLENGTH];
  int a = 0, i, k=0;

  printf("Hay nhap vao xau ho va ten: "); gets(hoten);
  printf("Xau nay da duoc chuan hoa thanh: %s\n", chuanhoaxau(hoten));
  for(i=0; i<strlen(hoten); i++)
    {
      if(hoten[i] == ' ') a++;
    }
  printf("Xau nay co %d tu.\n", a+1);
  for(i=strlen(hoten)-1; i>=0; i--)
    {
      daonguoc[k++] = hoten[i];
    }
  daonguoc[k] = '\0';
  printf("%d\n", k);
  printf("Xau dao nguoc la: %s\n", daonguoc);

  printf("Xau duoc tach ra thanh cac tu: \n");
  for(i=0; i<=a; i++)
    {
      printf("%s\n", timten(hoten));
    }

  return 0;
}
//------------------------------------------------------------------------

char *timten(char *hoten);
char *chuanhoaxau(char *str);
