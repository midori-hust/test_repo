/*
Hoàn thiện bài tập danh bạ trên lớp sử dụng linkedlist, tạo menu bao gồm các chức năng
+ Thiết lập danh bạ
+ In danh bạ ra màn hình
+ Xóa 1 số điện thoại
+ Thêm 1 số điện thoại vào trước 1 số điện thoại có sẵn
+ Tìm kiếm thông tin theo số điện thoại
+ Lưu nội dung danh sách vào 1 file contact.txt và 1 file contact.dat
*/

typedef struct
{
  char name[100];
  char number[12];
  char mail[40];
}profile;

typedef profile ElmType;

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LinkedList.h"

//==========================

ElmType makeData()
{
  ElmType key;

  getchar();
  printf("\nProfile:");
  printf("\n + Name: ");
  fgets(key.name,100,stdin);
  key.name[strlen(key.name) - 1] = '\0';
  printf(" + Phone number: ");   scanf("%s",key.number);
  printf(" + Email: ");          scanf("%s",key.mail);

  return key;
}

//===========================

Llist *search(Llist *root, char *s)
{
  Llist *cur;

  for(cur = root; cur != NULL;cur = cur->next)
    if(strcmp(cur->key.number,s) == 0) 
      return cur;
  return NULL;
}

//===========================

void printList(Llist *root)
{
  Llist *cur;
  int i = 1;

  printf("\n%-5s%-20s%-15s%-20s\n","STT","NAME","PHONE NUMBER","EMAIL");
  for(cur = root; cur != NULL; cur = cur->next)
    printf("%-5d%-20s%-15s%-20s\n",i++,cur->key.name,cur->key.number,cur->key.mail);
}

//===========================================

int menu()
{
  int choice;

  printf("\n\t======================");
  printf("\n\tPhone number list manager");
  printf("\n\t\t1. Create the list.");
  printf("\n\t\t2. Print the list.");
  printf("\n\t\t3. Delete a phone number.");
  printf("\n\t\t4. Insert a phone number before a position.");
  printf("\n\t\t5. Find a phone number.");
  printf("\n\t\t6. Save in file.");
  printf("\n\t\t7. Free and exit.");
  printf("\n\t=======================");  
  printf("\n\tYou choose:........");
  scanf("%d",&choice);

  return choice;
}
//====================================

void save_txt(Llist *root,FILE *f)
{
  Llist *cur;
  int i = 1;

  fprintf(f,"\n%-5s%-20s%-15s%-20s\n","STT","NAME","PHONE NUMBER","EMAIL");
  for( cur = root; cur != NULL; cur = cur->next)
    fprintf(f,"%-5d%-20s%-15s%-20s\n",i++,cur->key.name,cur->key.number,cur->key.mail);
}

//====================================

void rmenu()
{
  char ch;

  printf("\n Press any key to continue.....");
  getchar();
  scanf("%c",&ch);
}

//=============Ham chinh============//

main()
{
  int i,n,k;
  int quit = 0,choice;
  ElmType key;
  char s[12];
  FILE *f1,*f2;
  Llist *root,*p;

  newLlist(&root);

  while(quit == 0)
    {
      choice = menu();
      switch(choice)
	{

	case 1:  printf("How may people do you want to add? ");
	         scanf("%d",&n);
	         for(i = 0; i < n; i++)
		   { 
		     key = makeData();
		     addLast(&root,key);
		   }
		 rmenu();
		 break;

	case 2:  printList(root);
                 rmenu();
	         break;
	
	case 3:  printf("The position you want to delete: ");
	         scanf("%d",&k);
		 if(k < n && k > 0)
		   delNode(&root,k);
		 else 
		   printf("\nEnter position k(k >0 and k< %d) again.\n",n);
		 rmenu();
		 break;

	case 4:  printf("The position you want to insert: ");
	         scanf("%d",&k);
		 if(k < n && k > 0)
		   {
		     key = makeData();
		     addBefore(&root,k,key);
		   }
		 else 
		   printf("\nEnter position k(k >0 and k<= %d)again.\n",n);
		 rmenu();
		 break;

	case 5:  printf("The number you want to find: ");
	         scanf("%s",s);
		 p = search(root,s);
		 if(p == NULL) printf("This number is n't in the list.\n");
		 else printf(" + Name: %s\n + Email: %s\n",p->key.name,p->key.mail);
		 rmenu();
		 break;
		 
	case 6: f1 = fopen("contact.txt","w");
	        f2 = fopen("contact.dat","wb");
		save_txt(root,f1);
		saveDat(root,f2);
		fclose(f1);
		fclose(f2);
		rmenu();
		break;
	  
	case 7:  LlistFree(root);
	         printf("Have funny times!!\n");
		 quit++;
		 break;
		 
	default: printf("Please choose from 1 to 7.\n");

	}
    }
  return 0;
}
