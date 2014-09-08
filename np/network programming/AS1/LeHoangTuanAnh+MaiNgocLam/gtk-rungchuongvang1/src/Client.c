#include <stdio.h>          
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>  
#include <sys/select.h>

#define MAXBUFSIZE 1000
#define MAXSIZE 1024

int main(int args , char *argv[]){

  int fd;
  
  struct sockaddr_in server;
  struct hostent *he;
  
  int numBytes;
  char recvMessage[MAXBUFSIZE];
  char sendMessage[MAXBUFSIZE];
  char buf[MAXSIZE];
  int byteReceiv;
  
  if(args < 3){
    printf("Usage : %s <IP> <PORT>\n", argv[0]);
    exit(-1);
  }
  // get info from host
  
  if((he = gethostbyname(argv[1])) == NULL){
    printf("gethostbyname() error!\n");
    exit(-1);
  }
  
  // init info for server
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));
  server.sin_addr = *((struct in_addr*)he->h_addr);
  bzero(&(server.sin_zero),8); 
  
  // create socket connect to server
  
  if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    printf("socket() error!");
    exit(-1);
  }
  // connect Socket
  if( connect(fd,(struct sockaddr*)&server , sizeof(struct sockaddr)) == -1 ) {
      printf("error connect");
      exit(1);
   }
  do{ 
      printf("Client message : ");
      gets(sendMessage);
      send(fd, sendMessage,strlen(sendMessage), 0);
      if((strcmp(sendMessage,"q") ==0) || (strcmp(sendMessage,"Q")==0)) 
       break;
       /* Ket Thuc Tien Trinh Va Dong Socket Client */
     byteReceiv = recv(fd,buf,MAXSIZE,0);
	 buf[byteReceiv] = '\0';
	 printf(" \n Get Messages From Server : %s \n",buf);
     if(strcmp(buf,"q")==0 || strcmp(buf,"Q")==0)
      {
	    close(fd); /* Close With terminal of Child Socket */
	    break;
	  } 
   }while(1);

  close(fd);
}
