CC = gcc
CFLAGS = -g -std=c99

all: ex1

ex1: ex1.o MergeSort.o
	$(CC) ex1.o MergeSort.o -o ex1

ex1.o: ex1.c
	$(CC) $(CFLAGS) -c ex1.c -o ex1.o

MergeSort.o: MergeSort.c MergeSort.h
	$(CC) $(CFLAGS) -c MergeSort.c -o MergeSort.o

clean: rm -rf *.o ex1