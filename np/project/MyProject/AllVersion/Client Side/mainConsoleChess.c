#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "data.h"
#include "protos.h"
#include "message.h"

/* get_ms() returns the milliseconds elapsed since midnight,
   January 1, 1970. */

#include <sys/timeb.h>
BOOL ftime_ok = FALSE;  /* does ftime return milliseconds? */
int get_ms()
{
	struct timeb timebuffer;
	ftime(&timebuffer);
	if (timebuffer.millitm != 0)
		ftime_ok = TRUE;
	return (timebuffer.time * 1000) + timebuffer.millitm;
}

#define MAXLENGTH 100

/* mainConsoleChess() is basically an infinite loop that either calls
   think() when it's the enermy's turn to move or prompts
   the user for a command (and deciphers it). */

int mainConsoleChess(int pick_side, int sockfd)
{
	int enermy_side;
	char s[256];
	int m;
	char recvline[MAXLENGTH];
	message_t newMesg;

	printf("\n");
	printf("Phung Nhat Huy and Pham Duy Hung's Console Chess\n");
	printf("\n");
	printf("Type \"help\" to displays a list of commands.\n");
	printf("\n");
	init_hash();
	init_board();
	gen();
	enermy_side = EMPTY;
	if(pick_side == LIGHT)
		enermy_side = DARK;
	else
		enermy_side = LIGHT;

	max_time = 1 << 25;
	max_depth = 4;
	for (;;) {
		if (side == enermy_side) {  /* enermy's turn */
			
			/* think about the move and make it */
		if (recv(sockfd, recvline, MESSAGE_MAXLEN, 0) < 0) {
	      printf("str_cli: server terminated prematurely\n");
	      exit(1);
	    }

	    recvline[strlen(recvline)] = '\0';
	    newMesg = message_parse(recvline);

		if(newMesg->option != NULL && newMesg->option1 != NULL) {
			//s = strcat(newMesg->option, newMesg->option1);
			//printf("%s\n", s);
		}
		else {
			printf("Error occur\n");
		}

		printf("Your enermy's move: %s\n", s);
		m = parse_move(s);
		if (m == -1 || !makemove(gen_dat[m].m.b))
			printf("Illegal move.\n");
		else {
			ply = 0;
			gen();
			print_result(sockfd);
		}

		continue;
		}

		/* get user input */
		printf("ConsoleChess > ");
		if (scanf("%s", s) == EOF)
			return 0;
		if (!strcmp(s, "undo")) {
			if (!hply)
				continue;
			enermy_side = EMPTY;
			takeback();
			ply = 0;
			gen();
			continue;
		}
		if (!strcmp(s, "new")) {
			enermy_side = EMPTY;
			init_board();
			gen();
			continue;
		}
		if (!strcmp(s, "d")) {
			print_board();
			continue;
		}
		if (!strcmp(s, "bye")) {
			printf("Thanks for playing. Enjoy!\n");
			while(getchar() != '\n');
			break;
		}
		if (!strcmp(s, "help")) {
			printf("undo - takes back a move\n");
			printf("new - starts a new game\n");
			printf("d - display the board\n");
			printf("bye - exit the program\n");
			printf("Enter moves in coordinate notation, e.g., e2e4, e7e8Q (for promote moving)\n");
			continue;
		}

		/* maybe the user entered a move? */
		m = parse_move(s);
		if (m == -1 || !makemove(gen_dat[m].m.b))
			printf("Illegal move.\n");
		else {
			ply = 0;
			gen();
			print_result(sockfd);
		}
	}
	return 0;
}


/* parse the move s (in coordinate notation) and return the move's
   index in gen_dat, or -1 if the move is illegal */

