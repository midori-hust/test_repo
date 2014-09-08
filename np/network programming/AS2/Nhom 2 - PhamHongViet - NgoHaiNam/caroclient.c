#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<assert.h>
#include<signal.h>
#include<errno.h>

#define PORT 5000
#define STATE_MENU 0
#define STATE_GAMEMENU 1
#define STATE_GAME 2
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
#define VIEWSIZE 20
#define INFO_QUIT "Quit game (y or n)?"
#define INFO_WIN "You Win !!!Do you want to view log (y or n)?"
#define INFO_LOST "You Lost !!!Do you want to view log (y or n)?"

char* serverAddress;
int sock;
struct sockaddr_in server_addr;
int state;
int recieved;
char send_msg[1024];
char recv_msg[1024];
char error[100]; 
char choice;
char token[] = "#";
char user[100];
char id[30];
int size;
char* table;
int playerTurn;
int col, row;
int viewC, viewR;
int isCommunicating;
struct termios org_opts, new_opts;
int res;

int communicate(){
  int err;
  isCommunicating = 1;  
  if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    strcpy(error,"socket error");
    return -1;
  }
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  //server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_addr.s_addr = inet_addr(serverAddress);

  if(connect(sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) == -1){
    err = errno;
    sprintf(error,"Cant connect to server! %s",strerror(err));		
    return -1;
  }	
 
  send(sock, send_msg, strlen(send_msg), 0);
  recieved = recv(sock, recv_msg, 1024, 0);
  recv_msg[recieved] = '\0';
  
  strcpy(send_msg, SIGNAL_CLOSE);
  send(sock, send_msg, strlen(send_msg), 0);
  close(sock);
  isCommunicating = 0;
  return 0;
}

void setCustomTerminal(){
  res = 0;
  //store old setttings
  res = tcgetattr(STDIN_FILENO, &org_opts);
  assert(res == 0);
  //set new terminal parms
  memcpy(&new_opts, &org_opts, sizeof(new_opts));
  new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE |ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
  //new_opts.c_cc[VMIN] = 1;
  tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
}

void setDefaultTerminal(){  
  //restore old settings
  res = tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
  assert(res == 0);
}

int getPass(char pass[]){
  int i = 0;
  setCustomTerminal();
  while((pass[i] = getchar()) != '\n')
    i++;
  pass[i] = '\0';
  setDefaultTerminal();
  return i;  
}

int menu_login(){ 
  char pass[100];
  char* str;
  error[0] = '\0';
  while(1){
    write(1,"\E[H\E[2J", 7);
    printf("------CARO GAME ------\n");
    printf("        Login\n");
    printf("----------------------\n");
    if(error[0] != '\0'){
      printf("Error: %s!\n", error);
      printf("Do you want to try again? (y or n)\n");
      printf("Your choice: ");
      choice = getchar();
      while(getchar() != '\n');
      if(choice == 'n' || choice == 'N'){
	error[0] = '\0';
	return -1;
      }
      else if(choice != 'y' && choice != 'Y')
	continue;
      else{
	error[0] = '\0';
	continue;
      }
    }    
    printf("Username: ");
    gets(user);
    printf("Password: ");
    getPass(pass);

    //check user and pass
    sprintf(send_msg, "%s#%s#%s", SIGNAL_CHECK, user, pass);
    if(communicate() == 0){    
      str = strtok(recv_msg, token);
      //ok 
      if(strcmp(str, SIGNAL_OK) == 0)
	break;    
      //error
      else if(strcmp(str, SIGNAL_ERROR) == 0){
	str = strtok(NULL, token);
	strcpy(error, str);
      }
    }    
  }  
  return 0;
}

int menu_create(){
  char pass[100];
  char repass[100];
  char* str;
  error[0] = '\0';
  while(1){
    write(1,"\E[H\E[2J", 7);
    printf("------CARO GAME ------\n");
    printf("    Create new user\n");
    printf("----------------------\n");
    if(error[0] != '\0'){
      printf("Error: %s!\n", error);
      printf("Do you want to try again? (y or n)\n");
      printf("Your choice: ");
      choice = getchar();
      while(getchar() != '\n');
      if(choice == 'n' || choice == 'N'){
	error[0] = '\0';
	return -1;
      }
      else if(choice != 'y' && choice != 'Y')
	continue;
      else{
	error[0] = '\0';
	continue;
      }
    }    
    printf("Username: ");
    gets(user);
    printf("Password: ");
    getPass(pass);
    printf("\nRe-Pass : ");
    getPass(repass);
    if(strcmp(pass, repass) == 0){
      //create  user and pass
      sprintf(send_msg, "%s#%s#%s", SIGNAL_CREATE, user, pass);
      if(communicate() == 0){    
	str = strtok(recv_msg, token);
	//ok 
	if(strcmp(str, SIGNAL_OK) == 0)
	  break;    
	//error
	else if(strcmp(str, SIGNAL_ERROR) == 0){
	  str = strtok(NULL, token);
	  strcpy(error, str);
	}
      }    
    }
    else
      strcpy(error, "Password is not same");          
  }  
  return 0;
}

