#include "midterm.h"


char menu()
{
  char ch;
  printf("\t\tMENU\n\n");
  printf("1. Nhap thong tin.\n");
  printf("2. Doc du lieu vao mang.\n");
  printf("3. Tim kiem ban ghi bang ma san pham.\n");
  printf("4. Ket thuc.\n");
  printf("\tBan chon?\n");
  ch = getchar();
  char ch1;
  while((ch1 = getchar()) != '\n');
  printf("Processing...\n");
  return ch;
}

void nhapThongTin(FILE *f)
{
  int id;
  char name[MAXLENGTH];
  int price;
  char description[MAXLENGTH];
  int quantity;

  printf("Hay nhap lan luot cac thong tin cua san pham (go ma san pham khac so de ket thuc cong viec)\n");
  while(1)
    {
      printf("\nMa san pham: "); 
      if((scanf("%d", &id)) == 0) break;
      char ch;
      while((ch = getchar()) != '\n'); //clear cache
      if((id<101) || (id>500))
	{	
	  printf("Ban da nhap so qua khoang [101, 500]");
	  continue;
	}

      printf("Ten san pham: "); gets(name);
      printf("Gia tien: "); scanf("%d", &price);
      while((ch = getchar()) != '\n');
      printf("Mo ta san pham: "); gets(description);
      printf("So luong san pham: "); scanf("%d", &quantity);
      while((ch = getchar()) != '\n');
      fprintf(f, "%d\n", id);
      fputs(name, f);
      fprintf(f, "\n%d\t%d\n", price, quantity);
      fputs(description, f);
      fputs("\n",f);
    }
  
}

/*
void sortPhoneName(PhoneInfo *phoneList, int n)
{
  int min;
  int i, j;
  for(i=0; i<n-1; i++)
    {
      min = i;
      for(j=i+1; j<n; j++)
	if(strcmp(phoneList[j].name, phoneList[min].name)<0) min = j;
      swap(&(phoneList[min]), &(phoneList[i]));
    }
}
*/