int parse_move(char *s)
{
	int from, to, i;

	/* make sure the string looks like a move */
	if (s[0] < 'a' || s[0] > 'h' ||
			s[1] < '0' || s[1] > '9' ||
			s[2] < 'a' || s[2] > 'h' ||
			s[3] < '0' || s[3] > '9')
		return -1;

	from = s[0] - 'a';
	from += 8 * (8 - (s[1] - '0'));
	to = s[2] - 'a';
	to += 8 * (8 - (s[3] - '0'));

	for (i = 0; i < first_move[1]; ++i)
		if (gen_dat[i].m.b.from == from && gen_dat[i].m.b.to == to) {

			/* if the move is a promotion, handle the promotion piece;
			   assume that the promotion moves occur consecutively in
			   gen_dat. */
			if (gen_dat[i].m.b.bits & 32)
				switch (s[4]) {
					case 'N':
						return i;
					case 'B':
						return i + 1;
					case 'R':
						return i + 2;
					default:  /* assume it's a queen */
						return i + 3;
				}
			return i;
		}

	/* didn't find the move */
	return -1;
}


/* move_str returns a string with move m in coordinate notation */

char *move_str(move_bytes m)
{
	static char str[6];

	char c;

	if (m.bits & 32) {
		switch (m.promote) {
			case KNIGHT:
				c = 'n';
				break;
			case BISHOP:
				c = 'b';
				break;
			case ROOK:
				c = 'r';
				break;
			default:
				c = 'q';
				break;
		}
		sprintf(str, "%c%d%c%d%c",
				COL(m.from) + 'a',
				8 - ROW(m.from),
				COL(m.to) + 'a',
				8 - ROW(m.to),
				c);
	}
	else
		sprintf(str, "%c%d%c%d",
				COL(m.from) + 'a',
				8 - ROW(m.from),
				COL(m.to) + 'a',
				8 - ROW(m.to));
	return str;
}


/* print_board() prints the board */

void print_board()
{
	int i;
	
	printf("\n8 ");
	for (i = 0; i < 64; ++i) {
		switch (color[i]) {
			case EMPTY:
				printf(" .");
				break;
			case LIGHT:
				printf(" %c", piece_char[piece[i]]);
				break;
			case DARK:
				printf(" %c", piece_char[piece[i]] + ('a' - 'A'));
				break;
		}
		if ((i + 1) % 8 == 0 && i != 63)
			printf("\n%d ", 7 - ROW(i));
	}
	printf("\n\n   a b c d e f g h\n\n");
}



/* print_result() checks to see if the game is over, and if so,
   prints the result. */

void print_result(int sockfd)
{
	int i;

	/* is there a legal move? */
	for (i = 0; i < first_move[1]; ++i)
		if (makemove(gen_dat[i].m.b)) {
			takeback();
			break;
		}
	if (i == first_move[1]) {
		if (in_check(side)) {
			if (side == LIGHT) {
				printf("0-1 {Black mates}\n");
				if (send(sockfd, message_toString(message_construct(RESULT, "1", "0", "0", "0")), MESSAGE_MAXLEN, 0) != MESSAGE_MAXLEN ) {
	     		 printf("send() sent a different number of bytes than expected\n");
	    		}
			}
			else {
				printf("1-0 {White mates}\n");
				if (send(sockfd, message_toString(message_construct(RESULT, "0", "1", "0", "0")), MESSAGE_MAXLEN, 0) != MESSAGE_MAXLEN ) {
	     		 printf("send() sent a different number of bytes than expected\n");
	    		}
			}
		}
		else {
			printf("1/2-1/2 {Stalemate}\n");
				if (send(sockfd, message_toString(message_construct(DRAW, "0", "0", "0", "0")), MESSAGE_MAXLEN, 0) != MESSAGE_MAXLEN ) {
	     		 printf("send() sent a different number of bytes than expected\n");
	    		}
		}
	}
	else if (reps() == 3) {
		printf("1/2-1/2 {Draw by repetition}\n");
		if (send(sockfd, message_toString(message_construct(DRAW, "0", "0", "0", "0")), MESSAGE_MAXLEN, 0) != MESSAGE_MAXLEN ) {
    		 printf("send() sent a different number of bytes than expected\n");
		}
	}
	else if (fifty >= 100) {
		printf("1/2-1/2 {Draw by fifty move rule}\n");
		if (send(sockfd, message_toString(message_construct(DRAW, "0", "0", "0", "0")), MESSAGE_MAXLEN, 0) != MESSAGE_MAXLEN ) {
     		 printf("send() sent a different number of bytes than expected\n");
   		}
	}
}