#ifndef _QUEUE_TREE_H_
#define _QUEUE_TREE_H_

#define MAX 100

typedef struct
{
  Tree Elements[MAX];
  int Front;
  int Rear;
}Queue;

//==========================

void newQueue(Queue *Q)
{
  Q->Front = -1;
  Q->Rear = -1;
}

//==========================

int emptyQueue(Queue Q)
{
  return (Q.Front == -1);
}

//===========================

int fullQueue(Queue Q)
{
  return ((Q.Rear - Q.Front + 1) % MAX == 0);
}

//===========================================

void enQueue(Queue *Q,Tree X)
{
  if(!fullQueue(*Q))
    {
      if(emptyQueue(*Q)) 
	Q->Front = 0;
      Q->Rear = (Q->Rear + 1) % MAX;
      Q->Elements[Q->Rear] = X;
    }
  else printf("Queue is full.\n");
}

//============================================

Tree deQueue(Queue *Q)
{
  Tree x;

  if(!emptyQueue(*Q))
    {
      x = Q->Elements[Q->Front];
      if(Q->Front == Q->Rear)
	newQueue(Q);
      else Q->Front = (Q->Front + 1) % MAX;
      return x;
    }
  else printf("Queue is empty.\n");
}

//=============================================

#endif
