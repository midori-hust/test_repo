#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "linklist.h"
#include "caroai.h"

#define PORT 5000
#define SIGNAL_CHECK "SIG_C"
#define SIGNAL_CREATE "SIG_N"
#define SIGNAL_OK "SIG_O"
#define SIGNAL_ERROR "SIG_E" 
#define SIGNAL_CLOSE "SIG_CL"
#define SIGNAL_NEWGAME "SIG_G"
#define SIGNAL_ABORTGAME "SIG_A"
#define SIGNAL_TURN "SIG_T"
#define SIGNAL_WIN "SIG_W"
#define SIGNAL_LOST "SIG_L"
#define SIGNAL_VIEWLOG "SIG_V"
#define SIGNAL_LOGLINE "SIG_LL"  

struct sockaddr_in server_addr,client_addr;  
fd_set master;
char send_msg[1024] , recv_msg[1024]; 
char token[] = "#";
char* str;

int isValid(char* user, char* pass){
  FILE* f = fopen("user.txt", "r+");
  char line[100];
  char* temp;  
  if(pass != NULL){
    while(fgets(line, 100, f) != NULL){
      temp = line;
      while(temp[0] != '#')
	temp++;
      temp[0] = '\0';
      temp++;
      if(temp[strlen(temp) - 1] == '\n')
	temp[strlen(temp) - 1] = '\0';
      if(strcmp(line, user) == 0 && strcmp(temp, pass) == 0){
	fclose(f);
	return 1;
      }
    }
    fclose(f);
    return 0;
  }  
  else{
    while(fgets(line, 100, f) != NULL){
      temp = line;
      while(temp[0] != '#')
	temp++;
      temp[0] = '\0';      
      if(strcmp(line, user) == 0){
	fclose(f);
	return 1;
      }
    }
    fclose(f);
    return 0;
  }  
}

void registerUser(char* user, char* pass){
  FILE* f = fopen("user.txt", "a");
  fprintf(f, "%s#%s\n", user, pass);
  fclose(f);
}

void writeLog(char* logFile, int col, int row, int isPlayer){
  FILE* f = fopen(logFile, "a");
  if(isPlayer)
    fprintf(f, "Player:c:%d-r:%d\n", col, row);
  else
    fprintf(f, "Cpu:c:%d-r:%d\n", col, row);
  fclose(f);
}

void sendLog(char *logFile, int fd){
  char str[100];
  FILE* f = fopen(logFile, "r");
  while(fgets(str, 100, f) != NULL){
    if(str[strlen(str) - 1] == '\n')
      str[strlen(str) - 1] = '\0';
    
    sprintf(send_msg, "%s#%s", SIGNAL_LOGLINE, str);    
    send(fd, send_msg, strlen(send_msg), 0);
    recv(fd,recv_msg,1024,0);
  }
  recv(fd,recv_msg,1024,0);
  fclose(f);  
  strcpy(send_msg, SIGNAL_OK);  
  send(fd, send_msg, strlen(send_msg), 0);
}

