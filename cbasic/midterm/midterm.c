#include "midterm.h"


char menu()
{
  char ch;
  printf("\t\tMENU\n\n");
  printf("1. Doc thong tin.\n");
  printf("2. Sap xep.\n");
  printf("3. Tim theo so tuyen.\n");
  printf("4. Tim kiem theo ten tuyen.\n");
  printf("5. Ket thuc.\n");
  printf("\tBan chon?\n");
  ch = getchar();
  char ch1;
  while((ch1 = getchar()) != '\n');
  printf("Processing...\n");
  return ch;
}


void sortBusID(BusInfo *busList, int n)
{
  int min;
  int i, j;
  for(i=0; i<n-1; i++)
    {
      min = i;
      for(j=i+1; j<n; j++)
	if(busList[j].id < busList[min].id) min = j;
      swap(&(busList[min]), &(busList[i]));
    }
}

void swap(BusInfo *bus1, BusInfo *bus2)
{
  BusInfo temp = *bus1;
  *bus1 = *bus2;
  *bus2 = temp;

}
