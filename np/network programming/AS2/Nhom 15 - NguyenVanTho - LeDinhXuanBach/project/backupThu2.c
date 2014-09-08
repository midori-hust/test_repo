/* 
   PLEASE READ THE FILE NB-APOLOGY!!!!  There are some things you should
   know about this source before you read it.  Thanks.

   
   Quang Ngo alerted me to a bug where the variable listnum in deal_with_data()
   wasn't being passed in by parameter, thus it was always garbage. I have
   quick-fixed this in the code below. - Spencer (October 12, 1999)
   

   Non blocking server demo 
   By Vic Metcalfe (vic@acm.org)
   For the unix-socket-faq
*/

#include "sockhelp.h"
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "supportLib.h"

#define REGISTER 1
#define LOGIN 2
#define REQUEST 3
#define ANS 4
#define TIMEOUT 5
#define PRO 6
#define NOT_PRO 7
#define BACKLOG 2
int sock;            /* The socket file descriptor for our "listening"
                   	socket */
int connectlist[5];  /* Array of connected sockets so we know who
	 		we are talking to */
fd_set socks;        /* Socket file descriptors we want to wake
			up for, using select() */
int highsock;	     /* Highest #'d file descriptor, needed for select() */

int type;// REGISTER OR LOGIN

int indexMax=0;//Max number userLogedIn

int cqa=0;

QA currentQA;
//=======================================
NamePass cutNamePass(char str[])
{
  int i,j,len;
  NamePass dt;
  len=strlen(str);
  for(i=0;i<len;i++)
    {
      if(str[i]=='+')
	{
	  str[i]='\0';
	  strcpy(dt.name,str);
	  str=str+i+1;
	  for(j=0;j<len;j++)
	    if(str[j]=='+')
	      {
		str[j]='\0';
		strcpy(dt.pass,str);
		str=str+j+1;
		if(strcmp(str,"REG")==0)
		  type=REGISTER;
		else if(strcmp(str,"LOG")==0)
		  type=LOGIN;
		return dt;
	      }
	}
    }
}
int checkRequestAns(char Buffer[])
{
  int i;
  for(i=0;i<strlen(Buffer);i++)
    {
      if(Buffer[i]=='+')
	return REQUEST;
    }
  return ANS;
}
int calculateMark(int listnum,User *listUs,char ans[],QA q)
{
  int i;
  for(i=0;i<indexMax;i++)
    {
      if(connectlist[listnum]==listUs[i].FD)
	break;
    }
  if(q.toAns!=TIMEOUT)
    {
      if(strcmp(q.ans,ans)==0)
	{
	  listUs[i].mark +=10;
	  printf("Correct!\n");
	}
      else
	{
	  printf("Incorrect!\n");
	  if(strcmp(q.p,"P2_")==0)
	    {
	       listUs[i].mark -=5;
	    }
	}
    }
  printf("USER: %s MARK: %d\n",listUs[i].name,listUs[i].mark);
}
//==================================================================
void setnonblocking(int sock)
{
	int opts;

	opts = fcntl(sock,F_GETFL);
	if (opts < 0) {
	  perror("fcntl(F_GETFL)");
	  exit(EXIT_FAILURE);
	}
	opts = (opts | O_NONBLOCK);
	if (fcntl(sock,F_SETFL,opts) < 0) {
	  perror("fcntl(F_SETFL)");
	  exit(EXIT_FAILURE);
	}
}

void build_select_list() {
	int listnum;	     /* Current item in connectlist for for loops */

	/* First put together fd_set for select(), which will
	   consist of the sock veriable in case a new connection
	   is coming in, plus all the sockets we have already
	   accepted. */
	
	
	/* FD_ZERO() clears out the fd_set called socks, so that
		it doesn't contain any file descriptors. */
	
	FD_ZERO(&socks);
	
	/* FD_SET() adds the file descriptor "sock" to the fd_set,
		so that select() will return if a connection comes in
		on that socket (which means you have to do accept(), etc. */
	
	FD_SET(sock,&socks);
	
	/* Loops through all the possible connections and adds
		those sockets to the fd_set */
	
	for (listnum = 0; listnum < BACKLOG; listnum++) {
		if (connectlist[listnum] != 0) {
			FD_SET(connectlist[listnum],&socks);
			if (connectlist[listnum] > highsock)
				highsock = connectlist[listnum];
		}
	}
}

