#include "resource.h"

int main(int args,char *argv[])
{
  int client_sock;
  int client_len;
  char buf[256];
  int result;
  int number;
  struct sockaddr_in client_addr;
  FILE *f;
  char username[40];
  char password[40];
  int count=0;
  int choise;
  //char addr[20]="127.0.0.1";
  char openfile[40];
  char savefile[40];
  system("clear");

  /* create client socket*/
  if((client_sock = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
      perror("Can not create socket");
      exit(1);
    }

  /* set up client information */
  if(args != 2)
    {
      perror("chay lai:");
      exit(1);
    }
  client_addr.sin_family = AF_INET;
  inet_pton(AF_INET,argv[1],&client_addr.sin_addr);
  client_addr.sin_port = htons(9734);
  client_len = sizeof(client_addr);

  /* create client connect*/
  if((result = connect(client_sock,(struct sockaddr*)&client_addr,client_len)) < 0)
    {
      perror("Oop:client1");
      exit(2);
    }
  do{
    printf("\n------------------------------------------");
    printf("\n|          Nhap 2 de dang ki tai khoan   |");
    printf("\n|          Nhap 1 de dang nhap he thong  |");
    printf("\n|          Nhap 0 de thoat               |");
    printf("\n------------------------------------------\n");
    scanf("%d",&choise);
    while(getchar() != '\n');
  }while(0 > choise || choise >= 3);
  
  switch(choise)
    {
    case 1:
      /* Gui lua chon dang nhap len server */
      send(client_sock,&choise,1,0);
      if(dangnhap(client_sock))
	{
	  do{
	    printf("\n-------------------------------------");
	    printf("\n|          Nhap 1 de ma hoa file    |");
	    printf("\n|          Nhap 2 de giai ma file   |");
	    printf("\n|          Nhap 0 de thoat          |");
	    printf("\n-------------------------------------\n");
	    scanf("%d",&choise);
	    while(getchar() != '\n');
	  }while(0 > choise || choise >= 3);
	    switch(choise)
	      {
	      case 1:
		/* Gui lua chon la ma hoa cho server */
		send(client_sock,&choise,1,0);
		/* Nhap ten file can ma hoa */
		printf("\nNhap ten file can mo:");
		gets(openfile);
		printf("\nNhap ten file can luu:");
		gets(savefile);
		/* Gui file can ma hoa len server */
		if(guiFile(client_sock,openfile) == -1)
		  {
		    printf("File can gui la rong\n");
		     return -1;
		  }else{
		  printf("\nClient gui file ket thuc\n");
		  if(nhanFile(client_sock,savefile) == -1)
		    {
		      printf("Khong nhan duoc file ma hoa\n");
		      return -1;
		    }else{
		    printf("\nMa hoa thanh cong tao ra file: %s\n",savefile);
		    close(client_sock);
		    return 0;
		  }
		}
	      case 2:
		/* Gui lua chon la ma hoa cho server */
		send(client_sock,&choise,1,0);
		/* Nhap ten file can ma hoa */
		printf("\nNhap ten file can mo:");
		gets(openfile);
		printf("\nNhap ten file can luu:");
		gets(savefile);
		/* Gui file can ma hoa len server */
		if(guiFile(client_sock,openfile) == -1)
		  {
		    printf("File gui la rong\n");
		    return -1;
		  }else{
		  printf("\nClient gui file ket thuc\n");
		  if( nhanFile(client_sock,savefile) == -1)
		    {
		      printf("\nKhong nhan duoc file giai ma\n");
		      return -1;
		    }else{
		    printf("\nNhan file giai ma la: %s\n",savefile);
		    close(client_sock);
		    return 0;
		  }
		}
	      default:
		send(client_sock,&choise,1,0);
		break;
	      }
	}
      else
	{
	  printf("\nBan da nhap sai username or password\n");
	  break;
	}
      break;
    case 2:
      /* Gui lua chon len server la dang nhap */
      send(client_sock,&choise,1,0);
      if(dangki(client_sock))
	{
	  printf("\nDang ki thanh cong");
	}
      else
	{
	  printf("\nDang ki that bai");
	}
      close(client_sock);
      break;
    }
  exit(0);
}
