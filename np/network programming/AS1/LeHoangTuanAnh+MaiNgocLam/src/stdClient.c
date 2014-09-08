#include "stdClient.h"

struct sockaddr_in congifureServer()
{
   struct sockaddr_in server;
   struct hostent *he;
   if((he = gethostbyname("127.0.0.1")) == NULL){
    printf("gethostbyname() error!\n");
    exit(-1);
  }
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi("5000"));
  server.sin_addr = *((struct in_addr*)he->h_addr);
  bzero(&(server.sin_zero),8); 
}