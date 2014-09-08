#include <stdio.h>
#include <stdlib.h>

void swap(float *a, float *b);
void displayArray(float *a, int n);
void insertionSort(float *a, int n);
void bubbleSort(float *a, int n);

int main() {
  int n, i;
  float *a, *b;
  float temp;

  printf("Please enter the size of array: ");
  while(scanf("%d", &n) != 1) {
    printf("Wrong input! Please retry!\n");
    while(getchar() != '\n');
  }
  while(getchar() != '\n');

  a = (float*) malloc((n+1)*sizeof(float));
  if(a == NULL) {
    printf("Allocated failed!\n");
    return 1;
  }

  b = (float*) malloc((n+1)*sizeof(float));
  if(b == NULL) {
    printf("Allocated failed!\n");
    return 1;
  }

  printf("Please enter the elements of array:\n");
  for(i=0; i<n; i++) {
    printf("a[%d] = ", i);
    while(scanf("%f", &temp) != 1) {
      printf("Wrong input! Please retry!\n");
      while(getchar() != '\n');
    }
    while(getchar() != '\n');
    a[i] = temp;
    b[i] = temp;
  }

  if(a == NULL) {
    printf("The list has no element. Program's done!\n");
    return 1;
  }

  printf("\nBefore sorting\n");
  displayArray(a, n);
  bubbleSort(a, n);
  printf("\nAfter bubble sorting\n");
  displayArray(a, n);
  printf("\nAfter insertion sorting\n");
  insertionSort(b, n);
  displayArray(b, n);

  free(a);
  free(b);
  return 0;
}


void swap(float *a, float *b) {
  float temp = *a;
  *a = *b;
  *b = temp;
}

void displayArray(float *a, int n) {
  int i;

  if(a != NULL){
    printf("The members of this list:\n");
    for(i=0; i<n; i++) {
      printf("a[%d] = %f\n", i, a[i]);
    }
  }
  else {
    printf("This list has no member\n");
  }
}

void insertionSort(float *a, int n) {
  int i, j;
  float temp;

  for(i=0; i<n; i++) {
    temp = a[i];
    for(j=i-1; j>=0; j--)
      if(a[j] > temp)
	a[j+1] = a[j];
      else break;
    a[j+1] = temp;
  }
}

void bubbleSort(float *a, int n) {
  int i, j;
  float temp;

  for(i=0; i<n; i++) {
    for(j = n-1; j>i; j--) {
      if(a[j]<a[j-1]) {
	swap(&a[j], &a[j-1]);
      }
    }
  }
}