int clientHandle(int fd){
  int recieved;
  char *user, *pass;
  int col, row;
  ClientInfo *info;
  char* id;
  recieved = recv(fd,recv_msg,1024,0);
  recv_msg[recieved] = '\0';
  //printf("%s\n", recv_msg);
  str = strtok(recv_msg, token);
  if(strcmp(str, SIGNAL_CLOSE) == 0){

    FD_CLR(fd, &master);
    printf("Close connection from fd = %d\n", fd);    

  }
  else if(strcmp(str, SIGNAL_CHECK) == 0){   

    user = strtok(NULL, token);
    pass = strtok(NULL, token);
    if(isValid(user, pass))
      strcpy(send_msg, SIGNAL_OK);
    else
      sprintf(send_msg,"%s#%s",SIGNAL_ERROR, "Wrong username or password");
    send(fd, send_msg, strlen(send_msg), 0);

  }
  else if(strcmp(str, SIGNAL_CREATE) == 0){

    user = strtok(NULL, token);
    pass = strtok(NULL, token);
    if(isValid(user, NULL))
      sprintf(send_msg,"%s#%s",SIGNAL_ERROR, "This username already in use");
    else{
      registerUser(user, pass);
      sprintf(send_msg, SIGNAL_OK);
    }      
    send(fd, send_msg, strlen(send_msg), 0);

  }
  else if(strcmp(str, SIGNAL_NEWGAME) == 0){

    //get size
    str = strtok(NULL, token);
    recieved = atoi(str);
    //get user
    str = strtok(NULL, token);
    //get id game
    id = addInfo(inet_ntoa(client_addr.sin_addr), recieved, str);
    printf("Create a game with id = %s\n", id);
    printf("Game Info: ");
    printInfo(getInfo(id));
    sprintf(send_msg,"%s#%s", SIGNAL_OK, id);
    send(fd, send_msg, strlen(send_msg), 0);

  }
  else if(strcmp(str, SIGNAL_ABORTGAME) == 0){

    id = strtok(NULL, token);
    str = strtok(NULL, token);
    if(removeInfo(id) == 0){
      printf("Remove user %s's game with id = %s\n", str, id);
      strcpy(send_msg, SIGNAL_OK);
    }
    else{
      printf("Remove user %s's game with id = %d REQUEST FAILED!\n", str, id);
      sprintf(send_msg, "%s#%s%s%s", SIGNAL_ERROR, "Game with id=", id, "not existed");
    }    
    send(fd, send_msg, strlen(send_msg), 0);

  }
  else if(strcmp(str, SIGNAL_TURN) == 0){
    
    // get game id
    id = strtok(NULL, token);    
    //get col info
    str = strtok(NULL, token);
    col = atoi(str);
    //get row info
    str = strtok(NULL, token);
    row = atoi(str);
    printf("Recieved a turn of game id = %s : col = %d, row = %d\n", id, col, row);
    //set table
    info = getInfo(id);    
    if(info != NULL){
      setTable(info->table, info->size, -99, -100);
      //write log
      writeLog(info->logfile, col, row, 1);
      //if player win
      if(playerMove(col, row) == 1){
	printf("Player win\n");
	strcpy(send_msg, SIGNAL_WIN);
	send(fd, send_msg, strlen(send_msg), 0);
      }
      else if(cpuMove(&col, &row) == 0){
	//write log
	writeLog(info->logfile, col, row, 0);
	printf("Send a turn : col = %d, row = %d\n", col, row);
	sprintf(send_msg, "%s#%d#%d", SIGNAL_TURN, col, row);
	send(fd, send_msg, strlen(send_msg), 0);
      }    
      else{
	//write log
	writeLog(info->logfile, col, row, 0);
	printf("Send a turn : col = %d, row = %d\n", col, row);
	sprintf(send_msg, "%s#%d#%d", SIGNAL_LOST, col, row);
	send(fd, send_msg, strlen(send_msg), 0);
      }
    }
    else{
      printf("Request a turn of game with id = %d REQUEST FAILED!\n", id);
      sprintf(send_msg, "%s#%s%s%s", SIGNAL_ERROR, "Game with id=", id, "not existed");
      send(fd, send_msg, strlen(send_msg), 0);
    }
  }
  else if(strcmp(str, SIGNAL_VIEWLOG) == 0){
    // get game id
    id = strtok(NULL, token);    
    info = getInfo(id); 
    if(info != NULL){
      sprintf(send_msg, "%s#%s", SIGNAL_LOGLINE, info->logfile);
      send(fd, send_msg, strlen(send_msg), 0);
      sendLog(info->logfile, fd); 
    }
    else{
      printf("Request log of game with id = %d REQUEST FAILED!\n", id);
      sprintf(send_msg, "%s#%s%s%s", SIGNAL_ERROR, "Game with id=", id, "not existed");
      send(fd, send_msg, strlen(send_msg), 0);
    }
  }
}

int main(int args)
{
  int sock, connected;     
  int sin_size, true = 1;
  fd_set read_fds;
  int fdmax;
  int i;
  
  FD_ZERO(&master);
  FD_ZERO(&read_fds);
  initList();
  
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Socket error\n");
    exit(-1);
  }
  
  if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1) {
    perror("Setsockopt error\n");
    exit(-2);
  }
        
  server_addr.sin_family = AF_INET;         
  server_addr.sin_port = htons(PORT);     
  server_addr.sin_addr.s_addr = INADDR_ANY; 
  //server_addr.sin_addr.s_addr = inet_addr(serverAddress);
  bzero(&(server_addr.sin_zero),8); 
	
  if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
    perror("Unable to bind\n");
    exit(-3);
  }
  
  if (listen(sock, 5) == -1) {
    perror("Listen error\n");
    exit(-4);
  }  
  printf("CaroServer waiting for client on port %d\n", PORT);
  fflush(stdout);
	
  FD_SET(sock, &master);
  fdmax = sock;

  while(1){
    read_fds = master;
    if(select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1){
      perror("select error!\n");
      exit(-5);
    }
    
    for(i = 0; i <= fdmax; i++){
      if(FD_ISSET(i, &read_fds)){
	if(i == sock){
	  sin_size = sizeof(struct sockaddr_in);
	  connected = accept(sock, (struct sockaddr*)&client_addr, &sin_size);
	  if(connected == -1){
	    perror("accept error!\n");
	    exit(-6);
	  }
	  else{
	    FD_SET(connected, &master);
	    if(connected > fdmax)
	      fdmax = connected;	    
	    printf("Got a connection from (%s , %d) with fd = %d\n", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port), connected);
	    clientHandle(connected);
	  }
	}
	else{
	  clientHandle(i);
	}
      }
    }
  }       
  close(sock);
  return 0;
} 
