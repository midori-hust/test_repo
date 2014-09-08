#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct
{
  char id[10];
  char name[50];
  char pass[50];
}account;
int main()
{
  char tempt[1024];
  account acclist[100];
  FILE *f = fopen("list.txt","r");
  int i = 0;
  int j = 0;
  int accnum = 0;
  // while(getchar() != '\n');
  f=fopen("list.txt","r");
  while(fgets(tempt,50,f)!=NULL)
    {
      if(j==0) 
	{
	  tempt[strlen(tempt)-1]='\0';
 	  strcpy(acclist[accnum].id,tempt);
	  j=1;
	}
      else if (j==1)
	{
	  tempt[strlen(tempt)-1]='\0';
	  strcpy(acclist[accnum].name,tempt);
	  j=2;
	}
      else 
	{
	  tempt[strlen(tempt)-1]='\0';
	  strcpy(acclist[accnum].pass,tempt);
	  j=0;
	  accnum++;
	}
    }
    fclose(f);
    for(j=0;j<accnum;j++)
      {
	printf("ID:%s\nName:%s\nPass:%s\n",acclist[j].id,acclist[j].name,acclist[j].pass);
      }
    return 0;
}
