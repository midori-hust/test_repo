#include<stdio.h>

#define MAXLENGTH 100

int main() {
  int n, i, h;
  int k=0;
  char a[MAXLENGTH];
  char result[MAXLENGTH];
  int temp1, temp0;
  int count;
  int number = 1;
  int j=0;


  printf("Set number of characters: ");
  while(scanf("%d", &n) != 1) {
    printf("Invalid input! Please retry.\n");
    while(getchar() != '\n'); 
  }

  if(n<1) {
    printf("Nothing happened\n");
    return 1;
  }

  printf("Please give me characters:\n");
  for(i=0; i<n; i++) {
    printf("%d: ", i);
    while(getchar() != '\n'); 
    scanf("%c", &a[i]);
  }

  count = n;
  for(i=0; i<3; i++) {
    for(j=0; j<count;j++) {
      temp0 = j;
      while(1) {
	temp1 = temp0%n;
	temp0 = temp0/n;
	printf("%c", a[temp1]);
	k++;
	if(temp0 == 0) {
	  if(k<number) {
	    for(h=k; h<number; h++)
	      printf("%c", a[0]);
	  }
	  k=0;
	  break;
	}
      }
      printf("\n");
    }
    count *= n;
    number++;
  }


  return 0;
}
