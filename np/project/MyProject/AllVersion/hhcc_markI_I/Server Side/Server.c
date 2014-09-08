#include "EchoServer.h"
             
int main(){

  int serv_sockfd, client_sockfd;
  int server_len, client_len, bytes_received;

  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;

  char recv_data[1024], send_data[1024], recvdata[1024];
  int result;
  int fd;
  int nread;
  struct timeval tv;
  fd_set fdset, testfds;

  char id[MAXLENGTH], password[MAXLENGTH];

  serv_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(1234);
  server_len = sizeof(server_addr);
  
  //Create a TCP/IP socket to use
  if ((serv_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Socket() error");
    exit(1);
  }

  if (bind(serv_sockfd, (struct sockaddr *)&server_addr, server_len)== -1) {
    perror("bind() error");
    exit(1);
  }

  if (listen(serv_sockfd, 5) == -1) {
    perror("Listen() error");
    exit(1);
  }

  FD_ZERO(&fdset);    /*clear all bits in fdset*/
  FD_SET(serv_sockfd, &fdset);  /*turn on the bit for fd in fdset*/

  while(1) {    
    /* wait until either socket has data ready to be recv()d (timeout 5.5 secs)*/
    tv.tv_sec = 5;
    tv.tv_usec = 500000;
    testfds = fdset;
    printf("Server waiting\n");
    
    result = select(FD_SETSIZE, &testfds, (fd_set *)NULL,(fd_set *)NULL, &tv);
    
    if(result == -1) {
      perror("Select() error");   // error occurred in select() 
      exit(1);
    }
    else if(result == 0){
      printf("Timeout occurred! No data after 5.5 seconds.\n");    
       
    }
    else{
      //Client connected
      for(fd = 0; fd < FD_SETSIZE; fd++){
	if(FD_ISSET(fd,&testfds)) {
	  if(fd == serv_sockfd){
	    printf("Request on port %d\n", fd);

       client_len = sizeof(client_addr);
	     client_sockfd = accept(serv_sockfd,(struct sockaddr *)&client_addr, &client_len);
	     FD_SET(client_sockfd, &fdset);
	     printf("Client %d connected !\n", client_sockfd);
	  }
	  else {
	    ioctl(fd, FIONREAD, &nread);
	    if(nread != 0) {
	      printf("\nHandling on socket %d\n",fd);
	      //TODO: Handle socket here

        bytes_received = recv(fd,recv_data,1024,0);
	      recv_data[bytes_received] = '\0';
        message_t newMesg = message_parse(recv_data);
        
        switch(newMesg->cmd) {
          case SIGNIN:            
            strcpy(id, newMesg->arg);
            printf("%s\n", id);
            strcpy(password, newMesg->arg1);
            printf("%s\n", password);
            //TODO: check sign in here

            if(1) {
              if (send(fd, recv_data, MESSAGE_MAXLEN, 0) != MESSAGE_MAXLEN) {
                printf("send() sent a different number of bytes than expected\n");
              }         
              //TODO: play module here


            }
            else {
              if (send(fd, message_toString( message_construct(FAILURE, "0", "0", "0", "0") ), MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                printf("send() sent a different number of bytes than expected\n");
              }
            }
            
          break;
          case SIGNUP:
            strcpy(id, newMesg->arg);
            printf("%s\n", id);
            strcpy(password, newMesg->arg1);
            printf("%s\n", password);
            //TODO Check account here

            if(1) {
              if (send(fd, recv_data, MESSAGE_MAXLEN, 0) != MESSAGE_MAXLEN) {
                printf("send() sent a different number of bytes than expected\n");
              }         
            }
            else {
              if (send(fd, message_toString( message_construct(FAILURE, "0", "0", "0", "0") ), MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                printf("send() sent a different number of bytes than expected\n");
              }
            }

          break;
          case SIGNOUT:
            // TODO: decrease player counter
            if (send(fd, recv_data, MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
              printf("send() sent a different number of bytes than expected\n");
            }
          break;
          default:
          printf("Error occurred\n");

          if (send(fd, message_toString( message_construct(FAILURE, "0", "0", "0", "0") ), MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
            printf("send() sent a different number of bytes than expected\n");
          }
          break;
        }

	    } 
	    else {
	      close(fd);
	      FD_CLR(fd, &fdset);  /*turn off the bit for fd in fdset*/
	      printf("Not connect client on fd %d\n", fd);
	    }
	  }
	}
      }
    }
  }
  close(serv_sockfd);
}
