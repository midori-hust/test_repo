/*
Truy cập trang web thegioididong.com. Lấy thông tin các điện thoại di động Nokia và ghi vào file NokiaDB.txt theo format sau(trên 1 dòng):
   Model	Dung lượng     	Màn hình 	Giá
Viết chương trình menu sử dụng linkedlist gồm các chức năng:
+ Import file NokiaDB.txt và chuyển thành file NokiaDB.dat ( sử dụng mảng động)
+ Import từ file NokiaDB.dat
+ In ra màn hình toàn bộ dữ liệu(Nếu nhiều hơn 1 màn hình thì phải phân trang)
+ Tìm kiếm theo model
+ Thoát
*/

typedef struct
{
  char model[20];
  float memo;
  float screen;
  float price;
}phone;

typedef phone ElmType;

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LinkedList.h"

//========================

int n_line(FILE *fin)
{
  char buff[80];
  int dem = 0;

  while(fgets(buff,80,fin) != NULL)
    dem++;
  rewind(fin);

  return dem;
}

//=========================

Llist *search(Llist *root,char *s)
{
  Llist *cur;

  for(cur = root; cur != NULL;cur = cur->next)
    if(strcmp(cur->key.model, s) == 0)
      return cur;

  return NULL;      
}

//============================================

int menu()
{
  int choice;

  printf("\n\n\t========================");
  printf("\n\tNokiaDB menu");
  printf("\n\t\t1. Import file NokiaDB.txt to change NokiaDB.dat.");
  printf("\n\t\t2. Import from NokiaDB.dat.");
  printf("\n\t\t3. Print all data.");
  printf("\n\t\t4. Search by model.");
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
    {
      printf("%-5d%-20s%-15.2f%-20.1f%-15.1f\n",i++,cur->key.model,cur->key.memo,cur->key.screen,cur->key.price*1000);
      if (i % 25 == 0) printf("\nTrang tiep:\n\n");
    }
}

//============================================

void rmenu()
{
  char ch;

  printf("\nPress any key to continue......");
  getchar();
  scanf("%c",&ch);
}

//================Ham chinh=====================

main()
{
  FILE *f1,*f2;
  Llist *root,*p;
  int quit = 0,choice;
  int i,n;
  ElmType *key;
  char s[20];

  newLlist(&root);

  while(quit == 0)
    {
      choice = menu();
      switch(choice)
	{

	case 1:  f1 = fopen("NokiaDB.txt","r");
	         f2 = fopen("NokiaDB.dat","wb");
		 n = n_line(f1);
		 
		 key = (ElmType*)malloc(n*sizeof(ElmType));
		 
		 for(i = 0; i < n; i++)
		   fscanf(f1,"%s%f%f%f",key[i].model,&key[i].memo,&key[i].screen,&key[i].price);
   	  
		 fwrite(key,sizeof(ElmType),n,f2);
		 printf("\nImport data into NokiaDB.dat successfully!\n");
                 
		 fclose(f1);
		 fclose(f2);
		 free(key);
		 rmenu();
		 break;
		 
	case 2:  if((f2 = fopen("NokiaDB.dat","rb")) == NULL)
                   printf("Cannot open file %s.\n","NokiaDB.dat");
		 else
		   { 
		     key = (ElmType*)malloc(n*sizeof(ElmType));
		     fread(key,sizeof(ElmType),n,f2);
		     for(i = 0; i < n; i++)
		       addLast(&root,key[i]);
		     printf("\nRead data from file %s successfully!\n","NokiaDB.dat");
		   }
	         fclose(f2);
		 free(key);
		 rmenu();
		 break;
		  
       	case 3:  printList(root);
	         rmenu();
	         break;

	case 4:  printf("Enter model you want to find: ");
                 scanf("%s",s);
	         p = search(root,s);
		 if(p == NULL) printf("This model is n't in the list.\n");
		 else
		   {
		     printf("\nModel %s 's information:",s);
		     printf("\nMemory: %f G",p->key.memo);
		     printf("\nScreen: %.1f inch.",p->key.screen);
		     printf("\nPrice : %.1f dong.\n",p->key.price*1000);
		   }
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
