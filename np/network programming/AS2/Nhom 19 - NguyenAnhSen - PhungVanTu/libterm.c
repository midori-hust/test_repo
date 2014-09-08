#include "libterm.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <stdlib.h>

struct  termios argin, argout;
unsigned char   ch = 0;
struct termios orig_termios;

void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
    struct termios new_termios;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    /* register cleanup handler, and set the new terminal mode */
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

int getch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}

char checkStdin()
{
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(0,&readfds);
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	char str[10];
	int nselect = select(1,&readfds,NULL,NULL,&timeout);
	if (nselect >0)
	{
		gets(str);
		char i = str[strlen(str) - 1];
		return i;
	}
	else return 0;
}
 
void clearBack(int n)
{
	for (;n >0;n--)
	{
		putchar('\b');
	}
}

void getEndAnswer(char *welcome, char *endAnswer, int timeout)
{
	char templateStr[100];
	int count = 0;
	sprintf(templateStr,"Remain time : %5d s --> %20s : %c",count,welcome,' ');
	int len = strlen(templateStr);
	len = len + 1;
	count = timeout * 20;
	char c;
	char endAnswerChar;
	do
	{
		usleep(50000);
		c = checkStdin();
		if (c == 0) c = ' ';
		else 
		{
			endAnswerChar = c;
			clearBack(len + 1);
		}
		count--;
		clearBack(len);
		printf("Remain time : %2.2f s --> %20s : %c",(float)count/20,welcome,c);
		fflush(stdout);
	}
	while (count > 0);
	printf("\nEnd answer : %c\n",endAnswerChar);
	endAnswer[0] = endAnswerChar;
	endAnswer[1] = 0;
}
