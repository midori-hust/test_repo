#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "gtbitio.h"
#include "fgk.c"


#define IN_BUFSIZE 16384
#define PORT 5000
typedef struct taikhoan{
  char name[50];
  char pass[50];
  char code[10];
}account;



typedef struct 
{
  char algorithm[4];
  unsigned long file_size;
} file_stamp;
//creat buffer for I/O
unsigned char input_buf[ IN_BUFSIZE ];
unsigned int nread = 0, in_i = 0;


void Encode(char *source, char *output);
void Decode(char *source, char *output);

int khoa[10];
int giai[10];
int k=10;
void decode()
{
    int i,j;
    for(i=0;i<k;i++)
    for(j=0;j<k;j++) if(khoa[j]==i) giai[i]=j;
}
void intkhoa()
{
     int i,j;
     for(i=0;i<k;i++)
     do
       {
     khoa[i]=rand()%10;
     j=0;
     while((khoa[j]!=khoa[i])&&(khoa[i]<k)) { j=j+1;  }
     if(j>=i)
       break;
 }
       while(i<k);
}
 /**************************************/
char *mahoa(char *chuoi)
{
  int l,i,j,t;
  int resid;
    char tmp[1024];
    l=strlen(chuoi);
    resid = l%k;
    j=0;t=0;
    for(i=0;i<l-resid;i++)
       {
        tmp[i]=chuoi[khoa[j]+t*k];j++;
        if(j==k) {t++;j=0;}
       }
    for(i=0;i<resid;i++)
      tmp[l-resid+i]=chuoi[l-resid+i];
    tmp[l]='\0';
    return tmp;
  }
    /***************************************/
char *giaima(char *chuoi)
{
    int l,i,j,t;
    int resid;
    char tmp[1024];
    decode();
    l=strlen(chuoi);
    resid = l%k;
    j=0;t=0;
    for(i=0;i<l-resid;i++)
       {
        tmp[i]=chuoi[giai[j]+t*k];j++;
        if(j==k) {t++;j=0;}
       }
    for(i=0;i<resid;i++)
      tmp[l-resid+i]=chuoi[l-resid+i];
    tmp[l]='\0';
    return tmp;
   }


  /**************************************/


