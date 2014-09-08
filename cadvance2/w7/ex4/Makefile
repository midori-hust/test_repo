CC = gcc
CFLAGS = -g -std=c99

all: ex4

ex4: ex4.o extension_lib.o my_input_lib.o generic_lib.o file_handle.o symbol_table.o
	$(CC) ex4.o extension_lib.o my_input_lib.o generic_lib.o file_handle.o symbol_table.o -o ex4

ex4.o: ex4.c
	$(CC) $(CFLAGS) -c ex4.c -o ex4.o

extension_lib.o: extension_lib.c extension_lib.h
	$(CC) $(CFLAGS) -c extension_lib.c -o extension_lib.o

generic_lib.o: generic_lib.c generic_lib.h
	$(CC) $(CFLAGS) -c generic_lib.c -o generic_lib.o

file_handle.o: file_handle.c file_handle.h
	$(CC) $(CFLAGS) -c file_handle.c -o file_handle.o

symbol_table.o: symbol_table.c symbol_table.h
	$(CC) $(CFLAGS) -c symbol_table.c -o symbol_table.o

my_input_lib.o: my_input_lib.c my_input_lib.h
	$(CC) $(CFLAGS) -c my_input_lib.c -o my_input_lib.o

clean:
	rm -rf *.o *~ ex4