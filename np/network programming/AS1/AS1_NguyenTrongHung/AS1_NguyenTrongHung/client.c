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
#include "library.h"
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
int f_connect(void);
void inputAcc(int type,char user[],int *login);
void chonPlayer(char user[]);
/*--------------------------------------------the end-------------------------------------*/
main(){   
    struct account *client;
    struct error *err;
    
    char send_data[1024],recv_data[1024];
    char user[30],*pass;
    char LapGame[1024]="LAPGAME";
    int bytes_recieved,choose=1;
    int login=0;
    if(f_connect() == -1){
    	printf("Error connect() !\n");
    }
    do{
    	printf(" \n__________Tro choi O an quan___________\n");
    	printf(" 1. Dang ki\n 2. Dang nhap\n 3. Choi Game\n 4. Exit\n + Lua chon cua ban: ");
    	//while(getchar() != '\n');
    	scanf("%d",&choose);
    	switch(choose){
    	case 1:		/*Dang ki mot tai khoan de choi co vua truc tuyen*/
	  printf("\n******Dang ky tai khoan*******\n");
    		strcpy(send_data,"REG");
    		send(sockfd, send_data,1024, 0); 
    		inputAcc(1,user,&login);
    		break;
    	case 2:		/*Dang nhap tai khoan choi co vua*/
	  printf("******Dang Nhap********\n");
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
    	case 4:			/*Thoat ung dung*/
    		strcpy(send_data,"LOGOUT");
    		send(sockfd, send_data,1024, 0); 
    		printf("Chao tam biet !\n");
    		login=0;
    		break;
    	default:
    		printf("Lua chon khong dung.\n");
    	}
     }while(choose != 4);

     close(sockfd);
     fflush(stdout);
} 
/***********************Ham connect toi server******************************/
int f_connect(void){
	struct sockaddr_in address;
	int len;
	sockfd = socket(AF_INET, SOCK_STREAM,0);
    
    address.sin_family= AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port= htons(9091);
    bzero(&(address.sin_zero),8);
    
    len= sizeof(struct sockaddr);
    return connect(sockfd,(struct sockaddr*)&address,len);
}
/*************************Ham input Account*****************************/
void inputAcc(int type,char user[],int *login){
	char *pass,f_pass[20];
	char acc[60];
	char recv_data[1024];
	int size,status;
	printf("Username: ");
	while(getchar()!='\n');
    gets(user);
	pass = getpass("Password: ");
	strcpy(acc,pass);
	strcat(acc,":");
	strcat(acc,user);
	send(sockfd,acc,60,0);
	printf("%s\n",acc);
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
		}else{
				printf("Username or pass is incorrect ! Please try again!\n");		
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
char name1[1024],name2[1024];
do{
	byte=recv(sockfd,recv_data,1024,0);
	recv_data[byte]='\0';
	socong= ChuoiSo(recv_data);   // Nhan tu server ve so user online
	printf("\n_______________Danh sach Player ______________\n");
 	printf("User:Cong:Trang thai\n");
	lap=1;							
	for(j=0;j< socong; j++)
	{
		byte=recv(sockfd,recv_data,1024,0);
		recv_data[byte]='\0';
		puts(recv_data);
	}
	printf("\n_________________________________________________________\n");
	if(socong > 1)
	{
		printf("An 1 neu ban muon moi nguoi khac choi. An phim bat ki neu ban muon doi nguoi khac moi minh choi:\n");
		fflush(stdout);
		scanf("%d",&state);
		if( state == 1){
			printf("Chon doi thu cua banbang cach nhap so cong\n Nhap so cong=");
			while(getchar() !='\n');
			scanf("%d",&fd);
			SoChuoi(send_data,fd);
			send(sockfd,send_data,1024,0);
			printf("Cho doi tu doi thu:\n");
		}
		else 
		{
			printf("\nCho doi_____\n");
			send(sockfd,ketnoiDOI,1024,0);
		}
	}
	else{
		printf("\nBan chi co 1 minh, cho nguoi khac moi choi! \n");
		//printf("\nCho doi.................\n");
	}
	do{
		chodoi=1;
		byte=recv(sockfd,recv_data,1024,0);
		recv_data[byte]='\0';
		//puts(recv_data);
		if(strcmp(recv_data,"GAME") == 0){
			printf("Co nguoi muon choi co voi ban. An 1 neu ban muon choi voi nguoi do\n");
			//	while(getchar()!='\n');
			scanf("%d",&status);
			if(status == 1){
				send(sockfd,ketnoiOK,1024,0);
				byte=recv(sockfd,name1,1024,0);
				name1[byte]='\0';
			// Chay game
				state_game = 2;
				
			}
			else {
			send(sockfd,ketnoiNO,1024,0);
			chodoi = 0;
			}
			}
	else if(strcmp(recv_data,"GAMEOK")==0){
		printf("Nguoi kia da chap nhan loi moi cua ban\n");
		// Chay game
		byte=recv(sockfd,name1,1024,0);
		name1[1024]='\0';
		state_game = 1;
	}
	else if(strcmp(recv_data,"GAMENO") == 0){
		printf("Loi moi cua ban da bi tu choi! Hay chon nguoi khac\n");
		lap=0;
	}
	else if(strcmp(recv_data,"ERRORFD") == 0){
	printf("Khong co ai o cong ma ban vua moi!\n");
	lap =0;
	}
	}while(chodoi == 0); // Quay tro lai trang thai cho doi khi tu choi loi moi
	game(state_game,sockfd,name1,user);
}while(lap == 0);

}
/*---------------------------------------------------------------------------------------*/