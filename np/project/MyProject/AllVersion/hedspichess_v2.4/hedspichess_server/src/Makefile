CC = gcc -std=c99
CFLAGS=-Wall -g

all: chess_console

OBJS = EchoServer.o Server.o message.o

chess_console: $(OBJS)
	$(CC) -o chess_server $(OBJS)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm -f *.o
