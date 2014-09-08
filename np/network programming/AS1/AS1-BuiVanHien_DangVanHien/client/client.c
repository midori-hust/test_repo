#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/un.h>
#include <string.h>
#include "Game.h"
char ketnoiDOI[1024]="GAMEDOI";
/**********************************/
int sockfd;
int state_game = 0;
int lapgame=1;
struct account{
	char user[30];
	char pass[20];
};

struct error{
	char error[100];
	int status;
};
/*-----------------------Cac ham su dung o client----------------------------------------*/
void inputAcc(int type,char user[],int *login);
void chonPlayer(char user[]);
/*--------------------------------------------the end-------------------------------------*/
main(int args,char *argv[]){   
    struct account *client;
    struct error *err;
    
    char send_data[1024],recv_data[1024];
    char user[30],*pass;
    char LapGame[1024]="LAPGAME";
    int bytes_recieved,choose=1;
    int login=0;
    struct sockaddr_in address;
    int len;
    sockfd = socket(AF_INET, SOCK_STREAM,0);
    
    address.sin_family= AF_INET;
    inet_pton(AF_INET,argv[1],&address.sin_addr);
    address.sin_port= htons(9090);
    
    len= sizeof(struct sockaddr);
    int f_connect=connect(sockfd,(struct sockaddr*)&address,len);
    if(f_connect == -1){
    	printf("Error connect() !\n");
    }
    do{
    	printf(" \n>>>>>> MENU <<<<<<\n");
    	printf(" 1. Dang ki\n 2. Dang nhap\n 3. Choi Game\n 4. Exit\n >> Xin moi chon: ");
    	scanf("%d",&choose);
    	while(getchar()!='\n');
    	switch(choose){
    	case 1:		/*Dang ki mot tai khoan de choi co vua truc tuyen*/
    		strcpy(send_data,"REG");
    		send(sockfd, send_data,1024, 0); 
    		inputAcc(1,user,&login);
    		break;
    	case 2:		/*Dang nhap tai khoan choi co vua*/
    		strcpy(send_data,"LOGIN");
    		send(sockfd, send_data,1024, 0); 
    		inputAcc(2,user,&login);
    		break;
    	case 3:
    		if(login == 0 )
    			printf("Ban hay dang nhap truoc khi choi game nhe\n");
    		else {
			send(sockfd,LapGame,1024,0);
			chonPlayer(user);
    		}
    		break;
    	case 4:			/*Thoat ung dung*/
    		strcpy(send_data,"LOGOUT");
    		send(sockfd, send_data,1024, 0); 
    		printf("Chao tam biet !\n");
    		login=0;
    		break;
    	default:
    		printf("Lua chon khong dung.\n");
		break;
    	}
     }while(choose != 4);

     close(sockfd);
     fflush(stdout);
} 

