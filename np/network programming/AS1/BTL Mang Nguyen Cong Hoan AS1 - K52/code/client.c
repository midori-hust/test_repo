#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


#define PORT 5000	  /* Open Port on Remote Host */
#define MAXSIZE 500000
#define MAXDATASIZE 100   /* Max number of bytes of data */
void error(char *msg)
{
    perror(msg);
    exit(0);
}

main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int byte_recv;
    char fileluu[256];

    char buffer[256],filename[256];
    argv[1] = "127.0.0.1";
    portno = 5000;
    // Tao socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
        error("Loi tao socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,&serv_addr,sizeof(serv_addr)) == -1)
        error("Loi connecting");
    do{
        //==================dang nhap
        recv(sockfd, buffer, 256, 0);
	    printf("%s\n",buffer);
	    //nhap username
        printf("Nhap: ");
	    bzero(buffer,256);
	    fgets(buffer,255,stdin);
        send(sockfd,buffer, strlen(buffer),0);//gui xong username
        byte_recv =recv(sockfd, buffer, 256, 0);
        buffer[byte_recv-1] = '\0';
	    if(strcmp(buffer,"sai")==0)
        {
        //================= Dang ki tai khoan
        //neu sai username
        recv(sockfd, buffer, 256, 0);
	    printf("%s\n",buffer);
        printf("Nhap: ");
	    bzero(buffer,256);
	    fgets(buffer,255,stdin);
        send(sockfd,buffer, strlen(buffer),0);//gui xong username moi
        //nhap pass moi
        recv(sockfd, buffer, 256, 0);
	    printf("%s\n",buffer);
        printf("Nhap: ");
	    bzero(buffer,256);
	    fgets(buffer,255,stdin);
        send(sockfd,buffer, strlen(buffer),0);//gui pass moi
        recv(sockfd, buffer, 256, 0);
	    printf("%s\n",buffer);//dang ki thanh cong
	    break;
        }
        else
        {
	    //nhap password
        recv(sockfd, buffer, 256, 0);
	    printf("%s\n",buffer);
        printf("Nhap: ");
	    bzero(buffer,256);
	    fgets(buffer,255,stdin);
        send(sockfd,buffer, strlen(buffer),0);
        //check pass
        byte_recv =recv(sockfd, buffer, 256, 0);
        buffer[byte_recv-1] = '\0';
	    if(strcmp(buffer,"sai2") == 0){
	        //recv(sockfd, buffer, 256, 0);
	        printf("Dang nhap khong thanh cong. Vui long thu lai!!!!\n\n");
            close(sockfd); /* close fd =) */
	        break;
	    }else{
        //hien thi menu
        recv(sockfd, buffer, 256, 0);
	    printf("%s\n",buffer);
        printf("Chon: ");}
	    bzero(buffer,256);
	    fgets(buffer,255,stdin);
	    send(sockfd,buffer, strlen(buffer),0);//gui lua chon den server
	    // send data to server
	    if(buffer[0] == '3')
			break;
	    else
	      {
	          //nhap file va gui di
  FILE * pFile;
  FILE *pFile1;
  long lSize;
  char * buffer;
  size_t result;
  char filename[20];

  printf ("Nhap ten file:");
   scanf ("%s%*c", filename);
//gets(buffer);
//send(sockfd,filename,strlen(filename),0);
  int fd, numbytes;	  /* files descriptors */
  char buf[MAXDATASIZE];  /* buf will store received text */
  char buf1[MAXDATASIZE];

  pFile = fopen ( filename, "rb" );
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
  if ((numbytes = send (sockfd, buffer, lSize, 0)) == -1){
      printf ("send()error\n");
      exit(-1);
    }
  printf("--%ld ki tu da duoc gui di--\n", lSize);
  printf ("Ket thuc gui\n");
//nhan file da ma hoa
  if ((numbytes=recv(sockfd,buffer,MAXSIZE,0)) == -1){  /* calls recv() */
    printf("recv() error\n");
    exit(-1);
  }
   //printf ("-Nhan duoc %ld ki tu da ma hoa-\n", numbytes);
   printf("File tu Server gui ve: \n%s\n",buffer); /* it prints server's welcome message =) */
   printf("Nhap ten file de luu lai: ");
   scanf("%s%*c",fileluu);
   FILE *pFileluu;
   pFileluu = fopen (fileluu,"wb");
   fwrite(buffer,1,numbytes,pFileluu);//luu lai file da nhan
   fclose(pFileluu);
   exit(-1);
        }
        }
	}while(1);
    close(sockfd); /* close fd =) */
}
