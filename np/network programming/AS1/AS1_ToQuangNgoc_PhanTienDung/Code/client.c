#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


#define  PORT 9000


void login(char username[],char *passwd,int sock); // Ham dang nhap tai khoan
void signup(int sock);  //Ham dang ky tai khoan
void sendanswer(int sock); // Gui cau tra loi len phia Server
int answerinput(char s[]); // Tra loi cac cau hoi,moi cau gioi han trong 15s


struct question{
	char quest[1024];
};

struct question q[6];

int main()
{
  
  int sock, bytes_recieved;  
  char send_data[1024],*recv_data;
  struct hostent *host;
  struct sockaddr_in server_addr;  
  
  host = gethostbyname("localhost"); 
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    {
      perror("Socket() error!!");
      exit(1);
    }
  
  server_addr.sin_family = AF_INET;     
  server_addr.sin_port = htons(PORT);   
  server_addr.sin_addr = *((struct in_addr *)host->h_addr);
  
  bzero(&(server_addr.sin_zero),8); 
  
  if (connect(sock, (struct sockaddr *)&server_addr,
  sizeof(struct sockaddr)) == -1){
  perror("Connect() error!!");
  exit(1);
  }


  char *answer;
  int d,i,j,m;
  int state,log;
  int ghi;


  int choose;
  choose = 0;
  while(choose == 0)
    {
      printf("\nCHAO MUNG BAN DEN VOI CHUONG TRINH THI TRAC NGHIEM\n");
      printf("**************************************************\n");
      printf("1.Dang nhap\n");
      printf("2.Dang ky\n");
      printf("3.Thoat\n");
      printf("**************************************************\n");
      printf("Moi ban lua chon : ");scanf("%d",&choose);

      char username[40];
      char *passwd;
      switch(choose)
	{
	case 1 : 
	  m = 0;ghi = 0;
	  d = 0;log = 0;
	  while(1)
	    {
	      if(log == 0)  // Thao tac dang nhap
		{
		  login(username,passwd,sock);
		  log = 1;
		}


	      char *nhan;
	      nhan = (char *)malloc(1024*sizeof(char));
	      bytes_recieved = recv(sock,nhan,1024,0);
	      nhan[bytes_recieved] = '\0';

	      char *nhanda;
	      nhanda = (char *)malloc(9*sizeof(char));
	      strncpy(nhanda,nhan,9);



	      if(ghi == 1)
	      {
			m++;

  			FILE *file;
			file = fopen("dethivadapan.txt","a+");
			fprintf(file,"%s\n",nhan);
			fclose(file);
			free(nhan);
			if(m == 5)
			{
				exit(1);
				break;
			}
	      }



	      if(strcmp(nhanda,"Ket Qua :") == 0)
	      {
			int a;

			printf("\n%s\n",nhan); //In ra dap an
			printf("Ban co muon tai ve de thi va dap an ?\n");
			printf("1.Co\n");
			printf("2.Khong\n");
			printf("Hay lua chon : ");scanf("%d",&a);
			if(a == 1)
			{
				send(sock,"TAI VE DE THI VA DAP AN",strlen("TAI VE DE THI VA DAP AN"),0);
				ghi = 1;
			}
			if(a == 2)
			{
				exit(1);
				break;
			}

	      }
	      free(nhanda);
	      if(strcmp(nhan,"Username or password is incorrect") == 0)
		{
		  printf("%s\n\n",nhan);
		  free(nhan);
		  choose = 0;
		  exit(1);
		  break;
		}

	      if(strcmp(nhan,"Username or password is incorrect") != 0 && ghi == 0)
		{
		  strcpy(q[d].quest,nhan);
		  free(nhan);
		  d++;
		}
	      if(d == 5 && ghi ==0)
		{
		  printf("\nBAN DA DANG NHAP THANH CONG ! BAT DAU THI NAO ! \n");
		  printf("Chon cac phuong an A,B,C,D de tra loi. Chon N de bo qua di toi cau tiep theo\n");
		  printf("Moi cau hoi chi duoc tra loi trong vong 15s\n");

		  for(i = 0; i < 5; i++)
		    {
		      answer = (char *)malloc(10*sizeof(char));
		      printf("\n%s\n",q[i].quest);
		      state = answerinput(answer);
		      if(state == 0)
			strcpy(answer,"N");
		      send(sock,answer,strlen(answer),0);
		      free(answer);
		    }  
		   ghi = 1;

		}



	    }


	  close(sock);
	  exit(0);

	  break;
	case 2 : log = 0;
		while(1)
		{
			if(log == 0)
			{
				signup(sock);
				log = 1;
			}
	      		char *nhan;
	      		nhan = (char *)malloc(1024*sizeof(char));
	      		bytes_recieved = recv(sock,nhan,1024,0);
	      		nhan[bytes_recieved] = '\0';
			if(strcmp(nhan,"Username is existed") == 0)
			{
				printf("%s\n",nhan);
				printf("Ban can phai dang ky lai\n");
				choose = 0;
				break;
			}
			if(strcmp(nhan,"Your user is ready now") == 0)
			{
				printf("%s\n",nhan);
				choose = 0;
				break;
			}

		}
		break;
	case 3 : break;
	default : choose =0;break;

	}

    }

}

void sigHandleSigalrm(int signo)
{
  return;
}
int answerinput(char s[])
{
  struct sigaction sa;

  sa.sa_handler = sigHandleSigalrm;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGALRM, &sa, NULL);

  alarm(15);
  strcpy(s,"");
  printf("Nhap cau tra loi :");

  if (scanf("%s", s) == 1)
    {
      alarm(0); // Huy bo alarm
    }

  /* Cac lenh sau khi terminate scanf */

  if(strcmp(s,"") == 0)
	return 0;
  else
	return 1;

}

void login(char username[],char *passwd,int sock)
{
  char dangnhap[1024];
  while(getchar()!='\n');
  printf("Username :");gets(username);
  passwd = getpass("Password :");
  strcpy(dangnhap,"1");
  strcat(dangnhap,username);
  strcat(dangnhap," ");
  strcat(dangnhap,passwd);


  send(sock,dangnhap,strlen(dangnhap),0);

}

void signup(int sock)
{
	char username[30];
	char *passwd;
	char pass1[30],pass2[30];
	int flag;
	flag =0;
	while(getchar()!='\n');
	do{
		printf("Username :");gets(username);	
		passwd = getpass("Password :");strcpy(pass1,passwd);
		passwd = getpass("Confirm Password :");strcpy(pass2,passwd);
		if(strcmp(pass1,pass2) == 0)
			flag = 1;
		else
			printf("Hai mat khau chua trung khop, hay nhap lai !\n");
	}while(flag == 0);
	char dangnhap[1024];
	strcpy(dangnhap,"2");
	strcat(dangnhap,username);
	strcat(dangnhap," ");
	strcat(dangnhap,pass1);
	send(sock,dangnhap,strlen(dangnhap),0);

}



