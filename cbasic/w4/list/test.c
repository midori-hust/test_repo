#include<stdio.h>
#include<stdlib.h>
#include "linklist.h"

Node root = NULL;
Node cur = NULL;
Node sentinel = NULL;

int main()
{

  int input = 0;
  int i = 1;
  printf("Hay nhap vao cac phan tu, an -1 de ket thuc viec nhap lieu.\n");  
  Node new_node;
  
  while(1)
    {
      printf("Phan tu thu %d: ", i); scanf("%d", &input);
      if(input == -1) break;
      i++;

      if(root == NULL)
	{
	  root = newNode(input);
	  cur = root;
	  sentinel = root;
	}
      else
	{
	  new_node = newNode(input);
	  prepend(new_node);
	  cur = new_node;
	}
    }

  printf("Hay nhap them 1 node moi de nhet no vao dau tien!  "); scanf("%d", &input);
  Node  new_node1 = newNode(input);
  displayList();
  printf("\n\n");
  printf("Teehee!\n");
  printf("After inserting to the top:\n");
  Node new_node2 = search(4);
  if (new_node2 == NULL) 
    printf("Khong the xoa duoc phan tu co gia tri la 4.\n");
  else
    deleteNode(new_node2);

  displayList();

  return 0;
}
