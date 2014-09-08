#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct user_			//ban ghi nguoi dung
{
  char name[1024];
  char pwd[1024];
  struct user_ *next;
}user;

typedef struct indexarray_		//cau truc mang bam
{
  struct user_*header;
}indexarray;
void initarr(indexarray arr[])		//khoi tao
{
  int i;
  for(i=0;i<=25;i++)
    {
      arr[i].header=NULL;
    }
}

int emptyindex(indexarray arr[],int i)		//kiem tra mang bam rong
{
  return (arr[i].header==NULL);
}
int changeindex(char a[])
{
  if(a[0]>='A'&&a[0]<='Z')
    {
      return a[0]-'A';
    }
  else
    {
      return a[0]-'a';
    }
}
struct user_* makeuser(char a[],char b[])	//tao mot nguoi dung moi
{
  struct user_*new=(struct user_*)malloc(sizeof(struct user_));
  strcpy(new->name,a);
  strcpy(new->pwd,b);
  new->next=NULL;
  return new;
}
struct user_* search(indexarray arr[],char a[])		//tim kiem
{
  user*cur;
  int k;
  k=changeindex(a);
  if(emptyindex(arr,k)) return NULL;
  for(cur=(arr[k].header);cur!=NULL&&strcmp(cur->name,a)<=0;cur=cur->next)
    {
      if(strcmp(cur->name,a)==0) return cur;
    }
  return NULL;
}
void add(indexarray arr[],struct user_*new)		//them mot nguoi dung
{
  char temp1[1024],temp2[1024];
  int k;
  user*cur,*prev;
  k= changeindex(new->name);
  if(emptyindex(arr,k))
    {
      arr[k].header=new;
    }
  else
    {
      for(cur=arr[k].header;cur!=NULL&&strcmp(cur->name,new->name)<0;cur=cur->next);
      if(cur==arr[k].header)
	{
	  arr[k].header=new;
	  new->next=cur;
	}
      else if(cur==NULL)
	{
	  for(prev=arr[k].header;prev->next!=NULL;prev=prev->next);
	  prev->next=new;
	}
      else
	{
	  strcpy(temp1,cur->name);
	  strcpy(temp2,cur->pwd);
	  strcpy(cur->name,new->name);
	  strcpy(cur->pwd,new->pwd);
	  strcpy(new->name,temp1);
	  strcpy(new->name,temp2);
	  new->next=cur->next;
	  cur->next=new;
	}
    }
}
void nhaptufile(FILE*f1,indexarray arr[])	//them danh sach nguoi dung tu file
{
  char *p;
  char s[2048];
  char name[1024];
  char pwd[1024];
  user*new;
  while(fgets(s,2048,f1)!=NULL)
    {
      p=strtok(s," ");
      if(p==NULL) break;
      strcpy(name,p);
      p=strtok(NULL,"\n");
      if(p==NULL) break;
      strcpy(pwd,p);
      new=makeuser(name,pwd);
      add(arr,new);
    }
}
void printds(indexarray arr[])			//in toan bo danh sach
{
   int i;
   user*cur;
   for(i=0;i<26;i++)
	{
		for(cur=arr[i].header;cur!=NULL;cur=cur->next)
		{
			printf("%s %s\n",cur->name,cur->pwd);
		}
	}
}
void freeds(indexarray arr[])			//giai phong toan bo danh sach
{
   int i;
   user*cur;
   for(i=0;i<26;i++)
	{
	 	while(arr[i].header!=NULL)
		{
			cur=arr[i].header;
			arr[i].header=arr[i].header->next;
			free(cur);
		}
	}
}



