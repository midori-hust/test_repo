#include "phone.h"

char menu()
{
  char ch;
  printf("\t\tMENU\n\n");
  printf("1. Nhap thong tin dien thoai.\n");
  printf("2. Hien thi thong tin cac dien thoai.\n");
  printf("3. Sap xep ten dien thoai theo thu tu tang dan.\n");
  printf("4. Tim kiem dien thoai.\n");
  printf("5. Ket thuc.\n");
  printf("\tBan chon?\n");
  ch = getchar();
  char ch1;
  while((ch1 = getchar()) != '\n');
  printf("Processing...\n");
  return ch;
}

void nhapThongTin(FILE *f)
{
  char name[MAXLENGTH];
  long int price;
  float rating;
  printf("Hay nhap lan luot cac thong tin cua dien thoai (Go ten dien thoai: $$$ de ket thuc cong viec):\n");
  while(1)
    {
      printf("Ten dien thoai: "); gets(name);
      if(strcmp(name, "$$$") == 0) break;
      printf("Gia tien cua dien thoai: "); scanf("%li", &price);
      char ch = getchar();
      printf("Rating cua dien thoai: "); scanf("%f", &rating);
      ch = getchar();
      fputs(name, f);
      fprintf(f, "\n%li\t%f\n", price, rating);
    }
}

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

void swap(PhoneInfo *phone1, PhoneInfo *phone2)
{
  PhoneInfo temp = *phone1;
  *phone1 = *phone2;
  *phone2 = temp;
}
