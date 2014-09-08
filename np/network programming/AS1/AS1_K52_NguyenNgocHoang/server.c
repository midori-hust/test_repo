#include "resource.h"

int main()
{
  int server_sockfd, client_sockfd;
  int server_len, client_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  char buf[256];
  char filename[40];
  char outfile[40];
  char command[256];
  int result=0;
  FILE *f;

  if((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror("socket");
      exit(1);
    }
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(9734);
  server_len = sizeof(server_address);
  if((bind(server_sockfd, (struct sockaddr *)&server_address, server_len)) < 0)
    {
      perror("Bind:");
      exit(1);
    }
  
  /*  Create a connection queue, ignore child exit details and wait for clients.  */
  
  listen(server_sockfd, 5);
  
  signal(SIGCHLD, SIG_IGN);
  
  while(1) {
    
    printf("server waiting\n");
    
    /*  Accept connection.  */
    
    client_len = sizeof(client_address);
    client_sockfd = accept(server_sockfd, 
			   (struct sockaddr *)&client_address, &client_len);
    
    if(fork() == 0) {
      recv(client_sockfd,&result,1,0);
      switch(result)
	{
	case 1:
	  if(login(client_sockfd))
	    {
	      /* Nhan lua chon tu client */
	      
		recv(client_sockfd,&result,1,0);
		// buf[result]='\0';
		
		switch(result)
		  {
		  case 1:
		    printf("\nMa hoa file\n");
		    sprintf(filename,"temp%d.txt",client_sockfd);
		    if(nhanFile(client_sockfd,filename) == -1)
		      {
			printf("\nClient muon ma hoa file khong ton tai");
			exit(-1);
		      }else{
		      sprintf(outfile,"temp%d.out",client_sockfd);
		      mahoa(filename,outfile);
		      if(guiFile(client_sockfd,outfile) == -1)
			printf("\nKhong ma hoa duoc");
		      else
			printf("\nServer gui file ket thuc");
		      xoafile(outfile);
		      break;
		    }
		  case 2:
		    printf("\nClient muon giai ma file\n");
		    sprintf(outfile,"etemp%d.out",client_sockfd);
		    if(nhanFile(client_sockfd,outfile) == -1)
		      {
			printf("\nClient muon giai ma file khong ton tai");
			exit(-1);
		      }else{
		      sprintf(filename,"etemp%d.txt",client_sockfd);
		      giaima(outfile,filename);
		      if(guiFile(client_sockfd,filename) == -1)
			{
			  printf("\nKhong giai ma duoc");
			}else{
			xoafile(filename);
			printf("\nServer gui file ket thuc");
		      }
		    }
		    break;
		  case 0:
		    break;
		  }
	      exit(0);
	      }
	  else{
	    printf("\nUsername or password khong hop le");
	    exit(-1);
	  }
	case 2:
	  if(nhandangki(client_sockfd))
	    {
	      printf("\nDang ki user thanh cong");
	    }
	  else
	    {
	      printf("\nDang ki user that bai");
	    }
	  break;
	case 0:
	  break;
	}
      exit(0);
    }
    
    /*  Otherwise, we must be the parent and our work for this client is finished.  */
    
    else {
      close(client_sockfd);
    }
  }
}
