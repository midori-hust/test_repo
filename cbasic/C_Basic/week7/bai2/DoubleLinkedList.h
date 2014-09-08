#ifndef _DLLIST_H_
#define _DLLIST_H_


typedef struct node
{
  ElmType key;
  struct node *next;
  struct node *prev;
}dllist;

/* Functions in this library */

dllist *newDllist(dllist **head);
dllist *makeNode(ElmType key);
void addTail(dllist **head, ElmType key);
void delNode(dllist **head,int position);
void addAfter(dllist **head,int position,ElmType key);
void addBefore(dllist **head,int position,ElmType key);
dllist *split(dllist *head1,int n);
dllist *divide(dllist *head1,int n1,int n2, int n);
void dllistFree(dllist *head);
void saveDat(dllist *head, FILE *f);

/* Code of these functions */

//==============================

dllist *newDllist(dllist **head)
{
  return (*head) = NULL;
}

//==============================

dllist *makeNode(ElmType key)
{
  dllist *newNode;

  newNode=(dllist*)malloc(sizeof(dllist));
  newNode->key = key;
  newNode->prev = NULL;
  newNode->next = NULL;

  return newNode;
}

//=========================

void addTail(dllist **head, ElmType key)
{
  dllist *newNode,*tail;

  newNode = makeNode(key);

  if(*head == NULL) 
   {
     *head = newNode;
     tail = *head;
   }
  else
    {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
}

//=============================

void delNode(dllist **head,int position)
{
  dllist *cur = *head;
  int i;

  if(*head == NULL)
    {
      printf("List is empty!\n");
      return;
    }

  if(position == 1) 
    {
      *head = (*head)->next;
      if(*head != NULL) 
	(*head)->prev = NULL;
      free(cur);
      return;
    }

  for(i = 1; i< position; i++)
    cur = cur->next;
  
  cur->prev->next = cur->next;
  if (cur->next != NULL) 
    cur->next->prev = cur->prev;
  free(cur);
}

//===========================================

void addAfter(dllist **head,int position,ElmType key)
{
  dllist *cur = *head,*new;
  int i;

  new = makeNode(key);

  if(*head == NULL)
    {
      *head = new;
      return;
    }

  for(i = 1; i < position; i++)
    cur = cur->next;

  new->next = cur->next;
  if(cur->next != NULL)
    cur->next->prev = new;
  cur->next = new;
  new->prev = cur;
}

//===============================

void addBefore(dllist **head,int position,ElmType key)
{
  dllist *cur = *head,*new;
  int i;

  new = makeNode(key);

  if(*head == NULL)
    {
      *head = new;
      return;
    }
  
  if(position == 1)
    {
      new->next = *head;
      (*head)->prev = new;
      *head = new;
      return;
    }

  for(i = 1; i < position; i++)
    cur = cur->next;

  new->next = cur;
  new->prev = cur->prev;
  cur->prev->next = new;
  cur->prev = new;
}

//===============================

dllist *split(dllist *head1,int n)
{
  dllist *head2,*cur = head1;
  int i;

  for(i = 1; i < (n-1); i++)
    cur = cur->next;
  head2 = cur->next;
  head2->prev = NULL;
  cur->next = NULL;
  
  return head2;
}

//==============================

dllist *divide(dllist *head1,int n1,int n2, int n)
{
  dllist *head2,*cur1 = head1,*cur2;
  int i,j;

  if(n2 < (n-n1))
    {
      for(i = 1; i< (n1-1); i++)
	cur1 = cur1->next;
      head2 = cur1->next;
      head2->prev = NULL;
 
      cur2 = head2;
      for(j = 1; j < n2; j++)
	cur2 = cur2->next;

      cur1->next = cur2->next;
      cur2->next->prev = cur1;
      cur2->next = NULL;
    }
  else head2 = split(head1,n1); 

  return head2; 
}
//================================

void dllistFree(dllist *head)
{
  dllist *cur;

  while(head != NULL)
    {
      cur = head;
      head = head->next;
      free(cur);					
    }
}	     

//===================================

void reverse(dllist **head)
{
  dllist *x, *y, *z;
  x = NULL;
  y = *head;
  while (y != NULL)
    {
      z = y->next;
      y->next = x;
      x = y;
      y = z;
    }
  *head = x;
}

//===================================

void saveDat(dllist *head, FILE *f)
{
  dllist *cur;
  for(cur = head; cur != NULL; cur = cur->next)
    fwrite(&cur->key,sizeof(ElmType),1,f);  
}

//===================================

#endif
