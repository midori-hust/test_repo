CC = gcc
CFLAGS = -g -std=c99

all: test


test: test.o lib.o
	$(CC) test.o lib.o -o test

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o test.o

lib.o: lib.c lib.h
	$(CC) $(CFLAGS) -c lib.c -o lib.o

clean:
	rm -rf *.o test
