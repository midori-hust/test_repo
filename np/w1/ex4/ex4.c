#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void solveOddOrderMatrix(int n, int **p);
void solveSinglyEvenMagicSquare(int n, int **p);
void solveDoubleEvenMagicSquare(int n, int **p);
void printMagicalMatrix(int n, int **p, int delay);
void waitFor(unsigned int secs);

int main() {
  int n, i;
  int **pp;
  int *p;

  printf("Please enter the order of the magic square: ");
  while(scanf("%d", &n) != 1) {
    printf("Wrong input! Please retry!\n");
    while(getchar() != '\n');
  }
  
  if(n<=0) {
    printf("Invalid order. Program's done!\n");
    return 1;
  }

  pp = (int**)malloc(n*sizeof(int*));
  if(pp == NULL)  {
    printf("Allocation failed.\nEnding program.\n");
    return 1;
  }
  p = (int*)malloc(n*sizeof(int));
  if(p == NULL)  {
    printf("Allocation failed.\nEnding program.\n");
    return 1;
  }
  for(i=0; i<n; i++)
    pp[i] = p + i * n;  
  free(p);

  if(n%2 == 1)
    solveOddOrderMatrix(n, pp);
  else
    solveSinglyEvenMagicSquare(n, pp);

  printMagicalMatrix(n, pp, 0);
  printMagicalMatrix(n, pp, 1);
  free(pp);

  return 0;
}

void solveOddOrderMatrix(int n, int **p) {
  int i, j;
  int k = 1;

  for(i=0; i<n; i++) {
    for(j=0; j<n; j++) {
      p[i][j] = 0;
    }
  }

  i=0;
  j=n/2;
 
  while(k != (n*n+1)) {
    if(p[i][j] == 0) {
      p[i][j] = k;
      
      if(i == 0) i = n-1;
      else i--;
      
      if(j == (n-1)) j = 0;
      else j++;
    }
    else {
      if(i == (n-2)) i = 0;
      else if(i == (n-1)) i = 1;
      else i += 2;

      if(j == 0) j = n-1;
      else j--;
      continue;
    }
    k++;      
  }  
}

void solveSinglyEvenMagicSquare(int n, int **p) {
  int i, j;
  int m;

  if(n==2) {
    printf("Imposible to generate the magic square of order 2\n");
    return;
  }

  if(n%4 == 0)
    for(i=0; i<n; i++) {
      for(j=0; j<n; j++) {
	if((i-j)%4 == 0 || (i+j+1)%4 == 0)
	  p[i][j] = j + 1 + n*i;     
	else p[i][j] = n*n - j - n*i;
      }
    }
  else {
    solveDoubleEvenMagicSquare(n, p);
  }
}

void solveDoubleEvenMagicSquare(int n, int **p) {
  int i, j, k = 0;
  int *p1;
  int **pp1;
  
  pp1 = (int**)malloc((n/2)*sizeof(int*));
  if(pp1 == NULL)  {
    printf("Allocation failed.\nEnding program.\n");
    return;
  }

  p1 = (int*)malloc((n/2)*sizeof(int));
  if(p1 == NULL)  {
    printf("Allocation failed.\nEnding program.\n");
    return;
  }
  for(i=0; i<n/2; i++)
    pp1[i] = p1 + i * n/2;
  free(p1);
  
  solveOddOrderMatrix(n/2, pp1);

  int a[100];
  for(i=0; i<n/2; i++) {
    for(j=0; j<n/2; j++) {
      a[k] =  pp1[i][j];
      k++;
    }
  }  

  k=0;
  int m = (n-2)/4;

  for(i=0; i<n/2; i++) {
    for(j=0; j<n/2; j++) {
      if(i==(n/4) && j==(n/4)) { //The center: U
	p[2*i][2*j] = 4*a[k]-3;
	p[2*i][2*j+1] = 4*a[k];
	p[2*i+1][2*j] = 4*a[k]-2;
	p[2*i+1][2*j+1] = 4*a[k]-1;
      }
      else if(i==(n/4+1) && j == (n/4)) { // Under the center: L
	p[2*i][2*j] = 4*a[k];
	p[2*i][2*j+1] = 4*a[k]-3;
	p[2*i+1][2*j] = 4*a[k]-2;
	p[2*i+1][2*j+1] = 4*a[k]-1;
      }
      else if(i<=m) {  // m+1 lines L
	p[2*i][2*j] = 4*a[k];
	p[2*i][2*j+1] = 4*a[k]-3;
	p[2*i+1][2*j] = 4*a[k]-2;
	p[2*i+1][2*j+1] = 4*a[k]-1;
      }
      else if(i == m+1) { // U: 1 line
	p[2*i][2*j] = 4*a[k]-3;
	p[2*i][2*j+1] = 4*a[k];
	p[2*i+1][2*j] = 4*a[k]-2;
	p[2*i+1][2*j+1] = 4*a[k]-1;
      }
      else { // X: m-1 line(s)
	p[2*i][2*j] = 4*a[k]-3;
	p[2*i][2*j+1] = 4*a[k];
	p[2*i+1][2*j] = 4*a[k]-1;
	p[2*i+1][2*j+1] = 4*a[k]-2;
      }
      k++;
    }
  }  
}

void printMagicalMatrix(int n, int **p, int delay) {
  int i, j, k;

  printf("The magical magic square of order %d:\n\n", n);
  for(i=0; i<n; i++) {
    for(j=0; j<n; j++) {
      waitFor(delay);
      if(delay) printf("%5d\n", p[i][j]);
      else printf("%5d", p[i][j]);
    }
    printf("\n\n");
  }
}

void waitFor(unsigned int secs) {
  int retTime = time(0) + secs;
  while(time(0) < retTime);
}
