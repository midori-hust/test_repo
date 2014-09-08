CC = gcc -std=c99
CFLAGS=-Wall -g

all: chess_console

OBJS = mainConsoleChess.o ClientHandle.o Client.o message.o tscp.a

chess_console: $(OBJS)
	$(CC) -o chess_console $(OBJS)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm -f *.o
