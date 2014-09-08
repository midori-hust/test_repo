#include "convert.h"
 
typedef struct {
char name[30];
int fd;
int status;
}Player;
typedef struct{
	Player p1;
	Player p2;			// Trang thai cua nguoi choi: ranh roi hay dang choi
}PlayingChess;
char kitu[1024],doikitu[1024];	
//Player player[30],int online=0;

/**/
void checkLogin(char acc[],int subclient,Player player[],int *online,PlayingChess playing[],int *index);
int checkAcc(char acc[],int type,Player player[],int online);
int checkStr(char str[]);
int checkPlayer(Player player[],int online,char user[]);
Player* searchPlayer(int online,Player player[],int fd);
void addChessPlayer(int subclient1,int subclient2,PlayingChess playing[],int *index,Player player[],int online);
void removeChessPlayer(int fd,PlayingChess playing[],int *index);
void viewChessPlayer(PlayingChess playing[], int *index);
void connectGame(PlayingChess playing[],int *index,Player player[],int *online,int subclient);
void changeStatePlayer(Player player[],int online,int fd);
/*-----------------------------------Chuyen tu chuoi ki tu sang so nguyen------------------------------------*/
void checkLogin(char acc[],int subclient,Player player[],int *online,PlayingChess playing[],int *index){
	int bytes;
	int i,status=1;
	int doithu; // Luu so cong ma nguoi choi muon choi cung	
	char f_send[1024],send_data[1024];
	char ketnoi[1024]="GAME";
	char ketnoiOK[1024]="GAMEOK";
	char ketnoiNO[1024]="GAMENO";
	char Error[1024]="ERRORFD";
	char tthai[1024];
	char nameDT[1024];
	Player *p1,*p2;
	printf("so user online:%d %d\n",*online,subclient);
    	bytes = recv(subclient,acc,60,0);
        acc[bytes] = '\0';              				
        fflush(stdout);	
        if(checkAcc(acc,2,player,*online)==0){
        	strcpy(f_send,"NO");
            send(subclient,f_send,1024,0);
        }else 
     	{
     	fflush(stdout);	
     	strcpy(f_send,"OK");
     	send(subclient,f_send,1024,0);
     	// Lay ra user
     	char user[30];
		int j,k=0,check;
		int n=0,m=0;
		for(k=0;k<strlen(acc)&& acc[k]!=':';k++);
		k++;
			for(j=k;j<strlen(acc);j++){
			user[m]	= acc[j];		
			m++;
			}
		user[m] = '\0';
		/*----------------------------------------------*/
		strcpy(player[*online].name,user);// Add thong tin cho Player
		player[*online].fd= subclient;
		player[*online].status=0;
		(*online)=(*online) +1;
	do{
		SoChuoi(kitu,*online);
     	send(subclient,kitu,1024,0);// Truyen ve so Player online
     	status=1;
     	for(i=0;i<*online;i++)
     		{
				strcpy(send_data,player[i].name);
				strcat(send_data,":");
				SoChuoi(kitu,player[i].fd);
				doichuoi(kitu,doikitu);
				printf("Cong truyen ve");
				puts(kitu);
				puts(doikitu);
				strcat(send_data,doikitu);
				strcat(send_data,":");
				SoChuoi(tthai,player[i].status);
				strcat(send_data,tthai);
				send(subclient,send_data,1024,0);
     		}
     		if(*online >1){
     			bytes = recv(subclient,kitu,1024,0); // Nhan ve yeu cau ket noi
     			kitu[bytes]='\0';
     			puts(kitu);
     			if(strcmp(kitu,"GAMEDOI") != 0){
     				doithu= ChuoiSo(kitu);
     				printf("doithu=%d\n",doithu);
     				p1=searchPlayer(*online,player,doithu);
     				if(p1 != NULL ){
     					send(doithu,ketnoi,1024,0);
     					bytes=recv(doithu,kitu,1024,0);
     					kitu[bytes]='\0';
     					if(strcmp(kitu,"GAMEOK")==0){
     					send(subclient,ketnoiOK,1024,0);
     					send(subclient,p1->name,1024,0);
     					p2= searchPlayer(*online,player,subclient);
     					send(doithu,p2->name,1024,0);
     					addChessPlayer(subclient,doithu,playing,index,player,*online);
     					printf("Ai dang choi:\n");
     					viewChessPlayer(playing,index);
     					}
     					else {
     					send(subclient,ketnoiNO,1024,0);
						status =0;
     					}
					}
					else {
						send(subclient,Error,1024,0);
						status=0;
					}
				}	
			}
		}while(status == 0);
	}
}
/*
*	Check Account: Username and Pass
*	int type: is 1 - login or 2- reg account
*	return 1 if correct
*/

