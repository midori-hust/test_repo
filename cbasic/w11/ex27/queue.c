#include "queue.h"

void MakeNull_Queue(Queue *Q)
{
  Q->Front = -1;
  Q->Rear = -1;
}

int Empty_Queue(Queue Q)
{
  return Q.Front == -1;
}

int Full_Queue(Queue Q)
{
  return Q.Rear == MAXLENGTH - 1;
}

void EnQueue(char a, Queue *Q)
{
  if(!Full_Queue(*Q))
    {
      if(Empty_Queue(*Q)) 
	Q->Front = 0;
      Q->Rear = Q->Rear + 1;
      Q->elements[Q->Rear] = a;
    }
  else printf("Queue is full!\n");
}

void DeQueue(char *a, Queue *Q)
{
  if(!Empty_Queue(*Q))
    {
      *a = Q->elements[Q->Front];
      Q->Front = Q->Front+1;
      if(Q->Front > Q->Rear)
	{
	  MakeNull_Queue(Q);
	}
    }
  else 
    printf("Queue is empty!\n");
}
