/*
 *  This file is provided for use with the unix-socket-faq.  It is public
 *  domain, and may be copied freely.  There is no copyright on it.  The
 *  original work was by Vic Metcalfe (vic@brutus.tlug.org), and any
 *  modifications made to that work were made with the understanding that
 *  the finished work would be in the public domain.
 *
 *  If you have found a bug, please pass it on to me at the above address
 *  acknowledging that there will be no copyright on your work.
 *
 *  The most recent version of this file, and the unix-socket-faq can be
 *  found at http://www.interlog.com/~vic/sock-faq/.
 */

#include "sockhelp.h"
#include <stdio.h>
#include <unistd.h>
#define REGISTER 1
#define LOGIN 2
int type;
int kbhit()
{
  struct  timeval tv;
  fd_set fds;
  tv.tv_sec=15;
  tv.tv_usec=0;
  FD_ZERO(&fds);
  FD_SET(0,&fds);
  select(1,&fds,NULL,NULL,&tv);
  return FD_ISSET(0,&fds);
}
int checkValidName(char *name)
{
  return 1;
}
int checkValidPass(char *pass)
{
  return 1;
}
char* getNamePass(int flag)
{
  char *s,name[20],pass[20];
  s=(char*)malloc(sizeof(char)*100);
  while(1)
    {
      printf("Input Name: ");
      scanf("%s",name);
      printf("Input pass: ");
      scanf("%s",pass);
      if(checkValidName(name)==1 && checkValidPass(pass)==1)
	break;
    }
  strcpy(s,name);
  strcat(s,"+");
  strcat(s,pass);
  strcat(s,"+");
  if(flag==REGISTER)
    {
      strcat(s,"REG");
    } 
  else if(flag==LOGIN)
    {
      strcat(s,"LOG");
    }
  return s;
}
void printQuestion(char s[])
{
  int i,len;
  len=strlen(s);
  for(i=0;i<len;i++)
    {
      if(s[i]=='*')
	s[i]='\n';
    }
  printf("%s \n",s) ;
}
int main(argc, argv)
int argc;
char *argv[];
{
  int sock;
  int i=0,readStdin=0;
  char buffer[1024],*s,ans[5];
  s=(char*)malloc(sizeof(char)*1024);
  int connected = 1;
  int recb,choice,badChoice;
  name_pass ex;
  struct timeval timeout;  
  fd_set readfds;
  time_t start,end;
  if (argc != 3) {
    fprintf(stderr,"Usage:  tcpclient host port\n");
    fprintf(stderr,"where host is the machine which is running the\n");
    fprintf(stderr,"tcpserver program, and port is the port it is\n");
    fprintf(stderr,"listening on.\n");
    exit(EXIT_FAILURE);
  }
  ignore_pipe();
  sock = make_connection(argv[2], SOCK_STREAM, argv[1]);
  if (sock == -1) {
    fprintf(stderr,"make_connection failed.\n");
    return -1;
  }
 
  recb=sock_gets(sock,buffer,sizeof(buffer)-1); /* -1 added thanks to
    David Duchene <dave@ltd.com> for pointing out the possible
    buffer overflow resulting from the linefeed added below. */
  if(recb>0)
    printf("Server: %s\n",buffer);
  else
    printf("Why?\n");
 
  while (connected) {
    //---------------
    while(badChoice)
      {
	printf("*******************Menu:**********************\n");
	printf("1.Register\n");
	printf("2.Login\n");
	printf("**********************************************\n");
	printf("Your choice:");
	scanf("%d",&choice);
	if(choice<1||choice>2)
	  badChoice=1;
	else
	  {
	    badChoice=0;
	    type=choice;
	  }
      }
    badChoice=1;
    char ch=getchar();
    //---------------
    s=getNamePass(type);
    strcpy(buffer,s);
    if (strlen(buffer)==0)
      connected = 0;
    else {
      strcat(buffer,"\n"); 
      sock_puts(sock,buffer);
      if (sock_gets(sock,buffer,sizeof(buffer)) == -1) {
        connected = 0;
      }
      printf("Server: %s\n",buffer);
      if(strcmp(buffer,"OK!LOGED IN!")==0)//LOGIN SUCCESS
	{
	  while(1)
	    {
	      if (sock_gets(sock,buffer,sizeof(buffer)) >0) {
		break;
	      }
	    }
	  printf("Server: %s\n",buffer);//START
	  i=0;
	  //ch=getchar();
	 
	  while(1)
	    {
	      while(1)
		{
		  if( sock_gets(sock,buffer,sizeof(buffer))>0)
		    break;
		}
	      if(strcmp(buffer,"close")==0)
		{
		  connected=0;
		  break;
		}
	      printQuestion(buffer);
	      printf("\nChon dap an: ") ;
	      fflush(stdout);
	     
	      if(kbhit()==1)
		{
		  //fflush(stdin);
		 
		  //read(0,ans,1024);
		  scanf("%s",ans);
		  //while(getchar()!='\n');
		  //printf("ans1=%s\n",ans);
		  //ans[strlen(ans)-3]='\0';
		  printf("ans=%s\n",ans);
		  //sprintf(buffer,"%d",i);
		  //printf("buffer=%s\n",buffer);
		  //strcat(ans,buffer); 
		  //printf("ans=%s\n",ans);
		  strcpy(buffer,ans);
		  strcat(buffer,"\n"); 
		  printf("Ban da chon:%s",buffer);
		  sock_puts(sock,buffer); 
		}
	      else
		printf("Ban da khong da loi cau hoi nay.\n");	
	      i++;
	      // break;
	    }//while 
	      
	      printf("\n");
	}
    }
  }
  printf("<CLOSED>\n");
  close(sock);
  return 0;
}
