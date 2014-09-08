#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<conio.h>
#include "bai2.h"
void initds(dssv* ds)
{
  ds->header=NULL;
}
void initarr(indexarray arr[])
{
  int i;
  for(i=0;i<=19;i++)
    {
      arr[i].header=NULL;
    }
}
int emptyds(dssv ds)
{
  return (ds.header==NULL);
}
int emptyindex(indexarray arr[],int i)
{
  return (arr[i].header==NULL);
}
struct sinhvien_* makesv(int a,char b[],char c[],char d[])
{
  struct sinhvien_*new=(struct sinhvien_*)malloc(sizeof(struct sinhvien_));
  new->studentID=a;
  strcpy(new->name,b);
  strcpy(new->class,c);
  strcpy(new->department,d);
  new->next=NULL;
  return new;
}
struct sinhvien_* searchID(indexarray arr[],int a)
{
  sinhvien *cur;
  int k;
  k=a%20;
  if(emptyindex(arr,k)) return NULL;
  for(cur=(arr[k].header);cur!=NULL&&(cur->studentID%20)==k;cur=cur->next)
    {
      if(cur->studentID==a) return cur;
    }
  return NULL;
}
int searchByName(dssv ds,char a[],sinhvien*temp)
{
  sinhvien*cur;
  int i=0;
  for(cur=ds.header;cur!=NULL;cur=cur->next)
    {
      if(strcmp((cur->name),a)==0)
	i++;
    }
  temp=(sinhvien*)malloc(sizeof(sinhvien)*i);
  i=0;
  for(cur=ds.header;cur!=NULL;cur=cur->next)
    {
      if(strcmp((cur->name),a)==0)
	temp[i++]=(*cur);
    }
  return i;
}
int searchByDepartment(dssv ds,char a[],sinhvien*temp)
{
  sinhvien*cur;
  int i=0;
  for(cur=ds.header;cur!=NULL;cur=cur->next)
    {
      if(strcmp((cur->department),a)==0)
	i++;
    }
  temp=(sinhvien*)malloc(sizeof(sinhvien)*i);
  i=0;
  for(cur=ds.header;cur!=NULL;cur=cur->next)
    {
      if(strcmp((cur->department),a)==0)
	temp[i++]=(*cur);
    }
  return i;
}
int searchByClass(dssv ds,char a[],sinhvien*temp)
{
  printf("Ten\n");
  sinhvien*cur;
  int i=0;
  for(cur=ds.header;cur!=NULL;cur=cur->next)
    {
      if(strcmp((cur->class),a)==0)
	i++;
      printf("%d\n",i);
    }
  printf("%d\n",i);
  temp=(sinhvien*)malloc(sizeof(sinhvien)*i);
  i=0;
  for(cur=ds.header;cur!=NULL;cur=cur->next)
    {
      if(strcmp((cur->class),a)==0)
	temp[i++]=(*cur);
    }
  return i;
}
int delete(dssv*ds,indexarray arr[],int id)
{
  struct sinhvien_*temp=searchID(arr,id);
  struct sinhvien_*cur;
  int k;
  k=id%20;
  if(temp==NULL)
    {
      return 0;
    }
  else
    {
      if(temp==ds->header)
	{
	  ds->header=ds->header->next;
	  if(ds->header->studentID%20==k)  arr[k].header=arr[k].header->next;
	  else arr[k].header=NULL;
	}
      else
	{
	  for(cur=ds->header;cur->next!=temp;cur=cur->next);
	  cur->next=temp->next;
	  if(cur->next->studentID%20==k) arr[k].header=arr[k].header->next;
	  else arr[k].header=NULL;
	}
      free(temp);
    }
  return 1;
}
int addsv(dssv*ds,indexarray arr[],sinhvien*sv)
{
  int k;
  sinhvien*cur,*prev,*temp;
  //  m=sv->studentID;
  if(searchID(arr,sv->studentID)!=NULL) return 0;
  k=sv->studentID%20;
  if(emptyds(*ds)==1)
    {
      ds->header=sv;
      arr[k].header=sv;
    }
  else
    {
      for(temp=ds->header;temp!=NULL&&k>(temp->studentID%20);temp=temp->next);
      if(temp==NULL)
	{
	  for(prev=ds->header;prev->next!=NULL;prev=prev->next);
	  prev->next=sv;
	  arr[k].header=sv;
	}
      else if(temp->studentID%20==k)
	{
	    if(sv->studentID<temp->studentID)
	    {
	      	if(temp==ds->header)
		  {
		    ds->header=sv;
		    sv->next=temp;
		    arr[k].header=sv;
		  }
		else
		  {
		    for(prev=ds->header;prev->next!=temp;prev=prev->next);
		    prev->next=sv;
		    sv->next=temp;
		    arr[k].header=sv;
		  }
	    }
	  else
	    {
	      for(cur=temp;cur!=NULL&&k==(cur->studentID%20)&&cur->studentID<sv->studentID;cur=cur->next);
	      for(prev=temp;prev->next!=cur;prev=prev->next);
	      prev->next=sv;
	      sv->next=cur;
	    }
	}
      else
	{
	  if(temp==ds->header)
	    {
	      ds->header=sv;
	      sv->next=temp;
	      arr[k].header=sv;
	    }
	  else
	    {
	      for(prev=ds->header;prev->next!=temp;prev=prev->next);
	      prev->next=sv;
	      sv->next=temp;
	      arr[k].header=sv;
	    }
	}
    }
  return 1;
}
void freeds(dssv*ds)
{
  sinhvien*cur;
  while(ds->header!=NULL)
  {
    cur=ds->header;
    ds->header=ds->header->next;
    free(cur);
  }
}
void freearr(indexarray arr[])
{
  int i;
  for(i=0;i<=19;i++) arr[i].header=NULL;
}
void inds(dssv ds)
{
  sinhvien*cur;
  int i=0;
  printf("%8s\t%30s\t%10s\t%10s\n","StudentID","Name","Class","Department");
  printf("\n");
  if(emptyds(ds)==1) printf("FUCK!\n");
  for(cur=ds.header;cur!=NULL;cur=cur->next,i++)
    {
      if(i%40==0&&i!=0)
	{
	  printf("An Enter de tiep tuc: ");
	  while(getchar()!='\n');
	  system("clear");
	  printf("\n");	 
	  printf("%8s\t%30s\t%10s\t%10s\n","StudentID","Name","Class","Department");
	  printf("\n");
	}
      printf("%8d\t%30s\t%10s\t%10s\n",cur->studentID,cur->name,cur->class,cur->department);
    }
   printf("An Enter de quay ve menu: ");
   while(getchar()!='\n');
   system("clear");
}
void inbanghi(sinhvien sv[],int n)
{
  int i;
  printf("%8s\t%-30s\t%10s\t%10s\n","StudentID","Name","Class","Department");
  printf("\n");
  for(i=0;i<n;i++)
    {
      if(i%40==0&&i!=0)
	{
	  printf("An Enter de tiep tuc: ");
	  while(getchar()!='\n');
	  system("clear");
	  printf("\n");
	  printf("%8s\t%-30s\t%10s\t%10s\n","StudentID","Name","Class","Department");
	  printf("\n");

	}
      printf("%8d\t%30s\t%10s\t%10s\n",sv[i].studentID,sv[i].name,sv[i].class,sv[i].department);
     }

}
void taodulieu(FILE*f1,dssv*ds,indexarray arr[])
{
  int sid;
  char *p;
  char s[1000];
  char id[10];
  char name[30];
  char class[10];
  char department[10];
  struct sinhvien_*new;
  while(fgets(s,1000,f1)!=NULL)
    {
      p=strtok(s,":");
      if(p==NULL) break;
      strcpy(id,p);
      p=strtok(NULL,":");
      if(p==NULL) break;
      strcpy(name,p);
      if(p==NULL) break;
      p=strtok(NULL,":");
      strcpy(class,p);
      if(p==NULL) break;
      p=strtok(NULL,"\n");
      strcpy(department,p);
      sid=atoi(id);
      new=makesv(sid,name,class,department);
      printf("%d\n",sid);
      printf("%s\n",department);
      addsv(ds,arr,new);
    }
}
void nhaptufile(FILE*f1,dssv *ds,indexarray arr[])
{
  struct sinhvien_*tmp=(struct sinhvien_*)malloc(sizeof(sinhvien));
  struct sinhvien_ *nest;
  while(fread(tmp,sizeof(sinhvien),1,f1)>0)
    {
      //      nest=tmp->next;
      tmp->next=NULL;
      //    nest=tmp->next;
      //     printf("aaa\n");
      addsv(ds,arr,tmp);
    }
  fclose(f1);
}
void xuatfile(dssv ds)
{
  struct sinhvien_*cur;
  FILE*f1=fopen("sinhviens.dat","w+");
  for(cur=ds.header;cur!=NULL;cur=cur->next)
    {
      fwrite(cur,sizeof(sinhvien),1,f1);
    }
  fclose(f1);
}
void themsinhvien(dssv*ds,indexarray arr[])
{
    int a;
    char b[30];
    char c[10];
    char d[10];
    printf("Nhap ID sinh vien muon them: ");
    scanf("%d",&a);
    while(getchar()!='\n');
    printf("Nhap ten: ");
    gets(b);
    printf("Nhap lop: ");
    gets(c);
    printf("Nhap khoa: ");
    gets(d);
    struct sinhvien_*sv=makesv(a,b,c,d);
    if(addsv(ds,arr,sv)==1) printf("Nhap thanh cong\n");
    else printf("ID cua sinh vien bi trung\n");
    printf("An Enter de quay ve menu: ");
    while(getchar()!='\n');
    system("clear");
}
 void timtheoID(indexarray arr[])
 {
   int temp;
   struct sinhvien_*kq;
   printf("Nhap ID can tim: ");
   scanf("%d",&temp);
   while(getchar()!='\n');
   kq=searchID(arr,temp);
   if(kq==NULL)
     {
       printf("Khong co sinh vien can tim\n");
     }
   else inbanghi(kq,1);
   printf("An Enter de quay ve menu: ");
   while(getchar()!='\n');
   system("clear");

 }
