CC = gcc
CFLAGS = -g -std=c99

all: main

main: main.o extension_lib.o my_input_lib.o
	$(CC) main.o extension_lib.o my_input_lib.o -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

extension_lib.o: extension_lib.c extension_lib.h
	$(CC) $(CFLAGS) -c extension_lib.c -o extension_lib.o

my_input_lib.o: my_input_lib.c my_input_lib.h
	$(CC) $(CFLAGS) -c my_input_lib.c -o my_input_lib.o

clean:
	rm -rf *.o *~ main