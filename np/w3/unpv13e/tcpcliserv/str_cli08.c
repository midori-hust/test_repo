#include	"unp.h"

#define MAXLENGTH 100

void
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];
	char buff[MAXLINE];
	int i;
	int n;
	FILE *fout;
	char filename[MAXLENGTH] = "return.txt";


	if(fp != stdin) {
		if((fout = fopen(filename, "w+")) == NULL) {
			printf("Cannot open %s\n", filename);
			return;
		}
		while (1) {
			Fgets(sendline, MAXLINE, fp);
			if(feof(fp)) break;
			Writen(sockfd, sendline, strlen(sendline));
			
			if (Readline(sockfd, recvline, MAXLINE) == 0)
				err_quit("str_cli: server terminated prematurely");
			

			n = strlen(recvline);
			for(i=0; i<n; i++) {// Modify
				buff[i] = recvline[n-2-i];// Modify
			}

			buff[n-1] = '\n'; // Modify
			buff[n] = '\0';	// Modify

			Fputs(buff, fout);
		}
		fclose(fout);
	}

	else {
		while (Fgets(sendline, MAXLINE, fp) != NULL) {
	
			Writen(sockfd, sendline, strlen(sendline));
	
			if (Readline(sockfd, recvline, MAXLINE) == 0)
				err_quit("str_cli: server terminated prematurely");
	
			if(strcmp(sendline,"\n") == 0) { // Modify
				printf("Client finished.\n");// Modify
				return;
			}// Modify
	
			Fputs(recvline, stdout);
		}
	}
}
