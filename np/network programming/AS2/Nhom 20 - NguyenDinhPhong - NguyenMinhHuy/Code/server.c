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
    player_ing = 0;
    // khoi tao bo nho
    initMemory();
    //doc file cau hoi
    readQues("question.txt");
    // cau hoi thu bao nhieu
    int no_question = 0;

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
    printf("\t<<<Gameshow GHE NONG - AI LA TRIEU PHU>>>\n");
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
                                addAccount(buf.object);
                                buf.flag = SUCCESS;
                                strcpy(buf.message,"Dang ky thanh cong!");
                                send(i,&buf,sizeof buf,0);
                            }
                        }

                        else if (buf.flag == PLAY)
                        {
                            socket_in_allSocket = searchSocket(i);
                            if (socket_in_allSocket!=NOT_FOUND)
                            {

								if (isLimited()==NO)
									break;
								else
								{
									int j;
									if(buf.result != 1)	// tra loi sai
									{
										if(buf.result != 5 && buf.result != -1)	//nguoi choi tra loi sai
										{
											//client da bi out
											//se ko cho client duoc quyen tra loi nua
											role_ans[searchSocket(i)] = EMPTINESS;
										}
										int count = 0; // dem so lan quay vong lap, neu lap qua 2 lan = ko con ai choi
										while(1)		// chuyen luot choi sang nguoi tiep theo
										{
//											printf("chuyen luot choi\n");
											count++;
											player_ing = player_ing + 1;
											if(player_ing > BACKLOG)
												player_ing = 1;
											if(role_ans[player_ing - 1] != EMPTINESS)
												break;
											if(count > BACKLOG)
											{
												printf("Ko con ai du quyen choi\nEXit\n");
												printf("Chuong trinh ket thuc!\nKhong co nguoi thang cuoc\n");
												getchar();
											}
										}

									}

									if(buf.result == 1)
											no_question = (no_question + 1)%15;

									buf.role = player_ing;
									//nhap du lieu cau hoi vao buf gui di
									buf.document.IDQuestion = quesArr[no_question].IDQuestion;
									strcpy(buf.document.ques, quesArr[no_question].ques);
									strcpy(buf.document.ans1, quesArr[no_question].ans1);
									strcpy(buf.document.ans2, quesArr[no_question].ans2);
									strcpy(buf.document.ans3, quesArr[no_question].ans3);
									strcpy(buf.document.ans4, quesArr[no_question].ans4);
									buf.document.ans = quesArr[no_question].ans;

									printf("\n bat dau choi\n nguoi choi thu %d\n",buf.role);
									for(j=0; j<BACKLOG; j++)
									{
										if(allControl[j] != EMPTINESS)
											send(allControl[j],&buf,sizeof buf,0);
									}
									//break;
								}

                            }
                            else if (socket_in_allSocket==NOT_FOUND)
                            {
                                //client chua choi lan nao
                                if (isLimited()==NO)
                                {
                                    if (searchAccount(buf.object)==FOUND)
                                    {
                                        creatSocketData(i);
										buf.result = searchSocket(i) + 1;
										buf.role = player_ing;
                                        buf.flag=PLAY;
                                        strcpy(buf.message,"Chao mung ^^\nChuc ban may man!");
                                        ////tinh toan, choi voi thang Client moi den nay
                                        //dong goi tat ca cac thu vao buf, roi gui
                                        send(i,&buf,sizeof buf,0);
                                    }
                                    else if (searchAccount(buf.object)==NOT_FOUND)
                                    {
                                        buf.flag =FAILED;
                                        strcpy(buf.message,"Dang nhap that bai!");
                                        send(i,&buf,sizeof buf,0);
                                    }
                                    else if (searchAccount(buf.object)==WRONG_PASS)
                                    {
                                        buf.flag = WRONG_PASS;
                                        strcpy(buf.message,"Nhap sai mat khau!");
                                        send(i,&buf,sizeof buf,0);
                                    }

                                }
                                else if (isLimited()==YES)
                                {
                                    buf.flag = LIMITED;
                                    strcpy(buf.message,"Da du nguoi choi!");
                                    send(i,&buf,sizeof buf,0);
                                }

                            }


                        }
                        // exit
                        else if (buf.flag==EXIT)
                        {
                            printf("Client with the socket number %d exit\n",i);
                            if (searchSocket(i)!=NOT_FOUND)
                            {
                                clearSocketData(i);
                            }
                            close(i);
                            FD_CLR(i,&allSocket);

                        }
                    }
                }
            }
        }
    }
    return 0;
}


