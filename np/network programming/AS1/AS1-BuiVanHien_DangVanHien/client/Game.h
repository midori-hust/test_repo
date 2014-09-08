#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include "convert.h"
typedef struct
{
	char ten[20];		//Ten nguoi choi
	int Ma;			//Ma player : 1 or 2 	
	int ich;		//Chon vi tri quan co ma ban muon di chuyen: ich la dong,jch la cot 
	int jch;	
	int idi;		//Nuoc di: idi la dong, jdi la cot
	int jdi;		
}Player;
int ktwin;
int *ditot=0;
int TimVatCan(int a[][9],Player *p, int iphu, int jphu)
//nhap vao mang va thong tin player, iphu chinh la su thay doi cua idi voi ich, tuong tu voi j
{
	int i=p->ich+iphu;	
	int j=p->jch+jphu;		
	while(i!=p->idi  ||  j!=p->jdi)					
	{
		if(a[i][j]!=0)			// Co vat can ! Chem.
			return 0;	
		i=i+iphu;
		j=j+jphu;
	}
	return 1;
}
void HD_sudung()	
{
	printf("\n___________________________________________________________________\n");
	printf(" ______________________CHESS GAME__BY AS1-GROUP 3____________________\n");	
	printf(" ______________________HUONG DAN_____________________________________\n");
	printf("1. NHAP QUAN CO: (x,y) \n\t\t\tX HANG NGANG \n\t\t\tY COT DOC________\n");
	printf(" \t\t\tVI DU: Quan Ma (x=8 ,y=2) \n");
	printf("2. Nhap tao do nuoc di cua quan co (x,y)\n");
	printf("3. KHI MUON THOAT GAME XIN NHAP TOA DO 100 O BAT KI VI TRI NAO\n");
	printf("VD: 	x=1;y=100....\n");
	printf("4. KHI MUON XIN HOA CO NHAP TOA DO 90  BAT KI VI TRI NAO\n");
	printf("___________________________Thank you_________________________________\n");
}
void InTenCo(int a)
{
	printf("\n 	Ban dang chon quan ");
	a=abs(a);
	switch(a)
	{
		case 10: 	printf(" VUA !");
			break;
		case 20:	printf(" HAU !");
			break;
		case 30:	printf(" TUONG !");
			break;
		case 40:	printf(" MA !");
			break;
		case 50:	printf(" XE !");
			break;
		case 60:	printf(" LINH !");
			break;					
	}
}
void ChucMungWin( Player *p)
{
	printf("\n\n---------------Nguoi chien thang!!!------------");
	printf("\n   Cuoi cung chung ta cung tim duoc nguoi chien thang!!!");
	printf("\n   Do chinh la....... %s!!!\n\n\n",p->ten);
}
void BangPhongHau()
{
	printf("\n  __________________Chuc Mung Ban Da Den Voi Bang Phong Hau_____________\n");
	printf("\n         Lua chon 1: QUAN HAU\n");
	printf("\n         Lua chon 2: QUAN XE\n");	
	printf("\n         Lua chon 3: QUAN MA\n");
	printf("\n         Lua chon 4: QUAN TUONG\n");
}
void PhongHau(int a[][9],int Ma_Player,int i,int j)
{
	int LuaChon;	//Chon quan de phong hau cho LINH!
	BangPhongHau();
	do
	{
		printf("Nhap vao lua chon di ban!!  ");
		scanf("%d",&LuaChon);
	}while(LuaChon>4 || LuaChon<1);		
	switch	(LuaChon)
	{
		case 1:	if(Ma_Player==1)
					a[i][j]=-20;
				else
					a[i][j]=20;			
				break;	
		case 2:if(Ma_Player==1)
					a[i][j]=-50;
				else
					a[i][j]=50;
				break;	
		case 3:if(Ma_Player==1)
					a[i][j]=-40;
				else
					a[i][j]=40;
				break;
		case 4:if(Ma_Player==1)
					a[i][j]=-30;
				else
					a[i][j]=30;
				break;									
	}
}
int KtQuan_VUA(int a[][9],Player *p)
{
	int Hi,Hj; 			//Luu gia tri cua abs hieu di - ch
	Hi=abs(p->idi-p->ich);
	Hj=abs(p->jdi-p->jch);
	if(Hi>1 || Hj>1)		// di chuyen nhieu hon 1 o thi chem! 
		return 0;
	return 1;			// di chuyen trong vong 1 o
}
int KtQuan_XE(int a[][9],Player *p)
{
	int idi=p->idi,jdi=p->jdi,ich=p->ich,jch=p->jch;
	int flag=0;
	if( idi == ich )		//truong hop 1: chay tren 1 dong
		flag=1;
	if( jch == jdi )		//truong hop 2: chay tren 1 cot
		flag=2;
	if( flag == 0 )
		return 0;
	if( flag == 1 )			//truong hop 1:
	{
		if(jdi<jch)	//chay trai
			return TimVatCan(a,p,0,-1);	// i giu nguyen va j-1 moi lan!!
		else		//chay phai		
			return TimVatCan(a,p,0,1);	// i giu nguyen va j+1 moi lan!!
	}
	else		//truong hop 2
	{
		if(idi<ich)
			return TimVatCan(a,p,-1,0);	// j giu nguyen va i-1 moi lan!!
		else				
			return TimVatCan(a,p,1,0);	// j giu nguyen va i+1 moi lan!!
	}
	return 1;
}
int KtQuan_MA(int a[][9],Player *p)
{
	int Hi,Hj;		//Hieu cua idi va ich
	Hi=abs(p->idi-p->ich);
	Hj=abs(p->jdi-p->jch);
	if( Hi ==1 && Hj ==2 )	// 
		return 1;
	if( Hi ==2 && Hj ==1)
		return 1;
	return 0;			
}
int KtQuan_TUONG(int a[][9],Player *p)
{
	int idi=p->idi,jdi=p->jdi,ich=p->ich,jch=p->jch;
	int flag=0;			// Co hieu dung de phan biet cac truong hop
	if((idi+jdi)==(ich+jch))
		flag=1;			//truong hop 1: cheo phai,len xuong luon!
	else if((idi-ich)==(jdi-jch))
		flag=2;			//truong hop 2: cheo trai ,len xuong luon!	
	if(flag==0)
		return 0;		//Khong thuoc 2 truong hop tren, chem!
	if(flag==1)			//truong hop 1
	{
		if(idi<ich)
			return TimVatCan(a,p,-1,1);	//Cheo len phai, i-1 va j+1
		else
			return TimVatCan(a,p,1,-1);	//Cheo xuong trai, i+1 va j-1
	}
	else		//flag ==2
	{
		if(idi<ich)
			return TimVatCan(a,p,-1,-1);	//Cheo len trai, i-1 va j-1
		else
			return TimVatCan(a,p,1,1);		//Cheo xuong phai,  i+1 va j+1
	}
	return 1;
}
int KtQuan_LINH(int a[][9],Player *p ,int ditot)
{
	int gt=a[p->ich][p->jch],gtdi=a[p->idi][p->jdi];
	int idi=p->idi,jdi=p->jdi,ich=p->ich,jch=p->jch;
	if(gt<0)	//P1
	{
		if(ich==7)
		{
			if((idi==5) && (jdi==jch) &&(a[6][jdi]==0)){	// tai dong 7, di thang len 2 o va khong bi can	
			  return 1;
			}
		}
		if(ich == 4){
			if(idi==3 && jdi== jch+1 && a[4][jch+1] == 60 && ditot==1){
			    return 1;
			}
			if(idi==3 && jdi==jch-1 && a[4][jch-1]== 60 && ditot==1){   
			  return 1;
			}
		}
	}
	else	//P2
	{
		if(ich==2)
		{
			if((idi==4)&&(jdi==jch)&& (a[3][jdi]==0) )	// tai dong 2, di thang len 2 o va khong bi can
			  return 1;
		}
		if(ich==5){
			if(idi==6 && jdi== jch+1 && a[5][jch+1] == -60 && ditot==1){  
			    return 1;
			}
			if(idi==6 && jdi==jch-1 && a[5][jch-1]== -60 && ditot==1){   
			  return 1;
			}
		}
	}		
	//Kiem tra nuoc di quan LINH
	if(gt<0)	//Player 1
	{	
		//   Di lui!		Di qua 1 dong!					Di qua 1 cot!		
		if((idi>=ich)	||	(abs(idi-ich)>1)	||	(abs(jdi-jch)>1)	)
			return 0;
		if(gtdi==0)			//o nay trong
		{
			if(jdi!=jch)	//o nay la o trong ma di cheo -->sai
				return 0;
		}
		else				// quan thu ne!!!
		{
			if(jdi==jch)	// o nay co quan ma di thang, ---> sai luon!
				return 0;	
		}	
	}
	else				//Player 2
	{
		//   Di lui!		Di qua 1 dong!					Di qua 1 cot!		
		if((idi<=ich)	||	(abs(idi-ich)>1)	||	(abs(jdi-jch)>1)	)
			return 0;
		if(gtdi==0)		//o nay trong
		{
			if(jdi!=jch)	//o nay la o trong ma di cheo -->sai
				return 0;
		}
		else		// quan thu ne!!!
		{
			if(jdi==jch)	// o nay co quan ma di thang, ---> sai luon!
				return 0;	
		}	
	}
	return 1;
}
int KtQuan_HAU(int a[][9],Player *p)
{
	if(KtQuan_TUONG(a,p)==1)
		return 1;
	if(KtQuan_XE(a,p)==1)
		return 1;
	return 0;			
}
int ktNuocCan(int a[][9],Player *p,int ditot)
{
	int t=a[p->ich][p->jch];	
	t=abs(t);
	switch(t)
	{
		case 10:if(KtQuan_VUA(a,p)==0)
				return 0;
			break;
		case 20:if(KtQuan_HAU(a,p)==0)
				return 0;
			break;
		case 30:if(KtQuan_TUONG(a,p)==0)
				return 0;
			break;
		case 40:if(KtQuan_MA(a,p)==0)
				return 0;
			break;
		case 50:if(KtQuan_XE(a,p)==0)
				return 0;
			break;
		case 60:if(KtQuan_LINH(a,p,ditot)==0)
				return 0;
			break;						
	}
	return 1; 
}
int ktTonTaiofBanCo(int i, int j)
{
	if(i<1 || j<1)	//thieu dong va cot
		return 0;
	if(i>8 || j>8)	//vuot dong va cot
		return 0;
	return 1;
}
//Nhap vao mang , maplayer va idi va jdi hoac ich va jch
//Xuat 0 trong, 1 quan minh, -1 quan thu
int KiemTraQuanMinh(int a[][9],int MaPlayer, int i, int j)
{
	int t=a[i][j];	//t luu gia tri cua a[i][j]
	if(t==0)
		return 0;
	if(MaPlayer==1)
	{
		if(t<0)
			return 1;
	}
	else
	{
		if(t>0)
			return 1;	
	}
	return -1;		// ke thu!
}
//Kiem tra khi chon co
int ktCoChon(int a[][9],Player *p)
{
	if(ktTonTaiofBanCo(p->ich,p->jch) == 0)		//Sieu nhan,... bay ngoai vu tru!!
	{	
		printf("Khong ton tai ban co");		
		return 0;	
	}
	if(KiemTraQuanMinh(a,p->Ma,p->ich,p->jch) != 1)	//Co thuat thoi mien dieu khien doi phuong!??
		{
		printf("Day la 	quan doi phuong");
		return 0;
	}
	return 1;				
}
//Ham kiem tra nuoc di co hop le ko?
int ktCoDi(int a[][9],Player *p,int ditot)
{
	if(p->ich==p->idi && p->jch==p->jdi)		//Di tai cho!??
		{
		return 0;
		}
	if(ktTonTaiofBanCo(p->idi,p->jdi)==0)		
		{
		return 0;
		}
	if(KiemTraQuanMinh(a,p->Ma,p->idi,p->jdi)==1)	//Anh em choang nhau ah!??
	{
		return 0;
	}
	if(ktNuocCan(a,p,ditot)== 0)				//Phan nay dai va kho nhat day!!!
	{
		return 0;
	}		
	return 1;	
}
//Tao quan co tren ban co luc ban dau
void TaoQuanCo(int a[][9])
{
	int k,j;
	for(j=1;j<9;j++)	//Tao 2 hang Linh
	{
		a[2][j]=60;
		a[7][j]=-60;	
	}
	int gt_co=50;	
	for(k=1;k<=3;k++)	//Tao cac quan XE, MA, TUONG
	{	
		a[1][k]=a[1][9-k]=gt_co;
		a[8][k]=a[8][9-k]=-gt_co;
		gt_co=gt_co-10;
	}	
			//tao thu cong cac quan HAU, VUA
	a[1][4]=20 ;
				a[1][5]=10 ;
	a[8][4]=-20;
				a[8][5]=-10 ;
}
void TaoBanCo(int a[][9])
{
	int i,j,k;
	for(j=0;j<9;j++)
	{	
		for(k=0;k<9;k++)
		{
			a[j][k]=0;
		}
	}	
	for(i=0;i<9;i++)//Tao chi so dong
	{
		a[i][0]=i;
	}
	for(j=0;j<9;j++)//Tao chi so cot
	{
		a[0][j]=j;
	}
}
void InQuanCo(int a)
{
	switch(a)
	{
		case 10: 	printf("  V2");
			break;
		case 20:	printf("  H2");
			break;
		case 30:	printf("  T2");
			break;
		case 40:	printf("  M2");
			break;
		case 50:	printf("  X2");
			break;
		case 60:	printf("  L2");
			break;
		case -10: 	printf("  V1");
			break;
		case -20:	printf("  H1");
			break;
		case -30:	printf("  T1");
			break;
		case -40:	printf("  M1");
			break;
		case -50:	printf("  X1");
			break;
		case -60:	printf("  L1");
			break;						
	}
}
void InBanCo(int a[][9])
{
	system("clear");
	printf("\n\n\n");
	int i,j;	
	for(i=0;i<9;i++)
	{
		printf("    ");
		for(j=0;j<9;j++)
		{	
			if(i==0&&j==0)
			{
				printf("    ");	//Goc 0,0 thi bo trong cho dep!!! :)
			}
			else	if((a[i][j]>0)&& (a[i][j]<10))  //Day la nhung chi so, in binh thuong
					{
						printf("%4d",a[i][j]);
					}else if(a[i][j]==0)		//o trong ne, in ra dau cham nhe!
						{
							printf("  . ");
						}else	//quan co
							{
								InQuanCo(a[i][j]);	
							}
				}
			printf("\n\n"); //Xuong 2 dong
	}
}
void YN(char kt)  //day la ham  lua chon yes no, tu tao ra!!
{
	do
	{
		fflush(stdin);		
		printf("\n			Nhap (Y/N)");
		kt=getchar();
		fflush(stdin);
	}while((kt!='y')&&(kt!='Y')&&(kt!='n')&&(kt!='N'));	
}
int Ktthoat(int i, int j)	//Khi nguoi choi nhap 1 toa do ==100 thi thoat game
{
	if(i==100||j==100)
		return 1;	
	return 0;	
}
int ktHoa(int i,int j){
      if(i==90 || j==90)
	 return 1;
      return 0;
}
void ktra_cochon(int a[][9], Player *p){
	int i,j;
	if(ktTonTaiofBanCo(p->ich, p->jch)==1)	// neu chon vtri nam trong ban co.
	{
		InTenCo(a[p->ich][p->jch]);	//in ten quan co ra !
		printf("Tai vi tri ( %d , %d )",p->ich,p->jch);	// vi tri quan co dang "bi" chon!
		int kt=KiemTraQuanMinh(a, p->Ma, p->ich, p->jch);
		if(kt==-1)	// ke thu ne!
		{
			printf("\nNhung day dau phai la quan cua ban ?! \n");
			printf("Ban phai nhap vao toa do khac thoi       \n");
				
		}
		else if(kt == 0) // kt==0	==> o trong nhe!
		{
			printf("\nVi tri nay khong ton tai quan co nao ca.\n ");
			printf("Ban phai nhap vao toa do khac thoi   :P\n");
			
		}
	}
	else	// Nam ngoai ban co
	{
		printf("\nKhong co toa do nay tren ban co.");
		printf("Ban phai nhap vao toa do khac thoi\n");
			
	}
}
int so_vt_dichuyen(int a[][9],Player *p,int ditot){
int i,j;
int sovt=0;
if(ktTonTaiofBanCo(p->ich, p->jch)==1)	// neu chon vtri nam trong ban co.
	{
		int kt=KiemTraQuanMinh(a, p->Ma, p->ich, p->jch);
		if(kt==1){	// quan ta
			for(i=1;i<9;i++)
			{
				for(j=1;j<9;j++)
				{
					p->idi=i;
					p->jdi=j;
					if(ktCoDi(a,p,ditot)==1)	
					{
						sovt++;
					}
				}
			}	
		}	
	}
  return sovt;
}
void in_vt_DiChuyen(int a[][9] ,  Player *p , int  *flag,int ditot)
{
	int i,j;
	if(ktTonTaiofBanCo(p->ich, p->jch)==1)	// neu chon vtri nam trong ban co.
	{
		InTenCo(a[p->ich][p->jch]);	//in ten quan co ra !
		printf("Tai vi tri ( %d , %d )",p->ich,p->jch);	// vi tri quan co dang "bi" chon!
		int kt=KiemTraQuanMinh(a, p->Ma, p->ich, p->jch);
		if(kt==1)	// quan ta
		{
			*flag=1;
			printf("\nCac vi tri quan co nay co the di la:  ");
			for(i=1;i<9;i++)
			{
				for(j=1;j<9;j++)
				{
					p->idi=i;
					p->jdi=j;
					if(ktCoDi(a,p,ditot)==1)	
					{
						*flag=0;
						printf("(%d,%d)  ",i,j);
					}
				}
			}	
			if(*flag==1)
			{
				printf("\nKhong the di dau duoc!!! \n");
				printf("Ban phai nhap vao toa do khac thoi   :P\n");
				
			}
		}
		else if(kt==-1)	// ke thu ne!
		{
			printf("\nNhung day dau phai la quan cua ban ?!\n");
			printf("Ban phai nhap vao toa do khac thoi   :P\n");
				
		}
		else	// kt==0	==> o trong nhe!
		{
			printf("\n Vi tri nay dau co quan co nao !??\n");
			printf("Ban phai nhap vao toa do khac thoi  \n");
			
		}
	}
	else	// Nam ngoai ban co
	{
		printf("\n Khong co toa do nay tren ban co !?? \n ");
		printf("Ban phai nhap vao toa do khac thoi \n");
			
	}
}
void NhapNuocDiDP(Player *P,int a[][9],int *ktwin,int phonghau,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
	P->ich=x1;
	P->jch= y1;
	P->idi=x2;
	P->jdi=y2;
	if(x1 == x4 && x4== 5 && x2==6 && x3==7 && y2 == y3 && y3==y4 && a[x4][y4]==-60){// Kiem tra bat tot qua duong
	  if((y1==(y2-1))||( y1==(y2+1))){
	    a[P->idi][P->jdi]=a[P->ich][P->jch];
	    a[x4][y4]=0;
	  }
	}
	if(x1 == x4 && x4== 4 && x2==3 && x3==2 && y2 == y3 && y3==y4 && a[x4][y4]==60 ){ // kiem tra bat tot qua duong
	  if((y1==(y2-1)) || (y1==(y2+1))){
	    a[P->idi][P->jdi]=a[P->ich][P->jch];
	    a[x4][y4]=0;
	  }
	}
	if(abs(a[P->idi][P->jdi])==10)	//Quan vua tro thanh muc tieu tieu diet!!!	>>>Nguoi dang choi thang!! :)
		*ktwin=1;
	//Player 1 di len toi dong tren cung, Player 2 xuong dong cuoi cung (Phong vuong phong tuong no do ma!!! :))	
	if(phonghau != 0)
		a[P->idi][P->jdi]= phonghau;
	else
	{	
		a[P->idi][P->jdi]=a[P->ich][P->jch];
	}
	a[P->ich][P->jch]=0;
	InBanCo(a);
}
void NhapNuocDi(Player *P,int a[][9],int *ktwin,int *ktphonghau,int x1,int y1,int x2,int y2)
{
	int co_chet=1;	//Quan co khong the di chuyen
	int kt=0;
	int ditot=0;
	InBanCo(a);
	do{
		printf("\nLuot cua %s : ",P->ten);	
		printf("\n Nhap vao toa do quan co\n");
		printf("x=");scanf("%d",&P->ich);
		printf("y=");scanf("%d",&P->jch);
		if(P->ich==5 &&  x1==7 && y1==P->jch-1 && a[x2][y2] == -60 && x2==5 && y2 == P->jch-1){// kt bat tot qua duong
			   ditot=1;  
			}
		else if(P->ich==5 && x1==7&& y1==P->jch+1 && a[x2][y2]== -60 && x2==5 && y2 ==P->jch+1){
			 ditot=1;    
		}
		else if(P->ich== 4 &&  x1==2 && y1==P->jch-1 && a[x2][y2] == 60 && x2==4 && y2 == P->jch-1){// kt bat tot qua duong 
			    ditot=1;  
		}
		else if(P->ich==4 && x1==2 && y1==P->jch+1 && a[x2][y2]== 60 && x2==4 && y2 == P->jch+1){
			 ditot=1;    
		}
		else ditot=0;
		if(so_vt_dichuyen(a,P,ditot) == 0)
		    printf("Quan co nay khong co nuoc di. Ban hay chon lai quan\n");
		if((Ktthoat(P->ich,P->jch)== 1 )||(ktHoa(P->ich,P->jch)==1))
		{
		  break;
		}
		else ktra_cochon(a,P);
	}while(ktCoChon(a,P)== 0 ||so_vt_dichuyen(a,P,ditot) == 0);
	if((Ktthoat(P->ich,P->jch)== 1 )||( ktHoa(P->ich,P->jch) == 1));
	else{
		in_vt_DiChuyen(a,P,&co_chet,ditot);
		do{
			printf("\n Nhap vao toa do nuoc di\n ");
			printf("x=");scanf("%d",&P->idi);	
			printf("y=");scanf("%d",&P->jdi);
			if(ktCoDi(a,P,ditot) == 0)
				printf("\nKhong di duoc the nay dau. Di lai di nhe\n");
		}while(ktCoDi(a,P,ditot)==0);
		if(abs(a[P->idi][P->jdi])==10)	//Quan vua tro thanh muc tieu tieu diet!!!	>>>Nguoi dang choi thang!! :)
			*ktwin=1;
	//Player 1 di len toi dong tren cung, Player 2 xuong dong cuoi cung (Phong vuong phong tuong no do ma!!! :))	
		if( ( (P->idi == 1)|| (P->idi == 8) ) && ( abs(a[P->ich][P->jch])==60 ) && *ktwin == 0 )
		{		
			PhongHau(a, P->Ma, P->idi ,P->jdi);
			a[P->ich][P->jch]=0;
			*ktphonghau=1;		
		}
		else if(P->idi==6 && P->jdi==y2 && a[x2][y2]== -60 && ditot ==1 ){
			a[P->idi][P->jdi]=60;
			a[x2][y2]=0;
			a[P->ich][P->jch]=0;
		}
		else if(P->idi == 3 && P->jdi==y2 && a[x2][y2]==60 && ditot == 1)
		{
			a[P->idi][P->jdi]=-60;
			a[x2][y2]=0;
			a[P->ich][P->jch]=0;
		}
		else
		{	
			a[P->idi][P->jdi]=a[P->ich][P->jch];	//thay doi gia tri quan co
			a[P->ich][P->jch]=0;
		}
		InBanCo(a);
	}
}
void NhapThongtinPlayer(Player *p1,Player *p2, char name1[],char name2[],int state)
{
	p1->Ma=1;	//ma nguoi choi 1 la 1	
	p2->Ma=2;
	p1->idi=0;
	p2->idi=0;
	p1->jdi=0;
	p2->jdi=0;
	p1->ich=0;
	p2->ich=0;
	p1->jch=0;
	p2->jch=0;//ma nguoi choi 2 la 2
	if(state == 1){
		strcpy(p1->ten,name2); //Nhap ten nguoi choi 1
		strcpy(p2->ten,name1);
	}
	else {
	strcpy(p1->ten,name1); //Nhap ten nguoi choi 1
	strcpy(p2->ten,name2);
	}
}
void TaoMaTran(int a[][9])
{
	int i,j;
	for(j=0;j<9;j++)
	                for(i=0;i<9;i++)
	                {
		            a[j][i]=0;	
			}
}
void InPlayer(Player p1, Player p2){
  printf("\n_______________________In thong tin 2 player___________________\n");
  printf("Player 1 : %s\n", p1.ten);
  printf("Player 2 : %s\n", p2.ten);
}
void sigHandleSigalrm(int signo)
{
  return;
}
void doisansang(char s[])
{
  struct sigaction sa;
  sa.sa_handler = sigHandleSigalrm;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGALRM, &sa, NULL);
  alarm(10);
  strcpy(s,"");
  printf("\n Tro choi se tu dong bat dau sau 10s.\n");
  printf("An Ok neu ban da san sang bat dau tro choi:");

  if (scanf("%s", s) == 1)
    {
      if(strcmp(s,"OK")==0 || strcmp(s,"ok")==0 ||strcmp(s,"Ok")==0)
	alarm(0); // Huy bo alarm
    }
}
void game(int state,int sockfd,char name1[], char name2[]){
int banCo[9][9];
FILE *f;
Player P1,P2,P_now;
char win[1024]="WIN";
char end[1024]="END";
char tt[1024] = "TT";
char xinhoa[1024]="XINHOA";
char traloixh[1024]="TRALOIXH";
char phonghau[1024]="PHONGHAU";
char quanphong[10];
char ct[100];
char dulieu[1024];
char s[10];
char so1[10],so2[10],so3[10],so4[10],so5[10];
char send_data[1024],recv_data[1024],recvdata[1024];
int x1=0,x2=0,y1=0,y2=0,len,i=0,j=0,k,maPhongHau=0;
int x3=0,y3=0,x4=0,y4=0;
int ktthoat=0;
int ktphonghau=0;
int ktlap= 1;
int byte,kthoa;			//Thong tin 2 nguoi choi, p_now luu thong tin cu nguoi choi hien tai
TaoMaTran(banCo);		//Tao ma tran con tro 9 dong 9 cot, vi co 1 dong 1 cot lam chi muc
HD_sudung();
doisansang(s);
NhapThongtinPlayer(&P1,&P2,name1,name2,state);
int kt=1;	//kt dung de thay doi luot nguoi choi, 1 --> luot P1, 2--> P2
char ktContinue;	//hoi y nguoi choi co muon choi tiep ko, y hoac Y la choi tiep, n hoac N la nghi choi!!! :(
int ktwin=0;		//ktwin la kiem tra chien thang , 0 --->tiep tuc, 1 dung cuoc choi, vi co nguoi thang roi
TaoBanCo(banCo); //Tao ban co
TaoQuanCo(banCo); 	//Tao hien thi cac quan co
	do	//chay game
	{
		      if(state == 1)
			{
				InPlayer(P1,P2);
				printf("Ban la nguoi bat dau cuoc choi:\n");
				P_now=P1;
				NhapNuocDi(&P_now,banCo,&ktwin,&ktphonghau,x3,y3,x4,y4);
				x3=P_now.ich;y3=P_now.jch;x4=P_now.idi;y4=P_now.jdi;
				SoChuoi(so1,P_now.ich);
				SoChuoi(so2,P_now.jch);
				SoChuoi(so3,P_now.idi);
				SoChuoi(so4,P_now.jdi);
				SoChuoi(so5,banCo[P_now.idi][P_now.jdi]);
				strcpy(send_data,so1);
				strcat(send_data,":");
				strcat(send_data,so2);
				strcat(send_data,":");
				strcat(send_data,so3);
				strcat(send_data,":");
				strcat(send_data,so4);
				strcat(send_data,":");
				strcat(send_data,so5);
				send(sockfd,send_data,1024,0);
				if(ktwin == 1){
					send(sockfd,win,1024,0);// Thong tin chien thang					
				}
				else if(Ktthoat(P_now.ich,P_now.jch) == 1){
					send(sockfd,end,1024,0); // Xin ngung cuoc choi
					printf("\n Thoat co\n");
					ktthoat = 1;
				}
				else if(ktHoa(P_now.ich,P_now.jch)== 1){
					printf("\nBan xin hoa co\n");
					send(sockfd,xinhoa,1024,0);
					byte= recv(sockfd,recv_data,1024,0);
					recv_data[byte]='\0';
					if(strcmp(recv_data,"YES") == 0)
					    ktthoat=1;
					else printf("/nDoi thu cua ban khong dong y ban xin hoa. Hay di co di nhe!!!/n");
				}
				else { 
					if( ktphonghau == 1 ){
							
						SoChuoi(quanphong,banCo[P_now.idi][P_now.jdi]);
						strcat(phonghau,":");
						strcat(phonghau,quanphong);
						printf("\nPhonghau:");
						puts(phonghau);
						ktphonghau=0;
						send(sockfd,phonghau,1024,0);
					}
					else send(sockfd,tt,1024,0);
					P_now=P2;
					printf("Cho doi thu di co\n");			
					byte= recv(sockfd,recv_data,1024,0);
					recv_data[byte]='\0';
					puts(recv_data);
					tachnuocdi(so1,so2,so3,so4,so5,recv_data);
					x1=ChuoiSo(so1);y1=ChuoiSo(so2);x2=ChuoiSo(so3);y2=ChuoiSo(so4);
					byte= recv(sockfd,recvdata,1024,0);
					recvdata[byte]='\0';
				    	if(strcmp(recvdata,"WIN") == 0){
					 	printf("\nRat tiec ban da thua cuoc.\n");
					 	ktwin=1;
				   	}
					else if(strcmp(recvdata,"END")== 0){
						printf("\n Doi thu cua ban da yeu cau ket thuc cuoc choi\n");
						ktthoat = 1;
					}
					else if(strcmp(recvdata,"XINHOA")== 0){
						printf("\nDoi thu cua ban muon xin hoa. Nhap 1 neu ban dong y nhe\n");
						scanf("%d",&kthoa);
						send(sockfd,traloixh,1024,0);
						if(kthoa == 1){
						  send(sockfd,"YES",1024,0);
						  ktthoat=1;
						}
						else send(sockfd,"NO",1024,0);
					}
					else {
						if(strcmp(recvdata,"TT")==0);
						else {
							printf("\nDoi thu cua ban da duoc phong hau\n");
							i=0;
							while(recvdata[i] != ':')
								i++;
							i++;
							j=0;
							while(i<strlen(recvdata)){
							dulieu[j]=recvdata[i];
							i++;
							j++;
							}
							maPhongHau=ChuoiSo(dulieu);
						}
						NhapNuocDiDP(&P_now,banCo,&ktwin,maPhongHau,x1,y1,x2,y2,x3,y3,x4,y4);
						x3=P_now.ich;y3=P_now.jch;x4=P_now.idi;y4=P_now.jdi;
						maPhongHau=0;
					}
				}
			}
			else
			{
				InBanCo(banCo);
				P_now=P1;
				printf("Hay doi doi thu di co nhe:\n");			
				byte= recv(sockfd,recv_data,1024,0);
				recv_data[byte]='\0';
				tachnuocdi(so1,so2,so3,so4,so5,recv_data);
				x1=ChuoiSo(so1);y1=ChuoiSo(so2);x2=ChuoiSo(so3);y2=ChuoiSo(so4);
				byte= recv(sockfd,recvdata,1024,0);
				recvdata[byte]='\0';
				if(strcmp(recvdata,"WIN") == 0){
					printf("\nRat tiec ban da thua cuoc.\n");
					ktwin=1;
				 }
				else if(strcmp(recvdata,"END")== 0){
					printf("\n Doi thu cua ban da yeu cau ket thuc cuoc choi\n");
					ktthoat =1;
				}
				else if(strcmp(recvdata,"XINHOA")== 0){
						printf("\n Doi thu cua ban muon xin hoa. Nhap 1 neu ban dong y nhe:\n");
						scanf("%d",&kthoa);
						send(sockfd,traloixh,1024,0);
						if(kthoa == 1){
						  send(sockfd,"YES",1024,0);
						  ktthoat=1;
						}
						else send(sockfd,"NO",1024,0);
						//xh=0;
				}
				else{
					if(strcmp(recvdata,"TT")==0);
					else {
						printf("\nDoi thu cua ban da duoc phong hau\n");
						puts(recvdata);
						i=0;
						while(recvdata[i] != ':')
							i++;
						i++;
						j=0;
						while(i<strlen(recvdata)){
							dulieu[j]=recvdata[i];
							i++;
							j++;
						}
						maPhongHau=ChuoiSo(dulieu);
						maPhongHau=maPhongHau*(-1);
					}
					NhapNuocDiDP(&P_now,banCo,&ktwin,maPhongHau,x1,y1,x2,y2,x3,y3,x4,y4);
					x3=P_now.ich;y3=P_now.jch;x4=P_now.idi;y4=P_now.jdi;
					maPhongHau=0;
					InPlayer(P1,P2);
					P_now=P2;
					NhapNuocDi(&P_now,banCo,&ktwin,&ktphonghau,x3,y3,x4,y4);
					x3=P_now.ich;y3=P_now.jch;x4=P_now.idi;y4=P_now.jdi;
					SoChuoi(so1,P_now.ich);
					SoChuoi(so2,P_now.jch);
					SoChuoi(so3,P_now.idi);
					SoChuoi(so4,P_now.jdi);
					SoChuoi(so5,banCo[P_now.idi][P_now.jdi]);
					strcpy(send_data,so1);
					strcat(send_data,":");
					strcat(send_data,so2);
					strcat(send_data,":");
					strcat(send_data,so3);
					strcat(send_data,":");
					strcat(send_data,so4);
					strcat(send_data,":");
					strcat(send_data,so5);
					send(sockfd,send_data,1024,0);
					if(Ktthoat(P_now.ich,P_now.jch) == 1){
						send(sockfd,end,1024,0); // Xin ngung cuoc choi
						ktthoat = 1;
					}
					else if(ktHoa(P_now.ich,P_now.jch)==1){
						printf("Ban xin hoa co\n");
						send(sockfd,xinhoa,1024,0);
						byte= recv(sockfd,recv_data,1024,0);
						recv_data[byte]='\0';
						if(strcmp(recv_data,"YES") == 0)
						    ktthoat=1;
						else printf("/nDoi thu cua ban khong dong y ban xin hoa. Hay di co di nhe!!!/n");
					}
					else if( ktphonghau == 1 ){
						SoChuoi(quanphong,banCo[P_now.idi][P_now.jdi]);
						strcat(phonghau,":");
						strcat(phonghau,quanphong);
						ktphonghau=0;
						send(sockfd,phonghau,1024,0);
					}
					else send(sockfd,tt,1024,0);
				}
			}
		}while(ktwin != 1 && ktthoat == 0);
		if(state == 1 )
		    f= fopen("log.txt","w");
		else f= fopen("log1.txt","w");
		while(strcmp(recv_data,"ENDFILE")!=0){
		  byte=recv(sockfd,recv_data,1024,0);
		  recv_data[byte]='\0';
		  puts(recv_data);
		  if(strcmp(recv_data,"ENDFILE")!=0)
		    fputs(recv_data,f);
		}
		fclose(f);
}

