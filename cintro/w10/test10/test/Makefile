CC = gcc
CFLAGS = -g -std=c99

all: exp

exp: vd.o swap.o
	$(CC) vd.o swap.o -o exp

vd.o: vd.c
	$(CC) $(CFLAGS) -c vd.c -o vd.o

swap.o: swap.c swap.h 
	$(CC) $(CFLAGS) -c swap.c -o swap.o

clean: 
	rm -rf *.o exp *~
