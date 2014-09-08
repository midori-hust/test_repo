#include "linklist.h"


// -------------------------------------------------------------------------
node *newNode(elementType data) {
  node *new;
  new = (node*) malloc(sizeof(node));
  new->element = data;
  new->next = NULL;
  return new;
}

// -------------------------------------------------------------------------
void insertTop(elementType data) {
  node *new_item;

  new_item = newNode(data);
  if(root == NULL)
    root = cur = new_item;
  else {
    new_item->next = root;
    root = new_item;
  }
}

// -------------------------------------------------------------------------
void insert(elementType data) {
  node *new_item;

  new_item = newNode(data);
  if(root == NULL)
    root = cur = new_item;
  else {
    new_item->next = cur->next;
    cur->next = new_item;
    cur = new_item;
  }
}

// -------------------------------------------------------------------------
void displayList() {
  node *counter;

  if(root == NULL) {
    printf("This list have no element.\n");
    return;
  }
  else {
    printf("The members of this list:\n");
    for(counter = root; counter != NULL; counter = counter->next) {
      printf("%d\n", counter->element);
    }
  }
}

// -------------------------------------------------------------------------
void deleteNode(elementType data) {
  node *temp;
  node *counter;

  if(root == NULL)
    printf("This list have no elements.\n");
  else {
    if(root->element == data) {
      temp = root;
      root = root->next;
      free(temp);
      if(root != NULL)
	deleteNode(data);
    }
    for(counter = root; counter!= NULL; counter = counter->next) {
      if(counter->next == NULL) return;
      if(counter->next->element == data) {
	temp = counter->next;
	counter->next = temp->next;
	free(temp);
      }
    }
  }
}

// -------------------------------------------------------------------------
node *searchNode(elementType data) {
  node *counter;

  if(root == NULL)
    printf("This list have no elements.\n");
  else {
    for(counter = root; counter != NULL; counter = counter->next) {
      if(counter->element == data) {
	printf("Found!\n");
	return counter;
      }
    }
  }
  printf("No found!\n");
  return NULL;
}

// -------------------------------------------------------------------------
void freeList() {
  if(root == NULL) return;

  node *temp;
  temp = root;

  while(temp != NULL) {
    root = root->next;
    free(temp);
    temp = root;
  }
}

// -------------------------------------------------------------------------
void sortList() {
  node* counter1;
  node* counter2;
  elementType temp;

  for(counter2 = root; counter2->next != NULL; counter2 = counter2->next) {
    for(counter1 = counter2->next; counter1 != NULL; counter1 = counter1->next)
      if(counter2->element > counter1->element) {
	temp = counter1->element;
	counter1->element = counter2->element;
	counter2->element = temp;
      }
  }
}
