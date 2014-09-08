#include<stdio.h>
#include<stdlib.h>
#include "linklist.h"

node* cur = NULL;
node* root = NULL;

int main()
{
  int input = 0;
  int i = 1;
  printf("Hay nhap vao cac phan tu, an -1 de ket thuc viec nhap lieu.\n");  
  node* new_node;
  
  while(1)
    {
      printf("Phan tu thu %d: ", i); scanf("%d", &input);
      if(input == -1) break;
      i++;
      if(root == NULL)
	{
	  root = newNode(input);
	  cur = root;
	}
      else
	{
	  new_node = newNode(input);
	  cur->next = new_node;
	  cur = new_node;
	}
    }

  printf("Hay nhap them 1 node moi de nhet no vao dau tien!  "); scanf("%d", &input);
  new_node = newNode(input);

  printf("Teehee!\n");
  printf("After inserting to the top:\n");
  //insertTop(root,new_node);//error
  //  insert(root, cur, new_node);//Okay

  //  node* prev = getPrev(root, cur);//Something's wrong here
  //  printf("%d\n", prev->element);
  // displayList(prev);

  //deleteNode(root,cur);//okay

  displayList(root);

  return 0;
}
