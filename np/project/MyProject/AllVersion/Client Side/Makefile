CC = gcc -std=c99
CFLAGS=-Wall -g

chess_console: main board eval data search ClientHandle message Client
	$(CC) -o chess_console Client.o mainConsoleChess.o board.o eval.o data.o search.o ClientHandle.o message.o

Client: Client.c
	$(CC) $(CFLAGS) -c Client.c

ClientHandle: ClientHandle.c ClientHandle.h
	$(CC) $(CFLAGS) -c ClientHandle.c

message: message.c message.h
	$(CC) $(CFLAGS) -c message.c

mainConsoleChess.c:
	$(CC) $(CFLAGS) -c mainConsoleChess.c

board: board.c
	$(CC) $(CFLAGS) -c board.c

data: data.c
	$(CC) $(CFLAGS) -c data.c

eval: eval.c
	$(CC) $(CFLAGS) -c eval.c

search: search.c
	$(CC) $(CFLAGS) -c search.c

clean:
	rm -f *.o


