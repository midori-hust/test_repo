CC = gcc
CFLAGS = -g -std=c99

all: test

test: test.o library.o my_input_lib.o
	$(CC) test.o library.o my_input_lib.o -o test

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o test.o

library.o: library.c library.h
	$(CC) $(CFLAGS) -c library.c -o library.o

my_input_lib.o: my_input_lib.c my_input_lib.h
	$(CC) $(CFLAGS) -c my_input_lib.c -o my_input_lib.o

clean:
	rm -rf *.o test