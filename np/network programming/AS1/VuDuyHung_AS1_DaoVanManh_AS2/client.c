#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/select.h>

#include "library.h"


#define MAXBUFSIZE 1000


//void clear(void);
void displayMessage(data buf);
//int info[12];


int main(int args , char *argv[])
{
    //int info[1][12];
    int info[]={10,5,5,5,5,5,10,5,5,5,5,5,0,0};
    int luot=1,score;

    data buf;
    int fd,choice,test=0;

    struct sockaddr_in server;
    struct hostent *he;

    
    if (args < 3)
    {
        printf("Usage : %s <IP> <PORT>\n", argv[0]);
        exit(-1);
    }
    // get info from host

    if ((he = gethostbyname(argv[1])) == NULL)
    {
        printf("gethostbyname() error!\n");
        exit(-1);
    }

    // init info for server
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr = *((struct in_addr*)he->h_addr);
    bzero(&(server.sin_zero),8);

    // create socket connect to server

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("socket() error!");
        exit(-1);
    }

    if ( connect(fd,(struct sockaddr*)&server , sizeof(struct sockaddr)) == -1 )
    {
        printf("error connect");
        exit(1);
    }
    
    while (1)
    {
		//system("clear");
		printf("Welcome to the Game\n\n1.Register\n2.Login to play\n3.Exit\n");
        printf("Enter your choice:\n\n");
        scanf("%d%*c",&choice);
        switch (choice)
        {
        case 1:
        {
            //register
            printf("You choice register function!\n");
            buf.flag =REGISTER;
            printf("Enter your name:\n");
            scanf("%s%*c",buf.object.user);
            printf("Enter your password:\n");
            scanf("%s%*c",buf.object.pass);
            send(fd,&buf,sizeof buf,0);
            recv(fd,&buf,sizeof buf,0);
            if (buf.flag==SUCCESS)
            {
                displayMessage(buf);
                printf("Please choose login to play\n");
                break;
            }
            else if (buf.flag==FAILED)
            {
                displayMessage(buf);
                break;
            }
            break;
        }
        case 2:
        {
            //login
            printf("You choice playing function!\n");
            buf.flag =PLAY;
            printf("Enter your name:\n");
            scanf("%s%*c",buf.object.user);
            printf("Enter your password:\n");
            scanf("%s%*c",buf.object.pass);
            send(fd,&buf,sizeof buf,0);
            recv(fd,&buf,sizeof buf,0);
            if (buf.flag==LIMITED)
            {
                displayMessage(buf);
                break;
            }
            else if (buf.flag == WRONG_PASS)
            {
                displayMessage(buf);
                break;
            }
            else if (buf.flag == FAILED)
            {
                displayMessage(buf);
                break;
            }
            else if (buf.flag==PLAY)
            {
				char c;
				int sign;
                while (PLAYING)
                {
                    //send nuoc di, tat ca dong goi vao buf
                    buf.flag = PLAY;

                    printMap(info);
                    printf("\nLuot choi thu %d\n",luot++);
                    printf("please you\n");
                    //buf.play = choice(info);
                    step tmp;
                    //khoi tao step.position = 0
                    tmp.position = 0;
                    //char c;
                    sign = 1;
                    do
                    {
                        printf("Choice position :");
                        scanf("%c%*c",&c);
                        //c = getchar();
                        if(c=='q')
							break;
                        
                        if( (c >= 'a') && (c < 'f') &&  (info['e'-c+7]!=0))
							sign = 0;
                        else if (info['e'-c+7]==0)
                        {
                            printf("You have choosen empty cell, please again\n");
                            sign = 1;
                        }
                        
                    }
                    while (sign);
                    tmp.position = 'e'-c+7;
                    printf("You go left (L) or right (R), quit = q : ");
                    scanf("%c%*c",&c);
                    tmp.way = c;
                    buf.play = tmp;
                    if (buf.play.way == 'q')
                    {
                        buf.flag = QUIT_GAME;
                        printf("\n Quit game\nsend %d bytes\n  ",send(fd,&buf,sizeof buf, 0));
                        break;
                    }
                    else
                    {
                        score = play(info,buf.play);
                        info[13] += score;
                        printMap(info);


                        printf("\n send %d bytes\n  ",send(fd,&buf,sizeof buf, 0));

                        printf("nhan %d bytes\n  ",recv(fd,&buf,sizeof buf, 0));
                        //neu nhan duoc thong bao quit thi gui thong diep QUIT_GAME
                        if(buf.flag == QUIT_GAME)
                        {
							strcpy(buf.message,"");
                            send(fd,&buf,sizeof buf, 0);
                            break;
                        }
                        printf("Boss play: position %d, way %c\n",buf.play.position, buf.play.way);
                        score = play(info, buf.play);
                        info[12] += score;
                        if(info[0] == 0 && info[6] == 0)
                        {
							printMap(info);
							printf("\n--- boss play and quit game\n");
                            buf.flag = QUIT_GAME;
                            send(fd,&buf,sizeof buf, 0);
                            break;
                        }
					}
                }
                //SEND_LOG
                {
                    FILE *fp;
                    int addr_len;
                    long lSize;
                    char *buffer;
                    char filename[100];
                    buffer = (char*)malloc(sizeof(char)*20000);
                    lSize = recvfrom(fd,buffer,20000,0,(struct sockaddr *)&server, &addr_len);
                    printf("\nPlease input filename to save:");
                    scanf("%s%*c",filename);
                    fp = fopen(filename,"wb");
                    if (fp != NULL)
                        printf("mo file thanh cong\n");
                    else
                        exit(0);
                    fwrite (buffer , 1 , lSize , fp );
                    printf("nhan duoc %ld byte\n",lSize);
                    fclose(fp);
                    free(buffer);
                    buf.flag = EXIT;
					send(fd,&buf,sizeof buf,0);
					close(fd);
					exit(1);
                }
            }
            break;
        }
        case 3:
        {
            //exit
            printf("You choice exiting function!\n");
            buf.flag =EXIT;
            send(fd,&buf,sizeof buf,0);
            close(fd);
            exit(1);
            //server will close socket
            
		}
         default:
            printf("Wrong choice!\n");
            break;
            
        }
        getchar();
    }
    close(fd);
}


void displayMessage(data buf)
{
    printf("Message from server: %s\n",buf.message);
}
