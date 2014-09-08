#include "resource.h"
#define MAX_SIZE 256

int checkUser(char *username,char *password)
{
  FILE *f;
  char buf[256];
  char temp[40];
  int i=0;
  int j=0;
  int userLenght;
  int passLenght;
  int bufLenght;
  int flag=0;


  userLenght=strlen(username);
  passLenght=strlen(password);
  //printf("\nUserLenght:%d\tPssLenght:%d",userLenght,passLenght);

  if((f=fopen("user.txt","r")) == NULL)
    {
      perror("File:");
      return 0;
      exit(1);
    }

  while(fgets(buf,256,f))
    {
      bufLenght =strlen(buf);

      //printf("\nBufLenght:%d",bufLenght);

      if(bufLenght != (userLenght + passLenght +1))
	continue;

      //printf("\nKiem tra:%s",buf);
      j=0;
      while(buf[j] != ' ')
	{
	  flag=0;
	  if((j > userLenght) || (buf[j] != username[j]))
	    {
	      printf("\nUsername sai");
	      flag=1;
	      break;
	    }
	  j++;
	}
      if(flag==1)
      {
	printf("\nChay lenh continue flag=%d",flag);
	continue;
      }
      /*if(j < userLenght)
	{
	  fclose(f);
	  return 0;
	  }*/
      i=j+1;
      j=0;
      while(i<bufLenght)
	{
	  if(buf[i] != password[j])
	    {
	      printf("\nPassword Sai i=%d",i);
	      fclose(f);
	      return 0;
	    }
	  j++;
	  i++;
	}
      fclose(f);
      return 1;
    }
  fclose(f);
  return 0;
}

int login(int client_sock)
{
  char username[40];
  char password[40];
  int result;
  int kq=0;
  int count =0;
  /*
   * Nhan Username password kiem tra tinh hop le
   * neu hop le tra OK ve client bao cho client
   * truyen giao tiep.
   */
  do{
    result=read(client_sock,username,40);
    username[result]='\0';
    result=read(client_sock,password,40);
    password[result]='\0';
    if(checkUser(username,password))
      {
	kq=1;
	send(client_sock,&kq,1,0);
	return 1;
      }
    else
      {
	send(client_sock,&kq,1,0);
      }
    count++;
  }while(count < 3);
  return 0;
  }
  
int nhanFile(int client_sock,char *filename)
{
  FILE *f;
  int result;
  char buf[MAX_SIZE];
  long rfilesize;
  long filesize=0;
  char c;
  recv(client_sock,&rfilesize,sizeof(long),0);
  if(rfilesize == 0)
    {
      printf("File rong");
      return -1;
    }
  printf("\nBan se nhan %ld byte",rfilesize);
  if((f=fopen(filename,"w")) == NULL)
    {
      perror("Fail");
      exit(1);
    }
  while(filesize < rfilesize)
    {
      result=recv(client_sock,buf,MAX_SIZE-1,0);
      filesize += result;
      fwrite(buf,sizeof(char),result,f);
      // printf("\nBan da nhan %d byte",result);
    }
  fclose(f);
  return 1;
}

int guiFile(int client_sock,char *filein)
{
  FILE *f;
  int number;
  char buf[MAX_SIZE];
  long filesize;
  long sfilesize=0;
  char c;
  filesize=fsize(filein);
  if(filesize == -1 || filesize == 0)
    {
      filesize=0;
      send(client_sock,&filesize,sizeof(filesize),0);
      return -1;
    }
  send(client_sock,&filesize,sizeof(filesize),0);
  if((f=fopen(filein,"r")) == NULL)
    {
      perror("File");
      exit(1);
    }
 do
   {
     number=fread(buf,sizeof(char),MAX_SIZE-1,f);
     sfilesize += number;
     send(client_sock,buf,number,0);
   } while(sfilesize < filesize);
 printf("\nBan da gui %ld byte",sfilesize);
 fclose(f);
 return 1;
}

void mahoa(char *filein,char *fileout)
{
  char command[256];
  printf("\nThuc hien ma hoa");
  strcpy(command,"../src/bfc c sf ");
  strcat(command,filein);
  strcat(command,"  ");
  strcat(command,fileout);
  printf("%s",command);
  system(command);
  strcpy(command,"rm -rf  ");
  strcat(command,filein);
  system(command);
}

void giaima(char *filein,char *fileout)
{
  char command[256];
  printf("\nThuc hien giai ma");
  strcpy(command,"../src/bfc d ");
  strcat(command,filein);
  strcat(command,"  ");
  strcat(command,fileout);
  printf("%s",command);
  system(command);
  strcpy(command,"rm -rf  ");
  strcat(command,filein);
  system(command);
}

