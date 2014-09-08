CC = gcc
CFLAGS = -g -std=c99

all: libra

libra: test.o queue.o stack.o
	$(CC) test.o queue.o stack.o -o libra

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o test.o

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c -o queue.o

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c -o stack.o

clean: rm -rf *.o libra
