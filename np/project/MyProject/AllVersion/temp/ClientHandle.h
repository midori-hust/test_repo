#ifndef __CLIENTHANDLE_H__
#define __CLIENTHANDLE_H__

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <stdio.h>
#include "message.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */
#define DEFAULT_PORT 1234
#define MAXLENGTH 100
#define SERV_PORT 1234

void str_cli(int sockfd);
char menu();
message_t getIdAndPassword(int mesgType);

#endif
