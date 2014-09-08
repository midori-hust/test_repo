/*
Viết chương trình xây dựng cây nhị phân từ biểu thức số học dạng hậu tố
Kiểm tra kết quả bằng tính năng duyệt theo thứ tự sau
Tính giá trị biểu thức.
*/

typedef struct node
{
  char key;
  struct node *left;
  struct node *right;
}TreeNode;

typedef TreeNode *ElmType;

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Stack.h"

//==========================================

ElmType makeTreeNode(char key)
{
  ElmType new;
  new = (TreeNode*)malloc(sizeof(TreeNode));
  if(new != NULL)
    {
      new->left = NULL;
      new->right = NULL;
      new->key = key;
    }
  return new;
}

//==========================================

int isLeaf(ElmType T)
{
  if(T != NULL) 
    return (T->left == NULL) && (T->right == NULL);
  else return -1;
}

//==========================================

int isOperator(char c)
{
  if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
    return 1;
  else
    return 0;	
}

//==========================================

void LRN(ElmType T)  
{
  if (T != NULL)
    {
      LRN(T->left);
      LRN(T->right);
      printf("%c ", T->key);
    }
}

//==========================================

ElmType Postfix2ExpressionTree(char *postfix)
{
  int i;
  Stack s;
  newStack(&s);
  ElmType T;
 
  for(i = 0; i < strlen(postfix); i++)
    {
      char kitu = postfix[i];

      if(kitu >= '0' && kitu <= '9')
	push(&s,makeTreeNode(kitu));
      
      if (isOperator(kitu))
        {
	  T = makeTreeNode(kitu);
	  T->right = pop(&s);
	  T->left = pop(&s);
	  push(&s,T);
        }
    }
  return pop(&s);
}

//================================================

float Evaluate(ElmType T)
{
  float t = 0;
  int j;

  if (isLeaf(T))
    t = (float)(T->key - 48);
  else
    {
      float x = Evaluate(T->left);
      float y = Evaluate(T->right);
 
      switch (T->key)
        {
	case '+': t = x + y; break;
	case '-': t = x - y; break;
	case '*': t = x * y; break;
	case '/': t = x / y; break;
	case '^': t = 1;
	          for(j = 0; j < y; j++)
		    t *= x;
		  break;
        }
    }
  return t;
}

//================================================

int menu()
{
  int choice;

  printf("\n\n\t========================");
  printf("\n\tExpression Tree Postfix Program");
  printf("\n\t\t1. Enter the postfix.");
  printf("\n\t\t2. Check with Post-Order print.");
  printf("\n\t\t3. Calulate.");
  printf("\n\t\t4. About Algorithm.");
  printf("\n\t\t5. Quit.");
  printf("\n\t========================");
  printf("\n\tYou choose:.......");
  scanf("%d",&choice);

  return choice;
}

//=================================================

void rmenu()
{
  char ch;

  printf("\nPress any key to continue....");
  getchar();
  scanf("%c",&ch);
}

//=================================================

void about()
{
  printf("\nThuật toán tạo cây biểu thức từ biểu thức postfix:\nLặp qua từng token trong chuỗi postfix\n- Tạo một đối tượng BinaryTreeNode với tên node cho token này\n- Nếu là toán hạng: Push node vào stack\n- Nếu là toán tử:\no Pop một toán hạng ra khỏi stack và đặt làm RightChild của node\no Pop toán hạng kế tiếp ra khỏi stack và đặt làm LeftChild của node\no Push node vào stack\nSau khi vòng lặp kết thúc, phần tử cuối cùng còn lại trong stack là node gốc của cây biểu thức.\n");
}

//====================Ham chinh===================//

main()
{
  char postfix[100];
  int choice,quit = 0;
  ElmType T;
  
  while(quit == 0)
    {
      choice = menu();
      switch(choice)
	{

	case 1:  printf("\nEnter infix(Example: ab+*cde/-):\n");
	         scanf("%s",postfix);
		 rmenu();
		 break;

	case 2: T = Postfix2ExpressionTree(postfix);
	        printf("\nPostfix: ");
		LRN(T);
		rmenu();
		break;

	case 3: printf("\nResult: %.1f\n",Evaluate(T));
	        rmenu();
	        break;

	case 4: about();
	        rmenu();
		break;

	case 5: printf("Have funny time!!\n");
                quit++;
	        break;

	default: printf("Please choose from 1 to 5.\n");

	}
    }
  return 0;
}
