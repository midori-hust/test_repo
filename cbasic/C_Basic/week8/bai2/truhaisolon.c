/*
Viết chương trình trừ số nguyên dương khổ lớn sử dụng stack.
 */

typedef int ElmType;

#include<stdio.h>
#include<string.h>
#include"Stack.h"

//===================================

int bigger(char s1[], char s2[])                 // So sánh số nào lớn hơn
{ 
  int i;

  if (strlen(s1) > strlen(s2))  
    return 1; 
  else 
    if (strlen(s1) == strlen(s2)) 
      {  
	for (i = 0; i < strlen(s1); i++) 
	  { 
	    if (s1[i] > s2[i]) return 1; 
	    
	    if (s1[i] < s2[i]) return 0; 
	  } 
      } 
  return 0; 
} 

//===================================

Stack tru(char s1[],char s2[])
{
  Stack big,small,result;
  int i, memo = 0, x, y; 

  newStack(&big);
  newStack(&small);
  newStack(&result);

  for(i = 0; i < strlen(s1); i++)
    push(&big,s1[i] - 48);
  for(i = 0; i < strlen(s2); i++)
    push(&small,s2[i] - 48);

  while (!empty(big) || !empty(small))
    { 
      x = empty(big) ? 0 : pop(&big); 
      y = empty(small) ? memo : (pop(&small) + memo); 

      if (x < y) 
	{ 
	  x += 10; 
	  memo = 1; 
	} 
      else memo = 0;

      push(&result,x - y); 
    } 

   if(top(&result) == 0) 
     pop(&result);
  
  return result;
}

//==============Ham chinh=============//

main()
{
  char s1[100];
  char s2[100];
  char choice;
  Stack r;
  
  printf("\n\tChuong trinh tru 2 so nguyen duong lon\n\n");
  printf("Nhap so thu nhat: ");
  scanf("%s",s1);
  
  printf("Nhap so thu hai:  ");
  scanf("%s",s2);

  if(bigger(s1,s2) > 0)
    {
      r = tru(s1,s2);
      printf("Ket qua la:       ");
      while(!empty(r)) printf("%d",pop(&r));
      printf("\n");
    }
  else
    {
      r = tru(s2,s1);
      printf("Ket qua la:      -");
      while(!empty(r)) printf("%d",pop(&r));
      printf("\n");
    }

  printf("\nBan co muon tiep tuc[y/n]?..");
  scanf("%s",&choice);
  if(choice == 'y' || choice == 'Y')
    {
      getchar();
      main();
    }
  return 0;
}
