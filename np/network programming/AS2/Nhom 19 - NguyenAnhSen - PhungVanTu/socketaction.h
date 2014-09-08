#ifndef SOCKET_ACTION
#define SOCKET_ACTION
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;
int createTCPServerSocket(char *);
int createTCPClientSocket();
int createRemoteConnection(char *);
int sendData(int sock, void *, int len);
int receiveData(int sock, void *, int max_len);
void printData(void *, int );
#endif
