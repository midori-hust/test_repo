#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "transfile.h"
#define PORT 5000
//#define BACKLOG 2
void login(int fd);		//dang nhap
void nhapfile(int fd);		//nhap file
int mygetch( ) {		//ham tao dau * khi nhap password
  struct termios oldt,newt;
  int ch;
  tcgetattr( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
  return ch;
}
int csend(char a[])		//kiem tra khong truyen cho server ki tu trang
{
  if((strcmp(a,"")==0)||a==NULL||strcmp(a,"\n")==0) return 0;
  else return 1;
}

char *ckey(void)		//kiem tra khoa ma hoa hop le
{
  char a[1024];
  char*s;

  int i;
  int j=0;
  s=(char*)malloc(1000*sizeof(char));
  printf("Nhap key:(co it nhat 1 chu cai) ");
  gets(a);
  while(csend(a)==0) gets(a);
  for(i=0;i<strlen(a);i++)
    {
      if(a[i]>='A'&&a[i]<='Z')
	{
	  s[j++]=a[i]-'A'+'a';
	}
      else if(a[i]>='a'&&a[i]<='z')
	{
	  s[j++]=a[i];
	}
    }
  if(j==0)
    {
      printf("Nhap key sai moi nhap lai:\n");
      return NULL;
    }
  else return s;
}

int main()
{
  struct sockaddr_in server;
  struct hostent*he;
  int fd,s,size;
  char receive[1024];
  he=gethostbyname("127.0.0.1");
  if (he == NULL)
    {
      printf("Host error\n");
      return 0;
    }
  bzero(&server,sizeof(server));
  server.sin_family=AF_INET;
  server.sin_addr=*((struct in_addr *)he->h_addr);
  server.sin_port=htons(PORT);
  fd=socket(AF_INET,SOCK_STREAM,0);
  if(fd==-1)
    {
      printf("Socket Error\n");
      return 0;
    }
  s=connect(fd,(struct sockaddr *)&server, sizeof(server));
  if(s<0)
    {
      printf("Connect Error\n");
      return 0;
    }
  printf("Connect\n");
  size  = recv(fd,receive,1024,0);
  receive[size] = '\0';
  if (strcmp(receive , "menu") == 0)
    {
      login(fd);
    }
  close(fd);
  return 1;
}
void login(int fd)
{
  char sendd[1024],user[1024];
  char receive[1024];
  char c;
  int size,i;
  printf("1.Dang nhap\n");
  printf("2.Dang ky\n");
  printf("3.Thoat\n");
  gets(sendd);
  while(csend(sendd)==0) gets(sendd);
  send(fd,sendd,strlen(sendd),0);
  size  = recv(fd,receive,1024,0);
  receive[size] = '\0';
  if(strcmp(receive,"register")==0)
    {
      printf("Dang ky ten va mat khau. Chi chap nhan ki tu chu,so va dau gach duoi, ki tu dau tien phai bat dau la chu\n");
      printf("Ten: ");
      gets(sendd);
      while(csend(sendd)==0) gets(sendd);
      send(fd,sendd,strlen(sendd),0);
      size  = recv(fd,receive,1024,0);
      receive[size] = '\0';
      if(strcmp(receive,"NO")==0)
	{
	  printf("Nhap sai yeu cau, quay lai:\n");
	}
      else if(strcmp(receive,"NO1")==0)
	{
	  printf("Nhap trung ten tai khoan co truoc\n");
	}
      else
	{
	  printf("Mat khau: ");
	  gets(sendd);
	  while(csend(sendd)==0) gets(sendd);
	  send(fd,sendd,strlen(sendd),0);
	  size  = recv(fd,receive,1024,0);
	  receive[size] = '\0';
	  if(strcmp(receive,"NO")==0)
	    {
	      printf("Nhap sai yeu cau, quay lai:\n");
	    }
	  else
	    {
	      printf("Nhap lai mat khau: ");
	      gets(sendd);
	      while(csend(sendd)==0) gets(sendd);

	      send(fd,sendd,strlen(sendd),0);
	      size = recv(fd,receive,1024,0);
	      receive[size]='\0';
	      if(strcmp(receive,"NO")==0)
		{
		  printf("Mat khau nhap lai khong giong\n");
		}
	      else printf("Dang ky da thanh cong\n");
	    }
	}
      login(fd);
    }
  else if(strcmp(receive,"login")==0)
    {
      printf("Ten:\n");
      gets(sendd);
      while(csend(sendd)==0) gets(sendd);
      strcpy(user,sendd);
      send(fd,sendd,strlen(sendd),0);
      printf("Mat khau:\n");
      i=0;
      while(c!='\n')
	{
	  c=mygetch();
	  printf("*");
	  sendd[i++]=c;
	}
      sendd[--i]='\0';
      printf("\n");
      while(csend(sendd)==0)
	{
	  c='0';
	  i=0;
	  while(c!='\n')
	    {
	      c=mygetch();
	      printf("*");
	      sendd[i++]=c;
	    }
	  sendd[--i]='\0';
	  printf("\n");
	}
      send(fd,sendd,strlen(sendd),0);
      size  = recv(fd,receive,1024,0);
      receive[size]='\0';
      if(strcmp(receive,"NO")==0)
	{
	  printf("Dang nhap that bai\n");
	  login(fd);
	}
      else
	{
	  printf("Dang nhap thanh cong voi tai khoan %s\n",user);
	  nhapfile(fd);
	}
    }
  else if(strcmp(receive,"NO")==0)
    {
      printf("Nhap ngoai yeu cau, nhap lai:\n");
      login(fd);
    }
  else close(fd);
}
void nhapfile(int fd)
{
  FILE*f1;
  char sendd[1024];
  char receive[1024];
  int size;
  char *p;
  printf("1. Giai nen\n");
  printf("2. Ma hoa\n");
  printf("3. Thoat tai khoan\n");
  printf("4. Thoat\n");
  gets(sendd);
  while(csend(sendd)==0) gets(sendd);
  send(fd,sendd,strlen(sendd),0);
  size  = recv(fd,receive,1024,0);
  receive[size] = '\0';
  if(strcmp(receive,"logout")==0)
    {
      login(fd);
    }
  else if(strcmp(receive,"compress")==0)
    {
      printf("Nhap file ma hoa: ");
      gets(sendd);
      while(csend(sendd)==0) gets(sendd);
      f1=fopen(sendd,"r");
      if(f1==NULL)
	{
	  printf("Khong tim thay file - quay lai\n");
	  send(fd,"/",1,0);
	}
      else
	{
	  p=strtok(sendd,"/");
	  strcpy(sendd,p);
	  while((p=strtok(NULL,"/"))!=NULL) strcpy(sendd,p);
	  send(fd,sendd,strlen(sendd),0);
	  size  = recv(fd,receive,1024,0);
	  receive[size] = '\0';
	  sendfile(fd,f1);
	  size  = recv(fd,receive,1024,0);
	  receive[size] = '\0';
	  if(strcmp(receive,"OK")==0)
	    {
	      printf("Tien hanh ma hoa\n");
	      while((p=ckey())==NULL);
	      send(fd,p,strlen(p),0);
	      size  = recv(fd,receive,1024,0);
	      receive[size] = '\0';
	      send(fd,"OK",2,0);
	      recvfile(fd,receive);
	      printf("Ma hoa thanh cong duoc file: %s\n",receive);
	    }
	}
      nhapfile(fd);
    }
  else if(strcmp(receive,"decompress")==0)
    {
      printf("Nhap file giai ma: ");
      gets(sendd);
      while(csend(sendd)==0) gets(sendd);
      f1=fopen(sendd,"r");
      if(f1==NULL)
	{
	  printf("Khong tim thay file - quay lai\n");
	  send(fd,"/",1,0);
	}
      else
	{
	  p=strtok(sendd,"/");
	  strcpy(sendd,p);
	  while((p=strtok(NULL,"/"))!=NULL) strcpy(sendd,p);
	  send(fd,sendd,strlen(sendd),0);
	  size  = recv(fd,receive,1024,0);
	  receive[size] = '\0';
	  sendfile(fd,f1);
	  size  = recv(fd,receive,1024,0);
	  receive[size] = '\0';
	  if(strcmp(receive,"OK")==0)
	    {
	      printf("Tien hanh giai ma\n");
	      while((p=ckey())==NULL);
	      send(fd,p,strlen(p),0);
	      size  = recv(fd,receive,1024,0);
	      receive[size] = '\0';
	      send(fd,"OK",2,0);
	      recvfile(fd,receive);
	      printf("Giai ma thanh cong thu duoc file %s\n",receive);
	    }
	}
      nhapfile(fd);
    }
  else if(strcmp(receive,"exit")==0) close(fd);
  else
    {
      printf("Nhap ngoai yeu cau - quay lai:\n");
      nhapfile(fd);
    }
}
