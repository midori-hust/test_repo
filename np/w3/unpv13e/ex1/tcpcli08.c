#include	"unp.h"

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;
	FILE *f;

	if (argc != 2 && argc != 3)
		err_quit("usage: tcpcli <IPaddress>\nwith the default input is stdin, or\ntcpcli <IPaddress> <File name>\nwith the input is a file.\n");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	if(argc == 3) {	
		if((f = fopen(argv[2], "r")) == NULL) {
			printf("Cannot open %s\n", argv[2]);
			exit(1);
		}
		str_cli(f, sockfd);		/* do it all */
		fclose(f);
	}
	else
	{
		str_cli(stdin, sockfd);
	}

	exit(0);
}