int checkAcc(char acc[],int type,Player player[],int online){
	FILE *f;
	char user[30],pass[20];
	char f_user[30],f_pass[20],f_acc[60];
	int i,k=0,check;
	int n=0,m=0;
	f = fopen("user.txt","a+");
	for(i=0;i<strlen(acc);i++){
		if(acc[i] == ':'){
			i = i+1;
			k=1;
		}
		if(k==0){							
			pass[n] = acc[i];
			n++;			
		}else{
			user[m] = acc[i];
			m++;
		}			
	}
	user[m] = '\0';
	pass[n] ='\0';
	switch(type){ 
		case 1:	
			if(checkStr(user)==0) return 5;	     			//user chi la so hoac chu cai
			else if(checkStr(pass)==0) return 6;			//pass chi la so hoac chu cai
			else{
				while(!feof(f)){
					fscanf(f,"%s",&f_user);
					fscanf(f,"%s",&f_pass);
					if(strcmp(user,f_user)==0){
						return 0;
						break;
					}else check =1;
				}
				fclose(f);
			}		
			f = fopen("user.txt","a+");
			fprintf(f,"%s %s\n",user,pass);
			fclose(f);	
			return 1;
			break;					
		case 2:
			while(!feof(f)){
				fscanf(f,"%s",&f_user);
				fscanf(f,"%s",&f_pass);
				if(strcmp(user,f_user)==0 && strcmp(pass,f_pass) ==0 && checkPlayer(player,online,user)==1){
					printf("User %s da dang nhap vao he thong\n",user);
					return 1;
				}
			}
			fclose(f);
			return 0;		
	}	
	return 0;							// Account is incorrect or username is exited
}
/*
*	Kiem tra xau ki tu (a-z), (0-9) va (A-Z)
*	Return 1 if string is correct
*	else 0 if incorrect
*/

int checkStr(char str[]){
	int i;
	for(i=0;i<strlen(str);i++){
		if((str[i] >='0' && str[i]<='9') || (str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z'));
		else{
			return 0;
			break;
		}
	}	
	return 1;
}
int checkPlayer(Player player[],int online,char user[]){
int i;
for(i=0;i<online;i++)
	if(strcmp(player[i].name,user)==0)
		return 0;
return 1;
}
/*
*
*/
Player* searchPlayer(int online,Player player[],int fd){
int i=0;
Player* p=NULL;
for(i=0;i<online;i++){
	if(fd == player[i].fd){
		p=&player[i];
		return p;
	}
	}
	return NULL; 
}
void changeStatePlayer(Player player[],int online,int fd){
	int i=0;
	for(i=0;i<online;i++){
		if(fd == player[i].fd)
			player[i].status=1;
	}
}
void addChessPlayer(int subclient1,int subclient2,PlayingChess playing[],int *index,Player player[],int online){
	Player *p1= NULL,*p2=NULL;
	changeStatePlayer(player,online,subclient1);
	changeStatePlayer(player,online,subclient2);
	p1= searchPlayer(online,player,subclient1);
	p2= searchPlayer(online,player,subclient2);
	playing[*index].p1=*p1;
	playing[*index].p2= *p2;
	*index= *index + 1;
}
int searchPlaying(int fd,PlayingChess playing[],int index)
{
	int i;
	for(i=0;i<index;i++)
	{
		if(fd == playing[i].p1.fd)
			return playing[i].p2.fd;
		if(fd == playing[i].p2.fd)
			return playing[i].p1.fd;
	}
	return -1;
}
/*
*/
void removeChessPlayer(int fd,PlayingChess playing[],int *index){
	int i=0;
	for(i=0;i<*index;i++){
		if(fd == playing[i].p1.fd || fd == playing[i].p2.fd){
			while(i<*index-1){
				playing[i]=playing[i+1];
				i++;
			}
			*index= *index-1;
			break;
		}
	}
}
//---------------------------------------------------
void viewChessPlayer(PlayingChess playing[],int *index){
int k=0;
for(k=0;k<*index;k++){
     					printf("%s\t %d %d\n", playing[k].p1.name,playing[k].p1.fd,playing[k].p1.status);
     					printf("Danh voi\n");
     					printf("%s\t %d\n",playing[k].p2.name,playing[k].p2.fd,playing[k].p1.status);
     					}
}
/*-------------------------------Connect Game-----------------------*/
void connectGame(PlayingChess playing[],int *index,Player player[],int *online,int subclient){
Player *p1,*p2;
char kitu[1024],send_data[1024],recv_data[1024];
char ketnoi[1024]="GAME";
char ketnoiOK[1024]="GAMEOK";
char ketnoiNO[1024]="GAMENO";
char Error[1024]="ERRORFD";
char nameDT[1024];
int bytes,i,doithu,byte;
int status = 1;
	do{
		SoChuoi(kitu,*online);
     	send(subclient,kitu,1024,0);// Truyen ve so Player online
     	status=1;
     	for(i=0;i<*online;i++)
     		{
				strcpy(send_data,player[i].name);
				strcat(send_data,":");
				SoChuoi(kitu,player[i].fd);
				strcat(send_data,kitu);
				//puts(send_data);
				send(subclient,send_data,1024,0);
     		}
     		if(*online >1){
     			bytes = recv(subclient,kitu,1024,0); // Nhan ve yeu cau ket noi
     			kitu[bytes]='\0';
     			puts(kitu);
     			if(strcmp(kitu,"GAMEDOI") != 0){
     				doithu= ChuoiSo(kitu);
     				printf("doithu=%d\n",doithu);
     				p1=searchPlayer(*online,player,doithu);
     				if(p1 != NULL ){
     					send(doithu,ketnoi,1024,0);
     					bytes=recv(doithu,kitu,1024,0);
     					kitu[bytes]='\0';
     					if(strcmp(kitu,"GAMEOK")==0){
     					send(subclient,ketnoiOK,1024,0);
     					send(subclient,p1->name,1024,0);
     					p2= searchPlayer(*online,player,subclient);
     					send(doithu,p2->name,1024,0);
     					addChessPlayer(subclient,doithu,playing,index,player,*online);
     					printf("Ai dang choi:\n");
     					viewChessPlayer(playing,index);
     					}
     					else {
     					send(subclient,ketnoiNO,1024,0);
						status =0;
     					}
					}
					else {
						send(subclient,Error,1024,0);
						status=0;
					}
				}	
			}
		}while(status == 0);
}
