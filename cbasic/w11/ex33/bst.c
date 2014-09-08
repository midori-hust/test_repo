#include "bst.h"


Node* Search(char *key, Node* Root)
{
  if(Root == NULL) return NULL;
  else
    if(strcmp(Root->key, key) == 0)
      return Root;
    else
      if(strcmp(Root->key, key) < 0)
	return Search(key, Root->right);
      else
	{
	  return Search(key, Root->left);
	}
}

void InsertNode(char *key, Node** Root)
{
  if(*Root == NULL)
    {
      *Root = (Node*)malloc(sizeof(Node));      
      strcpy((*Root)->key, key);
      (*Root)->left = NULL;
      (*Root)->right = NULL;
      (*Root)->frequency = 1;
    }
  else
    if(strcmp(key, (*Root)->key) < 0)
      InsertNode(key, &(*Root)->left);
    else if(strcmp(key, (*Root)->key) > 0)
      InsertNode(key, &(*Root)->right);
    else (*Root)->frequency++;
}

void display(Node *Root)
{
  if(Root == NULL) return;
  display(Root->left);
  printf("%s:\t%d\n", Root->key, Root->frequency);
  display(Root->right);
}

void freeTree(Node *Root)
{
  if(Root == NULL) return;
  freeTree(Root->left);
  freeTree(Root->right);
  free(Root);
}
