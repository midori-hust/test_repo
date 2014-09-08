#include "linklist.h"

int main() {
  int n;

  printf("Enter input test (finish: -1):\n");
  while(1) {
    while(scanf("%d", &n) != 1) {
      printf("Wrong input! Please retry!");
      while(getchar() != '\n');
    }
    while(getchar() != '\n');
    if(n == -1) break;
    insertTop(n);
  }
  displayList();
  printf("Enter the value which you want to delete: ");
  while(scanf("%d", &n) != 1) {
    printf("Wrong input! Please retry!");
    while(getchar() != '\n');
  }
  searchNode(n);
  deleteNode(n);
  displayList();
  freeList();
  return 0;
}
