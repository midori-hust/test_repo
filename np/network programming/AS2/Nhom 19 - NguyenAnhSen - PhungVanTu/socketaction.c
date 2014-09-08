#include "socketaction.h"
#include "game_config.h"
#include <stdio.h>
#include <stdlib.h>

int createTCPServerSocket(char *address)
{
	int server;
	// Create TCP Server Socket
	server = socket(PF_INET,SOCK_STREAM,0);
	if (server == -1)
	{
		perror("Create TCP socket");
		return -1;
	}
	int check;
	// Set reuse the socket address
	int i = 1;
	check = setsockopt(server,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(int));
	if (check == -1)
	{
		perror("Set reuse");
	}
	// Binding to a address
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(GAME_PORT);
	if (address == NULL)
	{
		serverAddress.sin_addr.s_addr = INADDR_ANY;
	}
	else 
		serverAddress.sin_addr.s_addr = inet_addr(address);
	socklen_t len = sizeof(sockaddr_in);
	check = bind(server,(sockaddr*)&serverAddress,len);
	
	if (check == -1)
	{
		perror("BIND");
		exit(1);
	}
	// Listen in server socket
	check = listen(server,BACK_LOG);
	if (check == -1)
	{
		perror("Listen");
		exit(1);
	}
	return server;	
}

int createTCPClientSocket()
{
	printf("Create client socket---\n");
	int client;
	client = socket(PF_INET,SOCK_STREAM,0);
	if (client == -1)
	{
		perror("Create TCP socket");
		return -1;
	}
	return client;
}

int createRemoteConnection(char *address)
{
	int newCon = createTCPClientSocket();
	if (newCon == -1)
	{
		printf("Can't not connect\n");
		return -1;
	}
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(GAME_PORT);
	if (address == NULL)
	{
		serverAddress.sin_addr.s_addr = INADDR_ANY;
	}
	else 
		serverAddress.sin_addr.s_addr = inet_addr(address);
	socklen_t len = sizeof(sockaddr_in);
	if (connect(newCon,(sockaddr*)&serverAddress,len) == -1)
	{
		perror("CONNECT");
		return -1;
	}
	else
	{
		return newCon;
	}
}

int sendData(int sock, void *data, int len)
{
	int nsent = send(sock,data,len,0);
	if (nsent <= 0)
	{
		perror("Closed connection\n");
	}
	return nsent;
}

int receiveData(int sock, void *data, int max_len)
{
	int nrecv = recv(sock,data,max_len,0);
	if (nrecv <= 0)
	{
		perror("Closed connection\n");
	}
	return nrecv;
}

void printData(void *data, int len)
{
	char *temp = (char*)data;
	temp[len] = 0;
	printf("Data : %s\n",temp);
}
