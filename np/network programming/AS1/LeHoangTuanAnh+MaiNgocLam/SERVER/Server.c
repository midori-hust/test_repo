#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>

#define IREGISTER 0
#define IUSER 1
#define ITEST 2
#define ITOTALUSER 2

//###################################################
typedef struct _loginStr{
    char username[30];
    char password[20];
    char status[30];
    int  trueAnser;
}_loginStr;

typedef struct _question{
	char question[100];
	char anser[30];
	int idQuestion;
}_question;

typedef struct _userConcertrate{
	_loginStr lg[200];
	 int count;
}_userConcertrate;

typedef struct _packageSend{
	int idSocket;
	char username[30];
	char anser[30];
}_packageSend;

typedef enum {false,true} boolean;

typedef struct _userConnect{
	char username[30];
}_userConnect;

_userConnect uConnect[100];

//################### FILE OF CURRENT USER 
void resetFile()
{
   FILE *f;
   f=fopen("/home/anhlht/FinalProject/User.txt","w");
   fprintf(f,"%s","");
   fclose(f);	
}
void writeFileLog(int idfd,char *nameUser,char question)
{
   FILE *f;
   f=fopen("/home/anhlht/FinalProject/Log.txt","a+");
   fprintf(f,"SOCKET ID : %d NAMEUSER : %s COUNTQUESTION : %d \n ########################################## \n",idfd,nameUser,question);
   fclose(f);
}
void writeCurrentUser(int idfd)
{
   FILE *f;
   f=fopen("/home/anhlht/FinalProject/User.txt","a+");
   fprintf(f,"%d\n",idfd);
   fclose(f);
}
boolean checkExist(char *username)
{
   	 int i=0;
   	 for(i=0;i<100;i++)
   	  {
		//printf(" |%s compare %s| ",username,userConnect[i].username);
		if(strcmp(uConnect[i].username,username)==0)
		    return true;  
	  }
	 return false; 
}
int returnID(char *s,_packageSend pk[],int total)
{
	int i=0;
	for(i=0;i<total;i++)
	  {
	   if(strcmp(s,pk[i].username)==0)
	     return i;
	  }
	  return -1;
}
void SentForAllUser(char *question,_packageSend pk[],int total)
{
  FILE *f;
  char *buffer;
  int iCount=0;
  long lSize;
  int result;
  f=fopen("/home/anhlht/FinalProject/CurrentUser.txt","r");
   // obtain file size:
  fseek (f , 0 , SEEK_END);
  lSize = ftell (f);
  rewind (f);
  // allocate memory to contain the whole file:
  buffer = (char*) malloc (sizeof(char)*lSize);
  if (buffer == NULL) {
  fputs ("Memory error",stderr);
  }
  // copy the file into the buffer:
  result = fread (buffer,1,lSize,f);
  if (result != lSize) {
  fputs ("Reading error",stderr); 
  }
  char *ch;
  ch=strtok(buffer,"\n");
    while(ch!=NULL)
     {
	 send(returnID(ch,pk,total),question,strlen(question),0);	 
	 ch=strtok(NULL,"\n");
	 }
}
int getCountCurrentUser()
{
  FILE *f;
  char *buffer;
  int iCount=0;
  long lSize;
  int result;
  f=fopen("/home/anhlht/FinalProject/CurrentUser.txt","r");
   // obtain file size:
  fseek (f , 0 , SEEK_END);
  lSize = ftell (f);
  rewind (f);
  // allocate memory to contain the whole file:
  buffer = (char*) malloc (sizeof(char)*lSize);
  if (buffer == NULL) {
  fputs ("Memory error",stderr);
  }
  // copy the file into the buffer:
  result = fread (buffer,1,lSize,f);
  if (result != lSize) {
  fputs ("Reading error",stderr); 
  }
  char *ch;
  ch=strtok(buffer,"\n");
    while(ch!=NULL)
     {
	 iCount++;
	 strtok(NULL,"\n");
	 }
   fclose(f);
   return iCount;
}
_packageSend getFromClientSent(char *s,int idSk)
{
      _packageSend des;
      int i=0;
      char *ch;
      ch=strtok(s,"|");
      while(ch!=NULL)
        {  if(i==0)
           strcpy(des.anser,ch);
           else if(i==1)
           strcpy(des.username,ch);
           i++;
           ch=strtok(NULL,"|");
		}
	 des.idSocket=idSk;	
	return des;		
}
boolean checkUser(char *username ,char *password )
{
  FILE * pFile;
  long lSize;
  char  *buffer;
  size_t result;
  _loginStr client[200];
  int i=0;
  int j=-1;
  char *ch=(char*)malloc(sizeof(100));
  pFile = fopen ("/home/anhlht/FinalProject/Database.txt","r");
  if (pFile==NULL) {
	  fputs ("File error",stderr); 
  }
  // obtain file size:
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);
  // allocate memory to contain the whole file:
  buffer = (char*) malloc (sizeof(char)*lSize);
  if (buffer == NULL) {
  fputs ("Memory error",stderr);
  }
  // copy the file into the buffer:
  result = fread (buffer,1,lSize,pFile);
  if (result != lSize) {
  fputs ("Reading error",stderr); 
  }
  
  // printf("%s ",buffer);
  // Get Information
  
  ch=strtok(buffer,"|\n");
  
  while(ch!=NULL)
    {
	 if(i%2==0)
	    j++;  
	 if(i%2==0)
	   strcpy(client[j].username,ch);
	 else
	   strcpy(client[j].password,ch);
	  
	  ch = strtok (NULL, "|\n");
	   i++;
   }
  int k=0;
  for(k=0;k<j;k++)
    {
	  if(strcmp(client[k].username,username)==0 && strcmp(client[k].password,password)==0)
	   return true;  
    }
  
  fclose (pFile);
  free (buffer);

   return false;

 }
 boolean checkUserRegis(char *username)
{
  FILE * pFile;
  long lSize;
  char  *buffer;
  size_t result;
  _loginStr client[200];
  int i=0;
  int j=-1;
  char *ch=(char*)malloc(sizeof(100));
  pFile = fopen ("/home/anhlht/FinalProject/Database.txt","r");
  if (pFile==NULL) {
	  fputs ("File error",stderr); 
  }
  // obtain file size:
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);
  // allocate memory to contain the whole file:
  buffer = (char*) malloc (sizeof(char)*lSize);
  if (buffer == NULL) {
  fputs ("Memory error",stderr);
  }
  // copy the file into the buffer:
  result = fread (buffer,1,lSize,pFile);
  if (result != lSize) {
  fputs ("Reading error",stderr); 
  }
  
  // printf("%s ",buffer);
  // Get Information
  
  ch=strtok(buffer,"|\n");
  
  while(ch!=NULL)
    {
	 if(i%2==0)
	    j++;  
	 if(i%2==0)
	   strcpy(client[j].username,ch);
	 else
	   strcpy(client[j].password,ch);
	  
	  ch = strtok (NULL, "|\n");
	   i++;
   }
  int k=0;
  for(k=0;k<j;k++)
    {
	  if(strcmp(client[k].username,username)==0)
	   return true;  
    }
  
  fclose (pFile);
  free (buffer);

   return false;

 }
 _loginStr getUsernameAndpass(char *s)
{
      _loginStr str;
      int i=0;
      char *ch;
      ch=strtok(s,"|");
      while(ch!=NULL)
        {  if(i==0)
           strcpy(str.username,ch);
           else
           strcpy(str.password,ch);
           i++;
           ch=strtok(NULL,"|");
		}
	return str;		 
 }
 int getRegister(char *s)
 {
     int t;
     int i=0;
     char *ch;
     _loginStr str;
     FILE *f;
     f = fopen ("/home/anhlht/FinalProject/Database.txt","a+");
     int flag=0;
     ch=strtok(s,"/");
     while(ch!=NULL)
       { 
		 printf("|%s|\n",ch);
		 if(strcmp(ch,"0")==0)
		   { 
			   
			   printf("Kiem tra da ton tai hay chua ? ");
			    
           }
	     if(i==1)
	       {
			    str=getUsernameAndpass(ch);
			    if(checkUserRegis(str.username)==false)
			    {
			      fprintf(f,"%s\n",ch);
			      fclose(f); 
			      printf(" Da cap nhat xong ");
			    }
		   }
		 i++;
		 ch=strtok(NULL,"/");    
      }
     return flag; 
 }
 //***************************************************************
