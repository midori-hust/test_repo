/*
First run tutorial.glade through gtk-builder-convert with this command:
  gtk-builder-convert tutorial.glade tutorial.xml
  
Then save this file as main.c and compile it using this command
(those are backticks, not single quotes):
  gcc -Wall -g -o tutorial main.c `pkg-config --cflags --libs gtk+-2.0` -export-dynamic
  
Then execute it using:
  ./tutorial
*/
#include <gtk/gtk.h>
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
#define CLICKED 8
int sock;            /* The socket file descriptor for our "listening"
                   	socket */
int connectlist[5];  /* Array of connected sockets so we know who
	 		we are talking to */
fd_set socks;        /* Socket file descriptors we want to wake
			up for, using select() */
int highsock;	     /* Highest #'d file descriptor, needed for select() */

int type;// REGISTER OR LOGIN

int indexMax=0;//Max number userLogedIn

int cqa=0,total_ques=0;

char start[7],next[7];

QA currentQA;

QA *listQA;

User *listUs;

int connect_clicked=0,start_clicked=0;

GtkWidget   *window;
GtkWidget *dialog;
GtkBuilder      *builder; 
GtkTreeView *treeview;
enum{
  groupID=0,
  groupName,
  groupmark,
  COLUMNS
};
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
int calculateMark(int listnum,char ans[],QA q)
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
	}
      else
	{
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
void setup_tree_view()
{
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  /* Create a new GtkCellRendererText, add it to the tree view column and
   * append the column to the tree view. */
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes
                         ("GroupID", renderer, "text",groupID, NULL);
  gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes
                         ("GroupName", renderer, "text",groupName, NULL);
  gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes
                         ("Mark", renderer, "text",groupmark, NULL);
  gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);
  gtk_tree_view_set_headers_visible (treeview,1);
  storelist(treeview);
}
void storelist()
{
  GtkListStore *store;
  GtkTreeIter iter;
  int i;
  /* Create a new tree model with three columns, as string, gint and guint. */
  store = gtk_list_store_new (COLUMNS, G_TYPE_INT, G_TYPE_STRING,G_TYPE_INT);
  for(i=0;i<indexMax;i++)
    {
      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter, groupID,i+1,
			  groupName,listUs[i].name,groupmark, listUs[i].mark, -1);
    }
  gtk_tree_view_set_model (GTK_TREE_VIEW (treeview), GTK_TREE_MODEL (store));
  gtk_tree_view_expand_all (GTK_TREE_VIEW (treeview));
  g_object_unref (store);
}
void deal_with_data(
	int listnum			/* Current item in connectlist for for loops */
       	) {
	char buffer[80];     /* Buffer for socket reads */
	char *s,s1[2],s2[2];      /* Used in processing buffer */
	s=(char*)malloc(sizeof(char)*7);
	NamePass namep;
	NamePass *dt;
	char fileName[20];
	int i=0,total=0;
	GtkWidget *en;
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
		printf("\nReceived: %s From: %d; ",buffer,connectlist[listnum]);
	
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
				listUs[i].mark=0;
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
		    printf("ANS: %s\n",buffer);
		    strcpy(s,buffer);
		    s[1]='\0';
		    strcpy(s1,s);//ANS
		    strcpy(s,buffer);
		    s=s+1;
		    strcpy(s2,s);//index QA ANS for
		    i=atoi(s2);
		    printf("for quetion %d\n",i);
		    printf("ans cl=%s\n",s1);
		    if(i==cqa)
		      {
			if(listnum==0)
			  {
			    en=GTK_WIDGET (gtk_builder_get_object (builder, "entry1"));
			  }
			else if(listnum==1)
			 en=GTK_WIDGET (gtk_builder_get_object (builder, "entry2"));
			else if(listnum==2)
			 en=GTK_WIDGET (gtk_builder_get_object (builder, "entry3"));
			else if(listnum==3)
			 en=GTK_WIDGET (gtk_builder_get_object (builder, "entry4"));
			gtk_entry_set_text(en,s1);
		      }
		    calculateMark(listnum,s1,listQA[cqa]);
		  }
		  
	}
}

void read_socks() {
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
		  deal_with_data(listnum);
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
	      printf("Responded: \n");
	      printQuestion(q);
	      printf("To: %d \n",connectlist[listnum]);
	    }
	} /* for (all entries in queue) */
}

//--------------------------------------------------------

void 
on_window1_destroy (GtkObject *object, gpointer user_data)
{
  g_object_unref (G_OBJECT (builder));
  gtk_main_quit ();
}

