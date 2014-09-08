/*
Sử dụng dữ liệu từ file NokiaDB.dat của bài 1, viết 2 hàm chia và tách danh sách:
+ Chia làm 2 danh sách con. Tham số là vị trí n (bắt đầu từ phần tử đầu tiên của list)
+ Tách làm 2 danh sách. Tham số là n1, n2( tách ra 1 danh sách con dài n2 từ vị trí n1 ). Chú ý trường hợp n2 > số phần tử của list.
*/

typedef struct Data
{
  char model[20];
  float memo;
  float screen;
  float price;
}nokia;

typedef nokia ElmType;

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LinkedList.h"

#define MAX 1000

//=========================

Llist *search(Llist *root,char *s)
{
  Llist *cur;

  for(cur = root; cur != NULL; cur = cur->next)
    if(strcmp(cur->key.model,s) == 0)
      return cur;

  return NULL;      
}

//============================================

int menu()
{
  int choice;

  printf("\n\t========================");
  printf("\n\tNokiaDB menu");
  printf("\n\t\t1. Import from NokiaDB.dat.");
  printf("\n\t\t2. Print all data.");
  printf("\n\t\t3. Split into 2 list.");
  printf("\n\t\t4. Divide into 2 list with size.");
  printf("\n\t\t5. Exit.");
  printf("\n\t========================");
  printf("\n\tYou choose:.......");
  scanf("%d",&choice);

  return choice;
}

//============================================

void printList(Llist *root)
{ 
  Llist *cur;
  int i = 1;

  printf("\n%-5s%-20s%-15s%-20s%-15s\n","STT","MODEL","MEMORY","SCREEN","PRICE");
  for(cur = root; cur != NULL; cur = cur->next)
    printf("%-5d%-20s%-15.2f%-20.1f%-15.1f\n",i++,cur->key.model,cur->key.memo,cur->key.screen,cur->key.price*1000);
}

//=============================================

void rmenu()
{
  char ch;
  printf("Press any key to continue....");
  getchar();
  scanf("%c",&ch);
}

//================Ham chinh===================//

main()
{
  FILE *f;
  Llist *root,*root2;
  int quit = 0, choice;
  int i,n,k,k1,k2;
  ElmType *key;

  newLlist(&root);
  newLlist(&root2);

  while(quit == 0)
    {
      choice = menu();
      switch(choice)
	{
		 
	case 1:  if((f = fopen("NokiaDB.dat","rb")) == NULL)
                   printf("Cannot open file %s.\n","NokiaDB.dat");
		 else
		   { 
		     key = (ElmType*)malloc(MAX * sizeof(ElmType));
		     n = fread(key, sizeof(ElmType), MAX, f);
		     for(i = 0; i < n; i++)
		       addLast(&root,key[i]);
		     printf("\nRead data from file %s successfully!\n","NokiaDB.dat");
		   }
	         fclose(f);
		 free(key);
		 rmenu();
		 break;
		  
       	case 2:  printList(root);
	         rmenu();
	         break;

	case 3:  printf("Split from line: ");
                 scanf("%d",&k);
		 root2 = split(root,k);
		 printf("List 1:\n");
		 printList(root);
		 
		 printf("\nList 2:\n");
		 printList(root2);
		 rmenu();
		 break;
		 
	case 4: printf("Split from line: ");
                scanf("%d",&k1);
		printf("Split to line: ");
		scanf("%d",&k2);
	       
		root2 = divide(root,k1,k2,n);
		printf("List 1:\n");
		printList(root);
		printf("\nList 2:\n");
		printList(root2);
		rmenu();
		break;

	case 5: printf("Have funny time!!\n");
	        LlistFree(root);
                quit++;
                break;

	default:  printf("Wrong choice!\nChoose from 1 to 5.\n");

        }
    }
  return 0;
}
