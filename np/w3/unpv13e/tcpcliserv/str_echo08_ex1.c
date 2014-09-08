#include	"unp.h"

void
str_echo(int sockfd)
{
	ssize_t		n;
	char		line[MAXLINE];
	char		temp[MAXLINE];
	int 		i, byteCounter = 0, lineCounter = 0;

	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */

		// Modify
		Fputs(line, stdout);

		n = strlen(line);// Modify
		lineCounter += 1;

		if(strcmp(line, "\n") == 0) {
			byteCounter += n;
		} else {
			byteCounter += 1;
			printf("\nServer:\nBytes received: %d\n", byteCounter); // Modify	
			printf("Lines received: %d\n", lineCounter); // Modify	
			byteCounter = 0;
			lineCounter = 0;
		}

		for(i=0; i<n; i++) {// Modify
			temp[i] = line[n-2-i];// Modify
		}

		temp[n-1] = '\n'; // Modify
		temp[n] = '\0';	// Modify

		Writen(sockfd, temp, n);
		
	}
}