/*************************Ham input Account*****************************/
void inputAcc(int type,char user[],int *login){
	char *pass,f_pass[20],*repass;
	char acc[60];
	char recv_data[1024];
	int size,status;
	printf("Username: ");
	gets(user);
	pass = getpass("Password: ");
	strcpy(acc,pass);
	if(type==1){
		repass = getpass("Re-pass: ");
		while(strcmp(acc,repass)!=0){
			printf("Xac nhan pass sai. Nhap lai\n");
			pass = getpass("Password: ");
			strcpy(acc,pass);
			repass = getpass("Re-pass: ");
		}
	}
	strcat(acc,":");
	strcat(acc,user);
	send(sockfd,acc,60,0);
	size = recv(sockfd,recv_data,1024,0);
	recv_data[size] = '\0';
	switch(type){
		case 2:
			if(strcmp(recv_data,"OK") == 0){
				status =1;
				printf("Dang nhap thanh cong !\n");
				chonPlayer(user);
				*login=1;
				break;
		}
		else if(strcmp(recv_data,"NOONLINE") == 0){
			      printf("Dang nhat that bai. Tai khoan nay dang su dung");
		}
		else{
				printf("Dang nhap that bai. Usernam or passwd khong dung.!!\n");		
			}
				break;
		case 1:
			if(strcmp(recv_data,"OK") == 0){
				status =1;
				printf("Dang ki thanh cong !\n");
				break;
			}
			else{
					printf("%s",recv_data);
			}
			break;
		}		
}
/*--------------------------------------------------------------------------------*/
/*--------------------------------Chon nguoi choi---------------------------------*/
void chonPlayer(char user[]){
int i,j,fd;
int lap;
int chodoi; // Chuyen trang thai ve cho doi
int socong;
int status=0;
int state; // Trang thai cho nguoi khac moi choi hay moi nguoi khac choi
int byte;
char ketnoiOK[1024]="GAMEOK";
char ketnoiNO[1024]="GAMENO";
char Error[1024]="ERRORFD";
char LapGame[1024]="LAPGAME";
char recv_data[1024];
char send_data[1024];
char name1[1024],name2[1024],congdt[1024];
do{
	send(sockfd,"LISTPLAYER",1024,0);
	byte=recv(sockfd,recv_data,1024,0);
	recv_data[byte]='\0';
	socong= ChuoiSo(recv_data);   // Nhan tu server ve so user online
	printf("\n___________________Danh sach Player online______________\n");
 	printf("%10s%10s%20s\n","User","Cong","Trang thai");
	lap=1;							
	for(j=0;j< socong; j++)
	{
		byte=recv(sockfd,recv_data,1024,0);
		recv_data[byte]='\0';
		tachDSUser(recv_data);
	}
	printf("\n_________________________________________________________\n");
	if(socong > 1)
	{
		printf("\nChon cach choi\n1.Moi nguoi khac choi\n2.An phim bat ki de doi nguoi khac moi ban \n");
		fflush(stdout);
		printf("Ban chon:");
		scanf("%d",&state);
		if( state == 1){
			send(sockfd,"CHANGE",1024,0);
			printf("Chon doi thu cua ban(hay nhap vao so cong nhe!)\n So cong=");
			//while(getchar() !='\n');
			scanf("%d",&fd);
			while(getchar()!='\n');
			SoChuoi(send_data,fd);
			send(sockfd,"DOITHU",1024,0);
			send(sockfd,send_data,1024,0);
			printf("Cho phan hoi tu doi thu\n");
		}
		else 
		{
			printf("\nCho doi.................\n");
			send(sockfd,ketnoiDOI,1024,0);
		}
	}
	else{
		printf("\nRat tiec chi co mot minh ban online. Ban hay cho nguoi khac moi ban choi nhe. \n");
		printf("\nCho doi.................\n");
	}
	do{
		chodoi=1;
		state_game = 0;
		fflush(stdout);
		byte=recv(sockfd,recv_data,1024,0);
		recv_data[byte]='\0';
		fflush(stdout); 
		if(strcmp(recv_data,"GAME") == 0){
			byte= recv(sockfd,recv_data,1024,0);
			recv_data[byte]='\0';
			byte=recv(sockfd,congdt,1024,0);
			congdt[byte]='\0';
			printf("%s (online tai port %d)muon choi co voi ban. \nAn 1 neu ban muon choi voi nguoi do\n",recv_data,ChuoiSo(congdt));
			//while(getchar()!='\n');
			scanf("%d",&status);
			while(getchar()!='\n');
			if(status == 1){
				send(sockfd,"TRALOIKETNOI",1024,0);
				send(sockfd,congdt,1024,0);
				send(sockfd,ketnoiOK,1024,0);
				byte=recv(sockfd,name1,1024,0);
				name1[byte]='\0';
				state_game = 2;
			}
			else {
				send(sockfd,ketnoiNO,1024,0);
				chodoi = 0;
			}
		}
		else if(strcmp(recv_data,"GAMEOK")==0){
		    byte=recv(sockfd,name1,1024,0);
		    name1[byte]='\0';
		    printf("%s da chap nhan loi moi cua ban\n",name1);
		      // Chay game
		    state_game = 1;
	      }
	      else if(strcmp(recv_data,"GAMENO") == 0){
		    printf("Loi moi cua ban da bi tu choi!!! Hay chon nguoi khac nhe\n");
		    lap=0;
	      }
	      else if(strcmp(recv_data,"ERRORFD") == 0){
		    printf("Khong co ai online o cong ma ban vua moi!\n Hay xem lai danh sach cac player online va nhap lai nhe\n");
		    lap =0;
	      }
	      else if(strcmp(recv_data,"MOICHINHMINH")==0){
		    printf("Ban dang moi chinh ban do ^_^\n");
		    lap=0;
	      }
	      else if(strcmp(recv_data,"BUSY")==0){
		    printf("\nNguoi nay dang choi ma ban. Hay chon nguoi khac di nhe\n");
		    lap=0;
	      }
	}while(chodoi == 0); // Quay tro lai trang thai cho doi khi tu choi loi moi
    }while(lap == 0);
    if(state_game == 1 || state_game == 2)
      game(state_game,sockfd,name1,user);
}
/*---------------------------------------------------------------------------------------*/
