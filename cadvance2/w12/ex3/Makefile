CC = gcc
CFLAGS = -g -std=c99

all: ex3

ex3: ex3.o extension_lib.o my_input_lib.o file_handle.o graph.o fs_lib.o libfdr.a
	$(CC) ex3.o extension_lib.o my_input_lib.o file_handle.o graph.o fs_lib.o libfdr.a -o ex3

ex3.o: ex3.c
	$(CC) $(CFLAGS) -c ex3.c -o ex3.o

extension_lib.o: extension_lib.c extension_lib.h
	$(CC) $(CFLAGS) -c extension_lib.c -o extension_lib.o

fs_lib.o: fs_lib.c fs_lib.h
	$(CC) $(CFLAGS) -c fs_lib.c -o fs_lib.o

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c -o graph.o 

file_handle.o: file_handle.c file_handle.h
	$(CC) $(CFLAGS) -c file_handle.c -o file_handle.o

my_input_lib.o: my_input_lib.c my_input_lib.h
	$(CC) $(CFLAGS) -c my_input_lib.c -o my_input_lib.o

clean:
	rm -rf *.o *~ ex3