/* Cau 27: */
/* Kiem tra xau Palindromes, su dung stack va queue. */

#include "queue.h"
#include "stack.h"

char stack[MAXLENGTH];
int top = 0;

int main()
{
  Queue Q;
  char str[MAXLENGTH];
  char ch, ch1;
  int n = 0;
  int i;
  int flag = 0;

  MakeNull_Queue(&Q);
  printf("Xin hay nhap vao 1 xau de kiem tra xau do co phai xau Palindromes khong:\n");
  
  while((ch = getchar()) != '\n')
    {
      EnQueue(ch, &Q);
      push(&ch);
      n++;
    }

  for(i=0; i<n; i++)
    {
      DeQueue(&ch, &Q);
      pop(&ch1);
      if(ch != ch1)
	{
	  flag = 1;
	  break;
	}
      flag = 0;
    }
  if(flag == 0)
    printf("Xau da cho la xau Palindromes.\n");
  else
    printf("Xau da cho khong phai la xau Palindromes.\n");

  return 0;
}
