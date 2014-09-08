#include <stdio.h>
#include "core.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

Monitor newMonitor()
{
	Monitor new;
	new.errorNo = MONITOR_NO_ERROR;
	new.n_fd = 0;
	new.fd_max = -1;
	new.addFD = addFD;
	new.removeFD = removeFD;
	new.resetMonitor = resetMonitor;
	new.getFirstReadyFDList = getFirstReadyFDList;
	new.displayError = displayError;
	new.removeAllFD = removeAllFD;
	FD_ZERO(&new.master_readfds);
	FD_ZERO(&new.master_writefds);
	FD_ZERO(&new.master_exceptfds);
	bzero(&new . check , sizeof (int) * FD_SETSIZE);
	return new;
}

void addFD(Monitor *self, int newFD)
{	
	self->n_fd++;
	self -> check[newFD] = TRUE;
	FD_SET(newFD, &self -> master_readfds);
	FD_SET(newFD, &self -> master_writefds);
	FD_SET(newFD, &self -> master_exceptfds);
	if (newFD > self -> fd_max)
	self -> fd_max = newFD;
}

void removeFD(Monitor *self, int fd)
{
	self->n_fd--;
	self -> check[fd] = FALSE;
	FD_CLR(fd, &self -> master_readfds);
	FD_CLR(fd, &self -> master_writefds);
	FD_CLR(fd, &self -> master_exceptfds);
	if (fd  ==  self -> fd_max)
	self -> fd_max = self -> fd_max  - 1;
}

int getFirstReadyFDList(Monitor *self, int *list,int mask,int time_sec)
{
	fd_set *readfds;
	fd_set *writefds;
	fd_set *exceptfds;
	//printf("Max fd : %d\n",monitor -> fd_max);
	if (mask & CHECK_READY_READ)
	{
		readfds = (fd_set*) malloc(sizeof(self -> master_readfds));
		memcpy(readfds,&self->master_readfds,sizeof(self -> master_readfds));
	}
	else readfds = NULL;
	
	if (mask & CHECK_READY_WRITE)
	{
		writefds = (fd_set*) malloc(sizeof(self -> master_writefds));
		memcpy(writefds,&self->master_writefds,sizeof(self -> master_writefds));
	}
	else writefds = NULL;

	if (mask & CHECK_READY_EXCEPT)
	{
		exceptfds = (fd_set*) malloc(sizeof(self -> master_exceptfds));
		memcpy(exceptfds,&self->master_exceptfds,sizeof(self -> master_exceptfds));
	}
	else exceptfds = NULL;

	int nselect;
	if (time_sec == -1)
	{
		nselect = select(self -> fd_max +1 , readfds, writefds, exceptfds,NULL);
	}
	else
	{
		struct timeval timeout;
		timeout.tv_sec = time_sec;
		nselect = select(self -> fd_max + 1, readfds, writefds, exceptfds, &timeout);
	}
	
	if (nselect == -1)
	{
		perror("SELECT");
		self->errorNo = MONITOR_CONNECT_ERROR;
		return -1;
	}
	if (nselect == 0)
	{
		printf("Timeout\n");
		self->errorNo = MONITOR_TIMEOUT_ERROR;
		return -1;
	}
	int i = 0;
	int count = 0;
	//printf("Max fd : %d\n",monitor -> fd_max);
	if ((readfds != NULL) && (mask & CHECK_READY_READ))
	{
		for (i = 0; i <= self -> fd_max ;i++)
		{
			if (FD_ISSET(i,readfds)) 
			{
				list[0] = i;
				count++;
				break;
			}
		}
	}
	
	if ((writefds != NULL )&&(mask & CHECK_READY_WRITE))
	{
		for (i = 0; i <= self -> fd_max ;i++)
		{
			if (FD_ISSET(i,writefds)) 
			{
				list[1] = i;
				count++;
				break;
			}
		}
	}
	if ((exceptfds != NULL )&&(mask & CHECK_READY_EXCEPT))
	{
		for (i = 0; i <= self -> fd_max ;i++)
		{
			if (FD_ISSET(i,exceptfds)) 
			{
				list[2] = i;
				count++;
				break;
			}
		}
	}
	self->errorNo = MONITOR_NO_ERROR;
	return count;
}

void displayError(Monitor *self)
{
	switch (self -> errorNo)
	{
		case MONITOR_CONNECT_ERROR:
		{
			printf("CONNECTION ERROR");
			perror("SELECT");
			break;
		}
		case MONITOR_TIMEOUT_ERROR:
		{
			printf("Timeout\n");
			break;
		}
	}
}

void removeAllFD(Monitor *monitor)
{
	int i = 0;
	for (i = 1; i <= monitor -> fd_max;i++)
	{
		if (
			(monitor -> check[i] == TRUE)
			)
		{
			FD_CLR(i,&monitor -> master_readfds);
			FD_CLR(i,&monitor -> master_exceptfds);
			FD_CLR(i,&monitor -> master_writefds);
			close(i);
		}
	}
}

void resetMonitor(Monitor *monitor, int mainPlayer)
{
	int i = 0;
	for (i = 1; i <= monitor -> fd_max;i++)
	{
		if (
			(i != mainPlayer) &&
			(monitor -> check[i] == TRUE)
			)
		{
			FD_CLR(i,&monitor -> master_readfds);
			FD_CLR(i,&monitor -> master_exceptfds);
			FD_CLR(i,&monitor -> master_writefds);
			close(i);
		}
	}
}
