/*Description:
Xay dung chuong trinh Task Manager quan ly cac tien trinh trong may tinh.
  - Dung mot mang luu tru danh sach cac tien trinh dang chay.
  - Tao them cac tien trinh, neu tien trinh tao trung ten voi tien trinh dang chay thi cho tien trinh do' vao queue.
  - Kill 1 tien trinh dang chay. Chuong trinh tu dong lay 1 tien trinh dau tien o queue de chay.
*/

typedef struct
{
  char name[30];
  float memo;
  int status;
}Program;

typedef Program ElementType;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"

#define memMax 50

//============================================

ElementType makeData()
{
  ElementType key;
  
  printf("\n----------\n");
  printf("Name: ");
  getchar();
  scanf("%[^\n]",key.name);

  while(1)
    {
      printf("Memmory( <= 50 mb): ");
      scanf("%f", &key.memo);
      if(key.memo > memMax) 
	{
	  printf("Memory is too large. Try again!\n");
	  continue;
	}
      else break;
    }
     
  return key;
}

//===========================================

void status_t(int stt, char *s)
{
  switch(stt)
    {
    case 0: strcpy(s,"Stopped");break;
    case 1: strcpy(s,"Running");break;
    case 2: strcpy(s,"Waiting");break;
    }
}

//===========================================

int search(ElementType a[],int n,char *s)
{
  int i;
  for(i = 0; i < n; i++)
    if(strcmp(a[i].name,s) == 0)
      return i;
  return -1;
}

//===========================================

int menu()
{
  int choice;
  printf("\n\n\t========================");
  printf("\n\tComputer Task Manager");
  printf("\n\t\t1. Insert a new process.");
  printf("\n\t\t2. Display.");
  printf("\n\t\t3. Kill a process.");
  printf("\n\t\t4. Exit.");
  printf("\n\t========================");
  printf("\n\tYou choose:.......");
  scanf("%d",&choice);
  return choice;
}

//===========================================

void rmenu()
{
  char ch;
  printf("\nPress any key to continue....");
  getchar();
  scanf("%c",&ch);
}

//===============Ham chinh==============//

main()
{
  int choice, quit = 0;
  ElementType runList[100],x,y;
  Queue waitList,tmp;
  char s[100];
  int n = 0,res,i = 0;

  newQueue(&waitList);
  newQueue(&tmp);

  while(quit == 0)
    {
      choice = menu();
      
      switch(choice)
	{

	case 1: printf("Insert a new process:");
	        x = makeData();
		res = search(runList,n,x.name);
		if(res == -1) 
		  {
		    x.status = 1;
		    runList[n++] = x;
		  }
		else
		  {
		    printf("The same process is running. This process is in queue.\n");
		    x.status = 2;
		    enQueue(&waitList,x);
		  }		  
		rmenu();
		break;
		
	case 2:  printf("%-15s%-10s%-15s\n", "NAME", "MEMORY", "STATUS");
	         for(i = 0; i < n; i++)
		   {
		     status_t(runList[i].status,s);
		     printf("%-15s%-10.1f%-10s\n", runList[i].name, runList[i].memo, s);
		   }
		 
		 while (!emptyQueue(waitList))
		   {
		     x = deQueue(&waitList);
		     enQueue(&tmp,x);
		     status_t(x.status,s);
		     printf("%-15s%-10.1f%-10s\n", x.name, x.memo, s);
		   }

		 while (!emptyQueue(tmp))
		   {
		     y = deQueue(&tmp);
		     enQueue(&waitList,y);
		   }

		 rmenu();
		 break;

	case 3: printf("The process you want to kill: ");
		scanf("%s",s);
	        while((res = search(runList,n,s)) == -1)
		  {
		    printf("Cannot find process %s in the list.\n",s);
		    printf("\nThe process you want to kill: ");
		    scanf("%s",s);
		  }

		runList[res].status = 0;
		runList[res].memo = 0;
		if(!emptyQueue(waitList))
		  x = deQueue(&waitList);
		x.status = 1;
		runList[n++] = x;

		rmenu();
		break;

	case 4: printf("Have funny time!!\n");
                quit++;
	        break;

	default: printf("Choose from 1 to 4.\n");

	}
    }
  return 0;
}
