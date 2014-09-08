/*bai nay ko dung time-out nhe!*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "library.h"

#include <errno.h>



int main(int args, char *argv[])
{
    //data buf;
    fd_set allSocket;
    fd_set readfds;
    //writefds;
	char ip_address[20][100];
    int fdmax,k,l;
    int yes =1;

    int listener;
    int acceptSocket;
    struct sockaddr_in server, client;
    int sin_size;
    int socket_in_allSocket;

    int nbytes;

    int i;

    FD_ZERO(&allSocket);
    FD_ZERO(&readfds);

    //check args
    if ( args < 2)
    {
        printf("Usage : %s <PORT>\n", argv[0]);
        exit(-1);
    }
    /*
    for(k=0;k<BACKLOG;k++){//khoi tao cac mang gia tri
    	for(l=0;l<12;l++){
    		all[k][l]=5;
    	}

    }
    for(k=0;k<BACKLOG;k++){
    	allControl[k]=EMPTINESS;
    }
    */
    // khoi tao bo nho
    initMemory();

    // create socket for server to listen
    if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("socket() error!\n");
        exit(-1);
    }
    // init info for server
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server.sin_zero),8);

    // bind
    if (bind(listener, (struct sockaddr*)&server, sizeof(struct sockaddr)) == -1)
    {
        printf("bind() error!\n");
        exit(-1);
    }
    //listen
    if (listen(listener, 2) == -1)
    {
        perror("listen");
        exit(3);
    }
    FD_SET(listener, &allSocket);
    fdmax = listener;
    while (1)
    {
        readfds = allSocket;
        if (select(fdmax+1, &readfds, NULL, NULL, NULL) == -1)
        {
            perror("select");
            printf("errno = %d.\n", errno);
            exit(4);
        }
        for (i = 0; i <= fdmax; i++)
        {
            if (FD_ISSET(i, &readfds))
            {
                if (i == listener)
                {
                    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
                    acceptSocket = accept(listener, (struct sockaddr*)&client, &sin_size);
					//in dia chi ip
					printf("\n client address %s\n", inet_ntoa(client.sin_addr));
					strcpy(ip_address[acceptSocket],inet_ntoa(client.sin_addr));
                    if (acceptSocket == -1)
                    {
                        perror("accept");
                    }
                    else
                    {
                        FD_SET(acceptSocket, &allSocket);
                        printf("Server connected with socket %d\n", acceptSocket);
                        if (acceptSocket > fdmax)
                        {
                            fdmax = acceptSocket;

                        }
                    }
                }
                else
                {
					data buf;
                    if ((nbytes = recv(i, &buf, sizeof buf, 0)) <= 0)
                    {
                        printf("Server stopped connect %d\n", i);
                        close(i);
                        FD_CLR(i, &allSocket);
                    }
                    else
                    {
                        //xu ly thong tin tu client gui ve
                        //dang ki account
                        if (buf.flag == REGISTER)
                        {
                            if (searchAccount(buf.object)==FOUND)
                            {
                                buf.flag = FAILED;
                                strcpy(buf.message,"Account existed!");
                                send(i,&buf,sizeof buf,0);
                            }
                            else if (searchAccount(buf.object)==NOT_FOUND)
                            {
                                printf("im in register 2\n\n");
                                addAccount(buf.object);
                                buf.flag = SUCCESS;
                                strcpy(buf.message,"Register success!");
                                send(i,&buf,sizeof buf,0);
                                //buf.flag = PLAY;
                                //strcpy(buf.message,"Let's go!");
                                //send(i,&buf,sizeof buf,0);
                            }


                        }
                        // play game
                        else if (buf.flag == PLAY)
                        {
                            printf("play\n");
                            socket_in_allSocket = searchSocket(i);
                            if (socket_in_allSocket!=NOT_FOUND)
                            {
                                // clinet choi binh thuong
                                printf("socket %d dang choi\n",i);
                                int score;
								printf("client dang play");
                                printf(" position %d way %c\n",buf.play.position, buf.play.way);
                                score = play(all[socket_in_allSocket],buf.play);
                                all[socket_in_allSocket][13] += score;
                                //ghi log nuoc choi cua client
                                logGame(socket_in_allSocket, buf.play);
                                //kiem tra tro choi ket thuc chua
                                if(checkExit(socket_in_allSocket)==1)
                                {
                                    buf.flag = QUIT_GAME;
                                    send(i,&buf,sizeof buf,0);
                                }
                                else
                                {

                                    // may tinh tinh toan nuoc choi cua no
                                    buf.play = calculator(all[socket_in_allSocket]);
                                    if(buf.play.position != 0)
                                    {
										score = play(all[socket_in_allSocket],buf.play);
										all[socket_in_allSocket][12] += score;
										//ghi log nuoc choi cua may tinh
										logGame(socket_in_allSocket, buf.play);
										buf.flag=PLAY;
										strcpy(buf.message,"Please continue!");
										send(i,&buf,sizeof buf,0);
										checkExit(socket_in_allSocket);
									}
                                }
                            }
                            else if (socket_in_allSocket==NOT_FOUND)
                            {
                                //client chua choi lan nao
                                printf("socket %d chua choi\n",i);
                                if (isLimited()==NO)
                                {
                                    if (searchAccount(buf.object)==FOUND)
                                    {
                                        printf("Tao memory cho client\n");
                                        creatSocketData(i);
                                        //khoi tao file log
                                        initFileLog(searchSocket(i),buf, ip_address[i]);

                                        buf.flag=PLAY;
                                        strcpy(buf.message,"Welcome!\n Play now!");
                                        ////tinh toan, choi voi thang Client moi den nay
                                        //dong goi tat ca cac thu vao buf, roi gui
                                        send(i,&buf,sizeof buf,0);
                                    }
                                    else if (searchAccount(buf.object)==NOT_FOUND)
                                    {
                                        buf.flag =FAILED;
                                        strcpy(buf.message,"Login failed!");
                                        send(i,&buf,sizeof buf,0);
                                    }
                                    else if (searchAccount(buf.object)==WRONG_PASS)
                                    {
                                        buf.flag = WRONG_PASS;
                                        strcpy(buf.message,"Re-enter the correct password!");
                                        send(i,&buf,sizeof buf,0);
                                    }

                                }
                                else if (isLimited()==YES)
                                {
                                    buf.flag = LIMITED;
                                    strcpy(buf.message,"Server limited!");
                                    send(i,&buf,sizeof buf,0);
                                }

                            }


                        }
                        // exit game = close socket
                        else if (buf.flag==EXIT)
                        {
                            printf("Client with the socket number %d exit\n",i);
                            // khong hieu sao neu close socket thi bi loi select
                            
                            if (searchSocket(i)!=NOT_FOUND)
                            {
                                clearSocketData(i);
                            }
                            close(i);
                            FD_CLR(i,&allSocket);
                            //break;

                        }
                        else if (buf.flag == QUIT_GAME)
                        {
                            printf("dong file log------------------------\n");
                            socket_in_allSocket = searchSocket(i);
                            //kiem tra neu file chua dong thi phai dong lai
                            if(logArray[socket_in_allSocket] != NULL)
								fclose(logArray[socket_in_allSocket]);
							//kiem tra xem quit game do client hay da het nuoc di
							if(checkExit(socket_in_allSocket)==0)
							{
								FILE *fp;
								fp = fopen(fileName[socket_in_allSocket],"a");
								if( fp == NULL)
								{
									printf("loi mo file de check exit");
									return 0;
								}
								fprintf(fp,"--------------Game exit-----------\n");
								quitGame(all[socket_in_allSocket], fp);
								fclose(fp);
							}
                            buf.flag = SEND_LOG;
                            //send(i,&buf,sizeof buf,0);
                            logArray[socket_in_allSocket] = fopen(fileName[socket_in_allSocket],"rb");
                            if (logArray[socket_in_allSocket] == NULL)
                            {
								perror("file");
                                printf("loi mo file %s\n",fileName[socket_in_allSocket]);
                                exit(0);
                            }
                            printf("mo file ok\n");
                            
                            long lSize;
                            char *buffer;
                            size_t result;
                            fseek(logArray[socket_in_allSocket],0,SEEK_END);
                            lSize = ftell(logArray[socket_in_allSocket]);
                            rewind(logArray[socket_in_allSocket]);
                            buffer = (char*)malloc(sizeof(char)*lSize);
                            result = fread(buffer, 1, lSize, logArray[socket_in_allSocket]);
                            if (result != lSize)
                            {
                                printf("ko doc het file");
                                exit(0);
                            }
                            else
                                printf("doc file ok + %ld\n",lSize);
                            sendto(i, buffer, lSize, 0,
                                   (struct sockaddr *)&server, sizeof(struct sockaddr));

                            fclose(logArray[socket_in_allSocket]);
                            free(buffer);

                            //send(i,&buf,sizeof buf,0);
                        }
                        //printf("Messages received from %d is++++++: %s\n",i, buf.message);
                    }
                }
            }
        }
    }
    return 0;
}


