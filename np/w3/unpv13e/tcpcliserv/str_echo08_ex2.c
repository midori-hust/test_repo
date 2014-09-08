#include	"unp.h"

void
str_echo(int sockfd)
{
	long		arg1;
	ssize_t		n;
	char		line[MAXLINE];

	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */
		if (sscanf(line, "%ld", &arg1) == 1) {
			if(arg1 == 0) {
				snprintf(line, sizeof(line), "%ld\n", arg1);
				printf("Client closed\n");
			} else {
				if(arg1 < 1 || arg1 > 10) 
					snprintf(line, sizeof(line), "input not in [1, 10]\n");	
				else
					snprintf(line, sizeof(line), "%ld\n", arg1);
			}
		}
		else 
			snprintf(line, sizeof(line), "input error\n");

		n = strlen(line);
		Writen(sockfd, line, n);
		
	}
}
