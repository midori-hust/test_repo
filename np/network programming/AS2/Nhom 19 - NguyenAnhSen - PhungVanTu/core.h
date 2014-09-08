#ifndef CORE
#define CORE
#include <sys/time.h>
#include <sys/types.h>
// Define error
#define MONITOR_NO_ERROR 0
#define MONITOR_CONNECT_ERROR -1
#define MONITOR_TIMEOUT_ERROR -2
// Define mask
#define CHECK_READY_READ 1
#define CHECK_READY_WRITE 2
#define CHECK_READY_EXCEPT 4

typedef struct timeval timeval;
typedef struct Monitor
{
	int check[FD_SETSIZE];
	int errorNo;
	int n_fd;
	fd_set master_readfds;
	fd_set master_writefds;
	fd_set master_exceptfds;
	int fd_max;
	void (*addFD)(struct Monitor *, int );
	void (*removeFD)(struct Monitor *, int);
	int (*getFirstReadyFDList)(struct Monitor *,int *list, int mask, int time_sec);
	void (*removeAllFD)(struct Monitor *monitor);
	void (*	displayError)(struct Monitor *);
	void (*resetMonitor)(struct Monitor *, int);
}
Monitor;
Monitor newMonitor();
void addFD(Monitor *monitor, int newFD);
void removeFD(Monitor *monitor, int fd);
int getFirstReadyFDList(Monitor *monitor, int *list, int mask, int time_sec);
void displayError(Monitor *);
void removeAllFD(Monitor *);
void resetMonitor(Monitor *, int );
#endif
