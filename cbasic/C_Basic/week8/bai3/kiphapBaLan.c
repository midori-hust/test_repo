/*
Viết chương trình Kí pháp Ba Lan chuyển đổi biểu thức số học nhập vào thành biểu thức dạng hậu tố bằng stack sau đó tính giá trị biểu thức hậu tố đó.
*/

typedef char ElmType;

#include<stdio.h>
#include<string.h>
#include"Stack.h"

//=======================

int uutien(char op)
{
  if(op == '^')
    return 2;
  if(op == '*'|| op == '/')
    return 1; 
  if(op == '+'|| op == '-') 
    return 0; 
  if(op == '(' || op == ')')
    return -1;
}

//========================

int isOperator(char c)
{
  if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
    return 1;
  else
    return 0;	
}

//================================

void inFix_to_postFix(char *infix, char *postfix)
{
  Stack s;
  newStack(&s);
  int i;
  int j = 0;
  char kitutam;
  
  for(i = 0; i < strlen(infix); i++)
    {
      char kitu = infix[i];

      if(kitu >= '0' && kitu <= '9')
	postfix[j++] = kitu;
     
      if(kitu == '(')   
	push(&s,'(');
      
      if(kitu == ')')
	{
	  while(1) 
	    {
	      kitutam = pop(&s);
	      if (kitutam == '(') break;
	      postfix[j++] = kitutam;
	    } 
	}    
      
      if (isOperator(kitu))
	{
	  while(!empty(s) && uutien(top(&s)) >= uutien(kitu))
	    {
	      kitutam = pop(&s);
	      postfix[j++] = kitutam;
	    }
	  push(&s,kitu);
	}	
    }

  while(!empty(s))
    {
      kitutam = pop(&s);
      postfix[j++] = kitutam;
    }
  
  postfix[j++]='\0';
}

//==============================

float caculate(char *postfix)
{
  int i,j;
  float result;
  Stack s;
  char c;

  newStack(&s);
  
  for (i = 0; i < strlen(postfix); i++)
    {
      c = postfix[i];
      if (!isOperator(c)) 
	push(&s,c - 48);
      else
	{
	  float second = pop(&s);
	  float first  = pop(&s);
	  
	  switch(c)
	    {
	    case '+': result = first + second;break;
	    case '-': result = first - second;break;
	    case '*': result = first * second;break;
	    case '/': result = first / second;break;
	    case '^': result = 1;
	              for(j = 0; j < second; j++)
			result *= first;
		      break;
	    }	  
	  push(&s,result);
	}
    }
  return pop(&s);
}

//================================================

int menu()
{
  int choice;

  printf("\n\n\t========================");
  printf("\n\tInfix to Postfix Program");
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
  printf("\nThuật toán để chuyển một biểu thức Infix sang dạng Prefix:");
  printf("\n* Đọc từng phần tử trong biểu thức infix từ trái qua phải, với mỗi phần tử ta thực hiện các bước sau:\n- Nếu là toán hạng: cho ra output.\n + Nếu là dấu mở ngoặc \"(\": cho vào stack\n + Nếu là dấu đóng ngoặc \")\": lấy các toán tử trong stack ra và cho vào output cho đến khi gặp dấu mở ngoặc \"(\". (Dấu mở ngoặc cũng phải được đưa ra khỏi stack).\n- Nếu là toán tử:\n+ Chừng nào ở đỉnh stack là toán tử và toán tử đó có độ ưu tiên lớn hơn hoặc bằng toán tử hiện tại thì lấy toán tử đó ra khỏi stack và cho ra output.\n+ Đưa toán tử hiện tại vào stack.\n* Sau khi duyệt hết biểu thức infix, nếu trong stack còn phần tử thì lấy các phần tử trong đó ra và cho lần lượt vào output.\n");
}

//===============Ham chinh==============//

main()
{
  char infix[100];
  char postfix[100];
  int choice,quit = 0;

  while(quit == 0)
    {
      choice = menu();
      switch(choice)
	{

	case 1:  printf("\nEnter infix: ");
                 scanf("%s",infix);
		 rmenu();
		 break;

	case 2: inFix_to_postFix(infix,postfix);
	        printf("\nPostfix: %s\n",postfix);
		rmenu();
		break;

	case 3: printf("\nResult: %.1f\n",caculate(postfix));
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
