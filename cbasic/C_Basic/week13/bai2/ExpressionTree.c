/*
Viết chương trình Expression Tree sử dụng cây nhị phân tìm kiếm, nhập vào biểu thức số học dạng infix để tạo thành cây biểu thức, sau đó chuyển thành dạng hậu tố bằng cách duyệt cây theo kiểu sau(LRN) rồi tính giá trị biểu thức hậu tố đó.
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

int uutien(char op)
{
  if(op == '^')
    return 2;
  if(op == '*'|| op == '/')
    return 1; 
  if(op == '+'|| op == '-') 
    return 0; 
  if(op == '('|| op == ')') 
    return -1;
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

ElmType Infix2ExpressionTree(char *infix)
{
  Stack opStack,nodeStack;
  int i;
  ElmType T;

  newStack(&opStack);
  newStack(&nodeStack);
  
  for(i = 0; i < strlen(infix); i++)
    {
      char kitu = infix[i];
      
      if(kitu >= '0' && kitu <= '9')
	push(&nodeStack,makeTreeNode(kitu));
      
      if (kitu == '(')
	push(&opStack,makeTreeNode(kitu)); 
      
      if (kitu == ')')
        {
	  while (1)
	    {
	      T = pop(&opStack);
	      if(T->key == '(') break;
	      T->right = pop(&nodeStack);
	      T->left = pop(&nodeStack);
	      push(&nodeStack,T);
	    }
        }
      
      if (isOperator(kitu))
        {
	  while(!empty(opStack) && uutien(top(&opStack)->key) >= uutien(kitu))
	    {
	      T = pop(&opStack);
	      T->right = pop(&nodeStack);
	      T->left = pop(&nodeStack);
	      push(&nodeStack,T);
	    }
	  push(&opStack,makeTreeNode(kitu));
        }
    }
  
  while (!empty(opStack))
    {
      T = pop(&opStack);
      T->right = pop(&nodeStack);
      T->left = pop(&nodeStack);
      push(&nodeStack,T);
    }

  return pop(&nodeStack);
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
  printf("\n\tExpression Tree Program");
  printf("\n\t\t1. Enter the infix.");
  printf("\n\t\t2. Change to postfix.");
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
  printf("\nThuật toán tạo cây biểu thức này yêu cầu sử dụng 2 stack:\n- OperatorStack: chứa các toán tử\n- NodeStack: chứa các node tạo nên cấu trúc cây (node gốc của các cây con được xây dựng từ dưới lên).\nCác bước tiến hành thuật toán:\n\nTạo một phương thức phụ CreateSubTree() có nhiệm vụ tạo một cây biểu thức gồm 3 node. Node gốc là toán tử Pop ra từ OperatorStack, hai node lá là toán hạng Pop từ NodeStack. Cuối cùng đưa node gốc vào lại NodeStack.\nLặp qua từng token trong biểu thức infix\n- Nếu là toán hạng: push vào NodeStack\n- Nếu là dấu mở ngoặc “(“: push vào OperatorStack\n- Nếu là dấu đóng ngoặc “)”:\no Lặp cho đến khi lấy được dấu mở ngoặc “(“ trong OperatorStack, mỗi lần lặp gọi phương thức CreateSubTree().\no Pop dấu mở ngoặc ra khỏi OperatorStack.\n- Nếu là toán tử:\no Lặp cho đến khi OperatorStack rỗng hoặc độ ưu tiên của toán tử ở đỉnh OperatorStack nhỏ hơn độ ưu tiên của toán tử hiện tại. Mỗi lần lặp gọi phương thức CreateSubTree().\no Push toán tử vào OperatorStack.\nKhi hết vòng lặp, nếu OperatorStack còn phần tử, gọi phương thức CreateSubTree() cho đến khi OperatorStack rỗng.\nNode cuối cùng nằm trong NodeStack là node gốc của cây.\n");
}

//====================Ham chinh===================//

main()
{
  char infix[100];
  int choice,quit = 0;
  ElmType T;
  
  while(quit == 0)
    {
      choice = menu();
      switch(choice)
	{

	case 1:  printf("\nEnter infix(Example: (a+b)*c-d/e):\n");
	         scanf("%s",infix);
		 rmenu();
		 break;

	case 2: T = Infix2ExpressionTree(infix);
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
