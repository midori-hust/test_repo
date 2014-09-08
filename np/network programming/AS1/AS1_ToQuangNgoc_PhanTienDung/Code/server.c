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
#include "fields.h"


#define true 1
#define false 0
#define PORT 9000
#define BACKLOG 10


//MOT SO HAM CHINH SU DUNG TREN PHIA SERVER
void readfile(); //Doc file
void sendquestion();  // Gui cau hoi toi Client
int checklogin(char *username,int sock_client); // Kiem tra tai khoan dang nhao
int checksignup(char *username,int sock_client);// Kiem tra tai khoan dang ky
void chamdiem(char *dapan); // Cham diem khi Client gui dap an len Server
void sendsubject(int sock_client); // Gui dap an va cau hoi toi Client neu co yeu cau


struct question{
	char question[1024];
	char a[1024];
	char b[1024];
	char c[1024];
	char d[1024];
	char answer[10];
};
struct user{
	char name[50];
	int state;
};



int num_question;
int num_line;
int socaudung,socausai,socauboqua;
struct question q[10];


void handle_child(int x)
{
  pid_t rc;
  int stat;
  while((rc=waitpid(-1,&stat,WNOHANG))>0)
    { 
      printf(" Child terminate with PID : %d \n ",rc);
      if(WIFEXITED(stat))
	printf(" Child exited with code %d \n", WEXITSTATUS(stat));
      else
	printf(" Child terminated abnormally \n");
    }
  signal(SIGCHLD,handle_child);
  return ;
}

