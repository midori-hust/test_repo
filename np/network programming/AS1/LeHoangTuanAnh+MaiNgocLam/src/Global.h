#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _loginStr{
 
  char username[20];
  char password[20];  	

}_loginStr;
typedef struct _anser{
	char typeQuestion;
	int  idQuestion;
	char anser[4];
}_anser;
typedef struct _clientStr{
	
	char ipAdress[20];
    int  Sockfd;
   _loginStr lgStr;	
   _anser  ansStr;
   
}_clientStr;
typedef  enum {false,true} boolean;

typedef struct _question{
	char typeQuestion;
	int  idQuestion;
	char question[100];
	char anser[4]; 
}_question;

int  checkUser( );