int menuHandle(){  
  error[0] = '\0';  
  while(1){
    write(1,"\E[H\E[2J", 7);
    if(error[0] != '\0'){
      printf("Error: %s!\n", error);
      error[0] = '\0';
    }
    printf("------CARO GAME ------\n");
    printf("1.Login\n");
    printf("2.Create new user\n");
    printf("3.Exit\n");
    printf("----------------------\n");
    printf("Your choice: ");
    scanf("%c", &choice);
    while(getchar() != '\n');
    if(choice == '1'){
      if(menu_login() == 0)
	break;
    }
    else if(choice == '2'){
      if(menu_create() == 0)
	break;
    }
    else if(choice == '3')
      return -1;
    else {
      sprintf(error,"%c not an optional", choice);      
    }
  }

  return 0;
}

int gameMenu_new(){
  char* str;
  error[0] = '\0';
  int i;
  while(1){
    write(1,"\E[H\E[2J", 7);
    printf("------CARO GAME ------\n");
    printf("User  %s!\n", user);
    printf("New game\n");
    printf("----------------------\n");
    if(error[0] != '\0'){
      printf("Error: %s!\n", error);
      printf("Do you want to try again? (y or n)\n");
      printf("Your choice: ");
      choice = getchar();
      while(getchar() != '\n');
      if(choice == 'n' || choice == 'N'){
	error[0] = '\0';
	return -1;
      }
      else if(choice != 'y' && choice != 'Y')
	continue;
      else{
	error[0] = '\0';
	continue;
      }
    }    
    printf("Enter size of table(between 20 and 50): ");
    scanf("%d", &size);
    while(getchar() != '\n');
    if(size >= 20 &&  size <= 50){
      sprintf(send_msg, "%s#%d#%s", SIGNAL_NEWGAME, size, user);
      if(communicate() == 0){    
	str = strtok(recv_msg, token);
	//ok 
	if(strcmp(str, SIGNAL_OK) == 0){
	  str = strtok(NULL, token);
	  strcpy(id, str);
	  //init table
	  table = malloc(size * size);
	  for(i = 0; i < size * size; i++)
	    table[i] = ' ';
	  //set view
	  viewC = (size - VIEWSIZE) / 2;
	  viewR = viewC;
	  break;    
	}
	//error
	else if(strcmp(str, SIGNAL_ERROR) == 0){
	  str = strtok(NULL, token);
	  strcpy(error, str);
	}
      }    
    }
    else{
      sprintf(error, "Size %d is not available", size);
    }
  }  
  return 0;
}

int gameMenuHandle(){
  error[0] = '\0';  
  while(1){
    write(1,"\E[H\E[2J", 7);
    if(error[0] != '\0'){
      printf("Error: %s!\n", error);
      error[0] = '\0';
    }
    printf("------CARO GAME ------\n");
    printf("Welcome %s!\n", user);
    printf("1.New game\n");
    printf("2.Logout\n");
    printf("----------------------\n");
    printf("Your choice: ");
    scanf("%c", &choice);
    while(getchar() != '\n');
    if(choice == '1'){
      if(gameMenu_new() == 0)
	break;
    }
    else if(choice == '2')
      return -1;
    else {
      sprintf(error,"%c not an optional", choice);      
    }
  }
  return 0;
}

