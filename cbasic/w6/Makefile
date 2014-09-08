CC = gcc
CFLAGS = -g -std=c99

all: libra

libra: bai4.o phone.o
	$(CC) bai4.o phone.o -o libra

bai4.o: bai4.c
	$(CC) $(CFLAGS) -c bai4.c -o bai4.o

phone.o: phone.c phone.h
	$(CC) $(CFLAGS) -c phone.c -o phone.o

clean: rm -rf *.o libra
