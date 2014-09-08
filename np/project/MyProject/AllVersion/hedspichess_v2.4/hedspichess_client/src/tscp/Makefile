CC = gcc -std=c99
CFLAGS=-Wall -g

all: tscp.a

OBJS = search.o board.o data.o eval.o

tscp.a: $(OBJS)
	ar ru tscp.a $(OBJS)
	ranlib tscp.a

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm -f *.o


