#define  _BSD_SOURCE || (_XOPEN_SOURCE >= 500 || _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED) && !(_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600)
#define  _POSIX_SOURCE
#include "ClientHandle.h"
#include "message.h"

#define MAXLENGTH 100
#define MAXLINE 100

void
str_cli(int sockfd)
{
  char	*sendline, recvline[MESSAGE_MAXLEN], opt[100];
  int ch;
  char option[100];
  message_t newMesg;
  fd_set readset;
  char invite[MAXLENGTH];
  
    while(1)
      {
  	ch = menu();
	switch(ch)
	  {
	  case 1:
	    printf("\n\n----------------------------------------------------------------------------------------\nSIGN IN\n");
	    sendline = message_toString(getIdAndPassword(SIGNIN));
		
		if (send(sockfd, sendline, MESSAGE_MAXLEN, 0) != MESSAGE_MAXLEN) {
	      printf("send() sent a different number of bytes than expected\n");
	    }

	    if (recv(sockfd, recvline, MESSAGE_MAXLEN, 0) < 0) {
	      printf("Server terminated prematurely\n");
	      exit(1);
	    }
	    recvline[strlen(recvline)] = '\0';
	    newMesg = message_parse(recvline);
	    newMesg->arg[1] = '\0';
	    newMesg->arg1[1] = '\0';

	    switch(newMesg->cmd) {
	    	case SIGNIN:
	    	printf("\nWelcome to console chess game\n");
	    	menuPlay();

	    	while(1) {
	    		FD_ZERO(&readset);
				FD_SET(sockfd, &readset);
				FD_SET(fileno(stdin), &readset);
				select(max(sockfd, fileno(stdin)) + 1, &readset, NULL, NULL, NULL);
				if(FD_ISSET(sockfd, &readset)) {
					if(read(sockfd, recvline, MESSAGE_MAXLEN) == 0) {
						printf("Server terminated prematurely\n");
						exit(1);
					}
					//TODO: receive invitation
					newMesg = message_parse(recvline);

					switch(newMesg->cmd) {
					case INVITE_ACCEPT:
					printf("Client %s invited you to his/her game (y/n) ?\n", newMesg->arg1);
					scanf("%s", opt);
					if(strcmp(opt, "y") == 0 || strcmp(opt, "Y") == 0) {
						if (send(sockfd, recvline, MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
				            printf("send() sent a different number of bytes than expected\n");
				        }
					}
					else {
						if (send(sockfd, message_toString( message_construct(INVITE_DECLINE, newMesg->arg1, "0", "0", "0") ), MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
				            printf("send() sent a different number of bytes than expected\n");
				        }
					}
					break;
					case PICK_SIDE:
					if(strcmp(newMesg->arg, "0") == 0) {
					 	mainConsoleChess(0, sockfd);
					 	menuPlay();
					}
					else if (strcmp(newMesg->arg, "1") == 0) {
						mainConsoleChess(1, sockfd);
						menuPlay();
					}
					case GET_PLAYERLIST:
					parse(newMesg->arg);
					menuPlay();
					break;

					default:
					printf("Cannot get the message\n");
					break;
					}


				} else if(FD_ISSET(fileno(stdin), &readset)) {
					fgets(option, 100, stdin);
					option[strlen(option) -1] = '\0';
					if(strcmp(option, "1") == 0) {
						//TODO: inviting someone
						printf("Type the one'id who you want to invite\n");
						scanf("%s", invite);
						
						if (send(sockfd, message_toString(message_construct(INVITE_SEND, invite, "0", "0", "0")), MESSAGE_MAXLEN, 0) != MESSAGE_MAXLEN) {
		     				 printf("send() sent a different number of bytes than expected\n");
		    			}
		    			printf("Waiting for responding from server...\n");
					    if (recv(sockfd, recvline, MESSAGE_MAXLEN, 0) < 0) {
					      printf("Server terminated prematurely\n");
					      exit(1);
					    }
					    recvline[strlen(recvline)] = '\0';
					    newMesg = message_parse(recvline);
					    newMesg->arg[1] = '\0';
					    if(newMesg->cmd == PICK_SIDE) {
							if(strcmp(newMesg->arg, "0") == 0) {
							 	mainConsoleChess(0, sockfd);
							 	menuPlay();
							}
							else if (strcmp(newMesg->arg, "1") == 0) {
								mainConsoleChess(1, sockfd);
								menuPlay();
							}							    	
					    }
					    else {
					    	printf("He/she declined your request\n");
					    	menuPlay();
					    }

					} else if(strcmp(option, "2") == 0) {
						//TODO: get the current players list from server
						if (send(sockfd, message_toString(message_construct(GET_PLAYERLIST, "0", "0", "0", "0")), MESSAGE_MAXLEN, 0) != MESSAGE_MAXLEN) {
	     					 printf("send() sent a different number of bytes than expected\n");
	    				}
	    				printf("Waiting for responding from server...\n");
					} else if(strcmp(option, "3") == 0) {
						printf("Thanks for enjoying\n");
						break;
					} else {
						printf("Not the right option, baby\n");
						menuPlay();
						continue;
					}
				}
			}
	    	break;


	    	default:
	    	printf("MESSAGE COMMAND: %d\n", newMesg->cmd);
	    	printf("Fail to sign in\n");
	    	break;
	    }

	    continue;

	  case 2:
	    printf("\n\n----------------------------------------------------------------------------------------\nSIGN UP\n");
	    sendline = message_toString(getIdAndPassword(SIGNUP));

	    if (send(sockfd, sendline, MESSAGE_MAXLEN, 0) != MESSAGE_MAXLEN ) {
	      printf("send() sent a different number of bytes than expected\n");
	    }

	    if (recv(sockfd, recvline, MESSAGE_MAXLEN, 0) < 0) {
	      printf("str_cli: server terminated prematurely\n");
	      exit(1);
	    }
	    recvline[strlen(recvline)] = '\0';

	    newMesg = message_parse(recvline);
	    switch(newMesg->cmd) {
	    	case SIGNUP:
	    	printf("\nSuccessfull sign up\n");
	    	break;
	    	default:
	    	printf("Fail to sign up. Maybe this account doesn't exist\n");
	    	break;
	    }
	    continue;

	  case 3:
	    printf("----------------------------------------------------------------------------------------\nExit\n");
	    sendline = message_toString(message_construct(SIGNOUT, "0", "0", "0", "0"));
	    
	    if (send(sockfd, sendline, MESSAGE_MAXLEN, 0) != MESSAGE_MAXLEN) {
	      printf("send() sent a different number of bytes than expected\n");
	    }

	    if (recv(sockfd, recvline, MESSAGE_MAXLEN, 0) < 0) {
	      printf("Server terminated prematurely\n");
	      exit(1);
	    }
	    recvline[strlen(recvline)] = '\0';
	    printf("\nI'm done!\n");
	    exit(0);
	    break;

	  default:
	    printf("Wrong option! Please choose again\n");
	    continue;
	  }
	break;
      }
    printf("\n");
  
	
}

int menu()
{
  int option;
  printf("------------------------------------------o0o-------------------------------------------\n");
  printf("|\t\t\t\t     Console Chess      \t\t\t\t|\n");
  printf("|                                                                                       |\n");
  printf("|\t\t\tCreated by Phung Nhat Huy and Pham Duy Hung\t\t\t|\n");
  printf("|\t\t\t\t     AS K55 HEDSPI\t\t\t\t\t|\n");
  printf("|                                                                                       |\n");
  printf("|\t\t\t1. SIGN IN.\t\t\t\t\t\t\t|\n");
  printf("|\t\t\t2. SIGN UP.\t\t\t\t\t\t\t|\n");
  printf("|\t\t\t3. EXIT.\t\t\t\t\t\t\t|\n");
  printf("----------------------------------------------------------------------------------------\n");
  printf("\tYour choice?\n");

  while(scanf("%d", &option) != 1) {
      printf("Wrong input! Please retry.\n");
      while(getchar() != '\n');
  }
  while(getchar() != '\n');
  return option;
}

void menuPlay()
{
  printf("\t\tConsole Chess\n");
  printf("\n");
  printf("Please choose one option:\n");
  printf("\n");
  printf("1. Invite someone.\n");
  printf("2. Refresh the player list.\n");
  printf("3. This game's boring, I don't want to play chess anymore.\n\n");
  printf("\tYour choice?\n");
}

message_t getIdAndPassword(int mesgType) {
	char id[MAXLENGTH], *pass;

	printf("ID: ");
	fgets(id, 1000, stdin);
	id[strlen(id)-1] = '\0';
	pass = getpass("Password: ");
	return message_construct(mesgType, id, pass, "0", "0");
}

int max(int i1, int i2) {
	if (i1 > i2)
		return i1;
	else
		return i2;
}

void parse
(char *userlist_str)
{
    char *pch = strtok (userlist_str, "|");
        while (pch != NULL) {
            int user_id, user_sockfd;
            char username[64];
            sscanf(pch, "%d,%d,%s", &user_id, &user_sockfd, username);
            printf("Client:  %s in port %d\n", username, user_sockfd);
            pch = strtok (NULL, "|");
        }
}
