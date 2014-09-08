#ifndef __ECHOSERVER_H__
#define __ECHOSERVER_H__

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include "message.h"

#define MAXLENGTH 100

int checkAccount(char *id, char *password);

#endif