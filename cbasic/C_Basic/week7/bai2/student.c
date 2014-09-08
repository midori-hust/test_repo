/*
Sử dụng danh sách liên kết đôi
Quản lí điểm sinh viên gồm (HoTen, MSSV, Diem).
Các thao tác:
    - Thêm sinh viên theo thứ tự tăng dần điểm số
    - In ra màn hình danh sách sinh viên và điểm
    - Tìm và xóa sinh viên theo MSSV
    - Tìm kiếm 1 sinh viên theo MSSV
*/

typedef struct
{
  char name[30];
  char id[20];
  float mark;
}student;

typedef student ElmType;

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"DoubleLinkedList.h"

//==========================

ElmType makeData()
{
  ElmType key;
  
  printf("\n----------\n");
  printf("Name: ");getchar();
  scanf("%[^\n]",key.name);
  
  printf("ID: ");
  scanf("%s", key.id);
  printf("Mark: ");
  scanf("%f", &key.mark);
	
  return key;
}

//===========================================

void addOrder(dllist **head, ElmType key)
{
  dllist *cur,*new;
  int i = 0;
  new = makeNode(key);

  if (*head == NULL) 
    {
      *head = new;
      return;
    }
  
  if (new->key.mark > (*head)->key.mark)
    {
      new->next = *head;
      (*head)->prev = new;
      *head = new;
      return;
    }
  
  cur = *head;
  while (cur != NULL  &&  new->key.mark < cur->key.mark)
    {
      i++;
      cur = cur->next;
    }
  addAfter(head,i,key);
}

//===========================================

dllist *search(dllist *head,char *s)
{
  dllist *cur;

  for(cur = head; cur != NULL; cur = cur->next)
    if(strcmp(cur->key.id,s) == 0)
      return cur;

  return NULL;      
}

//===========================================

int searchID(dllist *head,char *s)
{
  dllist *cur;
  int i = 0;

  for(cur = head; cur != NULL; cur = cur->next)
    {
      i++;
      if(strcmp(cur->key.id,s) == 0)
	return i;
    }
      
  return -1;      
}

//============================================

int menu()
{
  int choice;

  printf("\n\n\t========================");
  printf("\n\tStudent Manager");
  printf("\n\t\t1. Insert new student in asscending order.");
  printf("\n\t\t2. Display.");
  printf("\n\t\t3. Delete a student by id.");
  printf("\n\t\t4. Search a student by id.");
  printf("\n\t\t5. Exit.");
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

  printf("\n%-10s%-20s%-10s\n\n","ID","NAME","MARK");
  for(cur = head; cur != NULL; cur = cur->next)
    printf("%-10s%-20s%-10.2f\n",cur->key.id,cur->key.name,cur->key.mark);
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
  dllist *head,*p;
  int quit = 0,choice;
  int i,n,res;
  ElmType x;
  char s[20];

  newDllist(&head);

  while(quit == 0)
    {
      choice = menu();
      switch(choice)
	{

	case 1: printf("How many students do you want to insert?..");
	        scanf("%d",&n);
	        for(i = 0; i < n; i++)
		  addOrder(&head,makeData());
		rmenu();
		break;
		  
       	case 2:  printList(head);
	         rmenu();
	         break;

	case 3:  printf("The student's id you want to delete: ");
	         scanf("%s",s);
		 res = searchID(head,s);
		 if(res == -1)
		   printf("This student isn't in the list.\n");
		 else
		   {
		     delNode(&head,res);
		     printf("ID %s 's been deleted.\n",s);
		   }
		 rmenu();
		 break;
		 
	case 4:  printf("The student's id you want to find: ");
	         scanf("%s",s);
	         p = search(head,s);
		 if(p == NULL) printf("This model is n't in the list.\n");
		 else
		   {
		     printf("\nInformation:");
		     printf("\n + ID: %s",p->key.id);
		     printf("\n + Name: %s",p->key.name);
		     printf("\n + Mark: %.2f\n",p->key.mark);
		   }
		 rmenu();
		 break;


	case 5:  printf("Have funny time!!\n");
	         dllistFree(head);
		 quit++;
		 break;

	default:  printf("Choose from 1 to 5.\n");

        }
    }
  return 0;
}
