#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <time.h>		/* for rand() */
#include <sys/time.h>
#include <sys/ioctl.h>

#include "message.h"
#include "gameserver_core.h"

#define LIGHT "0"
#define DARK "1"

void logging (char * message)
{
	time_t timev;
	struct tm *timeinfo;

	time (&timev);
	timeinfo = localtime (&timev);

	printf ("--- %s  > %s\n", asctime(timeinfo), message);
}

int main ()
{
    gameserver_core_init ();
    gameserver_core_loadUsers ();

    /**
     * Server connection handling
     */
    char temp[1024];
    int enemySide, otherSide;
    int randomNum, userCounter = 0;
    int serv_sockfd, client_sockfd;
    int bytes_received;
    socklen_t server_len, client_len;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    char recv_data[1024];
    int result;
    int fd;
    int nread;
    struct timeval tv;
    fd_set fdset, testfds;

    serv_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(1234);
    server_len = sizeof(server_addr);

    //Create a TCP/IP socket to use
    if ((serv_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket() error");
        exit(1);
    }

    if (bind(serv_sockfd, (struct sockaddr *)&server_addr, server_len)== -1) {
        perror("bind() error");
        exit(1);
    }

    if (listen(serv_sockfd, 5) == -1) {
        perror("Listen() error");
        exit(1);
    }

    FD_ZERO(&fdset);    /*clear all bits in fdset*/
    FD_SET(serv_sockfd, &fdset);  /*turn on the bit for fd in fdset*/

    while(1) {
        /* wait until either socket has data ready to be recv()d (timeout 5.5 secs)*/
        tv.tv_sec = 5;
        tv.tv_usec = 500000;
        testfds = fdset;

        result = select(FD_SETSIZE, &testfds, (fd_set *)NULL,(fd_set *)NULL, &tv);

        if(result == -1) {
            perror("Select() error");   // error occurred in select()
            exit(1);
        }
        else if(result == 0){
//            printf("Timeout occurred! No data after 5.5 seconds.\n");
        }
        else{
            //Client connected
            for(fd = 0; fd < FD_SETSIZE; fd++){
                if(FD_ISSET(fd,&testfds)) {
                    if(fd == serv_sockfd){
                        printf("Request on port %d\n", fd);

                        client_len = sizeof(client_addr);
                        client_sockfd = accept(serv_sockfd,(struct sockaddr *)&client_addr, &client_len);
                        FD_SET(client_sockfd, &fdset);
                        printf("Client %d connected !\n", client_sockfd);
                    }
                    else {
                        ioctl(fd, FIONREAD, &nread);
                        if(nread != 0) {
                            printf("\nHandling on socket %d\n",fd);
                            // Handle socket here
                            bytes_received = recv(fd,recv_data,1024,0);
                            recv_data[bytes_received] = '\0';
                            message_t newMesg = message_parse(recv_data);


                            /**
                             * Game server business logic
                             */
                            int response = 0;
                            char logStr[100];
                            switch(newMesg->cmd) {
                                case SIGNIN:
                                    {
                                    	sprintf (logStr, "User signing in at port %d", fd);
                                    	logging (logStr);
                                        response = gameserver_core_signin (newMesg->arg, newMesg->arg1, fd);
                                        if (response >= 0) {
                                            if (send(fd, recv_data, MESSAGE_MAXLEN, 0) != MESSAGE_MAXLEN) {
                                                printf("send() sent a different number of bytes than expected\n");
                                            }
                                            userCounter++;
                                            gameserver_core_signin(newMesg->arg, newMesg->arg1, fd);
                                           	sprintf (logStr, "User %s signed in at port %d", newMesg->arg, fd);
                                           	logging (logStr);
                                        } else {
                                            printf("SEND THIS COMMAND: %d\n", FAILURE);
                                            if (send(fd, message_toString( message_construct(FAILURE, "0", "0", "0", "0") ), MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                                                printf("send() sent a different number of bytes than expected\n");
                                            }
                                        }
                                    }
                                    break;

                                case SIGNUP:
                                    response = gameserver_core_signup (newMesg->arg, newMesg->arg1);
                                    if(response > 0) {
                                        if (send(fd, recv_data, MESSAGE_MAXLEN, 0) != MESSAGE_MAXLEN) {
                                            printf("send() sent a different number of bytes than expected\n");
                                        }
                                        gameserver_core_signup(newMesg->arg, newMesg->arg1);
                                        sprintf (logStr, "User %s signup in at port %d", newMesg->arg, fd);
                                    	logging (logStr);
                                    }
                                    else {
                                        if (send(fd, message_toString( message_construct(FAILURE, "0", "0", "0", "0") ), MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                                            printf("send() sent a different number of bytes than expected\n");
                                        }
                                    }
                                    break;

                                case SIGNOUT:
                                    // TODO: decrease player counter
                                    if (send(fd, recv_data, MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                                    	sprintf (logStr, "User %s signed out at port %d", newMesg->arg, fd);
                                    	logging (logStr);
                                        printf("send() sent a different number of bytes than expected\n");
                                    }
                                    userCounter--;

                                    break;
                                case MOVE:
                                    //Check the port here
                                	enemySide = gameserver_core_getOtherUserSockfd(fd);
                                    if (send(enemySide, recv_data, MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                                    	sprintf (logStr, "User moved %s in at port %d", newMesg->arg, fd);
                                    	logging (logStr);
                                        printf("send() sent a different number of bytes than expected\n");
                                    }
                                    break;
                                case INVITE_SEND:
                                    //send it to other socket
                                    newMesg->arg[1] = '\0';
                                    enemySide = atoi(newMesg->arg);
                                    sprintf(temp, "%d", fd);
                                    if (send(enemySide, message_toString( message_construct(INVITE_ACCEPT, newMesg->arg, temp, "0", "0") ), MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                                    	sprintf (logStr, "User at port %d sent invite to user at socket %s", fd, newMesg->arg);
                                    	logging (logStr);
                                        printf("send() sent a different number of bytes than expected\n");
                                    }
                                    break;

                                case INVITE_ACCEPT:
                                    newMesg->arg[1] = '\0';
                                    newMesg->arg1[1] = '\0';
                                    enemySide = atoi(newMesg->arg);
                                    otherSide = atoi(newMesg->arg1);
                                    srand(time(NULL));
                                    randomNum = rand() % 2;
                                    sprintf(temp, "%d", randomNum);
                                    if (send(enemySide, message_toString( message_construct(PICK_SIDE, temp, "0", "0", "0") ), MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                                        printf("send() sent a different number of bytes than expected\n");
                                    }
                                    sprintf(temp, "%d", randomNum ^ 1);
                                    if (send(otherSide, message_toString( message_construct(PICK_SIDE, temp, "0", "0", "0") ), MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                                        printf("send() sent a different number of bytes than expected\n");
                                    }
                                    //TODO: change status of user here
									sprintf (logStr, "Challege accepted :-< Battle has begun %d vs. %d", enemySide, otherSide);
                                    logging (logStr);
                                    gameserver_core_initNewRoom(enemySide, otherSide);
                                    break;
                                case INVITE_DECLINE:
                                	newMesg->arg[1] = '\0';
                                    newMesg->arg1[1] = '\0';
                                    if (send(atoi(newMesg->arg), recv_data, MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                                    	sprintf (logStr, "User %d declined", fd);
                                    	logging (logStr);
                                        printf("send() sent a different number of bytes than expected\n");
                                    }
                                break;
                                case RESULT:
                                	if (send(fd, message_toString( message_construct(SIGNOUT, "0", "0", "0", "0")), MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                                        printf("send() sent a different number of bytes than expected\n");
                                    }
                                    enemySide = gameserver_core_getOtherUserSockfd(fd);
                                    if (send(enemySide, message_toString( message_construct(SIGNOUT, "0", "0", "0", "0")), MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                                        printf("send() sent a different number of bytes than expected\n");
                                    }
                                    sprintf (logStr, "The war is over :-< ");
                                    logging (logStr);
                                break;
                                case GET_PLAYERLIST:
                                    if (send(fd, message_toString( message_construct(GET_PLAYERLIST, gameserver_core_getPlayerlist(), "0", "0", "0")), MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                                        printf("send() sent a different number of bytes than expected\n");
                                    }
                                    sprintf (logStr, "User %d requested player list", fd);
                                    logging (logStr);
                                break;
                                default:
                                    printf("Error occurred\n");

                                    if (send(fd, message_toString( message_construct(FAILURE, "0", "0", "0", "0") ), MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                                        printf("send() sent a different number of bytes than expected\n");
                                    }
                                    break;
                            }

                        }
                        else {
                            close(fd);
                            FD_CLR(fd, &fdset);  /*turn off the bit for fd in fdset*/
                            printf("Not connect client on fd %d\n", fd);
                            userCounter--;
                            //TODO change user status here
							enemySide = gameserver_core_getOtherUserSockfd(fd);
                            // if (send(enemySide, message_toString( message_construct(RESULT, "1/2", "1/2", "0", "0") ) , MESSAGE_MAXLEN , 0) != MESSAGE_MAXLEN ) {
                            // 	printf("send() sent a different number of bytes than expected\n");
                            // }
                        }
                    }
                }
            }
        }
    }
    gameserver_core_endSession();
    close(serv_sockfd);
}