main()
{

  get_numline();
  readfile(num_line);


  socaudung = 0; socausai =0,socauboqua=0;
  int state;
  struct sockaddr_in server;
  struct sockaddr_in client;
  pid_t pid;
  int flag;
  int sock;
  int sock_client;
  int sin_size;
  int byte_recv;
  char send_data[1024];
  char recv_data[1024];
  struct hostent *host;
  int stat_val;
  pid_t child_pid;
  
  // Tao kiem soat tin hieu
  signal(SIGCHLD, handle_child);

  if((sock = socket(AF_INET,SOCK_STREAM,0)) == -1) {
    perror("Init socket error!!");
    exit(0);
  }
  server.sin_family = AF_INET;
  server.sin_port  = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;


  bzero(&(server.sin_zero),8);
  if(bind(sock,(struct sockaddr*)&server,sizeof(struct sockaddr)) == -1){
    perror("bind() error!!");
    exit(0);
  }
  if(listen(sock,BACKLOG) == -1){
    perror("Listen() error!!");
    exit(0);
  }
	readfile();

	//char dapan;
	int byte_recv1;
	int i,j,d;

	int check;
	check = 0;
	d=0;
  while(1)
    {
      sin_size = sizeof(struct sockaddr_in);
      sock_client = accept(sock,(struct sockaddr*)&client,&sin_size);
      if( sock_client == -1)
	{
	  break;
	}

   // Forking Server
      if((pid = fork()) == 0)
	{
	      close(sock);       /* Child Socket Listening ; */
	      printf("Have a connection from :%s\n\n",inet_ntoa(client.sin_addr));

	  while(1)
	  {

	      char *nhan;
	      nhan = (char *)malloc(1024*sizeof(char));
	      byte_recv = recv(sock_client,nhan,1024,0);
	      nhan[byte_recv]='\0';	            
 	      //printf("%s\n",nhan);
	      if(strcmp(nhan,"TAI VE DE THI VA DAP AN") == 0)
		{
			sendsubject(sock_client);
			close(sock_client);
			break;
		}
	      if(check == 1)
	      {
			d++;
			char dapan[10];
			if(strcmp(nhan,"N") == 0)
				socauboqua++;
			sprintf(dapan,"%d",d);
			strcat(dapan,nhan);
			//puts(dapan);
		        chamdiem(dapan);
			if(d == 5)
			{
				char guikq[1024];
				char caudung[3];
				char causai[3];
				char boqua[3];
				socausai = socausai - socauboqua;
				sprintf(caudung,"%d",socaudung);
				sprintf(causai,"%d",socausai);
				sprintf(boqua,"%d",socauboqua);

				strcpy(guikq,"Ket Qua :\n");
				strcat(guikq,"So cau dung   : ");strcat(guikq,caudung);strcat(guikq,"\n");
				strcat(guikq,"So cau sai    : ");strcat(guikq,causai);strcat(guikq,"\n");
				strcat(guikq,"So cau bo qua : ");strcat(guikq,boqua);strcat(guikq,"\n");
				//puts(guikq);

				send(sock_client,guikq,strlen(guikq),0);  // Gui tra lai phia Client ket qua  bai thi

				//close(sock_client);
				//break;
			}
	       } 
	      if(check == 0 && strlen(nhan) > 0 )
	      {
			if(nhan[0] == '1')
			{
				//Xu ly thao tac login
		   		state = checklogin(nhan,sock_client);
	      			if(state == 1)
	      			{
		     			sendquestion(sock_client);
	      			}
				check = 1;
			}
			if(nhan[0] == '2')
			{
				//Xu ly thao tac signup
				state = checksignup(nhan,sock_client);
				if(state == 0)
				{
					char *username2;
  					username2 = (char *)malloc(strlen(nhan-1)*sizeof(char));
  					for(j = 1; j < strlen(nhan) ; j++)
						username2[j-1] = nhan[j];
  					username2[strlen(nhan)-1] = '\0';
  					FILE *f;
					f = fopen("user.txt","a+");
					fprintf(f,"%s\n",username2);
					fclose(f);
					
				}
			}

 	      }


		//check = 1;
		free(nhan);

	   }


	 }

      close(sock_client); /* Parent Close Connect Socket */
    }
close(sock);
exit(0);

}
int checksignup(char *username,int sock_client)
{
  int check;
  char *username1;
  int i,j;
  i = 0;
  while(username[i] != ' ')
  {
	i++;
  }
  username1 = (char *)malloc(i*sizeof(char));
  strncpy(username1,username,i);

  IS is;
  int flag;
  check = 0;
  is = new_inputstruct("user.txt");
  flag = 0;
  char user[1024];
  FILE *f;
  while(get_line(is)>=0)
    {
        strcpy(user,"2");
	strcat(user,is->fields[0]);
	if(strcmp(username1,user) == 0)
	   flag = 1;
    }
		
  if(flag ==  0)
    {
	check = 0;
	send(sock_client,"Your user is ready now",strlen("Your user is ready now"),0);
    }
  if(flag == 1)
    {
      check = 1;
      send(sock_client,"Username is existed",strlen("Username is existed"),0);
    }
  return check;
  
}
int checklogin(char *username,int sock_client)
{
  int check;
  IS is;
  int flag;
  check = 0;
  is = new_inputstruct("user.txt");
  flag = 0;
  char user[1024];
  while(get_line(is)>=0)
    {
        strcpy(user,"1");
	strcat(user,is->fields[0]);
	strcat(user," ");
	strcat(user,is->fields[1]);
	if(strcmp(username,user) == 0)
	   flag = 1;
    }
		
  if(flag ==  0)
    {
	check = 0;
        send(sock_client,"Username or password is incorrect",strlen("Username or password is incorrect"),0);
    }
  if(flag == 1)
    {
      check = 1;
    }
  return check;
  
}
int get_numline()
{
	IS is;
	int num_line=0;
	is = new_inputstruct("dethi.txt");
	while(get_line(is)>=0)
	{
		num_line++;
	}
	num_question = num_line/6;
  return num_line;
}
void readfile(int num_line)
{
	

	struct question qu[num_question];
	IS is;
	is = new_inputstruct("dethi.txt");
	int i,j,k;
	num_line = 0;
	while(get_line(is)>=0)
	{
		num_line++;
		char line[1024];
		strcpy(line,"");
		for(i=0; i<is->NF;i++)
		{
			strcat(line,is->fields[i]);
			strcat(line," ");
		}
		if(num_line%6 == 1)
		{
			strcpy(qu[num_line/6].question,line);
		}
		if(num_line%6 == 2)
		{
			strcpy(qu[num_line/6].a,line);
		}
		if(num_line%6 == 3)
		{
			strcpy(qu[num_line/6].b,line);
		}
		if(num_line%6 == 4)
		{
			strcpy(qu[num_line/6].c,line);
		}
		if(num_line%6 == 5)
		{
			strcpy(qu[num_line/6].d,line);
		}
		if(num_line%6 == 0)
		{
			strcpy(qu[num_line/6].answer,line);
		}		
	}

	for(i=0;i<num_question;i++)
	{
		strcpy(q[i].question,qu[i].question);
		strcpy(q[i].a,qu[i].a);
		strcpy(q[i].b,qu[i].b);
		strcpy(q[i].c,qu[i].c);
		strcpy(q[i].d,qu[i].d);
		strcpy(q[i].answer,qu[i].answer);		
	}


}

void sendquestion(int sock_client)
{
	int i;
	char quest[1024];
	for(i = 0 ; i<num_question; i++)
	{
		
		strcpy(quest,"");
		strcat(quest,q[i].question);
		strcat(quest,"\n");
		strcat(quest,q[i].a);
		strcat(quest,"\n");
		strcat(quest,q[i].b);
		strcat(quest,"\n");
		strcat(quest,q[i].c);
		strcat(quest,"\n");
		strcat(quest,q[i].d);
		//printf("%s\n",quest);

		send(sock_client,quest,strlen(quest),0);
		sleep(1);


	}
}

void sendsubject(int sock_client)
{
	FILE *f;
	char *s;
	f = fopen("dethi.txt","r");
	while(!feof(f))
	{
		s = fgets(s,100,f);
		send(sock_client,s,strlen(s),0);
	}
	fclose(f);
}

void chamdiem(char *dapan)
{
	IS is;
	is = new_inputstruct("dapan.txt");
	int flag;
	int i;
	flag = 0;

	while(get_line(is)>=0)
	{
		char *line;
		line = (char *)malloc(2*sizeof(char));

		for(i=0; i<is->NF;i++)
		{
			strcat(line,is->fields[i]);
		}
		if(strcmp(line,dapan) == 0)
		{

			socaudung++;
			flag = 1;
		}
		free(line);
	}
	if(flag == 0)
		socausai++;

}




