#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100


struct queue_
{
  char elements[MAXLENGTH];
  int Front, Rear;
};

typedef struct queue_ Queue;


void MakeNull_Queue(Queue *Q);
int Empty_Queue(Queue Q);
int Full_Queue(Queue Q);
void EnQueue(char a, Queue *Q);
void DeQueue(char *a, Queue *Q);

#endif
