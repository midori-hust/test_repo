CC = gcc
CFLAGS = -g -std=c99

all: test

test: test.o bst.o
	$(CC) test.o bst.o -o test

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o test.o

bst.o: bst.c bst.h
	$(CC) $(CFLAGS) -c bst.c -o bst.o

clean:
	rm -rf *.o test