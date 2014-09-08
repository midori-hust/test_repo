CC = gcc -std=c99
CFLAGS=-Wall -g

chess_console: main board eval data search
	$(CC) -o chess_console main.o board.o eval.o data.o search.o

main: main.c
	$(CC) $(CFLAGS) -c main.c

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


