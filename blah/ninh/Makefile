CC = gcc
CFLAGS = -g -std=c99

all: test

test: test.o library.o stack.o
	$(CC) test.o library.o stack.o -o test

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o test.o

library.o: library.c library.h
	$(CC) $(CFLAGS) -c library.c -o library.o

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c -o stack.o

clean:
	rm -rf *.o test *~