#include<stdio.h>
#include<ctype.h>
#include<termios.h>
#include"operation.h"
#include"choose.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>  
#include <sys/select.h>

#define ISUSER 0
#define ISDICT 1
#define SEARCH 1
#define EDIT 2
#define ADD 3
#define DELETE_W 4
#define DELETE_U 5
#define LOGOUT 9
#define FREE_USER 0
#define LOGIN 1
#define REGISTER 2
#define EXIT -1

int logout = 1;

void loginMenu(){
  printf("\033[22;34m");
  printf(" ********************************\n");
  printf(" *                              *\n");
  printf(" *    0: Free user              *\n");
  printf(" *    1: Login                  *\n");
  printf(" *    2: Register new account   *\n");
  printf(" *   -1: Exit                   *\n");
  printf(" *                              *\n");
  printf(" ********************************\n");
  printf("     Choose:");
  printf("\033[0m");
}
void operateMenu(int rights){
  printf("\033[22;34m");
  if(rights == 1){
    printf(" ********************************\n");
    printf(" *                              *\n");
    printf(" *    1: Search word            *\n");
    printf(" *    2: Edit word              *\n");
    printf(" *    3: Add word               *\n");
    printf(" *    9: Logout                 *\n"); 
    printf(" *   -1: Exit                   *\n");
    printf(" *                              *\n");
    printf(" ********************************\n");
  }
  else if(rights == 2){
    printf(" ********************************\n");
    printf(" *                              *\n");
    printf(" *    1: Search word            *\n");
    printf(" *    2: Edit word              *\n");
    printf(" *    3: Add word               *\n");
    printf(" *    4: Delete word            *\n");
    printf(" *    5: Delete user            *\n");
    printf(" *    9: Logout                 *\n");
    printf(" *   -1: Exit                   *\n");
    printf(" *                              *\n");
    printf(" ********************************\n");
  }
  else{
    printf(" ********************************\n");
    printf(" *                              *\n");
    printf(" *    1: Search word            *\n");
    printf(" *                              *\n");
    printf(" ********************************\n");
  }
  printf("  Choose:");
  printf("\033[0m");
}
void main(int args,char* argv[]){
  int sock,rcvByte;
  struct hostent *host;
  struct sockaddr_in server_addr;  
  int PORT;
  int loginChoose;                    // Select kind of user or register
  int operateChoose;                  // Select operation
  OP* choose;                         // Choose funtion
  RC* rc;
  char confirm;                       // Confirm you want to exsit?
  char confirmPass[30];
  dict* dic;                          // 
  USER* usr;
  USER* delUsr;
  dict* rcvDic;
  dictsd* rcvDicsd;
  char rcvCheckUser[5];
  char rcv[5];
  int k1,kindUser = 0;
  struct termios oflags,nflags;
  
  if(args < 3){
    printf("Agrument error\n");exit(0);
  }
  host = gethostbyname(argv[1]);
  PORT = atoi(argv[2]);
  
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Socket() error!!");
    exit(1);
  }
  
  server_addr.sin_family = AF_INET;     
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr = *((struct in_addr *)host->h_addr);
  bzero(&(server_addr.sin_zero),8); 
  
  if (connect(sock, (struct sockaddr *)&server_addr,
	      sizeof(struct sockaddr)) == -1){
    perror("Connect() error!!");
    exit(1);
  }
  usr = (USER*)malloc(sizeof(USER));
  dic = (dict*)malloc(sizeof(dict));
  rcvDic = (dict*)malloc(sizeof(dict));
  choose = (OP*)malloc(sizeof(OP));
  rc = (RC*)malloc(sizeof(RC));
  while(1){
    loginMenu();   
    printf("\033[22;34m");
    scanf("%d%*c",&loginChoose);
    printf("\033[0m");
    switch(loginChoose){
    case LOGIN://user had acount. 
      printf("\033[22;34m");    
      printf("username:");gets(usr->userName);fflush(stdin);      
      /// Disable echo
      tcgetattr(fileno(stdin),&oflags);
      nflags = oflags;
      nflags.c_lflag  &= ~ECHO;
      nflags.c_lflag |= ECHONL;
      if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
        perror("tcsetattr");        
      }
      /// Disable echo
      printf("password:");gets(usr->passWord);fflush(stdin);
      // restore terminal
      if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");        
      }
      // restore terminal
      printf("\033[0m");
      
      choose->kind = ISUSER;
      choose->opCode = LOGIN;
      
      send(sock,(char*)choose,sizeof(OP),0);
      send(sock,(char*)usr,sizeof(USER),0);
      
      recv(sock,(char*)rc,sizeof(RC),0);
      if(rc->value == 1||rc->value == 2){		// Logged
	logout = 1;
	kindUser = rc->value;
	printf("Login successful\n");                   // Login successful
	do{
	  if(kindUser == 1)
	    operateMenu(1);
	  else  
	    operateMenu(2);
	  printf("\033[22;34m");
	  scanf("%d%*c",&operateChoose);
	  printf("\033[0m");
	  switch(operateChoose){			// Choose operate
	  case SEARCH:	  // Search word
	    printf("\033[22;34m");	  
	    printf("Type word here: ");gets(dic->word);fflush(stdin);
	    printf("\033[0m");
	    choose->kind = ISDICT;
	    choose->opCode = SEARCH;
	    send(sock,(char*)choose,sizeof(OP),0);
	    send(sock,(char*)dic,sizeof(dict),0);
	    recv(sock,(char*)rc,sizeof(RC),0);
	    switch(rc->value){
	    case 1:					// Found
	      recv(sock,(char*)rcvDic,sizeof(dict),0);
	      printf("\033[1;31m\t%s:\033[0m\n",rcvDic->word);
	      printf("\033[1;38m\t%s \033[0m\n\n",rcvDic->mean);	      
	      break;
	    case 0:					// Not found but have a hint word
	      rcvDicsd = (dictsd*)malloc(sizeof(dictsd));
	      printf("\033[1;38mNot found!! You want to find this word:\033[0m\n");
	      recv(sock,(char*)rcvDicsd,sizeof(dictsd),0);
	      printf("\033[1;31m\t%s:\033[0m\n",rcvDicsd->word);
	      printf("\033[1;38m\t%s \033[0m\n\n",rcvDicsd->mean);	      
	      break;
	    case -1:					// Not found and haven't hint word
	      printf("Not found!!\n");
	      break;
	    }	    
	    break;
	  case EDIT:	   // Edit word
	    printf("\033[22;34m");
	    printf("Word:");gets(dic->word);fflush(stdin);
	    printf("Mean:");gets(dic->mean);fflush(stdin);
	    printf("\033[0m");
	    choose->kind = ISDICT;
	    choose->opCode = EDIT;

	    send(sock,(char*)choose,sizeof(OP),0);
	    send(sock,(char*)dic,sizeof(dict),0);
	    recv(sock,(char*)rc,sizeof(RC),0);
	    if(rc->value == 0){				// Not exsit in dictionary
	      printf("\033[1;31mThis word not exsit in dictionary.\033[0m\n");
	      printf("Do you want to add this word into dictionary?(Y/N):");
	      scanf("%c%*c",&confirm);
	      if(toupper(confirm) == 'Y'){
		choose->kind = ISDICT;
		choose->opCode = ADD;
		
		send(sock,(char*)choose,sizeof(OP),0);
		send(sock,(char*)dic,sizeof(dict),0);
		recv(sock,(char*)rc,sizeof(RC),0);
		switch(rc->value){
		case 1:
		  printf("Add successful\n");
		  break;
		case 0:
		  printf("\033[1;31mThis word are exsitted\033[0m\n");
		  break;
		case -1:
		  printf("\033[1;31mDon't follow you add word\033[0m\n");
		  break;
		}	
	      }
	    }
	    else if(rc->value == -1){
	      printf("\033[1;31mDon't follow you edit word\033[0m\n");
	    }
	    else
	      printf("Edit successful\n");
	    break;
	  case ADD:	// Add word
	    printf("\033[22;34m");
	    printf("\tWord:");gets(dic->word);fflush(stdin);
	    printf("\tMean:");gets(dic->mean);fflush(stdin);
	    printf("\033[0m");
	    choose->kind = ISDICT;
	    choose->opCode = ADD;

	    send(sock,(char*)choose,sizeof(OP),0);
	    send(sock,(char*)dic,sizeof(dict),0);
	    recv(sock,(char*)rc,sizeof(RC),0);
	  
	    switch(rc->value){
	    case 1:
	      printf("Add successful\n");
	      break;
	    case 0:
	      printf("\033[1;31mThis word are exsitted\033[0m\n");
	      break;
	    case -1:
	      printf("\033[1;31mDon't follow you add word\033[0m\n");
	      break;
	    }
	    break;
	  case EXIT:
	  case LOGOUT:
	    logout = 0;
	    choose->kind = ISUSER;
	    choose->opCode = LOGOUT;
	    send(sock,(char*)choose,sizeof(OP),0);
	    send(sock,(char*)usr,sizeof(USER),0);
	    if(operateChoose == LOGOUT)
	      break;
	  
	    choose->kind = ISUSER;
	    choose->opCode = EXIT;
	    send(sock,(char*)choose,sizeof(OP),0);
	    close(sock);
	    free(usr);
	    free(rc);
	    free(choose);
	    free(dic);
	    free(rcvDic);
	    exit(0);
	    break;
	  case DELETE_W:     // Delete word
	    if(kindUser == 2){
	      printf("\033[22;34m");
	      printf("\tWord:");gets(dic->word);fflush(stdin);
	      printf("\033[0m");	     	      
	      choose->kind = ISDICT;	      
	      choose->opCode = DELETE_W;
	      send(sock,(char*)choose,sizeof(OP),0);
	      send(sock,(char*)dic,sizeof(dict),0);
	      recv(sock,(char*)rc,sizeof(RC),0);
	      
	      if(rc->value == 0)
		printf("Delete succesful\n");
	      else
		printf("\033[1;31mDelete error\033[0m\n");
	    }
	    else{
	      printf("\033[1;31mChoose not right.Try again\033[0m\n\n");
	    }
	    break;
	  case DELETE_U:       // Delete user
	    if(kindUser == 2){
	      delUsr = (USER*)malloc(sizeof(USER));
	      printf("\033[22;34m");	     
	      printf("Username:");gets(delUsr->userName);fflush(stdin);
	      printf("\033[0m");
	      if(strcmp(usr->userName,delUsr->userName) == 0){
		printf("Don't allow delete this user\n");
		break;
	      }	      
	      choose->kind = ISUSER;	      
	      choose->opCode = DELETE_U;
	      send(sock,(char*)choose,sizeof(OP),0);
	      send(sock,(char*)delUsr,sizeof(USER),0);
	      recv(sock,(char*)rc,sizeof(RC),0);
	      
	      if(rc->value == 1)
		printf("Delete succesful\n");
	      else if(rc->value == 0){
		printf("\033[1;31mDelete error! User not exsit\033[0m\n");
	      }
	      else{	     
		printf("\033[1;31m%s: is Online now!!Delete Error\033[0m\n",usr->userName);
	      }
	    }
	    else{
	      printf("\033[1;31mChoose not right.Try again\033[0m\n\n");
	    }
	    break;	
	  default:
	    printf("\033[1;31mChoose not right.Try again\033[0m\n\n");
	    break;
	  }
	}while(logout > 0);
      } // if
      else if(rc->value == -3){
	printf("\033[1;31mThis user logged!!\033[0m\n");
      } // else if
      else{
	printf("\033[1;31mPassword or username incorrect. Login try again\033[0m\n\n");
      }
      break;
    case REGISTER:	// Register a new acount
      do{
	do{
	  printf("\033[22;34m");
	  printf("Username:");gets(usr->userName);fflush(stdin);	  
	  /// Disable echo
	  tcgetattr(fileno(stdin),&oflags);
	  nflags = oflags;
	  nflags.c_lflag  &= ~ECHO;
	  nflags.c_lflag |= ECHONL;
	  if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
	    perror("tcsetattr");        
	  } /// Disable echo

	  printf("Password:");gets(usr->passWord);fflush(stdin);
	  printf("Confirm pass:");gets(confirmPass);fflush(stdin);
	  // restore terminal
	  if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
	    perror("tcsetattr");        
	  }
	  // restore terminal
	  printf("\033[0m");
	  if(strcmp(usr->passWord,confirmPass)!=0){
	    printf("\033[1;31mConfirm password is not correct!!\033[0m\n");
	  }
	}while(strcmp(usr->passWord,confirmPass)!=0);
	usr->rights = 1;
	choose->kind = ISUSER;
	choose->opCode = REGISTER;

	send(sock,(char*)choose,sizeof(OP),0);
	send(sock,(char*)usr,sizeof(USER),0);

	recv(sock,(char*)rc,sizeof(RC),0);
	if(rc->value == 0){
	  printf("You regist successful!!\n");
	  printf("\033[1;31mYou have to login try again to access system!!\033[0m\n");
	  break;
	}
	else if(rc->value == -1){
	  printf("\033[1;31mError!! Please input both user and pass!!\033[0m\n");
	}
	else{
	  printf("\033[1;31mUser are exsited!! Try register again!!\033[0m");
	}
	printf("\033[22;34m");
	printf("You really want to register try again?(Y/N):");
	scanf("%c%*c",&confirm);
	printf("\033[0m");
      }while(toupper(confirm) == 'Y');
      break;
    case FREE_USER:		// Free user
      choose->kind = ISUSER;
      choose->opCode = FREE_USER; 
      send(sock,(char*)choose,sizeof(OP),0);
      do{
	printf("\033[22;34m");
	printf(" ********************************\n");
    	printf(" *                              *\n");
    	printf(" *       Search word            *\n");
    	printf(" *                              *\n");
    	printf(" ********************************\n");
	printf(" Type word here: ");gets(dic->word);fflush(stdin);
	printf("\033[0m");	
	choose->kind = ISDICT;
	choose->opCode = SEARCH;
	
	send(sock,(char*)choose,sizeof(OP),0);
	send(sock,(char*)dic,sizeof(dict),0);
	recv(sock,(char*)rc,sizeof(RC),0);
	switch(rc->value){
	case 1:
	  recv(sock,(char*)rcvDic,sizeof(dict),0);
	  printf("\033[1;31m\t%s:\033[0m\n",rcvDic->word);
	  printf("\033[1;38m\t%s \033[0m\n\n",rcvDic->mean);	  
	  break;
	case 0:
	  rcvDicsd = (dictsd*)malloc(sizeof(dictsd));
	  printf("\033[1;38mNot found!! You want to find this word\033[0m\n");
	  recv(sock,(char*)rcvDicsd,sizeof(dictsd),0);
	  printf("\033[1;31m\t%s:\033[0m\n",rcvDicsd->word);
	  printf("\033[1;38m\t%s \033[0m\n\n",rcvDicsd->mean);	  
	  break;
	case -1:
	  printf("\033[1;31mNot found!!\033[0m\n");
	  break;
	}
	printf("\033[22;34m");
	printf("You want to search continue?(Y/N):");
	scanf("%c%*c",&confirm);
	printf("\033[0m");	      
      }while(toupper(confirm) == 'Y');
      break;
    case EXIT: 		// Exit

      choose->kind = ISUSER;
      choose->opCode = EXIT;
      send(sock,(char*)choose,sizeof(OP),0);
      close(sock);
      free(usr);
      free(rc);
      free(choose);
      free(dic);
      free(rcvDic);
      exit(0);
      break;
    } // switch 1
  }// while 1
}


//Compile Command
// gcc -o client client.c
