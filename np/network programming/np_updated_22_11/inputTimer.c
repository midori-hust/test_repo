#include <stdio.h>

#define ESCAPE 27
int main() {

	time_t starttime, endtime;
	char ch;
	int done = 0;

	starttime = time();
	/* Poll for a keypress */
	while (!done) {
		if (kbhit()) {
			/* Get what key was pressed */
			ch = getch();
		}
		/* Check if 10 seconds have elapsed */
		endtime = time();
		if (difftime(endtime, starttime) > 10)
			done = 1;
	}
}