int main()
{
    FILE*f1, *f2, *f3;
    fd_set allSocket;
    fd_set readfds,writefds;
    int max,addr_len,choice,t;
    int listener,sockfd;
    struct sockaddr_in server_addr, client_addr;
    int sin_size;
    char send_data[1024], recv_data[1024], tempt[1024],data[1024],name[50],pass[50],code[20];
    int bytes_read,i,check,j=0,accnum=0;
    account acclist[100];
    int key=0,limit=0,cont=0;

    //INIT KHOA
    srand(NULL);
    intkhoa();

    //MO FILE ACCOUNT
    f3=fopen("acclist.txt","r");
    while(fgets(tempt,50,f3)!=NULL){
      if(j==0) 
	{
	  tempt[strlen(tempt)-1]='\0';
 	  strcpy(acclist[accnum].username,tempt);j=1;
	}
      else if (j==1)
	{
	  tempt[strlen(tempt)-1]='\0';
	  strcpy(acclist[accnum].password,tempt);j=2;
	}
      else 
	{
	  tempt[strlen(tempt)-1]='\0';
	  strcpy(acclist[accnum].code,tempt);j=0;accnum++;
	}
      }
    fclose(f3);
    //print acc test
    puts("list account");
    for(t=0;t<accnum;t++)
      {
	printf("name: %s\n",acclist[t].username);
	printf("pass: %s\n",acclist[t].password);
      }
    puts("end list");
    //ket noi
    if((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("socket() error!\n");
        exit(0);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    printf("nhap ip: ");
    scanf("%s",tempt);
    while(getchar()!='\n');
    server_addr.sin_addr.s_addr = inet_addr(tempt);//INADDR_ANY;
    bzero(&(server_addr.sin_zero),8);
    if(bind(listener, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        printf("bind() error!\n");
        exit(0);
    }
    if (listen(listener, 5) == -1)
    {
        perror("listen");
        exit(0);
    }
    FD_ZERO(&allSocket);
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_SET(listener, &allSocket);
    max = listener;
    printf("TCPServer waiting for client on port 5000\n");
    while(1)
    {
        readfds = allSocket;
	writefds = allSocket;
        if (select(max+1, &readfds, &writefds, NULL, NULL) == -1)
        {
            perror("select: ");
            exit(0);
        }
	else for(i = 0; i <= max; i++)
        {
            if (FD_ISSET(i, &readfds)||FD_ISSET(i,&writefds))
            {
                if (i == listener)
                {
                    sockfd = accept(listener, (struct sockaddr*)&client_addr, &sin_size);

                    if (sockfd == -1)
                    {
                        perror("accept: ");
                    }
                    else
                    {
                        FD_SET(sockfd, &allSocket);
			printf("Connected with %d\n", sockfd);
                        if (sockfd > max)
                        {
                            max = sockfd;
                        }
                    }
                }
                else
                {
		   //authentication
		    cont++;
	            limit=0;
		    bytes_read = recv(sockfd,recv_data,1024,0);
		    recv_data[bytes_read] = '\0';
		    send(sockfd,"dkm",3,0);
		    if(strcmp(recv_data,"dk")==0) 
		      {
			do{
			  check =0;
			  limit++;
			  bytes_read = recv(sockfd,recv_data,1024,0);
			  recv_data[bytes_read] = '\0';
			  strcpy(name,recv_data);
			  send(sockfd,"dkm",3,0);
			  bytes_read = recv(sockfd,recv_data,1024,0);
			  recv_data[bytes_read] = '\0';
			  strcpy(pass,recv_data);
			  if(strlen(name)<=50&&strlen(pass)<=50) check=1;
			  if(check==1) send(sockfd,"ok",2,0);
			  else if(limit<3) send(sockfd,"invalid",7,0);
			}while(check!=1&&limit<3);
			if(check==1)
			  {
			    strcpy(acclist[accnum].username,name);strcpy(acclist[accnum].password,pass);
			    for(t=0;t<k;t++)
			    intkhoa();
			    for(t=0;t<k;t++) acclist[accnum].code[t]=khoa[t]+'0';
			    acclist[accnum].code[k]='\0';
			    f3 = fopen("acclist.txt","a+");
			    fputs(name,f3);
			    fputs("\n",f3);
			    fputs(pass,f3);
			    fputs("\n",f3);
			    //puts(pass);
			    fputs(acclist[accnum].code,f3);
			    //puts(acclist[accnum].code);
			    fputs("\n",f3);
			    fclose(f3);
			  }
		      }
		    else if(strcmp(recv_data,"dn")==0) do{
			check =0;
			limit++;
			bytes_read = recv(sockfd,recv_data,1024,0);
			recv_data[bytes_read] = '\0';
			strcpy(name,recv_data);
			send(sockfd,"dkm",3,0);
			bytes_read = recv(sockfd,recv_data,1024,0);
			recv_data[bytes_read] = '\0';
			strcpy(pass,recv_data);
			for(j=0;j<accnum;j++)
			  {
			    if(strcmp(name,acclist[j].username)==0&&strcmp(pass,acclist[j].password)==0) {check =1;strcpy(code,acclist[j].code);}
			  }
			if(check==1) send(sockfd,"ok",2,0);
			else if(limit<3) send(sockfd,"invalid",7,0);
		      }while(check!=1&&limit<3);
		    else
		      {
			printf("Stop connect to %d\n", i);
			close(i);
			FD_CLR(i, &allSocket);
			if (cont==10) 
			{
				cont = 0;
				printf("So you want to stop server: y/n");
				gets(tempt);
				if(strcmp(tempt,"y")==0) return 1;
				else break;
			}
		      }
		    if(limit==3)
		      { 
			send(sockfd,"stop",4,0);
			printf("Stop connect to %d\n", i);
			close(i);
			FD_CLR(i, &allSocket);
			if (cont==10) 
			{
				cont = 0;
				printf("So you want to stop server: y/n");
				gets(tempt);
				if(strcmp(tempt,"y")==0) return 1;
				else break;
			}
		      }	
		    for(t=0;t<10;t++)
		      {
			khoa[t]=code[t]-'0';
		      }
		    printf("User %s logged in\n",name);
		    do{
		      //nhan yeu cau lua chon giao dich
		      //key=1;
		      bytes_read = recv(sockfd,recv_data,1024,0);
		      recv_data[bytes_read] = '\0';
		      send(sockfd,"dkm",3,0);
		      if(strcmp(recv_data,"encrypt")==0) choice=1;  //sosanh de dat choice tuong ung theo luachon
		      else if(strcmp(recv_data,"decrypt")==0) choice=2; else choice = 3;
		      switch(choice)
			{
			case 1:
			  //de mo nhan file
			  printf("Encrypt transaction\n");
			  bytes_read = recv(sockfd,recv_data,1024,0);//r
			  recv_data[bytes_read] = '\0';
			  send(sockfd,"dkm",3,0);//s
			  f1=fopen(recv_data,"w+");
			  strcpy(tempt,recv_data);	
			  bytes_read = recv(sockfd,recv_data,1024,0);//r
			  recv_data[bytes_read]= '\0';
			  while(strcmp(recv_data,"CLOSE")!=0)
			    {
			      fputs(recv_data,f1);
			      send(sockfd,"dkm",3,0);
			      bytes_read = recv(sockfd,recv_data,1024,0);
			      recv_data[bytes_read]= '\0';
			    }
			  fclose(f1);
			  printf("Received file %s\n",tempt);
			  //end de mo nhan file
			  
			  //bat dau ma hoa
			/*
			  f1=fopen(tempt,"r+");
			  f2=fopen("mahoa.txt","w+");
			  if(f1==NULL) {printf("open file error!");break;}
			  if(f2==NULL) {printf("open file error!");break;}
			  while(fgets(tempt,1024,f1)!=NULL){
			    strcpy(data,mahoa(tempt));
			    fputs(data,f2);
			  }
			  fclose(f1);
			  fclose(f2);*/
			  Encode(tempt,"mahoa.ah");
			  printf("Encrypted.\n");
			  //bat dau gui tra file ma hoa
			  printf("Sent file mahoa.ah\n");
			  send(sockfd,"mahoa.ah",9,0);
			  bytes_read = recv(sockfd,recv_data,1024,0);
			  recv_data[bytes_read] = '\0';
			  f1=fopen("mahoa.ah","rb");
			  while(fgets(send_data,1024,f1)!=NULL)
			    {
			      send(sockfd,send_data,strlen(send_data),0);
			      bytes_read = recv(sockfd,recv_data,1024,0);
			      recv_data[bytes_read] = '\0';
			    }
			  send(sockfd,"CLOSED",5,0);
			  fflush(stdout);
			  break;
			case 2: 
			  printf("Decrypt transaction\n");
			  bytes_read = recv(sockfd,recv_data,1024,0);//r
			  recv_data[bytes_read] = '\0';
			  send(sockfd,"dkm",3,0);//s
			  f1=fopen(recv_data,"w+");
			  strcpy(tempt,recv_data);	
			  bytes_read = recv(sockfd,recv_data,1024,0);//r
			  recv_data[bytes_read]= '\0';
			  while(strcmp(recv_data,"CLOSE")!=0)
			    {
			      fputs(recv_data,f1);
			      send(sockfd,"dkm",3,0);
			    bytes_read = recv(sockfd,recv_data,1024,0);
			    recv_data[bytes_read]= '\0';
			    }
			  fclose(f1);
			  printf("Received file %s!\n",tempt);
			  //end de mo nhan file
			  
			  //bat dau giai ma
			  Decode(tempt,"giaima.out");
			  //bat dau gui tra file giai ma
			  printf("Send file giaima.out\n");
			  send(sockfd,"giaima.out",10,0);
			  bytes_read = recv(sockfd,recv_data,1024,0);
			  recv_data[bytes_read] = '\0';
			  f1=fopen("giaima.out","rb");
			  while(fgets(send_data,1024,f1)!=NULL)
			    {
			    send(sockfd,send_data,strlen(send_data),0);
			    bytes_read = recv(sockfd,recv_data,1024,0);
			    recv_data[bytes_read] = '\0';
			    }
			  send(sockfd,"CLOSED",5,0);
			  fflush(stdout);
			  break;
			case 3:break;
			  
			}
		    }while(choice!=3);
		    printf("Stop connect from %d\n", i);
		    close(i);
		    FD_CLR(i, &allSocket);
		   if (cont==10) 
			{
				cont = 0;
				printf("So you want to stop server: y/n");
				gets(tempt);
				if(strcmp(tempt,"y")==0) return 1;
				else break;
			}
		}
	    }
	}
    }
    close(sockfd);
}

void Encode(char *source, char *output)
{ 
  unsigned long in_file_len, out_file_len;
  FILE *in;
  file_stamp fstamp;
  if ( (in = fopen( source, "rb" )) == NULL ) 
    {
      fprintf(stderr, "\nError opening input file.");
    }
  if ( (pOUT = fopen( output, "wb" )) == NULL ) 
    {
      fprintf(stderr, "\nError opening output file.");
    }
  init_put_buffer();
  fprintf(stderr, "\nName of input file : %s", source );
  fprintf(stderr, "\nName of output file: %s", output );
  /* get file length. */
  fseek( in, 0, SEEK_END );
  in_file_len = ftell( in );
  
  /* ===== The Main Huffman Implementation ======= */
  
  fprintf(stderr, "\n\nHuffman compressing...");
  
  /*	This is a DYNAMIC algorithm,
	so no need to read and store stats. */
  
  /* encode FILE STAMP. */
  rewind( pOUT );
  strcpy( fstamp.algorithm, "FGK" );
  fstamp.file_size = in_file_len;
  fwrite( &fstamp, sizeof(file_stamp), 1, pOUT );
  
  /* start huffman encoding the symbols/file bytes. */
  rewind( in );
  
  /* make sure all symbol node
     addresses are NULL. */
  init_hufflist();

  /* get first byte. */
  hc = fgetc( in );
  if ( hc == EOF ) goto halt_prog;
  
  /*
    create first 0-node which quickly becomes
    the root of the tree.
  */
  top = zero_node = create_node();
  
  /* output first byte. */
  fputc( (unsigned char) hc, pOUT );

  /* recompute the tree if necessary. */
  update_treeFGK( hc );  /* pass the symbol. */
  while( 1 ) 
    {
      /* load the input buffer. */
      nread = fread( input_buf, 1, IN_BUFSIZE, in );
      if ( nread == 0 ) break;
      in_i = 0;
      
      /* get bytes from the buffer and compress them. */
      while( in_i < nread )
	{
	  hc = (unsigned char) *(input_buf+in_i);
	  ++in_i;
	  
	  /* encode the byte hc. */
	  if ( hufflist[ hc ] )
	    {   
	      /* VALID address; previously seen. */
	      /* output the symbol's code. */
	      hcompress( hufflist[ hc ] );
	    }
	  else 
	    {	
	      /* NULL address, a new byte! */
	      /* output the zero node's code. */
	      hcompress( zero_node );
	      
	      /* send the actual byte. */
	      put_nbits( hc, 8 );
	    }
	  
	  /* recompute the tree if necessary. */
	  update_treeFGK( hc );	/* pass the symbol. */
	}
    }
  flush_put_buffer();
  fprintf(stderr, "done.");
  
  /* get outfile's size and get compression ratio. */
  out_file_len = ftell( pOUT );
  
  fprintf(stderr, "\n\nLength of input file     = %15lu bytes", in_file_len );
  fprintf(stderr, "\nLength of output file    = %15lu bytes", out_file_len );
  fprintf(stderr, "\nCompression ratio:         %15.2f %%\n",
	  ( ((float) in_file_len - (float) out_file_len) / (float) in_file_len
	    ) * (float) 100
	  );
  
 halt_prog:
  
  free_put_buffer();
  if ( in ) fclose( in );
	if ( pOUT ) fclose( pOUT );
	
}
void Decode(char *source,char *output)
{
  unsigned long in_file_len = 0, out_file_len = 0;
  FILE *out;
  file_stamp fstamp;
  if ( (gIN = fopen( source, "rb" )) == NULL ) 
    {
      fprintf(stderr, "\nError opening input file.");
    }
  if ( (out = fopen( output, "wb" )) == NULL ) 
    {
      fprintf(stderr, "\nError opening output file.");
    }
  
	fprintf(stderr, "\nName of input file : %s", source );
	fprintf(stderr, "\nName of output file: %s", output );
	
	/* get file length. */
	fseek( gIN, 0, SEEK_END );
	in_file_len = ftell( gIN );
	
	/* ===== The Main Huffman Implementation ======= */
	
	fprintf(stderr, "\n\nDecompressing...");
	
	/* This is a DYNAMIC algorithm, so no need to read stats. */
	
	/* start the decoding process. */
	rewind( gIN );
	
	/* read first the file stamp/header. */
	fread( &fstamp, sizeof(file_stamp), 1, gIN );
	
	/* make sure all symbol node
	   addresses are NULL. */
	init_hufflist();

	/* get FIRST symbol. */
	hc = fgetc( gIN );
	out_file_len = fstamp.file_size - 1;
	
	/*
	  create first 0-node which quickly becomes the root
	  of the Huffman tree.
	*/
	top = zero_node = create_node();
	
	/* output first symbol as a raw byte. */
	fputc( (unsigned char) hc, out );
	
	/* Update the Huffman tree. */
	update_treeFGK( hc );	/* pass the symbol. */
	
	/* now get the bit stream. */
	init_get_buffer();
	
	while ( out_file_len-- ) {
	  hc = hdecompress( top );
	  
	  if ( hc == ZERO_NODE_SYMBOL ) {	/* unseen byte. */
	    /* get raw byte. */
	    hc = get_nbits( 8 );
	  }
	  
	  /* update the Huffman tree. */
		update_treeFGK( hc );	/* pass the symbol. */
		
		/* output the decoded byte. */
		putc( (unsigned char) hc, out );
	}
	fprintf(stderr, "done.");
	
	/* get outfile's size. */
	out_file_len = ftell( out );

	fprintf(stderr, "\n\nLength of input file     = %15lu bytes", in_file_len );
	fprintf(stderr, "\nLength of output file    = %15lu bytes\n", out_file_len );
	
 halt_prog:
	
	free_get_buffer();
	if ( gIN ) fclose( gIN );
	if ( out ) fclose( out );
	
}
