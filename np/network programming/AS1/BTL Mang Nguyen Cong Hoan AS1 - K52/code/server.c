#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/wait.h>
#include <signal.h>
#include "huffman.c"
#include "dangnhap.c"

#define true 1
#define false 0
#define PORT 5000
#define BACKLOG 10
#define PORT 5000   /* Port that will be opened */
#define MAXSIZE 500000
#define MAXDATASIZE 100   /* Max number of bytes of data */
void handle_child(int x)
{
    pid_t rc;
    int stat;
    while((rc=waitpid(-1,&stat,WNOHANG))>0)
     { printf(" Child terminate with PID : %d \n ",rc);
           if(WIFEXITED(stat))
               printf(" Child exited with code %d \n", WEXITSTATUS(stat));
           else
               printf(" Child terminated abnormally \n");
     }
   signal(SIGCHLD,handle_child);
   return ;
}
main(){
  struct sockaddr_in server;
  struct sockaddr_in client;
  pid_t pid;
  int sock;
  int sock_client;
  int sin_size;
  int byte_recv;
  char send_data[1024];
  char recv_data[1024];
  struct hostent *host;
  int stat_val;
  pid_t child_pid;

  	    int checkuser, checkpass;

    huffman_node_t *huffmanTree;        /* root of huffman tree */
    int opt;
    char *inFile, *outFile;
    MODES mode;
long numbyte; // number of byte receive
  // Tao kiem soat tin hieu
  signal(SIGCHLD, handle_child);

  if((sock = socket(AF_INET,SOCK_STREAM,0)) == -1) {
    perror("Socket");
    exit(0);
  }
  server.sin_family = AF_INET;
  server.sin_port  = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;
  /*   Cach Khac Lay LocalHost
  server.sin_addr = *((struct in_addr *)host->h_addr);
  server.sin_addr.s_addr=inet_ntoa();
  */
  bzero(&(server.sin_zero),8);
  if(bind(sock,(struct sockaddr*)&server,sizeof(struct sockaddr)) == -1){
    perror("bind() error!!");
    exit(0);
  }
  if(listen(sock,BACKLOG) == -1){
    perror("Listen() error!!");
    exit(0);
  }


  while(1){
    sin_size = sizeof(struct sockaddr_in);
    sock_client = accept(sock,(struct sockaddr*)&client,&sin_size);
    if( sock_client == -1){
      perror("Accept() error!!\n");
      exit(0);
    }

   // Forking Server
   pid = fork();
   switch(pid){
case -1: //khong the tao them chuong trinh con
        printf("can't fork()\n");break;
case 0:
      close(sock);       /* Child Socket Listening ; */
      printf("Have a connection from:%s\n\n",inet_ntoa(client.sin_addr));
         FILE *pFilelog;
         pFilelog = fopen ("log.txt", "a");
         time_t rawtime;
         struct tm *timeinfo;
         time(&rawtime);
         timeinfo = localtime(&rawtime);
         fprintf(pFilelog,"%s%s\n",asctime(timeinfo),inet_ntoa(client.sin_addr));
         fclose(pFilelog);
      send(sock_client,"\t\tDang nhap he thong!\n\t\tUsername:",50,0);
      byte_recv = recv(sock_client,recv_data,1024,0);
      printf("Username: %s \n" , recv_data);
      //kiem tra username
	recv_data[byte_recv-1] = '\0';
	import();
	//if(strcmp(recv_data,"conghoan")!=0)
	if(timkiem(recv_data)!=1)
	{
	    send(sock_client,"sai",50,0);//neu sai ten
	    checkuser =-1;
	    }else
	    {
	    send(sock_client,"dung",50,0);//neu dung user
	    checkuser =0;
	    }
	    if(checkuser == -1)
      {
      send(sock_client,"\tTai khoan nay chua ton tai, nhap Username => Dang ki\n\t\tUsername:",150,0);
      byte_recv = recv(sock_client,recv_data,1024,0);
      recv_data[byte_recv-1] = '\0';
      printf("New Username: %s \n" , recv_data);
      char newuser[30],newpass[30];
      strcpy(newuser, recv_data);
          send(sock_client,"\tNhap Password => Dang ki\n\t\tPassword:",150,0);
      byte_recv = recv(sock_client,recv_data,1024,0);
      recv_data[byte_recv-1] = '\0';
      printf("New Password: %s \n" , recv_data);
      strcpy(newpass, recv_data);
      nhapmoi(newuser, newpass);
          send(sock_client,"Dang ki thanh cong",50,0);
	      close(sock_client); /* Close With terminal of Child Socket */
	      break;
      }
      else{
      send(sock_client,"\n\t\tPassword:",50,0);
      byte_recv = recv(sock_client,recv_data,1024,0);
      printf("Password: %s \n" , recv_data);
      //kiem tra password
	recv_data[byte_recv-1] = '\0';
    //if(strcmp(recv_data,"conghoan")!=0)
    if(pass(recv_data)!=1)
	{
	    send(sock_client,"sai2",50,0);//sai pass
	    checkpass =-1;
	    }else
	    {
	    send(sock_client,"dung2",50,0);//dung pass
	    checkpass = 0;
	    }
      if(checkpass == -1)//neu sai
      {
          //send(sock_client,"Dang nhap khong thanh cong",50,0);
	      close(sock_client); /* Close With terminal of Child Socket */
          break;
      }
      else
{
      //menu chuong trinh
   send(sock_client,"\t\tWelcome to my server!\n\t\tMenu:\n\t\t1: Ma hoa.\n\t\t2: Giai ma.\n\t\t3: Thoat.",200,0);

	byte_recv = recv(sock_client,recv_data,1024,0);
	recv_data[byte_recv] = '\0';
	if(strcmp(recv_data,"3")==0)
            {
	    close(sock_client); /* Close With terminal of Child Socket */
	    break;
	    }
//=================================giai ma mot file gui toi
	if(recv_data[0]=='2')
	{
	//else{
	    printf("\nClient da chon: %s -- Giai ma\n" , recv_data);
	    //nhan file va luu file
  FILE *pFileluu;
  pFileluu = fopen ("giaima.txt", "wb");
   if ((numbyte = recv(sock_client,recv_data,MAXSIZE,0)) == -1){  /* calls recv() */
    printf("recv() error\n");
    exit(-1);
  }
  printf ("Da nhan -%ld-ki tu", numbyte);
   fwrite(recv_data,1,numbyte,pFileluu);//luu lai file da nhan
   //fclose(pFileluu);
   printf("File tu Client da Upload: \n%s\n",recv_data); /* it prints server's welcome message =) */
   fclose(pFileluu);
        //ma hoa
        DecodeFile(huffmanArray,"giaima.txt","da_giaima.txt");
{
  FILE * pFile;
  FILE *pFile1;
  long lSize;
  char * buffer;
  size_t result;

  int fd, numbytes;	  /* files descriptors */
  char buf[MAXDATASIZE];  /* buf will store received text */
  char buf1[MAXDATASIZE];

  pFile = fopen ("da_giaima.txt", "rb" );
  // pFile1 = fopen ("myfile1.txt", "wb");

  if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

  // obtain file size:
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);

  // allocate memory to contain the whole file:
  buffer = (char*) malloc (sizeof(char)*lSize);
  if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

  // copy the file into the buffer:
  result = fread (buffer,1,lSize,pFile);
  if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
  if ((numbytes = send (sock_client, buffer, lSize, 0)) == -1){
      printf ("send()error\n");
      exit(-1);
    }
  printf("--%ld ki tu da duoc gui di--\n", lSize);

  printf ("Ket thuc gui\n");
  exit(-1);
//  if ((numbytes=recv(fd,buf,MAXDATASIZE,0)) == -1){  /* calls recv() */
//    printf("recv() error\n");
//    exit(-1);
//  }
       }
	  close(sock_client); /* Close With terminal of Child Socket */
	  break;
	}
//  ----------------------==-=-===================== ma hoa file gui toi
if(recv_data[0]=='1'){
    printf("\nClient da chon: %s -- Ma hoa\n" , recv_data);
	    //nhan file va luu file
  FILE *pFileluu;
  pFileluu = fopen ("mahoa.txt", "wb");
   if ((numbyte = recv(sock_client,recv_data,MAXSIZE,0)) == -1){  /* calls recv() */
    printf("recv() error\n");
    exit(-1);
  }
  printf ("Da nhan -%ld-ki tu", numbyte);
   fwrite(recv_data,1,numbyte,pFileluu);//luu lai file da nhan
   //fclose(pFileluu);
   printf("File tu Client da Upload: \n%s\n",recv_data); /* it prints server's welcome message =) */
   fclose(pFileluu);
        //ma hoa
        huffmanTree = GenerateTreeFromFile("mahoa.txt");
        EncodeFile(huffmanTree,"mahoa.txt","da_mahoa.txt");
        PrintCode(huffmanTree,"bangma.txt");
        FreeHuffmanTree(huffmanTree);     /* free allocated memory */
{
  FILE * pFile;
  FILE *pFile1;
  long lSize;
  char * buffer;
  size_t result;

  int fd, numbytes;	  /* files descriptors */
  char buf[MAXDATASIZE];  /* buf will store received text */
  char buf1[MAXDATASIZE];

  pFile = fopen ("da_mahoa.txt", "rb" );
  // pFile1 = fopen ("myfile1.txt", "wb");

  if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

  // obtain file size:
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);

  // allocate memory to contain the whole file:
  buffer = (char*) malloc (sizeof(char)*lSize);
  if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

  // copy the file into the buffer:
  result = fread (buffer,1,lSize,pFile);
  if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
  if ((numbytes = send (sock_client, buffer, lSize, 0)) == -1){
      printf ("send()error\n");
      exit(-1);
    }
  printf("--%ld-- ki tu da ma hoa gui ve cho Client--\n", lSize);
  printf ("Ket thuc gui\n");
  exit(-1);
//  if ((numbytes=recv(fd,buf,MAXDATASIZE,0)) == -1){  /* calls recv() */
//    printf("recv() error\n");
//    exit(-1);
//  }
       }
	  close(sock_client); /* Close With terminal of Child Socket */
	  break;
	}
	  }
	}
case 1:
    if(strcmp(recv_data,"3")==0){
      close(sock); /* Close Listening */
      break;
   }
   break;
    }
    }

    close(sock_client); /* Parent Close Connect Socket */
  }