void timtudo(dssv ds,int b)
{
  int kq=0;
  int i;
  struct sinhvien_*temp;
  char a[30];
  if(b==0)
    {
      printf("Nhap lop ban muon tim: ");
      gets(a);
      kq=searchByClass(ds,a,temp);
    }
  if(b==1)
    {
      printf("Nhap ten ban muon tim: ");
      gets(a);
      kq=searchByName(ds,a,temp);
    }
  if(b==2)
    {
      printf("Nhap khoa ban muon tim: ");
      gets(a);
      kq=searchByDepartment(ds,a,temp);
    }
  if(kq==0)
    {
      printf("Khong co sinh vien can tim\n");
    }
  else
    {
      inbanghi(temp,kq);
    }
   printf("An Enter de quay ve menu: ");
   while(getchar()!='\n');
   system("clear");
}
void xoasinhvien(dssv*ds,indexarray arr[])
{
  int d,k=0;
  printf("Nhap ID sinh vien ban muon xoa: ");
  scanf("%d",&d);
  while(getchar()!='\n');
  k=delete(ds,arr,d);
  if(k==0)
    {
      printf("Khong co sinh vien co ID nao nhu tren\n");
    }
  else printf("Xoa thanh cong\n");
  printf("An Enter de quay ve menu: ");
  while(getchar()!='\n');
  system("clear");

}
void suasinhvien(dssv*ds,indexarray arr[])
{
  int d;
  char a[30];
  char b[10];
  char c[10];
  int t,k=0;
  printf("Nhap ID sinh vien ban muon sua: ");
  scanf("%d",&t);
  while(getchar()!='\n');
  struct sinhvien_*temp;
  temp=searchID(arr,t);
  if(temp==NULL)
    {
      printf("Khong co sinh vien co ID nao nhu tren\n");
    }
  else
    {
      printf("Sua ID: ");
      scanf("%d",&d);
      if(d==t)
	{
	  delete(ds,arr,t);
	}
      while(getchar()!='\n');
      printf("Sua ten: ");
      gets(a);
      printf("Sua lop: ");
      gets(b);
      printf("Sua khoa: ");
      gets(c);
      struct sinhvien_*sv=makesv(d,a,b,c);
      if(addsv(ds,arr,sv)==1)
	{
	  delete(ds,arr,t);
	  printf("Sua thanh cong\n");
	}
      else printf("ID cua sinh vien sua bi trung\n");
      printf("An Enter de quay ve menu: ");
      while(getchar()!='\n');
      system("clear");
    }
}
int main()
{
  int choice;
  indexarray arr[20];
  dssv ds;
  initds(&ds);
  initarr(arr);
  FILE*f1=fopen("sinhviens.dat","rb");
  if(f1==NULL)
	{
	  f1=fopen("sinhviens.txt","r");
	  if(f1==NULL)
	    {
	      printf("Khong tim thay file du lieu\n");
	      return 0;
	    }
	  taodulieu(f1,&ds,arr);
	}
      else nhaptufile(f1,&ds,arr);
    do
    {
      printf("1. Nhap sinh vien\n");
      printf("2. In danh sach sinh vien\n");
      printf("3. Tim kiem theo studentID\n");
      printf("4. Tim kiem theo ten\n");
      printf("5. Tim kiem theo lop\n");
      printf("6. Tim kiem theo khoa\n");
      printf("7. Xoa sinh vien\n");
      printf("8. Sua thong tin sinh vien\n");
      printf("9. Thoat\n");
      printf("Moi nhap: ");
      scanf("%d",&choice);
      while(getchar()!='\n');
      switch(choice)
	{
    case 1:
      themsinhvien(&ds,arr);
      break;
	case 2:
	  inds(ds);
	  break;
	case 3:
	  timtheoID(arr);
	  break;
	case 4:
	  timtudo(ds,1);
	  break;
	case 5:
	  timtudo(ds,0);
	  break;
	case 6:
	  timtudo(ds,2);
	  break;
	case 7:
	  xoasinhvien(&ds,arr);
	  break;
	case 8:
	  suasinhvien(&ds,arr);
	  break;
	case 9:
	  break;
	default: printf("Nhap sai moi nhap lai\n");
	}
    }
    while(choice!=9);
    xuatfile(ds);
    freeds(&ds);
    freearr(arr);
    return 1;
}
