#include	"unp.h"

void
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];

	while (Fgets(sendline, MAXLINE, fp) != NULL) {

		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		if(strcmp(recvline, "0\n") == 0) {
			printf("Client terminated\n");
			return;
		}

		printf("Server: ");
		Fputs(recvline, stdout);
	}
}
