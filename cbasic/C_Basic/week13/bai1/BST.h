#ifndef _BST_H_
#define _BST_H_

typedef struct node
{
  ElmType key;
  struct node *left;
  struct node *right;
}Node;

typedef Node *Tree;

//====================================

Tree newTree()
{
  Tree T;
  T = NULL;
  return T;
}

//====================================

int emptyTree(Tree T)
{
  return T == NULL;
}

//=====================================

Tree leftChild(Tree T)
{
  if(T != NULL) 
    return T->left;
  else return NULL;
}

//=====================================

Tree rightChild(Tree T)
{
  if(T != NULL) 
    return T->right;
  else return NULL;
}

//=====================================

Tree makeTreeNode(ElmType key)
{
  Tree new;
  new = (Node*)malloc(sizeof(Node));
  if(new != NULL)
    {
      new->left = NULL;
      new->right = NULL;
      new->key = key;
    }
  return new;
}

//======================================

int isLeaf(Tree T)
{
  if(T != NULL) 
    return (leftChild(T) == NULL) && (rightChild(T) == NULL);
  else return -1;
}

//======================================

int countNode(Tree T)
{
  if(emptyTree(T)) 
    return 0;
  else 
    return 1 + countNode(leftChild(T)) + countNode(rightChild(T));
}

//=======================================

Tree merge2Tree(Tree l,Tree r,ElmType key)
{
  Tree new;
  new = (Node*)malloc(sizeof(Node));
  if(new != NULL)
    {
      new->key = key;
      new->left = l;
      new->right = r;
    }
  return new;
}

//=======================================

int depth(Tree T)
{
  if (T == NULL) 
    return 0;
  else
    {
      int ld = depth(T->left);
      int rd = depth(T->right);
      return 1+(ld > rd ? ld : rd);
    }
}

//=======================================

int MAX2(int a,int b)
{
  if(a >= b)
    return a;
  else return b;
}

int heightTree(Tree T)
{
  if(emptyTree(T)) 
    return 0;
  else return 1 + MAX2(heightTree(leftChild(T)),heightTree(rightChild(T)));
}

//========================================

int countLeaf(Tree T)
{
  if(emptyTree(T)) 
    return 0;
  else 
    if(isLeaf(T)) return 1;
  else 
    return countLeaf(leftChild(T)) + countLeaf(rightChild(T));
}

//=====================================

int internalNode(Tree T) // Tinh so node ma khong tinh so la'
{
  return countNode(T) - countLeaf(T);
}

//=====================================

int countRightchild(Tree T, int *dem) //Khi goi ban dau thi dem = 0    
{                                   
  if(emptyTree(T)) 
    return 0;
  else
    {
      if(T->right != NULL)
	{
	  (*dem)++;
	  countRightchild(rightChild(T),dem);
	}
      countRightchild(leftChild(T),dem);
    }
  return *dem;
}

//======================================

int countLeftchild(Tree T, int *dem) //khi goi ban dau thi dem = 0 
{                                          
  if(emptyTree(T)) 
    return 0;
  else
    {
      if(T->left != NULL)
	{
	  (*dem)++;
	  countLeftchild(leftChild(T),dem);
	}
      countLeftchild(rightChild(T),dem);
    }
  return *dem;
}

//=====================================

void addLeft(Tree *T, ElmType key) //them 1 node moi vao vi tri trai nhat
{
  Tree newNode = makeTreeNode(key);
  if(newNode == NULL) 
    printf("Out of memory!\n");
  if(*T == NULL)
    *T = newNode;
  else
    {
      Tree Lnode = *T;
      while(Lnode->left != NULL)
	Lnode = Lnode->left;
      Lnode->left = newNode;
    }
}

//=====================================

void addRight(Tree *T, ElmType key) //them 1 node moi vao vi tri phai nhat
{
  Tree newNode = makeTreeNode(key);
  if(newNode == NULL) 
    printf("Out of memory!\n");
  if(*T == NULL)
    *T = newNode;
  else
    {
      Tree Lnode = *T;
      while(Lnode->right != NULL)
	Lnode = Lnode->right;
      Lnode->right = newNode;
    }
}

//======================================

void freeTree(Tree T)
{
  if (T != NULL)
    {
    freeTree(T->left);
    freeTree(T->right);
    free((void*) T);
   }
}


//****************************************************************
/* Cac ham duoi day tuy tung kieu du lieu cua tung bai ma thay doi

void prettyPrint(Tree T,char *s)
{
  char *sh = s + strlen(s);
  if (T != NULL)
    {
      printf("%4d",T->key);
      if (T->left != NULL) 
	if (T->right == NULL)
	  {
	    printf("\n");
	    strcat(s," ");
	  }
	else 
	  {
	    printf("\304");
	    strcat(s,"\263");
	  }
      prettyPrint(T->left,s);
      *sh = '\0';
      if (T->right != NULL) 
	if (T->left != NULL)
	  {
	    printf("\n%s",s);
	    printf("\300");
	  }
	else printf("\304");
      strcat(s," ");
      prettyPrint(T->right,s);
    }
}

//===========================

Tree searchBST(Tree T, ElmType x)
{ 
  if (T == NULL) 
    return NULL; 
  else 
    if (T->key == x) return T; 
    else if (T->key < x)
      return searchBST(T->right, x); 
    else 
      return searchBST(T->left, x); 
}

*/

#endif
