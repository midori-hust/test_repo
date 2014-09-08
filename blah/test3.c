#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 100

void displayList(int *a, int n);

int main()
{
  int i, max, n, k, m;
  int flag = 0;
  int count = 0;
  int list[MAXLENGTH];
  
  printf("Set the size of the array: ");
  while(scanf("%d", &n) != 1) {
    printf("Invalid input, please retry.\n");
    while(getchar() != '\n');
  }
  
  if(n < 1) {
    printf("There is no element in this array\nExit...\n");
    return 1;
  }

  printf("The element of array\n");
  for(i=0; i<n; i++) {
    printf("\tA[%d]: ", i);
    while(scanf("%d", &list[i]) != 1) {
      printf("Invalid input, please retry.\n");
      while(getchar() != '\n');
    }
  }
  
  printf("The max value is \n");

  max = list[0];
  for (i=0; i<n ; i++) {
    if(list[i] > max)
      max = list[i];
  }
  printf("%d\n", max);

  printf("Give me the value which you want to insert into the max value position: ");
  while(scanf("%d", &k) != 1) {
    printf("Invalid input, please retry.\n");
    while(getchar() != '\n');
  }

  for (i=0; i<n ; i++) {
    if(max == list[i])
      count++;
  }
  if(count > 1)
    printf("There are %d max elements\n", count);
  else
    printf("There is 1 max element\n");

  m = n + count;

  for (i=n-1; i>=0 ; i--) {
    if(count == 0) break;

    list[i+count] = list[i];

    if(list[i] == max) {
      --count;
      list[i+count] = k;
    }
     
  }

  displayList(list, m);

  return 0;
}


//--------------------------------------------------------------------
// a: array
// n: the size of array
void displayList(int *a, int n) {
  int i;
  if(a != NULL) {
    printf("The elements in current list:\n");
    for(i=0; i<n; i++) {
      printf("\tA[%d] = %d\n", i, a[i]);
    }
    printf("\n");
  }
  else
    printf("The current list is empty.\n");
}
