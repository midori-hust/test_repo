CC = gcc
CFLAGS = -g -std=c99

all: ex4

ex4: ex4.o extension_lib.o my_input_lib.o
	$(CC) ex4.o extension_lib.o my_input_lib.o -o ex4

ex4.o: ex4.c
	$(CC) $(CFLAGS) -c ex4.c -o ex4.o

extension_lib.o: extension_lib.c extension_lib.h
	$(CC) $(CFLAGS) -c extension_lib.c -o extension_lib.o

my_input_lib.o: my_input_lib.c my_input_lib.h
	$(CC) $(CFLAGS) -c my_input_lib.c -o my_input_lib.o

clean:
	rm -rf *.o *~ ex4