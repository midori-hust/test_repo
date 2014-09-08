#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supportLib.h"
/*#include<gtk/gtk.h>
void setBackGround(GtkWidget *widget,char cl[])
{
  GdkColor color;
  gdk_color_parse (cl, &color);//"#A3B07C"
  gtk_widget_modify_bg (widget, GTK_STATE_NORMAL, &color);
}*/
void printQuestion(char s[])
{
  int i,len;
  char temp[1024];
  strcpy(temp,s);
  len=strlen(s);
  for(i=0;i<len;i++)
    {
      if(temp[i]=='*')
	temp[i]='\n';
    }
  printf("%s \n",temp) ;
}
NamePass* getNamePassFromFile(char *fileName,int *total)
{
  FILE *fp;
  char* s;
  NamePass* dt;
  int i,j=0,k;
  dt=(NamePass*)malloc(sizeof(NamePass)*100);
  s=(char*)malloc(sizeof(char)*100);
  fp=fopen(fileName,"r");
  if(fp==NULL)
    {
      printf("ERROR REGISTER FILE: %s\n",fileName);
      return NULL;
    }
  while(fgets(s,100,fp)!=NULL)
    {
      s[strlen(s)-1]='\0';
      for(i=0;k!=1;i++)
	{
	  if(s[i]=='+')
	    {
	      s[i]='\0';
	      strcpy(dt[j].name,s);
	      strcpy(dt[j].pass,s+i+1);
	      //printf("%s %s %d\n",dt[j].name,dt[j].pass,j);
	      k=1;
	    }
	}
      k=0;
      j++;
      s=(char*)malloc(sizeof(char)*100);
    }
  //total=(int*)malloc(sizeof(int));
  *total=j;
  fclose(fp);
  return dt;
}
QA* getQAFromFile(char *fileName,int *total)
{
  FILE *fp;
  char* s,str[10];
  QA* dt;
  int i,j=0,k;

  dt=(QA*)malloc(sizeof(QA)*100);
  s=(char*)malloc(sizeof(char)*100);
  fp=fopen(fileName,"r");
  if(fp==NULL)
    {
      printf("ERROR REGISTER FILE: %s\n",fileName);
      return NULL;
    }
  while(fgets(s,100,fp)!=NULL)
    {
      s[strlen(s)-1]='\0';
      if(strcmp(s,"P1_")==0 || strcmp(s,"P2_")==0)
	{
	  strcpy(dt[j].p,s);
	}
      if(strcmp(s,"Q_")==0)
	{
	  k=1;
	  strcpy(dt[j].question,s);
	  sprintf(str,"%d",j);
	  strcat(dt[j].question,str);
	  strcat(dt[j].question,". ");
	}
      if(strcmp(s,"A_")==0)
	{
	  k=2;
	}
      if(strcmp(s,"Q_")!=0 && k==1)
	{
	  strcat(dt[j].question,"*");
	  strcat(dt[j].question,s);
	  //strcat(dt[j].question,"\n");
	}
      
      if(strcmp(s,"A_")!=0 && k==2)
	{
	  strcpy(dt[j].ans,s);
	  j++;
	  k=0;
	}
      s=(char*)malloc(sizeof(char)*100);
   
    }
  //total=(int*)malloc(sizeof(int));
  *total=j;
  fclose(fp);
  return dt;
}
int compareForRegister(NamePass us,NamePass *dt,int total)
{
  int i;
  for(i=0;i<total;i++)
    {
      if(strcmp(us.name,dt[i].name)==0)
	{
	  return 0;//duplicate
	}
    }
  return 1;//OK
}
int compareForLogin(NamePass us,NamePass *dt,int total)
{
  int i;
  for(i=0;i<total;i++)
    {
      if(strcmp(us.name,dt[i].name)==0 && strcmp(us.pass,dt[i].pass)==0)
	{
	  return 1;//OK
	}
    }
  return 0;//Not Match
}
int registerToFile(char *fileName,NamePass us)
{
  FILE *fp;
  char s[50];
  fp=fopen(fileName,"a+");
  if(fp==NULL)
    {
      printf("ERROR! Can not open register file to register!\n");
      return 0;
    }
  strcpy(s,us.name);
  strcat(s,"+");
  strcat(s,us.pass);
  strcat(s,"\n");
  fprintf(fp,"%s",s);
  fclose(fp);
  return 1;
}
User* userLogedIn(NamePass us,int FD,User *listUs,int *total)
{
  int i,j;
  i=*total;
  for(j=0;j<i;j++)
    {
      if(listUs[j].FD==FD||strcmp(listUs[j].name,us.name)==0)
	{
	  listUs[j].lost=1;
	  printf("return day\n");
	  return listUs;
	}
    }
  listUs[i].FD=FD;
  strcpy(listUs[i].name,us.name);
  listUs[i].lost=1;
  i++;
  *total=i;
  return listUs;
}
