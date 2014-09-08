#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include "vigenere.h"
#include "login.h"
#include "transfile.h"
void sig_child(int signo);			//xu ly ki hieu ket thuc
int check(char a[],int n);			//kiem tra ten dang nhap, dang ky nguoi dung gui toi hop le chua
void nhap(int connected,indexarray arr[],FILE*f1);		//nhan dang nhap, dang ky tu nguoi dung
void nhapfile(int connected, indexarray arr[], FILE *f1);	//nhan file tu nguoi dung
int main()
{
    int sock, connected, true = 1;
    pid_t pid;
    struct sockaddr_in server_addr,client_addr;
    int sin_size;

    FILE*f1;
    indexarray arr[26];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket");
        exit(1);
    }

    if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1)
    {
        perror("Setsockopt");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr =INADDR_ANY;
    bzero(&(server_addr.sin_zero),8);

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
            == -1)
    {
        perror("Unable to bind");
        exit(1);
    }

    if (listen(sock, 5) == -1)
    {
        perror("Listen");
        exit(1);
    }

    printf("\nServer waiting for client on port 5000\n");
    fflush(stdout);
    signal(SIGCHLD,sig_child);
    while (1)
    {

        sin_size = sizeof(struct sockaddr_in);

        connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

        printf("I got a connection from (%s , %d)\n",
               inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
        if ((pid=fork())==0)
        {
            close(sock);
            send(connected,"menu",4,0);
            f1=fopen("user","a+");
            initarr(arr);
            nhaptufile(f1,arr);
            nhap(connected,arr,f1);
            fclose(f1);
            freeds(arr);
            fflush(stdout);
            exit(0);
        }
    }
    close(sock);
    return 0;
}
void sig_child(int signo)
{
    pid_t pid;
    int stat;
    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("\nChild %d terminated\n", pid);
    return;
}

