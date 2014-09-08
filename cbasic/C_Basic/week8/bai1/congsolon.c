/*
Viết chương trình cộng số nguyên dương khổ lớn sử dụng stack.
*/

typedef int ElmType;

#include<stdio.h>
#include"Stack.h"

main()
{
  Stack s1,s2,s3;
  int c,x,y;
  int result = 0,memo = 0;
  char choice;

  newStack(&s1);
  newStack(&s2);
  newStack(&s3);
  
  printf("\n\tChuong trinh cong 2 so nguyen duong lon\n");
  printf("\nNhap so thu nhat: ");
  while((c = getchar())!= '\n')
    push(&s1,c-48);

  printf("Nhap so thu hai:  ");
  while((c = getchar())!='\n')
    push(&s2,c-48);
  
  while(!empty(s1) || !empty(s2))
    {
      x = (empty(s1)) ? 0 : pop(&s1); 
      y = (empty(s2)) ? 0 : pop(&s2); 

      result = x + y + memo;

      push(&s3,result % 10); 
      memo = result / 10; 
    }
  if(memo != 0)  push(&s3,memo);
  
  printf("Ket qua la:       ");
  while(!empty(s3)) printf("%d",pop(&s3));
  printf("\n");

  printf("\nBan co muon tiep tuc[y/n]?..");
  scanf("%s",&choice);
  if(choice == 'y' || choice == 'Y')
    {
      getchar();
      main();
    }
  return 0;
}