void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}
//***************************************************************
char * convertInttoChar(int t)
{
  char *s=(char*)malloc(sizeof(char)*3);

  if(t==10)
     strcpy(s,"10");
  else if(t==9)
     strcpy(s,"9");   
  else if(t==8)
     strcpy(s,"8");   
  else if(t==7)
     strcpy(s,"7");   
  else if(t==6)
     strcpy(s,"6");   
  else if(t==5)
     strcpy(s,"5");   
  else if(t==4)
     strcpy(s,"4");   
  else if(t==3)
     strcpy(s,"3");   
  else if(t==2)
     strcpy(s,"2");   
  else if(t==1)
     strcpy(s,"1");   
  else if(t==0)
     strcpy(s,"0");   
  
  return s;
}
 int main(int args, char *argv[])
{
    fd_set allSocket;    
    fd_set readfds;  
    int fdmax;        
    
    int listener;     
    int acceptSocket;       
    struct sockaddr_in server, client; 
    int sin_size;

    char buf[256];    
    int nbytes;
    char send_data[1024];
    int i, rv;
    
    FD_ZERO(&allSocket);   
    FD_ZERO(&readfds); 
    
    int _gSocID[100];
    int _iSocCount=0;
    
    int iCountSend=0;
    int firstSend=0;
    int iFlag=IUSER;
   _packageSend userConnect[100];
  //###################### GET FILE
  FILE *pf;
  int t;
  FILE * pFile;
  long lSize;
  char * buffer;
  size_t result;
  char *messages=(char*)malloc(sizeof(char)*100);
  pFile = fopen ( "Cauhoi.txt" , "r" );
  if (pFile==NULL) {
  fputs ("File error",stderr); 
  }
  // obtain file size:
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);
  printf(" %d ",lSize);
  // allocate memory to contain the whole file:
  buffer = (char*) malloc (sizeof(char)*lSize);
  if (buffer == NULL) {
  fputs ("Memory error",stderr);
  }
  // copy the file into the buffer:
  result = fread (buffer,sizeof(char),lSize,pFile);
  if (result != lSize) {
  fputs ("Reading error",stderr); 
  }
  //############################### GET QUESTION  
  buffer[result]='\0';
  printf(" %s ",buffer);
  char *ch;
  int j=0;
  int idQuestion=-1;
  _question   quesStr[40];
  ch=strtok(buffer,"[]");
  while(ch!=NULL)
  {  if(j%3==0)
        idQuestion++;
     if(j%3==0)
     {
     	strcpy(quesStr[idQuestion].question,ch);
     	quesStr[idQuestion].idQuestion=idQuestion;
     }
	  else if(j%3==2)
	 {
 	    strcpy(quesStr[idQuestion].anser,ch);	
 	 }
      
	  j++; 
     ch=strtok(NULL,"[]");
  }
    //##################################
    //check args
    if( args < 2)
    {
        printf("Usage : %s <PORT>\n", argv[0]);
        exit(-1);
    }
    // create socket for server to listen
    if((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("socket() error!\n");
        exit(-1);
    }
    // init info for server
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server.sin_zero),8);
    // bind
    if(bind(listener, (struct sockaddr*)&server, sizeof(struct sockaddr)) == -1)
    {
        printf("bind() error!\n");
        exit(-1);
    }
    //listen
    if (listen(listener, 100) == -1)
    {
        perror("listen");
        exit(3);
    }
    FD_SET(listener, &allSocket);
    //***************************
    struct timeval tv;
    tv.tv_sec=10;
    tv.tv_usec=0;
    //***************************
    fdmax = listener;
    j=0;
    int iConnect;
    int rv1;
    int iCountMessages=0;
    int iCountClient=0;
    char chose[2];
    //***************************
    int defTotal=ITOTALUSER;
  //###################################################################### 
    for(;;)
    {
        readfds = allSocket; 
        if ((rv1=select(fdmax+1, &readfds, NULL, NULL, &tv)) == -1)
        {
            perror("select");
            exit(4);
        }
       for(i = 0; i <= fdmax; i++)
        {
            if (FD_ISSET(i, &readfds)) // <> 
            {
                if (i == listener)
                {
                    acceptSocket = accept(listener, (struct sockaddr*)&client, &sin_size);

                    if (acceptSocket == -1)
                    {
                        perror("accept");
                    }
                    else
                    {
                        FD_SET(acceptSocket, &allSocket); 
			            printf(" Connect with socket %d\n", acceptSocket);
			            //  iFlag=IUSER;
			            //  Mang Socket Client 
			            _gSocID[_iSocCount]=acceptSocket;
			            _iSocCount++;
			            // ------------------
                        if (acceptSocket > fdmax)   
                        {
                            fdmax = acceptSocket;
                        }
                    }
                }
                else
                {
                    
                  if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0)
                    {
      			        printf(" Stop connect %d\n", i);
                        close(i); 
                        FD_CLR(i, &allSocket); 
                    }
                   else
                    {
                    // Nhan du lieu thanh cong :   
                       
                        buf[nbytes] = '\0';
                        printf("Receiver From %d : %s\n",i, buf);
                        getRegister(buf);
                  if(iFlag==IUSER)
                    {      
                 _loginStr str=getUsernameAndpass(buf); 
                                    
                 if(checkUser(str.username,str.password)==true && checkExist(str.username)==false)
                         {
							
							strcpy(uConnect[iConnect].username,str.username);
							printf(" |%s| ",uConnect[iConnect].username);
							j=0;
							iConnect++;
							// Thuc hien coppy vao cau truc UserConnect 
							strcpy(userConnect[iCountClient].username,str.username);
							userConnect[iCountClient].idSocket=i;
							iCountClient++;
							printf(" iCount Client %d ",iCountClient);
							// Thao tac cap nhat vao FILE profile nguoi dung 
							writeCurrentUser(i);
							send(i,"OK",2,0);
			             }
                      else 
                        send(i,"Ban Hay Dang Nhap Lai",22,0);
                            // Neu ma du so Client thi bat dau chuyen sang trang thai Test 
                      if(iCountClient==defTotal)      
                            {
							    printf(" Chuyen sang trang thai gui cau hoi roai ");
							    iFlag=ITEST;
							    iCountClient=0;
							  // Thuc hien gui cau hoi dau tien 
							} 
       //#######################  End USER
			      }
                else if(iFlag==ITEST)
			        {
					          // THUC HIEN GIAO TIEP TRA LOI VA NHAN CAU HOI 
					          
					          
					          _packageSend sSent=getFromClientSent(buf,i);
							  if(strcmp(sSent.anser,"OK")==0)
							  {
							      
							      userConnect[iCountClient].idSocket=i;
								  iCountClient++;
								  writeCurrentUser(i);
								  writeFileLog(i,sSent.username,j);
							      defTotal++; 
							       
							  }
							 else  if(strcmp(sSent.anser,quesStr[j].anser)==0)
							  {   
								  //send(sSent.idSocket,quesStr[j].question,strlen(quesStr[j].question),0);
								  // Ghi vao file la thang nay tra loi dung 
								  userConnect[iCountClient].idSocket=i;
								  iCountClient++;
								  writeCurrentUser(i);
								  writeFileLog(i,sSent.username,j);
					          } 
					          else 
					          {
								  // Truong hop tra loi sai cau hoi  
								  char *s1=(char*)malloc(sizeof(char)*100);
								  strcpy(s1,"QUIT");
								  //strcat(s1,"\n");
								  //strcat(s1,quesStr[j].anser);
								  send(i,s1,strlen(s1),0);
								  defTotal--;  
							  }
							  // Thuc hien doi trong vong 15 giay 
							   
						     // Can xet lai truong hop chi gui cho nhung thang nao dung thoi .
							  if(iCountClient==defTotal)
							   {
								int l=0;
								j++;
								int t=15;
								 if(iCountClient==1)
                                   send(userConnect[iCountClient-1].idSocket,"WIN",3,0);
                                 else 
                                 {                              
								// Gui lai cho nhung client tra loi dung 
							    for(l=0;l<iCountClient;l++)
							     { 
									
									  send(userConnect[l].idSocket,quesStr[j].question,strlen(quesStr[j].question),0);
								                                      
						         }  
						         // Tra ve trang thai ban dau .
							    iCountClient=0;
							    resetFile();
							    }
							}
				      	  }
                   
                    }
                } 
            } //<!>
         } 
 }
    printf(" SERVER TEMINATED ... ");
    return 0;
}

