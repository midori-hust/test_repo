#include <stdio.h>
#include <string.h>
// Chuyen tu chuoi ki tu so ve so nguyen
int ChuoiSo(char recv_data[])
{
int socong=0;
int i,j=0,heso=1;
int len= strlen(recv_data);
for(i=0;i<len;i++){
	if(i>0)
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
		
	}
	return socong;
}
// Chuyen tu so nguyen ve chuoi ki tu so
void SoChuoi(char kitu[],int i)
{
	int j=0,k,z;
	int socong[10];
	if(i<0)
		i=abs(i);
	do{
			socong[j]=i%10;
			i=i/10;
			j++;
	}while( i != 0 );
	for(k=0;k<j;k++){
	if(socong[k] == 1)
		kitu[k]= '1';
	if(socong[k] == 0)
		kitu[k]= '0';
	if(socong[k] == 2)
		kitu[k]= '2';
	if(socong[k] == 3)
		kitu[k]= '3';
	if(socong[k] == 4)
		kitu[k]= '4';
	if(socong[k] == 5)
		kitu[k]= '5';
	if(socong[k] == 6)
		kitu[k]= '6';
	if(socong[k] == 7)
		kitu[k]= '7';
	if(socong[k] == 8)
		kitu[k]= '8';
	if(socong[k] == 9)
		kitu[k]= '9';
	}
	kitu[j]='\0';
	j++;	
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