int check(char a[],int n)
{
    int i;
    if (n==0) return 0;
    if (a[0]<'A'||(a[0]>'Z'&&a[0]<'a')||a[0]>'z') return 0;
    for (i=1;i<n;i++)
    {
        if (a[i]<'0'||(a[i]>'9'&&a[i]<'A')||(a[i]>'Z'&&a[i]<'a'&&a[i]!=95)||(a[i]>'z')) return 0;
    }
    return 1;
}
void nhapfile(int connected, indexarray arr[], FILE *f1)
{
    int bytes_recieved;
    char recv_data[1024];
    char *p1;
    char *p;
    char p2[1000];
    bytes_recieved=recv(connected,recv_data,1024,0);
    recv_data[bytes_recieved]='\0';
    if (strcmp(recv_data,"1")==0)
    {
        p=(char*)malloc(1000*sizeof(char));
        p1=(char*)malloc(1000*sizeof(char));
        send(connected,"decompress",10,0);
        bytes_recieved=recv(connected,recv_data,1024,0);
        recv_data[bytes_recieved]='\0';
        if (strcmp(recv_data,"/")!=0)
        {
            sprintf(p,"%d_%s",connected,recv_data);
            send(connected,"OK",2,0);
            recvfile(connected,p);
            send(connected,"OK",2,0);
            bytes_recieved=recv(connected,recv_data,1024,0);
            recv_data[bytes_recieved]='\0';
            strcpy(p2,p);
            p=strtok(p,".");
            strcat(p,".dvig");
            if (strcmp(p2,p)==0)
            {
                p=strtok(p,".");
                strcat(p,".dvig1");
            }
            decompress(recv_data,p2,p);
            sprintf(p1,"rm %s",p2);
            system(p1);
            strcpy(p2,p);
            p=strtok(p,"_");
            p=strtok(NULL,"\0");
            send(connected,p,strlen(p),0);
            bytes_recieved=recv(connected,recv_data,1024,0);
            recv_data[bytes_recieved]='\0';
            sendfile(connected,p2);
            sprintf(p1,"rm %s",p2);
            system(p1);
        }
        nhapfile(connected,arr,f1);
    }
    else if (strcmp(recv_data,"2")==0)
    {
        p=(char*)malloc(1000*sizeof(char));
        p1=(char*)malloc(1000*sizeof(char));
        send(connected,"compress",8,0);
        bytes_recieved=recv(connected,recv_data,1024,0);
        recv_data[bytes_recieved]='\0';
        if (strcmp(recv_data,"/")!=0)
        {
            sprintf(p,"%d_%s",connected,recv_data);
            send(connected,"OK",2,0);
            recvfile(connected,p);
            send(connected,"OK",2,0);
            bytes_recieved=recv(connected,recv_data,1024,0);
            recv_data[bytes_recieved]='\0';
            strcpy(p2,p);
            p=strtok(p,".");
            strcat(p,".vig");
            if (strcmp(p2,p)==0)
            {
                p=strtok(p,".");
                strcat(p,".vig1");
            }
            compress(recv_data,p2,p);
            sprintf(p1,"rm %s",p2);
            system(p1);
            strcpy(p2,p);
            p=strtok(p,"_");
            p=strtok(NULL,"\0");
            send(connected,p,strlen(p),0);
            bytes_recieved=recv(connected,recv_data,1024,0);
            recv_data[bytes_recieved]='\0';
            sendfile(connected,p2);
            sprintf(p1,"rm %s",p2);
            system(p1);
        }
        nhapfile(connected,arr,f1);
    }
    else if (strcmp(recv_data,"3")==0)
    {
        send(connected,"logout",6,0);
        nhap(connected,arr,f1);
    }
    else if (strcmp(recv_data,"4")==0)
    {
        send(connected,"exit",4,0);
        close(connected);
    }
    else 
	{
		send(connected,"NO",2,0);
		nhapfile(connected,arr,f1);
	}
}
void nhap(int connected,indexarray arr[],FILE*f1)
{


    char pwd[1024],name[1024];
    char send_data[1024],recv_data[1024];
    int bytes_recieved;
    user*new;
    {
        bytes_recieved = recv(connected,recv_data,1024,0);
        recv_data[bytes_recieved] = '\0';
        if (strcmp(recv_data,"3")==0)
        {
            send(connected,"exit",4,0);
            close(connected);
        }
        else if (strcmp(recv_data, "2")==0)
        {
            send(connected,"register",8,0);
            bytes_recieved = recv(connected,recv_data,1024,0);
            recv_data[bytes_recieved] = '\0';
            if (check(recv_data,bytes_recieved)==0)
            {
                strcpy(send_data,"NO");
                send(connected,send_data,strlen(send_data),0);
            }
            else
            {
                if (search(arr,recv_data)!=NULL)
                    send(connected,"NO1",3,0);
                else
                {
                    strcpy(name,recv_data);
                    strcpy(send_data,"OK");
                    send(connected,send_data,strlen(send_data),0);
                    bytes_recieved = recv(connected,recv_data,1024,0);
                    recv_data[bytes_recieved] = '\0';
                    if (check(recv_data,bytes_recieved)==0)
                    {
                        strcpy(send_data,"NO");
                        send(connected,send_data,strlen(send_data),0);
                    }
                    else
                    {
                        strcpy(pwd,recv_data);
                        strcpy(send_data,"OK");
                        send(connected,send_data,strlen(send_data),0);
                        bytes_recieved = recv(connected,recv_data,1024,0);
                        recv_data[bytes_recieved] = '\0';
                        if (strcmp(recv_data,pwd)!=0)
                        {
                            strcpy(send_data,"NO");
                            send(connected,send_data,strlen(send_data),0);
                        }
                        else
                        {
                            strcpy(send_data,"OK");
                            send(connected,send_data,strlen(send_data),0);
                            fprintf(f1,"%s %s\n",name,pwd);
                            new=makeuser(name,pwd);
                            add(arr,new);
                        }
                    }
                }
            }
            nhap(connected,arr,f1);
        }
        else if (strcmp(recv_data,"1")==0)
        {
            send(connected,"login",5,0);
            bytes_recieved = recv(connected,recv_data,1024,0);
            recv_data[bytes_recieved] = '\0';
            strcpy(name,recv_data);
            bytes_recieved = recv(connected,recv_data,1024,0);
            recv_data[bytes_recieved] = '\0';
            strcpy(pwd,recv_data);
            if ((new=search(arr,name))==NULL)
            {
                send(connected,"NO",2,0);
                nhap(connected,arr,f1);
            }
            else
            {
                if (strcmp(new->pwd,pwd)!=0)
                {
                    send(connected,"NO",2,0);
                    nhap(connected,arr,f1);
                }
                else
                {
                    send(connected,"YES",3,0);
                    nhapfile(connected,arr,f1);
                }
            }

        }
        else
        {
            send(connected,"NO",2,0);
            nhap(connected,arr,f1);
        }
    }
}
