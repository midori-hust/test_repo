/*
Làm lại bài NokiaDB gồm 12 chức năng như tuần trước, sử dụng Double Linkedlist.
*/

typedef struct
{
  char model[20];
  float memo;
  float screen;
  float price;
}phone;

typedef phone ElmType;

//========================

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"DoubleLinkedList.h"

#define MAX 1000

//==========================

ElmType makeData()
{
  ElmType key;

  getchar();
  printf("\nMobile infomation:");
  printf("\n + Model: ");  scanf("%[^\n]",key.model);  getchar();
  printf(" + Memory: ");scanf("%f",&key.memo);
  printf(" + Screen: ");scanf("%f",&key.screen);
  printf(" + Price: ");scanf("%f",&key.price);
  return key;
}

//===========================================

dllist *search(dllist *head,char *s)
{
  dllist *cur;

  for(cur = head; cur != NULL; cur = cur->next)
    if(strcmp(cur->key.model,s) == 0)
      return cur;

  return NULL;      
}

//============================================

int menu()
{
  int choice;

  printf("\n\n\t========================");
  printf("\n\tNokiaDB menu");
  printf("\n\t\t1. Import from NokiaDB.dat.");
  printf("\n\t\t2. Display.");
  printf("\n\t\t3. Add a new phone before a position.");
  printf("\n\t\t4. Add a new phone after a position.");
  printf("\n\t\t5. Delete a new phone at position.");
  printf("\n\t\t6. Search by model.");
  printf("\n\t\t7. Update by model.");
  printf("\n\t\t8. Split into 2 list.");
  printf("\n\t\t9. Divide into 2 list with size.");
  printf("\n\t\t10. Reverse list.");
  printf("\n\t\t11. Save to file.");
  printf("\n\t\t12. Exit.");
  printf("\n\t========================");
  printf("\n\tYou choose:.......");
  scanf("%d",&choice);

  return choice;
}

//============================================

void printList(dllist *head)
{ 
  dllist *cur;
  int i = 1;

  printf("\n%-5s%-20s%-15s%-20s%-15s\n\n","STT","MODEL","MEMORY","SCREEN","PRICE");
  for(cur = head; cur != NULL;cur = cur->next)
    printf("%-5d%-20s%-15.2f%-20.1f%-15.1f\n",i++,cur->key.model,cur->key.memo,cur->key.screen,cur->key.price*1000);
}

//============================================

void rmenu()
{
  char ch;
  printf("\nPress any key to continue....");
  getchar();
  scanf("%c",&ch);
}

//================Ham chinh=====================

main()
{
  FILE *f;
  dllist *head,*head2,*p;
  int quit = 0,choice;
  int i,n,k,k1,k2;
  ElmType *key,x;
  char s[20];

  newDllist(&head);
  newDllist(&head2);

  while(quit == 0)
    {
      choice = menu();
      switch(choice)
	{

	case 1:  if((f = fopen("NokiaDB.dat","rb"))==NULL)
	         printf("Cannot open file %s.\n","NokiaDB.dat");
	         else
		   { 
		     key = (ElmType*)malloc(MAX * sizeof(ElmType));
		     n = fread(key,sizeof(ElmType),MAX,f);
		     for(i = 0; i < n; i++)
		       addTail(&head,key[i]);
		     printf("\nRead data from file %s successfully!\n","NokiaDB.dat");
		   }
	         fclose(f);
		 free(key);
		 rmenu();
		 break;
		  
       	case 2:  printList(head);
	         rmenu();
	         break;

	case 3:  printf("The position you want to insert before: ");
	         scanf("%d",&k);
		 if(k < n && k > 0)
		   {
		     x = makeData();
		     addBefore(&head,k,x);
		   }
		 else 
		   printf("\nEnter position k(k < %d and k > 0 ) again.\n",n);
		 rmenu();
		 break;

	case 4:  printf("The position you want to insert after: ");
	         scanf("%d",&k);
		 if(k < n && k > 0)
		   {
		     x = makeData();
		     addAfter(&head,k,x);
		   }
		 else 
		   printf("\nEnter position k(k < %d and k > 0 ) again.\n",n);
		 break;

	case 5:  printf("The position you want to delete: ");
	         scanf("%d",&k);
		 if(k < n && k > 0)
		   delNode(&head,k);
		 else 
		   printf("\nEnter position k(k < %d and k > 0 ) again.\n",n);
		 rmenu();
		 break;
		 
	case 6:  printf("Enter model you want to find: ");
                 scanf("%s",s);
	         p = search(head,s);
		 if(p == NULL) printf("This model is n't in the list.\n");
		 else
		   {
		     printf("\nModel %s 's information:",s);
		     printf("\n + Memory: %f G",p->key.memo);
		     printf("\n + Screen: %.1f inch.",p->key.screen);
		     printf("\n + Price : %.1f dong.\n",p->key.price*1000);
		   }
		 rmenu();
		 break;
		 
	case 7:  printf("Enter model you want to update: ");
                 scanf("%s",s);
	         p = search(head,s);
		 if(p == NULL) printf("This model is n't in the list.\n");
		 else
		   {
		     printf("\nModel %s 's information:",s);
		     printf(" + Memory: "); scanf("%f",&p->key.memo);
		     printf(" + Screen: "); scanf("%f",&p->key.screen);
		     printf(" + Price : "); scanf("%f",&p->key.price);
		   }
		 rmenu();
		 break;

	case 8:  printf("Split from line: ");
                 scanf("%d",&k);
		 head2 = split(head,k);
		 printf("List 1:\n");
		 printList(head);
		 
		 printf("\nList 2:\n");
		 printList(head2);

		 rmenu();
		 break;
		 
	case 9: printf("Split from line: ");
                scanf("%d",&k1);
		printf("Number of lines to split: ");
		scanf("%d",&k2);
	       
		head2 = divide(head,k1,k2,n);
		printf("List 1:\n");
		printList(head);
		printf("\nList 2:\n");
		printList(head2);

		rmenu();
		break;

	case 10: reverse(&head);
	         printf("\nReverse the list successfully!\n");
	         rmenu();
		 break;

	case 11: f = fopen("NokiaDB.dat","wb");
	         saveDat(head,f);
		 printf("Save to file successfully!\n");
		 fclose(f);
		 rmenu();
		 break;

	case 12: printf("Have funny time!!\n");
	         dllistFree(head);
		 quit++;
		 break;

	default:  printf("Choose from 1 to 12.\n");

        }
    }
  return 0;
}