int viewLog(){  
  char* str;
  isCommunicating = 1;
  
  if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    strcpy(error,"socket error");
    return -1;
  }
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  //server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_addr.s_addr = inet_addr(serverAddress);

  if(connect(sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) == -1){
    strcpy(error, "Cant connect to server");				
    return -1;
  } 

  sprintf(send_msg, "%s#%s", SIGNAL_VIEWLOG, id);
  send(sock, send_msg, strlen(send_msg), 0);  
  
  recieved = recv(sock, recv_msg, 1024, 0);
  recv_msg[recieved] = '\0';
  str = strtok(recv_msg, token);
  if(strcmp(str, SIGNAL_LOGLINE) == 0){
    str = strtok(NULL, token);
    printf("User: %s ", str);
    str = strtok(NULL, token);
    printf("- GameID: %s ", str);
    str = strtok(NULL, token);
    printf(" - Address: %s\n", str);
    str = strtok(NULL, token);
    printf("Day: %s ", str);
    str = strtok(NULL, token);
    str[strlen(str) - 4] = '\0';
    printf("- Time: %s\n", str);
    
    strcpy(send_msg, SIGNAL_OK);
    send(sock, send_msg, strlen(send_msg), 0);

    while(1){
      recieved = recv(sock, recv_msg, 1024, 0);
      recv_msg[recieved] = '\0';    
      str = strtok(recv_msg, token);
      if(strcmp(str, SIGNAL_LOGLINE) == 0){
	str = strtok(NULL, token);
	printf("%s\n", str);
	strcpy(send_msg, SIGNAL_OK);
	send(sock, send_msg, strlen(send_msg), 0);      
      }
      else{
	strcpy(send_msg, SIGNAL_CLOSE);
	send(sock, send_msg, strlen(send_msg), 0);
	close(sock);
	isCommunicating = 0;
	break;     
      }
    }   
    printf("Press any key to quit!\n");
    setCustomTerminal();
    getchar();  
    setDefaultTerminal();
    return 0; 
  }
  else if(strcmp(str, SIGNAL_ERROR) == 0){
    strcpy(send_msg, SIGNAL_CLOSE);
    send(sock, send_msg, strlen(send_msg), 0);
    close(sock);
    isCommunicating = 0;
    str = strtok(NULL, token);
    strcpy(error, str);
    return -1;
  }
  return 0;
}

void drawTable(){
  int i, j, k;
  
  printf("   ");
  for(i = 0; i < VIEWSIZE; i++){
    if(i + viewC < 10)
      printf("%d  ", i + viewC);
    else
      printf("%d ", i + viewC);
  }
  printf("\n");

  for(i = viewR; i < viewR + VIEWSIZE; i++){
    if(i < 10)      
      printf("%d  ", i);
    else
      printf("%d ", i);

    for(j = viewC; j < viewC + VIEWSIZE; j++){
      if(i == row && j == col)
	printf("\033[0;31m[%c]\033[0;30m", table[i * size + j]);      
      else
	printf("[%c]", table[i * size + j]);      
    }    
    printf("\n");
  }
}

int max(int a, int b){
  if(a > b)
    return a;
  return b;
}

int min(int a, int b){
  if(a < b)
    return a;
  return b;
}

