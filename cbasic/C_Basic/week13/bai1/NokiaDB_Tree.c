/*
Phát triển chương trình NokiaDB sử sụng cây nhị phân tìm kiếm. Khóa của 1 nút là cấu trúc điện thoại Nokia bao gồm: model, bộ nhớ, màn hình, giá.
Chương trình menu có các chức năng sau:
+ Import dữ liệu từ NokiaDB.dat
+ Thêm 1 mobile
+ Xóa 1 mobile
+ Cập nhật 1 mobile
+ Tìm kiếm 1 mobile
+ Duyệt trước
+ Duyệt giữa
+ Duyệt sau
+ Duyệt theo chiều rộng
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
#include<string.h>
#include<stdlib.h>
#include"BST.h"
#include"QueueTree.h"

//==========================

ElmType makeData()
{
  ElmType key;

  getchar();
  printf("\nMobile infomation:\n");
  printf("+ Model: ");  
  scanf("%[^\n]",key.model);  getchar();
  printf("+ Memory: ");scanf("%f",&key.memo);
  printf("+ Screen: ");scanf("%f",&key.screen);
  printf("+ Price: ");scanf("%f",&key.price);

  return key;
}

//===========================================

void addOrder(Tree *T, ElmType x)
{
  if(*T == NULL)
    *T = makeTreeNode(x);  
  else
    if (strcmp((*T)->key.model,x.model) > 0) 
      return addOrder(&(*T)->left,x);
    else if(strcmp((*T)->key.model,x.model) < 0) 
      return addOrder(&(*T)->right,x);
}

//===========================================

ElmType DeleteLeaf(Tree *T)
{ 
  ElmType k; 
  if ((*T)->left == NULL)
    { 
      k = (*T)->key; 
      (*T) = (*T)->right; 
      return k; 
    } 
  else return DeleteLeaf(&(*T)->left); 
}

//===========================================

void DeleteNode(Tree *T, char *s)
{ 
  if (*T != NULL) 
    if(strcmp((*T)->key.model,s) > 0) 
      DeleteNode(&(*T)->left,s);
      else 
	if (strcmp((*T)->key.model,s) < 0) 
	  DeleteNode(&(*T)->right,s);
	  else 
	    if(((*T)->left == NULL) && ((*T)->right == NULL))
	      *T = NULL; 
	    else 
	      if ((*T)->left == NULL)
		*T = (*T)->right; 
	      else 
		if ((*T)->right == NULL) 
		  *T = (*T)->left; 
		else (*T)->key = DeleteLeaf(&(*T)->right); 
} 

//===========================================

Tree search(Tree T, char *s)
{ 
  if (T == NULL) 
    return NULL;
  else 
    if (strcmp(T->key.model,s) == 0) 
      return T;
     else 
       if (strcmp(T->key.model,s) < 0)
	 return search(T->right,s); 
       else 
	 return search(T->left,s); 
}

//===========================================

int menu()
{
  int choice;

  printf("\n\n\t========================");
  printf("\n\tNokiaDB menu");
  printf("\n\t\t1.  Import from NokiaDB.dat.");
  printf("\n\t\t2.  Add a new mobile.");
  printf("\n\t\t3.  Delete a mobile.");
  printf("\n\t\t4.  Search by model.");
  printf("\n\t\t5.  Update a model.");
  printf("\n\t\t6.  In-Order print.");
  printf("\n\t\t7.  Pre-Order print.");
  printf("\n\t\t8.  Post-Order print.");
  printf("\n\t\t9.  BFS print.");
  printf("\n\t\t10. Save to file.");
  printf("\n\t\t11. Exit.");
  printf("\n\t========================");
  printf("\n\tYou choose:.......");
  scanf("%d",&choice);

  return choice;
}

//============================================

void printTree(Tree T)
{ 
  printf("%-20s%-15.2f%-20.1f%-15.1f\n",T->key.model,T->key.memo,T->key.screen,T->key.price*1000);
}

//============================================

void LNR(Tree T)  
{
  if (T != NULL)
  {
    LNR(T->left);
    printTree(T);
    LNR(T->right);
  }
}

//============================================

void NLR(Tree T)  
{
  if (T != NULL)
  {
    printTree(T);
    NLR(T->left);
    NLR(T->right);
  }
}

//============================================

void LRN(Tree T)  
{
  if (T != NULL)
  {
    LRN(T->left);
    LRN(T->right);
    printTree(T);
  }
}

//============================================

void save(Tree T, FILE *f)  
{
  if (T != NULL)
  {
    save(T->left,f);
    fwrite(&T->key,sizeof(ElmType),1,f);
    save(T->right,f);
  }
}

//============================================

void breadthFirst(Tree T)
{
   Queue queue;	
   newQueue(&queue);

   if (T != NULL) 
     {
       enQueue(&queue,T);
       while (!emptyQueue(queue)) 
	 {
	   T = deQueue(&queue);
	   printTree(T);
	   if (T->left != NULL)
             enQueue(&queue,T->left);
	   if (T->right != NULL)
	     enQueue(&queue,T->right);
         }
     }
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
  Tree T = newTree(), p;
  int quit = 0, choice;
  int i,n = 0;
  ElmType x;
  char s[20],ch;

  while(quit == 0)
    {
      choice = menu();
      switch(choice)
	{

	case 1:  if((f = fopen("NokiaDB.dat","rb")) == NULL)
	         printf("Cannot open file %s.\n","NokiaDB.dat");
	         else
		   { 
		     while(1)
		       {
			 fread(&x,sizeof(ElmType),1,f);
			 if(feof(f)) break;
			 addOrder(&T,x);
			 n++;
		       }
		     printf("\nRead data from file %s successfully!\n","NokiaDB.dat");
		   }
	         fclose(f);
		 rmenu();
		 break;

	case 2:  addOrder(&T,makeData());
		 rmenu();
		 break;

	case 3:  printf("The model you want to delete: ");
	         scanf("%s",s);
 
		 if(search(T,s) != NULL)
		   {
		     getchar();
		     printf("\nDo you wan to delete model %s? (y/n): ",s);
		     scanf("%c",&ch);
		     if(ch == 'y' || ch == 'Y')
		       {
			 DeleteNode(&T,s);
			 printf("\nModel %s 's been deleted.\n",s);
		       }
		   }
		 else 
		   printf("\nModel %s is not in the list.\n",s);
		 rmenu();
		 break;

	case 4:  printf("Enter model you want to find: ");
                 scanf("%s",s);
	         p = search(T,s);
		 if(p == NULL) 
		   printf("This model is n't in the list.\n");
		 else
		   {
		     printf("\nModel %s 's information:",s);
		     printf("\nMemory: %f G",p->key.memo);
		     printf("\nScreen: %.1f inch.",p->key.screen);
		     printf("\nPrice : %.1f dong.\n",p->key.price*1000);
		   }
		 rmenu();
		 break;
		 
	case 5:  printf("Enter model you want to update: ");
                 scanf("%s",s);
	         p = search(T,s);
		 if(p == NULL) 
		   printf("This model is n't in the list.\n");
		 else
		   {
		     printf("\nModel %s 's information:\n",s);
		     printf(" + Memory: "); scanf("%f",&p->key.memo);
		     printf(" + Screen: "); scanf("%f",&p->key.screen);
		     printf(" + Price : "); scanf("%f",&p->key.price);
		   }
		 rmenu();
		 break;

	case 6:  LNR(T);
		 rmenu();
		 break;

	case 7:  NLR(T);
		 rmenu();
		 break;
		 
	case 8:  LRN(T);
		 rmenu();
		 break;
		 
	case 9: breadthFirst(T);
		rmenu();
		break;

	case 10: f = fopen("NokiaDB.dat","wb");
	         save(T,f);
		 printf("\nSave to file successfully!\n");
		 fclose(f);
		 rmenu();
		 break;

	case 11: printf("Have funny time!!\n");
	         freeTree(T);
		 quit++;
		 break;   

	default:  printf("Choose from 1 to 11.\n");

        }
    }
  return 0;
}
