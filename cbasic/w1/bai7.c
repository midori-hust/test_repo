/* Cau 7: */
/* Viet chuong trinh nhap vao 1 xau roi xuat xau do ra man hinh  */
/* duoi dang moi tu mot dong. */



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
  chuanhoaxau(hoten);
  for(i=0; i<strlen(hoten); i++) //Dem so tu
    {
      if(hoten[i] == ' ') a++;
    }
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
