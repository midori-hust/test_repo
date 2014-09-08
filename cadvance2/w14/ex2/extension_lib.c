#include "extension_lib.h"

int solve() {
  Graph g;
  int path[SIZE], length, n, i,k;
  char* a[10];
  char s[10][10];

  int source, target;

  source = 1;

  if((g = createGraph()) == NULL) {
    return 1;
  }

  int x;
  printf("nhap vao so cong viec\n");
  scanf("%d",&x);
  for(i=0; i<x; i++)
    {
      printf("nhap vao ten cong viec %d",i+1);
      scanf("%s",s[i]);
      addVertex(g, i+1, s[i]);
      printf("%s", s[i]);
    }

  dropGraph(g);

  return 0;
}