int dangnhap(int client_sock)
{
  char username[40];
  char password[40];
  struct termios init,new;
  int number;
  int count=0;
  int result=0;
  do{
    do{
      printf("\nNhap username:");
      gets(username);
      number=strlen(username);
    }while(number <= 0);
    send(client_sock,username,number,0);
    
    /* luu cau hinh terminer */
    tcgetattr(fileno(stdin),&init);
    /* Dinh cau hinh moi */
    new=init;
    /* tat chuc nang echo */
    new.c_lflag &= ~ECHO;
    
    printf("\nNhap password:");
    if(tcsetattr(fileno(stdin),
		 TCSAFLUSH,&new) != 0){
      fprintf(stderr,"Could not set attributes\n");
    }else
    {
      do{
	fgets(password,40,stdin);
	number=strlen(password);
      }while(number <= 0);
      tcsetattr(fileno(stdin),TCSANOW,&init);
    }
    send(client_sock,password,number,0);
    recv(client_sock,&result,1,0);
    if(result==1)
      return 1;
    else
      printf("\nBan da nhap sai username hoac password\n");
    count++;
  }while(count < 3);
  return 0;
}

int fsize(char* file) {
  int size;
  FILE* fh;
  
  fh = fopen(file, "rb"); //binary mode
  if(fh != NULL){
    if( fseek(fh, 0, SEEK_END) ){
      fclose(fh);
      return -1;
    }
    
    size = ftell(fh);
    fclose(fh);
    return size;
  }
  
  return -1; //error
}

void xoafile(char *file)
{
  char command[256];
  strcpy(command,"rm -rf ");
  strcat(command,file);
  system(command);
}

int checkusername(char *username)
{
  FILE *f;
  char buf[256];
  int userLenght;
  int bufLenght;
  
  
  userLenght=strlen(username);

  if((f=fopen("user.txt","r")) == NULL)
    {
      perror("File:");
      return 0;
      exit(1);
    }

  while(fgets(buf,256,f))
    {
      if((strncmp(username,buf,userLenght) == 0) && (buf[userLenght] == ' '))
	{
	  fclose(f);
	  return 1;
	}
    }
  fclose(f);
  return 0;
}

int dangki(int client_sock)
{
  char username[40];
  char password[40];
  char repassword[40];
  struct termios init,new;
  int number;
  int count=0;
  int result=0;
  do{
    result = 0;
    do{
      printf("\nNhap username:");
      gets(username);
      number=strlen(username);
    }while(number <= 0);
    send(client_sock,username,number,0);
    recv(client_sock,&result,1,0);
    if(result == 1)
      {
	printf("\nUsername da ton tai");
      }
  }while(result != 0);
  
  /* luu cau hinh terminer */
  tcgetattr(fileno(stdin),&init);
  /* Dinh cau hinh moi */
  new=init;
  /* tat chuc nang echo */
  new.c_lflag &= ~ECHO;
  do{
    printf("\nNhap password:");
    if(tcsetattr(fileno(stdin),
		 TCSAFLUSH,&new) != 0){
      fprintf(stderr,"Could not set attributes\n");
    }else{
      fgets(password,40,stdin);
      printf("\nNhap lai password:");
      fgets(repassword,40,stdin);
      if(strcmp(password,repassword) !=0)
	{
	  printf("\nBan phai nhap 2 password giong nhau");
	}
    }
  } while(strcmp(password,repassword) != 0);
  number=strlen(password);
  tcsetattr(fileno(stdin),TCSANOW,&init);
  send(client_sock,password,number,0);
  recv(client_sock,&result,1,0);
  if(result==1)
    return 1;
  return 0;
}

int nhandangki(client_sock)
{
  char username[40];
  char password[40];
  FILE *f;
  int number;
  int result=0;
  do{
    result = 0;
    number=recv(client_sock,&username,40,0);
    username[number]='\0';
    if(checkusername(username))
      {
	result=1;
	send(client_sock,&result,1,0);
      }
    else
      {
	result=0;
	send(client_sock,&result,1,0);
      }
  }while(result == 1);
  number=recv(client_sock,&password,40,0);
  password[number]='\0';
  if((f=fopen("user.txt","a")) == NULL)
    {
      result=0;
      send(client_sock,&result,1,0);
      perror("File:");
      exit(1);
    }
  if(fprintf(f,"%s %s",username,password))
    {
      result=1;
      send(client_sock,&result,1,0);
      printf("\nThanh cong");
      fclose(f);
      return 1;
    }else
    {
      result=0;
      send(client_sock,&result,1,0);
      return 0;
    }
}