int gameHandle(){
  char c;    
  char info[100];
  char* str;
  setCustomTerminal();

  error[0] = '\0';  
  info[0] = '\0';
  col = size / 2;
  row = size / 2;
  playerTurn = 1;
  while(1){
    write(1,"\E[H\E[2J", 7);
    printf("------CARO GAME ------\n");
    printf("User %s - GameID = %s\n", user, id);    
    printf("Press w,a,s,d to move \n");
    printf("Press enter to select\n");
    printf("Press q to quit\n");
    printf("----------------------\n");   
    drawTable();
    if(playerTurn){
      if(error[0] != '\0'){
	setDefaultTerminal();

	printf("Error: %s!\n", error);
	printf("Do you want to try again? (y or n)\n");
	printf("Your choice: ");
	choice = getchar();
	while(getchar() != '\n');
	if(choice == 'n' || choice == 'N'){
	  error[0] = '\0';	  
	  return -1;
	}
	else if(choice == 'y' || choice == 'Y'){
	  error[0] = '\0';	  
	  if(info[0] == '\0')
	    playerTurn = 0;
	  else if(strcmp(info, INFO_WIN) == 0 || strcmp(info, INFO_LOST) == 0){
	    if(choice == 'y' || choice == 'Y'){
	      if(viewLog() == 0){
		sprintf(send_msg, "%s#%s#%s",SIGNAL_ABORTGAME, id, user);
		communicate();
		return -1;
	      }
	    }
	  }
	}
			
	setCustomTerminal();
      }
      else if(info[0] != '\0'){
	setDefaultTerminal();

	printf("%s\n", info);
	printf("Your choice: ");
	choice = getchar();
	while(getchar() != '\n');
	if(choice == 'n' || choice == 'N'){
	  if(strcmp(info, INFO_QUIT) == 0)
	    info[0] = '\0';
	  else if(strcmp(info, INFO_WIN) == 0 || strcmp(info, INFO_LOST) == 0){
	    sprintf(send_msg, "%s#%s#%s",SIGNAL_ABORTGAME, id, user);
	    communicate();	   
	    return -1;
	  }
	}
	else if(choice == 'y' || choice == 'Y'){
	  if(strcmp(info, INFO_QUIT) == 0){
	    sprintf(send_msg, "%s#%s#%s",SIGNAL_ABORTGAME, id, user);
	    communicate();
	    return -1;	
	  }
	  else if(strcmp(info, INFO_WIN) == 0 || strcmp(info, INFO_LOST) == 0){
	    if(viewLog() == 0){
	      sprintf(send_msg, "%s#%s#%s",SIGNAL_ABORTGAME, id, user);
	      communicate();
	      return -1;
	    }
	  }
	}
	  
	setCustomTerminal();  
      }
      else{
	c = getchar();
	if(c == 'w' && row > 0){
	  row--;
	  if(viewR > row)
	    viewR = max(0, viewR - 5);
	}
	else if(c == 's' && row < size - 1){
	  row++;
	  if(viewR + VIEWSIZE - 1< row)
	    viewR = min(size - VIEWSIZE, viewR + 5);
	}
	else if(c == 'd' && col < size - 1){
	  col++;
	  if(viewC + VIEWSIZE - 1< col)
	    viewC = min(size - VIEWSIZE, viewC + 5);
	}
	else if(c == 'a' && col > 0){	  
	  col--;
	  if(viewC > col)
	    viewC = max(0, viewC - 5);
	}
	else if(c == '\n' && table[row * size + col] == ' '){
	  table[row * size + col] = 'x';
	  playerTurn = 0;	  	  
	}
	else if(c == 'q'){
	  strcpy(info, INFO_QUIT);
	}
      }
    }
    else{
      sprintf(send_msg, "%s#%s#%d#%d", SIGNAL_TURN, id, col, row);
      if(communicate() == 0){
	str = strtok(recv_msg, token);
	if(strcmp(str, SIGNAL_TURN) == 0){
	  str = strtok(NULL, token);
	  col = atoi(str);
	  str = strtok(NULL, token);
	  row = atoi(str);
	  table[row * size + col] = 'o';
	  if(viewR > row)
	    viewR = max(0, viewR - 5);
	  if(viewR + VIEWSIZE - 1< row)
	    viewR = min(size - VIEWSIZE, viewR + 5);
	  if(viewC + VIEWSIZE - 1< col)
	    viewC = min(size - VIEWSIZE, viewC + 5);
	  if(viewC > col)
	    viewC = max(0, viewC - 5);
	}
	else if(strcmp(str, SIGNAL_WIN) == 0)
	  strcpy(info, INFO_WIN);
	else if(strcmp(str, SIGNAL_LOST) == 0){
	  str = strtok(NULL, token);
	  col = atoi(str);
	  str = strtok(NULL, token);
	  row = atoi(str);
	  table[row * size + col] = 'o';
	  if(viewR > row)
	    viewR = max(0, viewR - 5);
	  if(viewR + VIEWSIZE - 1< row)
	    viewR = min(size - VIEWSIZE, viewR + 5);
	  if(viewC + VIEWSIZE - 1< col)
	    viewC = min(size - VIEWSIZE, viewC + 5);
	  if(viewC > col)
	    viewC = max(0, viewC - 5);
	  strcpy(info, INFO_LOST);
	}
	else if(strcmp(str, SIGNAL_ERROR) == 0){
	  str = strtok(NULL, token);
	  strcpy(error, str);
	}
      }
      playerTurn = 1;
    }    
  }
  setDefaultTerminal();
  return 0;
}

void signalHandle(int sig){
  if(sig == SIGINT || sig == SIGTERM){
    printf("\nTerminating...\n");
    if(state == STATE_GAME){
      while(isCommunicating);
      sprintf(send_msg, "%s#%s#%s", SIGNAL_ABORTGAME, id, user);
      communicate();
      setDefaultTerminal();
    }
    if(sig == SIGINT){
      printf("Program is terminated by user!\n");   
    }
    else{
      printf("Program is terminated by OS!\n");    
    }
    exit(-1);
  }
}

int main(int args, char* argv[]){     
  int err;
  if(args != 2){
    printf("Error\n");
    exit(-1);
  }  
  serverAddress = argv[1];

  signal(SIGINT, &signalHandle);
  signal(SIGTERM, &signalHandle);
  
  state = STATE_MENU;  
  while(1){
    if(state == STATE_MENU){
      if(menuHandle() == -1)
	break;
      else
	state = STATE_GAMEMENU;
    }
    else if(state == STATE_GAMEMENU){
      if(gameMenuHandle() == - 1)
	state = STATE_MENU;	
      else
	state = STATE_GAME;
    }
    else if(state == STATE_GAME){
      if(gameHandle() == - 1){
	free(table);
	table = NULL;
	state = STATE_GAMEMENU; 	  
      }
    }
  }    

  return 0;
}
