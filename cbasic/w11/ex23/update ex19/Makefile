CC = gcc
CFLAGS = -g -std=c99

all: libra

libra: test.o midterm.o
	$(CC) test.o midterm.o -o libra

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o test.o

midterm.o: midterm.c midterm.h
	$(CC) $(CFLAGS) -c midterm.c -o midterm.o

clean: rm -rf *.o libra
