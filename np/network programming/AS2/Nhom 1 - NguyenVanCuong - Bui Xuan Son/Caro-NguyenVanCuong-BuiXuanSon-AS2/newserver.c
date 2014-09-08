#include "library.h"


int number = 0;
room Room[ROOMSIZE];
int WaitingRoom[ROOMSIZE];
int EmptyRoom[ROOMSIZE];
int FullRoom[ROOMSIZE];
int numPlayer = 0;
player Player[FD_SETSIZE];
int xCross;
int yCross;

char ListUsername[FD_SETSIZE][MAXLINE];
char ListIPAdress[FD_SETSIZE][MAXLINE];


int main(int argc, char **argv)
{
    int     i, maxi, maxfd, listenfd, connfd, sockfd;
    int     nready, client[FD_SETSIZE];
    ssize_t n;
    fd_set  rset, allset;
    char    buf[MAXLINE];
    socklen_t  clilen;
    struct sockaddr_in cliaddr, servaddr;
    // other variable
    char *welcomeMessage = "welcome to e-Team's Server!";
    char username[MAXLINE], password[MAXLINE];
    char info[MAXLINE];
    char message[MAXLINE]; // x_y_str
    room *tempRoom;
    user userA;
    int nUser;
    user listUser[FD_SETSIZE];
    char filename[MAXLINE];
    FILE *f;
    int bufMax;
    char buffer[MAXLINE];
    char buffer1[MAXLINE*MAXLINE];
    //time
    time_t rawtime;
    struct tm * timeinfo;


    int waitPlay[FD_SETSIZE];
    int Playing[FD_SETSIZE];
    int notPlay[FD_SETSIZE];
    int numWaitPlay = 0, numPlaying = 0, numNotPlay = 0;
    int currentPlayer = 0;


    // Init server
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);
    maxfd = listenfd;            /* initialize */
    maxi = -1;                   /* index into client[] array */
    for (i = 0; i < FD_SETSIZE;  i++)
        client[i] = -1;          /* -1 indicates available entry */
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);


    // init room
    initRoom(Room);
    for(i = 0; i < ROOMSIZE; i++)
    {
        FullRoom[i] = 0;
        WaitingRoom[i] = 0;
        EmptyRoom[i] = 0;
    }
    // khoi tao list user
    nUser = readFile(listUser);
    // Start server
    for ( ; ; )
    {
        rset = allset;          /* structure assignment */
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (FD_ISSET(listenfd, &rset))         /* new client connection */
        {
            clilen = sizeof(cliaddr);
            connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
            printf("Connect o socket %d IP : %s\n",connfd, inet_ntoa(cliaddr.sin_addr));
            //gan dia chi IP vao list
            sprintf(message, "%s", inet_ntoa(cliaddr.sin_addr));
            strcpy(ListIPAdress[connfd], message);
            //send welcome message
            send(connfd, welcomeMessage, strlen(welcomeMessage), 0);

            for (i = 0; i < FD_SETSIZE; i++)
                if (client[i] < 0)
                {
                    client[i] = connfd; /* save descriptor */
                    break;
                }
            if (i == FD_SETSIZE)
                exit(1);
            FD_SET(connfd, &allset);       /* add new descriptor to set */
            if (connfd > maxfd)
                maxfd = connfd; /* for select */
            if (i > maxi)
                maxi = i;          /* max index in client[] array */
            if (--nready <= 0)
                continue;          /* no more readable descriptors */
        }
        for (i = 0; i <= maxi; i++)         /* check all clients for data */
        {
            if ( (sockfd = client[i]) < 0)
                continue;
            if (FD_ISSET(sockfd, &rset))
            {
                // Nhan tin hieu tu nguoi choi
                if ( (n = recv(sockfd, buf, MAXLINE, 0 )) == 0)
                {
                    /* connection closed by client */
                    printf("close socket %d\n", sockfd);
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }
                else
                {
                    buf[n] = '\0';
                    printf("Signal from client %d _ %s\n", sockfd, buf);
                    if( strcmp(buf, SIGNAL_LOGIN) == 0)
                    {
                        //recv username and password from client
                        n = recv(sockfd, username, MAXLINE, 0);
                        username[n] = '\0';
                        n = recv(sockfd, password, MAXLINE, 0);
                        password[n] = '\0';
                        strcpy(userA.username, username);
                        strcpy(userA.password, password);

                        if(checkLogin(listUser, nUser, userA, ListUsername))
                        {
                            strcpy(ListUsername[sockfd], username);

                            //Khoi tao player
                            Player[numPlayer].sockfd = sockfd;
                            Player[numPlayer].roomID = -1;
                            Player[numPlayer].wait = -1;
                            numPlayer++;


                            send(sockfd, SIGNAL_LOGIN_OK, strlen(SIGNAL_LOGIN_OK), 0);
                        }
                        else
                        {
                            send(sockfd, SIGNAL_LOGIN_FALSE, strlen(SIGNAL_LOGIN_FALSE), 0);
                        }
                    }
                    else if(strcmp(buf, SIGNAL_REGISTER) == 0 )
                    {
                        //recv username and password from client
                        n = recv(sockfd, username, MAXLINE, 0);
                        username[n] = '\0';
                        n = recv(sockfd, password, MAXLINE, 0);
                        password[n] = '\0';
                        if(checkExistUsername2(username,listUser, nUser ) == 0)
                        {
                            registerUser(username, password, "users.txt");

                            strcpy(listUser[nUser].username, username);
                            strcpy(listUser[nUser].password, password);
                            nUser++;
                            send(sockfd, "ok", 3, 0);
                        }
                        else
                        {
                            send(sockfd,"fail", 5, 0);
                        }
                    }
                    else if(strcmp(buf,SIGNAL_GET_LIST_ROOM)==0)
                    {
                        printf("Getting list room....\n");
                        getListRoomFree(Room, FullRoom, WaitingRoom, EmptyRoom);
                        strcpy(buf, makeMessage(WaitingRoom));
                        send(sockfd, buf, strlen(buf), 0);
                        strcpy(buf, makeMessage(EmptyRoom));
                        send(sockfd, buf, strlen(buf), 0);
                        // cho gui tin hieu chon phong choi len
                        n = recv(sockfd, buf, MAXLINE, 0);
                        buf[n]='\0';
                        currentPlayer = checkExistPlayer(Player, sockfd);
                        if( currentPlayer == -1)
                        {
                            // neu chua ton tai thi tao ra nguoi choi moi.
                            Player[numPlayer].roomID = atoi(buf);
                            Player[numPlayer].mark = ' ';
                            Player[numPlayer].sockfd = sockfd;
                            Player[numPlayer].wait = 1;
                            currentPlayer = numPlayer;
                            numPlayer++;
                        }
                        else
                        {
                            Player[currentPlayer].roomID = atoi(buf);
                            Player[currentPlayer].mark = ' ';
                            Player[currentPlayer].wait = 1;
                        }
                        if(Room[atoi(buf)].PlayerA.sockfd == -1)
                        {
                            copyPlayer(&Room[atoi(buf)].PlayerA, &Player[currentPlayer]);
                            Player[currentPlayer].mark = 'X';
                            Room[atoi(buf)].state++;
                            send(sockfd, SIGNAL_WAIT, strlen(SIGNAL_WAIT), 0);
                            initTable(Room[atoi(buf)].table);
                        }
                        else if(Room[atoi(buf)].PlayerB.sockfd == -1)
                        {
                            copyPlayer(&Room[atoi(buf)].PlayerB, &Player[currentPlayer]);
                            Room[atoi(buf)].state++;
                            Player[currentPlayer].mark = 'O';
                            send(sockfd, SIGNAL_START, strlen(SIGNAL_START), 0);
                            send(Room[atoi(buf)].PlayerA.sockfd, SIGNAL_START, strlen(SIGNAL_START), 0);
                        }
                        else
                        {
                        }
                    }
                    else if(strcmp(buf,SIGNAL_READY_PLAY)==0)
                    {
                        //** create file log khi bat dau tran dau
                        time ( &rawtime );
                        timeinfo = localtime ( &rawtime );
                        strftime (info, MAXLINE, "%c", timeinfo);
                        sprintf(message, "%-10s %-10s %s", "Bat dau", ":", info);
                        sprintf(filename,"%s.txt",ListUsername[sockfd]);
                        CreatFileLog(message, filename);
                        // ket thuc file log
                        printf("Ready to play...\n");
                        tempRoom = getRoom(Player, sockfd, Room);
                        sprintf(info, "%-10s %-10s %-10s \n%-10s %-10s %-10s","IP1", " : ", ListIPAdress[tempRoom->PlayerA.sockfd], "IP2", " : ", ListIPAdress[tempRoom->PlayerB.sockfd]);
                        sprintf(filename,"%s.txt",ListUsername[sockfd]);
                        CreatFileLog(info, filename);
                        tempRoom->PlayerA.wait = 0;
                        tempRoom->PlayerB.wait = 1;
                        if(sockfd == tempRoom->PlayerB.sockfd)
                        {
                            printf("do nothing...\n");
                        }
                        else if( sockfd == tempRoom->PlayerA.sockfd && tempRoom->PlayerA.wait == 0)
                        {
                            send(tempRoom->PlayerA.sockfd, SIGNAL_START, strlen(SIGNAL_START), 0);
                            printf("send starting...\n");
                            tempRoom->PlayerA.wait = 1;
                        }
                    }
                    else if(strcmp(buf,SIGNAL_QUIT)==0)
                    {
                        tempRoom = getRoom(Player, sockfd, Room);
                        strcpy(ListUsername[sockfd],"");
                        if(tempRoom != NULL)
                        {
                            if( tempRoom->PlayerA.sockfd == sockfd)
                            {
                                tempRoom->PlayerA.sockfd = -1;
                                tempRoom->PlayerB.sockfd = -1;
                                tempRoom->state = 0;
                                tempRoom->PlayerA.wait = 0;
                                tempRoom->PlayerB.wait = 1;
                                initTable(tempRoom->table);

                            }
                            else
                            {
                                tempRoom->PlayerA.sockfd = -1;
                                tempRoom->PlayerB.sockfd = -1;
                                tempRoom->state = 0;
                                tempRoom->PlayerA.wait = 0;
                                tempRoom->PlayerB.wait = 1;
                                initTable(tempRoom->table);
                            }
                        }
                        //numPlayer--;
                        printf("close socket %d IP %s\n", sockfd, inet_ntoa(cliaddr.sin_addr));
                        close(sockfd);
                        FD_CLR(sockfd, &allset);
                        client[i] = -1;
                    }
                    else if(strcmp(buf, SIGNAL_OUT_ROOM) == 0)
                    {
                        tempRoom = getRoom(Player, sockfd, Room);
                        send(sockfd, "abc", 4, 0); //send lai signal loose cho ben thua.
                        if(tempRoom->state == 2)
                        {
                            initTable(tempRoom->table);
                            if(sockfd == tempRoom->PlayerA.sockfd)
                            {
                                send(tempRoom->PlayerB.sockfd, SIGNAL_WIN, strlen(SIGNAL_WIN), 0);
                                tempRoom->PlayerA.roomID = -1;
                                tempRoom->PlayerA.sockfd = -1;
                                tempRoom->PlayerB.sockfd = -1;
                                tempRoom->PlayerA.wait = 0;
                                tempRoom->PlayerB.wait = 1;
                            }
                            else if(sockfd == tempRoom->PlayerB.sockfd)
                            {
                                send(tempRoom->PlayerA.sockfd, SIGNAL_WIN, strlen(SIGNAL_WIN), 0);
                                tempRoom->PlayerB.roomID = -1;
                                tempRoom->PlayerA.sockfd = -1;
                                tempRoom->PlayerB.sockfd = -1;
                                tempRoom->PlayerA.wait = 0;
                                tempRoom->PlayerB.wait = 1;
                            }
                            tempRoom->state = 0;

                        }
                        if(tempRoom->state == 1)
                        {
                            tempRoom->state = 0;
                        }
                    }
                    else if(strcmp(buf, SIGNAL_LOOSE) == 0)
                    {
                        tempRoom = getRoom(Player, sockfd, Room);
                        if(tempRoom->state == 2)
                        {
                            initTable(tempRoom->table);
                            tempRoom->state = 0;
                            if(sockfd == tempRoom->PlayerA.sockfd)
                            {
                                send(tempRoom->PlayerB.sockfd, SIGNAL_WIN, strlen(SIGNAL_WIN), 0);
                                send(tempRoom->PlayerA.sockfd, SIGNAL_GET_LOG_FILE, strlen(SIGNAL_GET_LOG_FILE), 0);
                            }
                            else if(sockfd == tempRoom->PlayerB.sockfd)
                            {
                                send(tempRoom->PlayerA.sockfd, SIGNAL_WIN, strlen(SIGNAL_WIN), 0);
                                send(tempRoom->PlayerB.sockfd, SIGNAL_GET_LOG_FILE, strlen(SIGNAL_GET_LOG_FILE), 0);

                            }
                            tempRoom->PlayerA.sockfd = -1;
                            tempRoom->PlayerB.sockfd = -1;
                        }
                    }
                    else if(strcmp(buf, SIGNAL_GET_LOG_FILE) == 0)
                    {
                        printf("get log file from %d\n", sockfd);
                        time ( &rawtime );
                        timeinfo = localtime ( &rawtime );
                        strftime (info, MAXLINE, "%c", timeinfo);
                        sprintf(message, "%-10s %-10s %s", "ket thuc", ":", info);
                        sprintf(filename,"%s.txt",ListUsername[sockfd]);
                        CreatFileLog(message, filename);
                        f = fopen(filename, "rb");
                        if(f != NULL)
                        {
                            // obtain file size:
                            strcpy(buf,"");
                            fseek (f , 0 , SEEK_END);
                            bufMax = ftell (f);
                            rewind (f);
                            sprintf(buf, "%d", bufMax);
                            send(sockfd, buf, strlen(buf), 0);
                            n = fread(buffer1,  sizeof(char), MAXLINE*MAXLINE, f);
                            buffer1[n] = '\0';
                            send(sockfd, buffer1, strlen(buffer1), 0);
                            fclose(f);
                            printf("finish send file....\n");
                            delFile(filename);
                        }
                    }
                    else if(strcmp(buf, SIGNAL_OK) == 0 )
                    {
                        printf("done!\n");
                    }
                    else
                    {

                        tempRoom = getRoom(Player, sockfd, Room);
                        if(tempRoom->state == 2)
                        {
                            sprintf(info, "%-10s %-10s %-10s", ListUsername[sockfd], " : ", buf);
                            sprintf(filename,"%s.txt",ListUsername[tempRoom->PlayerA.sockfd]);
                            CreatFileLog(info, filename);
                            sprintf(filename,"%s.txt",ListUsername[tempRoom->PlayerB.sockfd]);
                            CreatFileLog(info, filename);
                            if(sockfd == tempRoom->PlayerA.sockfd)
                            {
                                signInTable(tempRoom->table, buf, 2);
                                sscanf(buf, "%d %d", &xCross, &yCross);
                                if(checkWiner(tempRoom->table,xCross, yCross, 2))
                                {
                                    strcpy(message, buf);
                                    strcat(message," ");
                                    strcat(message, SIGNAL_LOOSE);
                                    send(tempRoom->PlayerB.sockfd, message, strlen(message), 0);
                                }
                                else send(tempRoom->PlayerB.sockfd, buf, n, 0);
                            }
                            else if(sockfd == tempRoom->PlayerB.sockfd)
                            {
                                signInTable(tempRoom->table, buf, 1);
                                sscanf(buf, "%d %d", &xCross, &yCross);
                                if(checkWiner(tempRoom->table,xCross, yCross, 1))
                                {
                                    strcpy(message, buf);
                                    strcat(message," ");
                                    strcat(message, SIGNAL_LOOSE);
                                    send(tempRoom->PlayerA.sockfd, message, strlen(message), 0);
                                }
                                else send(tempRoom->PlayerA.sockfd, buf, n, 0);
                            }
                        }

                    }
                }
                if (--nready <= 0)
                    break;         /* no more readable descriptors */
            }
        }
    }
}

