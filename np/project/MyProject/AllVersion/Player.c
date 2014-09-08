#include "Player.h"

PlayerList *root;
PlayerList *cur;





int checkAcc(char acc[], int type, Player player[], int online){
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