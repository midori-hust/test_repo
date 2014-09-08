#include <stdio.h>
#include <stdlib.h>

int main() {
  int m, n, max;
  int i, j;
  int temp1 = 0;
  int temp2 = 0;
  int *a;
  int *b;

  printf("Set the size of the first array: "); 
  while(scanf("%d", &m) != 1) {
    printf("Wrong value! Please retry!  ");
    while(getchar() != '\n');
  }

  printf("Set the size of the second array: ");
  while(scanf("%d", &n) != 1) {
    printf("Wrong value! Please retry!  ");
    while(getchar() != '\n');
  }

  a = (int*)malloc((m+1) * sizeof(int));
  if(a == NULL) {
    printf("Memory allocation failed!\n");
    return -1;
  }
  
  b = (int*)malloc((n+1) * sizeof(int));
  if(b == NULL) {
    printf("Memory allocation failed!\n");
    return -1;
  }

  printf("Please enter the elements of the first array\n");
  for(j=0; j<m; j++) {
    printf("A[%d] = ", j);
    while(scanf("%d", &a[j]) != 1) {
      printf("Wrong input! Retry: A[%d] = ", j);
      while(getchar() != '\n');
    }
  }

  printf("Please enter the elements of the second array\n");
  for(j=0; j<n; j++) {
    printf("B[%d] = ", j);
    while(scanf("%d", &b[j]) != 1) {
      printf("Wrong input! Retry: B[%d] = ", j);
      while(getchar() != '\n');
    }
  }

  printf("\n");
  max = m<n ? n : m;

  for(i=0; i<max; i++) {
    if(i<m && i<n) {
      temp1 += a[i];
      temp2 += b[i];
      printf("\t%d\t%d\t%d\n", temp1, temp2, temp1+temp2);
      }
    else
      if(i>=m && i<n) {
	//temp1 += a[i];
	temp2 += b[i];
	printf("\t__\t%d\t%d\n", temp2, temp1+temp2);
      }
      else if(i<m && i>=n) {
	temp1 += a[i];
	//temp2 += b[i];
	printf("\t%d\t__\t%d\n", temp1, temp1+temp2);
      }

  }
  printf("\nThe show's over!\n");

  free(a);
  free(b);

  return 0;
}
