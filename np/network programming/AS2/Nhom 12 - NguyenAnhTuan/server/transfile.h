#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int sendfile(int sock,char s[])			//gui file
{
    FILE*f1;
    char s1[1024];
    int bytes;
    f1=fopen(s,"r");
    if (f1==NULL)
        return 0;
    else
    {
        while (fgets(s1,1024,f1)!=NULL)
        {
            send(sock,s1,strlen(s1),0);
            bytes=recv(sock,s1,1024,0);
            s1[bytes]='\0';
        }
        send(sock,"END",3,0);
        return 1;
    }
    fclose(f1);
}
void recvfile(int sock,char s[])		//nhan file
{
    FILE*f1;
    int bytes;
    char s1[1024];
    f1=fopen(s,"w");
    bytes=recv(sock,s1,1024,0);
    s1[bytes]='\0';
    while(strcmp(s1,"END")!=0)
    {
      //  if(strcmp(s1,"END")==0) break;
     //   printf("%s",s1);
       // printf("%d",strcmp(s1,"END"));
        fputs(s1,f1);
        send(sock,"OK",2,0);
        bytes=recv(sock,s1,1024,0);
        s1[bytes]='\0';
    }
    fclose(f1);
}
