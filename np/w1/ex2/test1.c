#include "linklist.h"

int main() {
  int n;

  printf("Enter input test (finish: any letter):\n");
  while(1) {
    if(scanf("%d", &n) != 1) {
      while(getchar() != '\n');
      break;
    }
    while(getchar() != '\n');
    insert(n);
  }

  printf("The list before sorting:\n");
  displayList();
  sortList();
  printf("The list after sorting:\n");
  displayList();
  freeList();
  return 0;
}
