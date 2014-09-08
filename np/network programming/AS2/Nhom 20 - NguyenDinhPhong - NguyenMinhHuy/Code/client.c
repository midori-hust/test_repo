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

void displayMessage(data buf);

int main(int args , char *argv[])
{
    int money;
    int luot=1;
	int id_player = -1;
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
		printf(" == Ai La Trieu Phu - Ghe Nong == \n\t1.Dang ky de choi\n\t2.Dang nhap\n\t3.Thoat\n");
        printf("Nhap lua chon:");
        scanf("%d%*c",&choice);
        switch (choice)
        {
        case 1:
        {
            //register
            printf("Nhap thong tin!\n");
            buf.flag =REGISTER;
            printf("\tTen:");
            scanf("%s%*c",buf.object.user);
            printf("\tMat khau:");
            scanf("%s%*c",buf.object.pass);
            send(fd,&buf,sizeof buf,0);
            recv(fd,&buf,sizeof buf,0);
            if (buf.flag==SUCCESS)
            {
                displayMessage(buf);
                printf("Vui long dang nhap de tiep tuc choi\n");
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
            buf.flag =PLAY;
            printf("Nhap thong tin nguoi choi\n");
            printf("\tTen :");
            scanf("%s%*c",buf.object.user);
            printf("\tMat khau :");
            scanf("%s%*c",buf.object.pass);
            send(fd,&buf,sizeof buf,0);
            recv(fd,&buf,sizeof buf,0);
            id_player = buf.result ;
            printf("Nguoi choi thu  %d\n",id_player);
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
				buf.flag = PLAY;
				if(buf.role == id_player)
				{
					printf("Moi nhap cau tra loi\n");
				}
				else
				{
					printf("Vui long cho du nguoi choi ^^\n");
				}
				buf.flag = PLAY;
				buf.result = -1;
				send(fd,&buf,sizeof buf,0);
				int dap_an;
				int skip = 2;
				while(1)
				{
					recv(fd,&buf,sizeof buf,0);
					printf("\t==================.===================\n");
					printf("\t    Luot choi cua player %d\n",buf.role);
					printf("Cau hoi thu %d\n",buf.document.IDQuestion);
					printf("Noi dung : %s\n",buf.document.ques);
					printf("Phuong an 1 : %-30s",buf.document.ans1);
					printf("Phuong an 2 : %s\n",buf.document.ans2);
					printf("Phuong an 3 : %-30s",buf.document.ans3);
					printf("Phuong an 4 : %s\n",buf.document.ans4);
					if(buf.role == id_player)
					{
						printf("Moi nhap cau tra loi, (skip = 5) : ");
						scanf("%d",&dap_an);
						if(dap_an == 5 && skip >0)
							skip--;
						while(dap_an == 5 && skip == 0)
						{
							printf("Ban da het quyen bo qua, xin hay tra loi : ");
							scanf("%d",&dap_an);
						}
						buf.flag = PLAY;
						if(dap_an == buf.document.ans)
						{
							buf.result = 1;
							if( buf.document.IDQuestion == 1)
                                money = 100;
                            else if( buf.document.IDQuestion == 2)
                                money = 200;
                            else if (buf.document.IDQuestion == 3)
                                money = 300;
                            else if (buf.document.IDQuestion == 4)
                                money = 500;
                            else if (buf.document.IDQuestion == 5)
                                money = 1000;
                            else if (buf.document.IDQuestion == 6)
                                money = 2000;
                            else if (buf.document.IDQuestion == 7)
                                money = 3600;
                            else if (buf.document.IDQuestion == 8)
                                money = 6000;
                            else if (buf.document.IDQuestion == 9)
                                money = 9000;
                            else if (buf.document.IDQuestion == 10)
                                money = 15000;
                            else if (buf.document.IDQuestion == 11)
                                money = 25000;
                            else if (buf.document.IDQuestion == 12)
                                money = 35000;
                            else if (buf.document.IDQuestion == 13)
                                money = 50000;
                            else if (buf.document.IDQuestion == 14)
                                money = 80000;
                            else
                                money = 120000;
                            printf("So tien ban co la %d000 VND\n",money);
							if(buf.document.IDQuestion == 15)
							{
								printf("Ban la nguoi thang cuoc \n");
								exit(0);
							}
						}
						else
							buf.result = 0;
						if(dap_an > 5)
							buf.flag = EXIT;
						if(dap_an == 5)
							buf.result = 5;
						send(fd,&buf,sizeof buf,0);
						if(buf.flag == EXIT)
						{
							printf("Quit Game\n");
							exit(0);
						}
					}
					else
					{
						printf("Ngoi xem tra loi\n");

					}
				}


            }
            break;
        }
        case 3:
        {
            //exit
            printf("Hen gap ban lan sau!\n");
            buf.flag =EXIT;
            send(fd,&buf,sizeof buf,0);
            close(fd);
            exit(1);
		}
         default:
            printf("Lua chon sai!\n");
            break;

        }
        getchar();
    }
    close(fd);
}


void displayMessage(data buf)
{
    printf("  %s\n",buf.message);
}
