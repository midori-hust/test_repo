#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "Global.h"


int main(int args, char *argv[])
{
    fd_set allSocket;    
    fd_set readfds;  
    int fdmax;        
    
    int listener;     
    int acceptSocket;       
    struct sockaddr_in server, client; 
    int sin_size;

    char buf[256];    
    int nbytes;
    char send_data[1024];
    int i, rv;
    
    FD_ZERO(&allSocket);   
    FD_ZERO(&readfds); 

    int _gSocID[100];
    int _iSocCount=0;
    
    int iCountSend=0;
    int firstSend=0;
    //check args
    if( args < 2)
    {
        printf("Usage : %s <PORT>\n", argv[0]);
        exit(-1);
    }

    // create socket for server to listen
    if((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
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
    if(bind(listener, (struct sockaddr*)&server, sizeof(struct sockaddr)) == -1)
    {
        printf("bind() error!\n");
        exit(-1);
    }
    //listen
    if (listen(listener, 100) == -1)
    {
        perror("listen");
        exit(3);
    }
    FD_SET(listener, &allSocket);
    fdmax = listener;
    for(;;)
    {
        readfds = allSocket; 
        if (select(fdmax+1, &readfds, NULL, NULL, NULL) == -1)
        {
            perror("select");
            exit(4);
        }
        for(i = 0; i <= fdmax; i++)
        {
            if (FD_ISSET(i, &readfds)) 
            {
                if (i == listener)
                {
                    acceptSocket = accept(listener, (struct sockaddr*)&client, &sin_size);

                    if (acceptSocket == -1)
                    {
                        perror("accept");
                    }
                    else
                    {
                        FD_SET(acceptSocket, &allSocket); 
			            printf("connect with socket %d\n", acceptSocket);
			            // Mang Socket Client 
			            _gSocID[_iSocCount]=acceptSocket;
			            _iSocCount++;
			            // ------------------
                        if (acceptSocket > fdmax)   
                        {
                            fdmax = acceptSocket;
                        }
                    }
                }
                else
                {
                    if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0)
                    {
      			        printf("stop connect %d\n", i);
                        close(i); 
                        FD_CLR(i, &allSocket); 
                    }
                    else
                    {
                        buf[nbytes] = '\0';
                        printf("Receiver From %d : %s\n",i, buf); 
                        iCountSend++;
                        
       //####################### Send Data 
	                if(strcmp(send_data,"q")==0 || strcmp(send_data,"Q")==0)
	                    {
	                    send(i,send_data,strlen(send_data),0);
	                    close(i); /* Close With terminal of Child Socket */
	                    printf(" Close Socket %d ",i);
	                    }
	                else{
						printf(" So Client hien tai connet voi Server %d",iCountSend);
						if(iCountSend==4)
						  {   printf("Sending Messages For Client %d ",i);  
						      gets(send_data);fflush(stdin);
							  send(4,send_data,strlen(send_data),0);
					          send(5,send_data,strlen(send_data),0);
					          firstSend=1;          
					      }
					      if(firstSend==1)
					      {
							 if(iCountSend>4)
							 { printf("Sending Messages For Client %d ",i);  
						      gets(send_data);fflush(stdin);
					          send(4,send_data,strlen(send_data),0);
					          send(5,send_data,strlen(send_data),0);
						    } 
						  }   
                        }
                        
        //#######################  End Send Data              
                    }
                } 
            } 
        } 
    } 
    printf(" SERVER TEMINATED ... ");
    return 0;
}