void handle_new_connection() {
	int listnum;	     /* Current item in connectlist for for loops */
	int connection; /* Socket file descriptor for incoming connections */

	/* We have a new connection coming in!  We'll
	try to find a spot for it in connectlist. */
	connection = accept(sock,NULL,NULL);
	if (connection < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	setnonblocking(connection);
	for (listnum = 0; (listnum < BACKLOG) && (connection != -1); listnum ++)
		if (connectlist[listnum] == 0) {
			printf("\nConnection accepted:   FD=%d; Slot=%d\n",
				connection,listnum);
			connectlist[listnum] = connection;
			sock_puts(connection,"Connected yoooo!\r\n");  
			connection = -1;
		}
	if (connection != -1) {
		/* No room left in the queue! */
		printf("\nNo room left for new client.\n");
		sock_puts(connection,"Sorry, this server is too busy.Try again later!\r\n");  
			       
		close(connection);
	}
}
void deal_with_data(
	int listnum			/* Current item in connectlist for for loops */
	,User *listUs,
	QA *listQA
	) {
	char buffer[80];     /* Buffer for socket reads */
	char *s,s1[2],s2[2];      /* Used in processing buffer */
	s=(char*)malloc(sizeof(char)*7);
	NamePass namep;
	NamePass *dt;
	char fileName[20];
	int i=0,total=0;
	dt=(NamePass*)malloc(sizeof(NamePass)*100);
	if (sock_gets(connectlist[listnum],buffer,80) < 0) {
		/* Connection closed, close this end
		   and free up entry in connectlist */
		printf("\nConnection lost: FD=%d;  Slot=%d\n",
			connectlist[listnum],listnum);
		close(connectlist[listnum]);
		connectlist[listnum] = 0;
	
	} else {
		/* We got some data, so upper case it
		   and send it back. */
		//printf("\nReceived: %s From: %d; ",buffer,connectlist[listnum]);
		/*cur_char = buffer;
		while (cur_char[0] != 0) {
			cur_char[0] = toupper(cur_char[0]);
			cur_char++;
			}*/
		//buffer[strlen(buffer)-1]='\0';
		if(checkRequestAns(buffer)==REQUEST)
		  {
		    printf("REQUEST PROCESSING.....\n");
		    strcpy(fileName,"demo.txt");
		    namep=cutNamePass(buffer);
		    dt=getNamePassFromFile(fileName,&total);
		    if(type==REGISTER)
		      {
			if(compareForRegister(namep,dt,total)==1)
			  {
			    //printf("OK!REGISTERD\n");
			    strcpy(buffer,"OK!REGISTERD!");
			    registerToFile(fileName,namep);
			  }
			else
			  strcpy(buffer,"BAD!");
		      }
		    else if(type==LOGIN)
		      {
			if(compareForLogin(namep,dt,total)==1)
			  {
			    //printf("OK!LOGED IN\n");
			    strcpy(buffer,"OK!LOGED IN!");
			    listUs=userLogedIn(namep,connectlist[listnum],listUs,&indexMax);
			    for(i=0;i<indexMax;i++)
			      {
				printf("listUs: %s ",listUs[i].name);
			      }
			    printf("\n");
			  }
			else
			  // printf("BAD!\n");
			  strcpy(buffer,"BAD!");
		      }
		    sock_puts(connectlist[listnum],buffer);
		    sock_puts(connectlist[listnum],"\n");
		    printf("Responded: %s",buffer);
		    printf("To: %d \n",connectlist[listnum]);
		   
		  }
		else //ANS
		  {
		    
		    strcpy(s,buffer);
		    s[1]='\0';
		    strcpy(s1,s);//ANS
		    printf("\nANS: %s From %s\n",s1,listUs[listnum].name);
		    strcpy(s,buffer);
		    s=s+1;
		    strcpy(s2,s);//index QA ANS for
		    i=atoi(s2);
		    printf("For quetion %d\n",i);
		    calculateMark(listnum,listUs,s1,listQA[cqa]);
		  }
		  
	}
}

void read_socks(User *listUs,QA *listQA) {
	int listnum;	     /* Current item in connectlist for for loops */

	/* OK, now socks will be set with whatever socket(s)
	   are ready for reading.  Lets first check our
	   "listening" socket, and then check the sockets
	   in connectlist. */
	
	/* If a client is trying to connect() to our listening
		socket, select() will consider that as the socket
		being 'readable'. Thus, if the listening socket is
		part of the fd_set, we need to accept a new connection. */
	
	if (FD_ISSET(sock,&socks))
		handle_new_connection();
	/* Now check connectlist for available data */
	
	/* Run through our sockets and check to see if anything
		happened with them, if so 'service' them. */
	
	for (listnum = 0; listnum < BACKLOG; listnum++) {
		if (FD_ISSET(connectlist[listnum],&socks))
		  deal_with_data(listnum,listUs,listQA);
	} /* for (all entries in queue) */
}
void write_socks(char q[])
{
  	int listnum;	     /* Current item in connectlist for for loops */
	for (listnum = 0; listnum < BACKLOG; listnum++) {
	  if(connectlist[listnum]!=0)
	    {
	      sock_puts(connectlist[listnum],q);
	      sock_puts(connectlist[listnum],"\n");
	      //printf("Send Question: \n");
	      //printQuestion(q);
	      //printf("To: %d \n",connectlist[listnum]);
	    }
	} /* for (all entries in queue) */
}

//--------------------------------------------------------

//----------------------------------------------------------
int main (argc, argv) 
int argc;
char *argv[];
{
	char *ascport;  /* ASCII version of the server port */
	int port;       /* The port number after conversion from ascport */
	struct sockaddr_in server_address; /* bind info structure */
	int reuse_addr = 1;  /* Used so we can re-bind to our port
				while a previous connection is still
				in TIME_WAIT state. */
	struct timeval timeout;  /* Timeout for select */
	int readsocks;	     /* Number of sockets ready for reading */
	User *listUs;
	listUs=(User*)malloc(sizeof(User)*5);
	QA *listQA;
	listQA=(QA*)malloc(sizeof(QA)*100);
	char start[7],next[7],*sdb;
	sdb=(char*)malloc(sizeof(char)*100);
	strcpy(start,"init");
	int i=0,total;
	double db;
	long temp=0;
	time_t start1,start2;
	int process;
	/* Make sure we got a port number as a parameter */
	if (argc < 3) {
	  printf("Usage: %s %s HOSTADDR PORT \r\n",argv[0],argv[1]);
		exit(EXIT_FAILURE);
	}

	/* Obtain a file descriptor for our "listening" socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	/* So that we can re-bind to it without TIME_WAIT problems */
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse_addr,
		sizeof(reuse_addr));
	/* Set socket to non-blocking with our setnonblocking routine */
	setnonblocking(sock);

	/* Get the address information, and bind it to the socket */
	ascport = argv[1]; /* Read what the user gave us */
	/*port = atoport(ascport); /* Use function from sockhelp to
                                    convert to an int */
	
	memset((char *) &server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	if(strcmp(argv[1],"127.0.0.1")==0)
	  server_address.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr("ip")
	else
	  server_address.sin_addr.s_addr = inet_addr(argv[1]);
	server_address.sin_port = htons(atoi(argv[2]));//port;
	if (bind(sock, (struct sockaddr *) &server_address,
	  sizeof(server_address)) < 0 ) {
		perror("bind");
		close(sock);
		exit(EXIT_FAILURE);
	}
		
	/* Set up queue for incoming connections. */
	listen(sock,BACKLOG);

	/* Since we start with only one socket, the listening socket,
	   it is the highest socket so far. */
	highsock = sock;
	memset((char *) &connectlist, 0, sizeof(connectlist));
	
	while (1) { /* Main server loop - for accept connect*/
		build_select_list();
		timeout.tv_sec=0;
		timeout.tv_usec = 0;
		readsocks = select(highsock+1, &socks, (fd_set *) 0, 
		  (fd_set *) 0,&timeout);
		
		if (readsocks < 0) {
			perror("select");
			exit(EXIT_FAILURE);
		}
		if (readsocks == 0) {
			/* Nothing ready to read, just show that
			   we're alive */
			//printf(".");
		
			fflush(stdout);
		} else{
			printf("read_socks .....\n");
			read_socks(listUs,listQA);
			/*if(indexMax>=1 && strcmp(start,"init")==0)
			  {
			    printf("Start?(y or n):");
			    gets(start);
			    if(strcmp(start,"y")==0)
			      {
				write_socks("START!");
				break;
			      }
			    else
			      strcpy(start,"init");
			      }*/
			if(indexMax==BACKLOG)
			  break;
		}
	} /* while(1) */

	printf("Start\n");
	write_socks("START!");
			
	listQA=getQAFromFile("QA.txt",&total);
	cqa=i=0;
	int t=0;
	while(i<total)
	  {
	    printf("Send Question?(y or n)");
	    gets(next);
	    if(strcmp(next,"y")==0)
	      {
		if(i>=1)
		  listQA[i-1].toAns=TIMEOUT;
		currentQA=listQA[i];
		cqa=i;
		write_socks(currentQA.question);
		printf("----------------------\n");
		printf("Send Question:\n");
		printQuestion(currentQA.question);
		time(&start1);
		i++;
		
	      }
	    while(1)
	      {
		time(&start2);
		if(start2-start1>15)
		  {
		    printf("\n");
		    break;
		  }
		if((start2-start1)%2==0||(start2-start1)%3==0||(start2-start1)%5==0||(start2-start1)==0||(start2-start1)==1||(start2-start1)==7||(start2-start1)==11||(start2-start1)==13)
		  {
		    if(start2-start1>t)
		      printf("%d ",(int)(15-(start2-start1)));
		  }
		build_select_list();
		timeout.tv_sec=0;
		timeout.tv_usec = 0;
		readsocks = select(highsock+1, &socks, (fd_set *) 0, 
				   (fd_set *) 0,&timeout);
		
		if (readsocks < 0) {
		  perror("select");
		  exit(EXIT_FAILURE);
		}
		if (readsocks == 0) {
		  /* Nothing ready to read, just show that
		     we're alive */
		  //printf(".");
		  
		  fflush(stdout);
		} else{
		  //printf("read_socks .....\n");
		  read_socks(listUs,listQA);
	          
		}
		t=start2-start1;
	      }
	   
	  }/*while(1)*/
	for(i=0;i<indexMax;i++)
	  {
	    printf("USER: %s MARK: %d\n",listUs[i].name,listUs[i].mark);
	  }

} /* main */
