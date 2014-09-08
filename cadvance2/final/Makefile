CC = gcc
CFLAGS = -g -std=c99

all: main

main: main.o extension_lib.o my_input_lib.o file_handle.o directed_graph.o shortest_path.o fs_lib.o libfdr.a
	$(CC) main.o extension_lib.o my_input_lib.o file_handle.o directed_graph.o shortest_path.o fs_lib.o libfdr.a -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

extension_lib.o: extension_lib.c extension_lib.h
	$(CC) $(CFLAGS) -c extension_lib.c -o extension_lib.o

fs_lib.o: fs_lib.c fs_lib.h
	$(CC) $(CFLAGS) -c fs_lib.c -o fs_lib.o

shortest_path.o: shortest_path.c shortest_path.h
	$(CC) $(CFLAGS) -c shortest_path.c -o shortest_path.o

directed_graph.o: directed_graph.c directed_graph.h
	$(CC) $(CFLAGS) -c directed_graph.c -o directed_graph.o 

file_handle.o: file_handle.c file_handle.h
	$(CC) $(CFLAGS) -c file_handle.c -o file_handle.o

my_input_lib.o: my_input_lib.c my_input_lib.h
	$(CC) $(CFLAGS) -c my_input_lib.c -o my_input_lib.o

clean:
	rm -rf *.o *~ main