void on_quit_activate(GtkObject *object,gpointer user_data)
{
  gtk_main_quit ();
}
void on_start_clicked(GtkObject *object,gpointer user_data)
{
  if(connect_clicked!=CLICKED)
    return ;
  GtkWidget *start_bt= GTK_WIDGET (gtk_builder_get_object (builder, "start"));
  int total=0;
  write_socks("START!");
  strcpy(start,"started");
  int i=0;
  for(i=0;i<indexMax;i++)
	  {
	    // printf("USER: %s MARK: %d\n",listUs[i].name,listUs[i].mark);
	    listUs[i].mark=0;
	  }
  if(cqa==0)
    {
      listQA=getQAFromFile("QA.txt",&total);
      total_ques=total;
    }
  gtk_widget_set_sensitive(start_bt,0);
  start_clicked=CLICKED;
}

void on_send_clicked(GtkObject *object,gpointer user_data)
{
  if(connect_clicked!=CLICKED)
    return ;
  if(start_clicked!=CLICKED)
    return;
  struct timeval timeout;  /* Timeout for select */
  int readsocks;	     /* Number of sockets ready for reading */
  int i=0;
  time_t start1,start2;
  int t=0;
  
  printf("%d %d \n",cqa,total_ques);
  if(cqa<total_ques)
	  {
	    
		if(cqa>=1)
		  listQA[cqa-1].toAns=TIMEOUT;
		currentQA=listQA[cqa];
		write_socks(currentQA.question);
		time(&start1);
		
	      
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
		      printf("%d ",(int)(start2-start1));
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
		  printf("read_socks .....\n");
		  read_socks();
		  storelist();
		}
		t=start2-start1;
	      }
	    cqa++;
	  }/*if(1)*/
  else if(cqa>=total_ques)
    {
      GtkWidget *send= GTK_WIDGET (gtk_builder_get_object (builder, "send"));
      gtk_widget_set_sensitive(send,0);
    }

}
void on_button4_clicked(GtkObject *object,gpointer user_data)
{
  if(connect_clicked!=CLICKED) 
    return;
  int i=0;
  GtkTextBuffer* buff;	

  GtkWidget *tv= GTK_WIDGET (gtk_builder_get_object (builder, "textview1"));
  buff = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tv));
  GtkWidget *en1=GTK_WIDGET (gtk_builder_get_object (builder, "entry1"));
  GtkWidget *en2=GTK_WIDGET (gtk_builder_get_object (builder, "entry2"));
  GtkWidget *en3=GTK_WIDGET (gtk_builder_get_object (builder, "entry3"));
  GtkWidget *en4=GTK_WIDGET (gtk_builder_get_object (builder, "entry4"));
  gtk_entry_set_text(en1,"");
  gtk_entry_set_text(en2,"");
  gtk_entry_set_text(en3,"");
  gtk_entry_set_text(en4,"");
  GtkTextMark *mark;
  GtkTextIter iter;
  char temp[1024];
  strcpy(temp,listQA[cqa].question);
  //gtk_text_view_set_buffer(tv,buff);
  //mark=gtk_text_buffer_get_insert(buff);
  //gtk_text_buffer_get_iter_at_mark(buff,&iter,mark);
  for(i=0;i<strlen(temp);i++)
    {
      if(temp[i]=='*')
	temp[i]='\n';
    }
  //gtk_text_buffer_insert(buff,&iter,listQA[cqa].question,-1);   
  gtk_text_buffer_set_text(buff,temp,-1);
  gtk_text_view_set_buffer(tv,buff);      
}
void on_connect_clicked(GtkObject *object,gpointer user_data)
{
  dialog= GTK_WIDGET (gtk_builder_get_object (builder, "dialog1"));
  gtk_widget_show(dialog);
}
void on_button_ok_connect_clicked(GtkObject *object,gpointer user_data)
{
  GtkWidget *port_en= GTK_WIDGET (gtk_builder_get_object (builder, "entry_port"));
  GtkWidget *host_en= GTK_WIDGET (gtk_builder_get_object (builder, "entry_host"));
  GtkWidget *connect_button= GTK_WIDGET (gtk_builder_get_object (builder, "connect"));
  GtkWidget *ok_button= GTK_WIDGET (gtk_builder_get_object (builder, "button_ok_connect"));
  GtkWidget *cancel_button= GTK_WIDGET (gtk_builder_get_object (builder, "button_cancel_connect"));
  //gtk_widget_set_sensitive(ok_button,0);
  //gtk_widget_set_sensitive(cancel_button,0);
  gchar *gport=gtk_entry_get_text(port_en);
  gchar *ghost=gtk_entry_get_text(host_en);
  printf("%s %s",gport,ghost);
  printf("%s %s",gport,ghost);
  //gtk_entry_set_text(port_en,"waiting for client connect...");
  //gtk_entry_set_text(host_en,"waiting for client connect...");
  //=============
	char *ascport;  /* ASCII version of the server port */
	int port;       /* The port number after conversion from ascport */
	struct sockaddr_in server_address; /* bind info structure */
	int reuse_addr = 1;  /* Used so we can re-bind to our port
				while a previous connection is still
				in TIME_WAIT state. */
	struct timeval timeout;  /* Timeout for select */
	int readsocks;	     /* Number of sockets ready for reading */
	char *sdb;
	sdb=(char*)malloc(sizeof(char)*100);
	strcpy(start,"init");
	int i=0,total;
	double db;
	long temp=0;
	time_t start1,start2;
	int process;
	/* Make sure we got a port number as a parameter */

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
	//ascport = argv[1]; /* Read what the user gave us */
	/*port = atoport(ascport); /* Use function from sockhelp to
                                    convert to an int */
	
	memset((char *) &server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	if(strcmp(ghost,"127.0.0.1")==0)
	  server_address.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr("ip")
	else
	  server_address.sin_addr.s_addr = inet_addr(ghost);
	server_address.sin_port = htons(atoi(gport));//port;
	if (bind(sock, (struct sockaddr *) &server_address,
	  sizeof(server_address)) < 0 ) {
		perror("bind");
		close(sock);
		exit(EXIT_FAILURE);
	}
		
	/* Set up queue for incoming connections. */
	listen(sock,5);
	highsock = sock;
	memset((char *) &connectlist, 0, sizeof(connectlist));
	/* Since we start with only one socket, the listening socket,
	   it is the highest socket so far. */
	time(&start1);
	while (1) { /* Main server loop - for accept connect*/
	  time(&start2);
	  if(start2-start1>1000)
	    {
	      //gtk_entry_set_text(host_en,"Connection timeout!");
	      //gtk_entry_set_text(port_en,"Connection timeout!");
	      break;
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
			printf("read_socks .....\n");
			read_socks();
			if(indexMax==BACKLOG && strcmp(start,"init")==0)
			  {
			    //write_socks("START!");
			    //gtk_entry_set_text(host_en,"press Start to Start game!");
			    //gtk_entry_set_text(host_en,"press Start to Start game!");
			    treeview = GTK_WIDGET (gtk_builder_get_object (builder, "treeview1"));
			    setup_tree_view();
			    break;
			  }
			else
			  strcpy(start,"init");
		
		}
	} /* while(1) */
    	//for(i=1;i<500;i++){
	  //delay
	//}
	gtk_widget_set_sensitive(connect_button,0);
	gtk_widget_destroy(dialog);
	connect_clicked=CLICKED;
}
int
main (int argc, char *argv[])
{
	char *ascport;  /* ASCII version of the server port */
	int port;       /* The port number after conversion from ascport */
	struct sockaddr_in server_address; /* bind info structure */
	int reuse_addr = 1;  /* Used so we can re-bind to our port
				while a previous connection is still
				in TIME_WAIT state. */
	struct timeval timeout;  /* Timeout for select */
	int readsocks;	     /* Number of sockets ready for reading */
	listUs=(User*)malloc(sizeof(User)*5);
	listQA=(QA*)malloc(sizeof(QA)*100);
	char *sdb;
	sdb=(char*)malloc(sizeof(char)*100);
	strcpy(start,"init");
	int i=0,total;
	double db;
	long temp=0;
	time_t start1,start2;
	int process;

    gtk_init (&argc, &argv);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "giaodien.xml", NULL);
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
   
    gtk_builder_connect_signals (builder, NULL);

    //g_object_unref (G_OBJECT (builder));
    setBackGround(window,"#9173AF");        
    gtk_widget_show (window);                
   

    time(&start1);
    while(1)
      {
	time(&start2);
	if(start2-start1==10)break;
	if((start2-start1)%3==0)
	  setBackGround(window,"#A6C871");   
	else
	  setBackGround(window,"#9173AF"); 
      }
    //=============
    gtk_main ();
    //-===========

    return 0;
}
