#ifndef __resource_h
#define __resource_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>

#define SERVER_PORT 9734

int checkUser(char *username,char *password);
int login(int client_sock);
int nhanFile(int client_sock,char *fileout);
void mahoa(char *filein,char *fileout);
void giaima(char *filein,char *fileout);
int guiFile(int client_sock,char *filein);
int dangnhap(int client_sock);
int fsize(char *file);
void xoafile(char *file);
int dangki(int client_sock);
int nhandangki(int client_sock);
#endif
