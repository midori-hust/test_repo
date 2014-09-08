#include "midterm.h"


char menu()
{
  char ch;
  printf("\t\tMENU\n\n");
  printf("1. Nhap thong tin.\n");
  printf("2. Doc du lieu tu file.\n");
  printf("3. Tim kiem san pham.\n");
  printf("4. Ket thuc.\n");
  printf("\tBan chon?\n");
  ch = getchar();
  char ch1;
  while((ch1 = getchar()) != '\n');
  printf("Processing...\n");
  return ch;
}


int BinarySearch(ProductInfo *productList, int id, int n)
{
  int Low, Mid, High;
  Low = 0;
  High = n-1;
  while(Low <= High)
    {
      Mid = (Low + High)/2;
      if(productList[Mid].id < id)
	Low = Mid + 1;
      else if(productList[Mid].id > id)
	High = Mid - 1;
      else
	return Mid;
    }
  return -1;
}

