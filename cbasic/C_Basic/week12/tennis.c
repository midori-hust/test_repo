typedef struct
{
  char name[20];
}info;

typedef info ElmType;

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"BST.h"

//===================================

ElmType winner(Tree x, Tree y)
{
  if (rand()%3 == 1)
    return x->key;
  else
    return y->key;
}

//==============Ham chinh============//

main()
{
  FILE *f;
  Tree T[16],vt[8];
  int i;
  char s[100];
  ElmType a[16];

  srand((unsigned)time(NULL));

  f = fopen("USOpen.txt", "r");
  printf("\nLoading names from USOpen.txt .......\n");

  if (f == NULL)
    printf("File opening failed!\n\n");
  else
    for(i = 0; i < 16; i++)
      {
	fscanf(f, "%s", a[i].name);
	T[i] = makeTreeNode(a[i]);
      }  
  fclose(f);
  printf("Create data successfully!\n");

  printf("\nPress Enter to start the tournament!");
  getchar();
  printf("Generating . . .\n");
  printf("\nPress Enter to view result.\n");
  getchar();

  printf("Round 1:\n");
  for(i = 0; i < 16; i++)
    printf("%-8s",T[i]->key.name);

  printf("\nRound 2:\n");
  for(i = 0; i < 16; i = i + 2)
      vt[i/2] = merge2Tree(T[i],T[i+1],winner(T[i],T[i+1]));
  for(i = 0; i < 8; i++)
    printf("%8s",vt[i]->key.name);

  printf("\nRound 3:\n");
  for(i = 0; i < 8; i = i + 2)
      T[i/2] = merge2Tree(vt[i],vt[i+1],winner(vt[i],vt[i+1]));
  for(i = 0; i < 4; i++)
    printf("%8s%5s","",T[i]->key.name);

  printf("\nRound 4:\n");
  for(i = 0; i < 4; i = i + 2)
      vt[i/2] = merge2Tree(T[i],T[i+1],winner(T[i],T[i+1]));
  for(i = 0; i < 2; i++)
    printf("%10s%5s","",vt[i]->key.name);

  printf("\nThe winner:\n");
  T[0] = merge2Tree(vt[0],vt[1],winner(vt[0],vt[1]));
  printf("%14s%5s\n\n","",T[0]->key.name);

  freeTree(T[0]);

  return 0;
}
