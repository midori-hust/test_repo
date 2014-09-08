#ifndef _LLIST_H_
#define _LLIST_H_

typedef struct Llist
{
  ElmType key;
  struct Llist *next;
}Llist;

//Functions in this library: 

Llist *newLlist(Llist **root);
Llist *makeNode(ElmType key);
void addLast(Llist **root,ElmType key);
void delNode(Llist **root,int n);
void addBefore(Llist **root,int n,ElmType key);
void addAfter(Llist **root,int n,ElmType key);
Llist *split(Llist *root1,int n);
Llist *divide(Llist *root1,int n1,int n2, int n);
void reverse(Llist **root);
void LlistFree(Llist *root);
void saveDat(Llist *root, FILE *f);

// Code of these functions:

//=========================

Llist *newLlist(Llist **root)
{
  return (*root) = NULL;
}

//=========================

Llist *makeNode(ElmType key)
{
  Llist *newNode;

  newNode=(Llist*)malloc(sizeof(Llist));
  newNode->key=key;
  newNode->next=NULL;

  return newNode;
}

//=========================

void addLast(Llist **root,ElmType key)
{
  Llist *newNode,*cur;

  newNode = makeNode(key);

  if(*root==NULL) 
   {
     *root = newNode;
     cur = *root;
   }
  else
    {
      cur->next = newNode;
      cur = newNode;
    }
}

//=============================

void delNode(Llist **root,int n)
{
  Llist *cur = *root,*delnode = NULL;
  int i;

  if(root == NULL)
    {
      printf("List is empty!\n");
      return;
    }

  if(n == 1) 
    {
      *root=(*root)->next;
      free(cur);
      return;
    }

  for(i = 1; i < n-1; i++)
    cur = cur->next;
  
  delnode = cur->next;
  cur->next = delnode->next;
  free(delnode);
}

//===========================================

void addBefore(Llist **root,int n,ElmType key)
{
  Llist *cur = *root,*prev,*new;
  int i;

  new = makeNode(key);

  if(*root == NULL)
    {
      *root = new;
      return;
    }
  
  if(n == 1)
    {
      new->next = *root;
      *root = new;
      return;
    }

  for(i = 1; i < n; i++)
    {
      prev = cur;
      cur =cur->next;
    }

  new->next = cur;
  prev->next = new;
}

//===============================

void addAfter(Llist **root,int n,ElmType key)
{
  Llist *cur,*new;
  int i;

  new = makeNode(key);

  if(*root == NULL)
    {
      *root = new;
      return;
    }
  
  if(n == 1)
    {
      new->next = (*root)->next;
      (*root)->next = new;
      return;
    }

  cur = *root;
  for(i = 1; i < n; i++)
      cur = cur->next;

  new->next = cur->next;
  cur->next = new;
}

//===============================

Llist *split(Llist *root1,int n)
{
  Llist *root2,*cur = root1;
  int i;

  for(i = 1; i < (n-1); i++)
    cur = cur->next;
  root2 = cur->next;
  cur->next = NULL;
  
  return root2;
}

//==============================

Llist *divide(Llist *root1,int n1,int n2, int n)
{
  Llist *root2,*cur1 = root1,*cur2;
  int i,j;

  if(n2 < (n-n1))
    {
      for(i = 1;i < (n1-1); i++)
	cur1 = cur1->next;
      root2 = cur1->next;
 
      cur2 = root2;
      for(j = 1; j < n2; j++)
	cur2 = cur2->next;
      cur1->next = cur2->next;
      cur2->next = NULL;
    }
  else root2 = split(root1,n1); 

  return root2; 
}

//=================================

void reverse(Llist **root)
{
  Llist *x, *y, *z;
  x = NULL;
  y = *root;
  while (y != NULL)
    {
      z = y->next;
      y->next = x;
      x = y;
      y = z;
    }
  *root = x;
}

//================================

void LlistFree(Llist *root)
{
  Llist *cur;

  while(root != NULL)
    {
      cur = root;
      root = root->next;
      free(cur);					
    }
}	     

//===========================

void saveDat(Llist *root, FILE *f)
{
  Llist *cur;
  for(cur = root; cur != NULL; cur = cur->next)
    fwrite(&cur->key,sizeof(ElmType),1,f);  
}

//===========================

#endif
