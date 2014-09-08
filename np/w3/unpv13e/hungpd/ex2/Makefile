include ../Make.defines

PROGS =	 tcpcli08 tcpserv08

all:	${PROGS}

tcpcli08:	tcpcli08.o str_cli08.o
		${CC} ${CFLAGS} -o $@ tcpcli08.o str_cli08.o ${LIBS}

tcpserv08:	tcpserv08.o str_echo08.o sigchldwaitpid.o
		${CC} ${CFLAGS} -o $@ tcpserv08.o str_echo08.o sigchldwaitpid.o \
			${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}
