#include <stdio.h>
#include <string.h>
// Chuyen tu chuoi ki tu so ve so nguyen
int ChuoiSo(char recv_data[]){
int socong=0;
int i,j=0,heso=1;
int len= strlen(recv_data);
for(i=len-1;i>=0;i--){
	if(j>0)
		heso=heso*10;
	if(recv_data[i]== '0')
		socong=socong+0*heso;
	if(recv_data[i]== '1')
		socong=socong+1*heso;
	if(recv_data[i]== '2')
		socong=socong+2*heso;
	if(recv_data[i]== '3')
		socong=socong+3*heso;
	if(recv_data[i]== '4')
		socong=socong+4*heso;
	if(recv_data[i]== '5')
		socong=socong+5*heso;
	if(recv_data[i]== '6')
		socong=socong+6*heso;
	if(recv_data[i]== '7')
		socong=socong+7*heso;
	if(recv_data[i]== '8')
		socong=socong+8*heso;
	if(recv_data[i]== '9')
		socong=socong+9*heso;
	j++;	
	}
	return socong;
}
// Chuyen tu so nguyen ve chuoi ki tu so
void SoChuoi(char kitu[],int i){
	int j=0,k,z;
	int socong[10];
	char kitu1[100];
	if(i<0)
		i=abs(i);
	do{
			socong[j]=i%10;
			i=i/10;
			j++;
	}while( i != 0 );
	for(k=0;k<j;k++){
	if(socong[k] == 1)
		kitu1[k]= '1';
	if(socong[k] == 0)
		kitu1[k]= '0';
	if(socong[k] == 2)
		kitu1[k]= '2';
	if(socong[k] == 3)
		kitu1[k]= '3';
	if(socong[k] == 4)
		kitu1[k]= '4';
	if(socong[k] == 5)
		kitu1[k]= '5';
	if(socong[k] == 6)
		kitu1[k]= '6';
	if(socong[k] == 7)
		kitu1[k]= '7';
	if(socong[k] == 8)
		kitu1[k]= '8';
	if(socong[k] == 9)
		kitu1[k]= '9';
	}
	i=0;
	for(k=j-1;k>=0;k--){
	kitu[i]=kitu1[k]; 
	i++;
	}
	kitu[i]='\0';
	i++;
}
void doichuoi(char user1[],char user2[]){
	char kt[1024];
	int i=strlen(user1);
	int k,m=0;
	for(k=i-1;k>=0;k--){
		kt[m]=user1[k];
		m++;
	}
	strcpy(user2,kt);
}
// Tach danh sach online cua user
void tachDSUser(char dsuser[]){
	int i,j,k,len;
	char user[30];
	char fd[30];
	char trangthai[30];
	len= strlen(dsuser);
	i=0;
	while(dsuser[i] != ':'){
		user[i]=dsuser[i];
		i++;
	}
	user[i]='\0';
	i++;
	j=0;
	while(dsuser[i] != ':'){
		fd[j]= dsuser[i];
		i++;
		j++;
	}
	fd[j]='\0';
	i++;
	j=0;
	while(i<len){
	trangthai[j]=dsuser[i];
	i++;
	j++;
	}
	trangthai[j]='\0';
	if(strcmp(trangthai,"1")== 0)
		strcpy(trangthai,"Dang choi co");
	else if(strcmp(trangthai,"2") == 0 )
		strcpy(trangthai,"Dang ban");
	else strcpy(trangthai,"Ranh roi");
	printf("%10s%10s%20s\n",user,fd,trangthai);
}
void tachnuocdi(char so1[],char so2[],char so3[],char so4[],char so5[],char recv_data[]){
   int i=0,j=0;
   while(recv_data[i] != ':'){
	  so1[i]=recv_data[i];
	  i++;
	}
	so1[i]='\0';
	i++;
	j=0;
	while(recv_data[i] != ':'){
	  so2[j]=recv_data[i];
	  i++;
	  j++;
	}
	so2[j]='\0';
	j=0;					
	i++;
	while(recv_data[i] != ':'){
	  so3[j]=recv_data[i];
	  i++;
	  j++;
	}
	so3[j]='\0';
	j=0;
	i++;
	while(recv_data[i] != ':'){
	  so4[j]=recv_data[i];
	  i++;
	  j++;
	}
	so4[j]='\0';
	j=0;
	i++;
	while(i<strlen(recv_data)){
	  so5[j]=recv_data[i];
	  i++;
	  j++;
	}
	so5[j]='\0';
}
void ghifile(char nuocdi[],char recv_data[],char recvdata[]){
  char so1[10],so2[10],so3[10],so4[10],so5[10],so6[100];
  tachnuocdi(so1,so2,so3,so4,so5,recv_data);
  strcpy(nuocdi,"");
    if(strcmp(recvdata,"WIN")!=0 && strcmp(recvdata,"END") !=0 && strcmp(recvdata,"TT")!=0 && strcmp(recv_data,"XINHOA") !=0)
	strcpy(so6,"Phong Hau. Quan duoc chon phong:"); 
    else strcpy(so6,"Quan:");
    if(ChuoiSo(so5)== 10)
	strcat(so6,"VUA");
    else if( ChuoiSo(so5)== 20)
      strcat(so6,"HAU");
    else if(ChuoiSo(so5)==30)
      strcat(so6,"TUONG");
    else if(ChuoiSo(so5)==40)
      strcat(so6,"MA");
    else if(ChuoiSo(so5)==50)
      strcat(so6,"XE");
    else if(ChuoiSo(so5)==60)
     strcat(so6,"LINH");
  if(strcmp(so1,"100") != 0 && strcmp(so2,"100")!=0 && strcmp(so1,"90")!=0 && strcmp(so2,"90")!= 0){
    strcat(nuocdi,so6);
    strcat(nuocdi," Vi tri: (");
    strcat(nuocdi,so1);
    strcat(nuocdi,",");
    strcat(nuocdi,so2);
    strcat(nuocdi,") Toi Vi Tri(");
    strcat(nuocdi,so3);
    strcat(nuocdi,",");
    strcat(nuocdi,so4);
    strcat(nuocdi,")");
  }
  else if(strcmp(so1,"100") == 0 || strcmp(so2,"100")==0){
    strcpy(nuocdi,"Xin thoat");
  }
  else strcpy(nuocdi,"Xin hoa co");
}
