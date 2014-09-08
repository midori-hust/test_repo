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
				else{
					//snprintf(temp, sizeof(temp), "%ld\n", arg1);
					switch(arg1) {
						case 1:
						snprintf(line, sizeof(line), "mot\n");
						break;
						case 2:
						snprintf(line, sizeof(line), "hai\n");
						break;
						case 3:
						snprintf(line, sizeof(line), "ba\n");
						break;
						case 4:
						snprintf(line, sizeof(line), "bon\n");
						break;
						case 5:
						snprintf(line, sizeof(line), "nam\n");
						break;
						case 6:
						snprintf(line, sizeof(line), "sau\n");
						break;
						case 7:
						snprintf(line, sizeof(line), "bay\n");
						break;
						case 8:
						snprintf(line, sizeof(line), "tam\n");
						break;
						case 9:
						snprintf(line, sizeof(line), "chin\n");
						break;
						case 10:
						snprintf(line, sizeof(line), "muoi\n");
						break;
					}

				}
			}
		}
		else 
			snprintf(line, sizeof(line), "input error\n");

		n = strlen(line);
		Writen(sockfd, line, n);
		
	}
}
