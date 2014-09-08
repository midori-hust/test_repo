CC = gcc
CFLAGS = -g -std=c99

all: libra

libra: test1.o stack.o
	$(CC) test1.o stack.o -o libra

test1.o: test1.c
	$(CC) $(CFLAGS) -c test1.c -o test1.o

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c -o stack.o

clean: rm -rf *.o libra
