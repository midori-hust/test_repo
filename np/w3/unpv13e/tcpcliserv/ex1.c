#include	"unp.h"

void
str_echo(int sockfd)
{
	//long		arg1, arg2;
	ssize_t		n;
	char		line[MAXLINE];
	char		temp[MAXLINE];
	int 		i, byteCounter = 0, lineCounter = 0;

	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */
/*
		if (sscanf(line, "%ld%ld", &arg1, &arg2) == 2) 
			snprintf(line, sizeof(line), "%ld\n", arg1 + arg2);
		else 
			snprintf(line, sizeof(line), "input error\n");
*/		
		// Modify
		Fputs(line, stdout);

		n = strlen(line);// Modify
		lineCounter += 1;

		if(line[0] != '\n') {
			byteCounter += n;
		} else {
			byteCounter += 1;
			printf("%d\n", byteCounter); // Modify	
			printf("%d\n", lineCounter); // Modify	
			byteCounter = 0;
			lineCounter = 0;
		}

		for(i=0; i<n; i++) {// Modify
			temp[i] = line[n-2-i];// Modify
		}

		temp[n-1] = '\n'; // Modify
		temp[n] = '\0';	// Modify
		//printf("%s", temp);

		Writen(sockfd, temp, n);
		
	}
}


/*
#include	"unp.h"

void
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];

	while (Fgets(sendline, MAXLINE, fp) != NULL) {

		if(sendline[0] == '\n') { // Modify
			printf("Client finished.\n");// Modify
			Writen(sockfd, sendline, strlen(sendline));
			return;// Modify
		}// Modify

		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		Fputs(recvline, stdout);
	}
}

*/