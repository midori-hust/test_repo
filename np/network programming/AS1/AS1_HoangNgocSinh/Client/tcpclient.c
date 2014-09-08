#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/select.h>
int main()
{
  FILE*f1;
  int sockfd,choice,bytes_read;
  int count=0;
  struct sockaddr_in server;
  struct hostent *host;
  char message[1000],name[50],pass[50];
  char send_data[1024],recv_data[1024],tempt[1024],data[1024];
  
   printf("nhap ip: ");
    scanf("%s",tempt);
    while(getchar()!='\n');
  if((host = gethostbyname(tempt)) == NULL){
    printf("gethostbyname() error!\n");
    exit(0);
  }
  server.sin_family = AF_INET;
  server.sin_port = htons(5000);
  server.sin_addr = *((struct in_addr*)host->h_addr);
  bzero(&(server.sin_zero),8);
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    printf("socket() error!");
    exit(0);
  }
  if( connect(sockfd,(struct sockaddr*)&server , sizeof(struct sockaddr)) == -1 ) {
      printf("connect error!");
      exit(0);
   }
  while(1)
    {
      count=0;
      do{
      printf("1.dang ki tai khoan\n2.dang nhap\nBan chon: ");
      choice = getchar();
      while(getchar()!='\n');
      if(choice!='1'&&choice!='2') printf("nhap sai lua chon, vui long nhap lai!\n");
      }while(choice!='1'&&choice!='2');
      if(choice=='1') {send(sockfd,"dk",2,0);printf("nhap username va password(khong qua 50 ki tu)\n");}
      else if(choice=='2') send(sockfd,"dn",2,0);
      bytes_read = recv(sockfd,recv_data,1024,0);
      recv_data[bytes_read]= '\0';
      while(1){
	printf("username: ");
	gets(name);
	send(sockfd,name,strlen(name),0);
	bytes_read = recv(sockfd,recv_data,1024,0);
	recv_data[bytes_read]= '\0';
	printf("password: ");
	gets(pass);
	send(sockfd,pass,strlen(pass),0);
	bytes_read = recv(sockfd,recv_data,1024,0);
	recv_data[bytes_read]= '\0';
	if(strcmp(recv_data,"ok")==0) break;
	else if(strcmp(recv_data,"invalid")==0) printf("invalid, please retype username and password\n"); 
		else break;
      }
	if(strcmp(recv_data,"stop")==0) return 1;
	if(choice=='1') printf("chuc mung ban da dang ki thanh cong!\n");
      //mennu
      do{
	printf("*****menu*****\n");
	printf("1.ma hoa file\n");
	printf("2.giai ma file\n");
	printf("3.Exit\n");
	printf("Ban chon: ");
	choice = getchar();
	while(getchar() !='\n');
	switch(choice)
	  {
	  case '1': 
	    //demo phan gui
	      send(sockfd,"encrypt",7,0);
	      bytes_read = recv(sockfd,recv_data,1024,0);
	      recv_data[bytes_read]= '\0';
	      do{
		printf("File name: ");
		gets(send_data);
		f1=fopen(send_data,"r");
		if(f1==NULL) printf("File not found!\n");
	      }while(f1==NULL);
	      strcpy(tempt,send_data);
	      send(sockfd,send_data,strlen(send_data),0);
	      bytes_read = recv(sockfd,recv_data,1024,0);
	      recv_data[bytes_read]= '\0';
	      while(fgets(send_data,1024,f1)!=NULL)
		{
		  send(sockfd,send_data,strlen(send_data),0);
		  bytes_read = recv(sockfd,recv_data,1024,0);
		  recv_data[bytes_read]= '\0';
		}
	      send(sockfd,"CLOSED",5,0);
	      printf("Da gui file %s den server!\n",tempt);  
	      bytes_read = recv(sockfd,recv_data,1024,0);
	      recv_data[bytes_read]= '\0';
	      strcpy(tempt,recv_data);
	      send(sockfd,"",1,0);
	      f1=fopen(tempt,"w+");
	      bytes_read = recv(sockfd,recv_data,1024,0);
	      recv_data[bytes_read]= '\0';
	      while(strcmp(recv_data,"CLOSE")!=0)
		{
		  fputs(recv_data,f1);
		  send(sockfd,"",1,0);
		  bytes_read = recv(sockfd,recv_data,1024,0);
		  recv_data[bytes_read]= '\0';
		}
	      fclose(f1);
	      printf("Da nhan file %s tu server!\n",tempt);
	      break;
	  case '2':
	   //phan giai ma
	      send(sockfd,"decrypt",7,0);
	      bytes_read = recv(sockfd,recv_data,1024,0);
	      recv_data[bytes_read]= '\0';
	       do{
		printf("File name: ");
		gets(send_data);
		f1=fopen(send_data,"r");
		if(f1==NULL) printf("File not found!\n");
	      }while(f1==NULL);
	      strcpy(tempt,send_data);
	      send(sockfd,send_data,strlen(send_data),0);
	      bytes_read = recv(sockfd,recv_data,1024,0);
	      recv_data[bytes_read]= '\0';
	      while(fgets(send_data,1024,f1)!=NULL)
		{
		  send(sockfd,send_data,strlen(send_data),0);
		  bytes_read = recv(sockfd,recv_data,1024,0);
		  recv_data[bytes_read]= '\0';
		}
	      send(sockfd,"CLOSED",5,0);
	      printf("Da gui file %s den server!\n",tempt);  
	      bytes_read = recv(sockfd,recv_data,1024,0);
	      recv_data[bytes_read]= '\0';
	      strcpy(tempt,recv_data);
	      send(sockfd,"",1,0);
	      f1=fopen(tempt,"w+");
	      bytes_read = recv(sockfd,recv_data,1024,0);
	      recv_data[bytes_read]= '\0';
	      while(strcmp(recv_data,"CLOSE")!=0)
		{
		  fputs(recv_data,f1);
		  send(sockfd,"",1,0);
		  bytes_read = recv(sockfd,recv_data,1024,0);
		  recv_data[bytes_read]= '\0';
		}
	      fclose(f1);
	      printf("Da nhan file %s tu server!!!\n",tempt);
	      break;
	  case '3':
	    send(sockfd,"exit",4,0);
	    printf("Cam on ban da su dung he thong!");
	    break;
	  default: printf("lua chon sai, vui long chon lai!\n"); break;
	    //end choice
	  } 
      }while(choice!='3');
      //end menu
      break;
    }

  close(sockfd);
}
