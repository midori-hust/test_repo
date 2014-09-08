CC = gcc
CFLAGS = -g -std=c99

all: libra

libra: test1.o linklist.o
	$(CC) test1.o linklist.o -o libra

test1.o: test1.c
	$(CC) $(CFLAGS) -c test1.c -o test1.o

linklist.o: linklist.c linklist.h
	$(CC) $(CFLAGS) -c linklist.c -o linklist.o

clean: rm -rf *.o libra