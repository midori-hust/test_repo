#include "bst.h"

Node* Search(char *key, Node* Root) {
  if(Root == NULL) return NULL;
  else
    if(strcmp(Root->content.name, key) == 0)
      return Root;
    else
      if(strcmp(Root->content.name, key) < 0)
	      return Search(key, Root->right);
      else 
    	  return Search(key, Root->left);
}

void InsertNode(Key *key, Node** Root) {
  if(*Root == NULL) {

    printf("Node #%d: The new node at address: ", ++counter);
    *Root = (Node*)malloc(sizeof(Node));
    strcpy((*Root)->content.name, key->name);
    (*Root)->left = NULL;
    (*Root)->right = NULL;
    (*Root)->content.point = key->point;
    printf("%p\n", *Root);
  }
  else
    if(strcmp(key->name, (*Root)->content.name) < 0)
      InsertNode(key, &(*Root)->left);
    else if(strcmp(key->name, (*Root)->content.name) > 0)
      InsertNode(key, &(*Root)->right);
    else {
      (*Root)->content.point += key->point;
    }
}

void display(Node *Root) {
  if(Root == NULL) return;
  display(Root->left);
  printf("%s:\t%d\n", Root->content.name, Root->content.point);
  display(Root->right);
}

Key DeleteMin(Node **Root) {
  Key k;
  if((*Root)->left == NULL) {
    k = (*Root)->content;
    (*Root) = (*Root)->right;
    return k;
  }
  else
    return DeleteMin(&(*Root)->left);
}

void DeleteNode(Key *key, Node **Root) {
  if(Root != NULL) {
    if(strcmp(key->name, (*Root)->content.name) < 0) {
      DeleteNode(key, &(*Root)->left);
    } else if (strcmp(key->name, (*Root)->content.name) > 0) {
      DeleteNode(key, &(*Root)->right);
    } else if (((*Root)->left == NULL) && ((*Root)->right == NULL)) {
      (*Root) = NULL;
    } else if ((*Root)->left == NULL) {
      (*Root) = (*Root)->right;
    } else if ((*Root)->right == NULL) {
      (*Root) = (*Root)->left;
    } else {
      (*Root)->content = DeleteMin(&(*Root)->right);
    }
  }
}

void freeTree(Node *Root) {
  if(Root == NULL) return;
  freeTree(Root->left);
  freeTree(Root->right);
  free(Root);
}

int menu() {
    int option;

    printf("\n\t\tMENU\n");
    printf("\t1. Make tree \n");
    printf("\t2. Result\n");
    printf("\t3. Search\n");
    printf("\t4. Relegated club\n");
    printf("\t5. Make file\n");
    printf("\t6. Exit program\n");
    printf("\nWhich option would you like to choose?\n");

    do {
      option = getInt();
      if (option < 0 || option > 6) {
        printf("Invalid option! Please choose again!\n");
      }
    } while (option < 0 || option > 6);

    return option;
}

int getInt() {
  int result;

  while(scanf("%d",&result) != 1) {
    printf("This is not an integer number. Please retype the input: ");
    while(getchar() != '\n');
  }

  return result;
}

void genResultFile(FILE *f, Node *Root) {

  if(Root == NULL) return;
  genResultFile(f, Root->left);
  fprintf(f, "%s\t%d\n", Root->content.name, Root->content.point);
  genResultFile(f, Root->right);
}

Node* searchForRelegated(int point, Node* Root) {
  Node *temp;

  if(Root == NULL) return NULL;
  if(Root->content.point == point)
  	return Root;
  
  temp = searchForRelegated(point, Root->left);
  if(temp != NULL) {
  	return temp;
  }
  
  temp = searchForRelegated(point, Root->right);
  if(temp != NULL) {
  	return temp;
  }

  return NULL;
}