#include "linklist.h"


// -------------------------------------------------------------------------
node *newNode(int id, char *name, float grade) {
  node *new;
  new = (node*) malloc(sizeof(node));
  new->element.id = id;
  new->element.grade = grade;
  strcpy(new->element.name, name);
  new->next = NULL;
  return new;
}

// -------------------------------------------------------------------------
void insertTop(int id, char *name, float grade) {
  node *new_item;

  new_item = newNode(id, name, grade);
  if(root == NULL)
    root = cur = new_item;
  else {
    new_item->next = root;
    root = new_item;
  }
}

// -------------------------------------------------------------------------
void insert(int id, char *name, float grade) {
  node *new_item;

  new_item = newNode(id, name, grade);
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
  int n = 0;

  if(root == NULL) {
    printf("This list have no element.\n");
    return;
  }
  else {
    printf("The members of this list:\n");
    for(counter = root; counter != NULL; counter = counter->next) {
      printf("Student ID: %d\nStudent name: %s\nStudent grade: %f\n\n", counter->element.id, counter->element.name, counter->element.grade);
    }
  }
}

// -------------------------------------------------------------------------
void deleteNode(int id) {
  node *temp;
  node *counter;

  if(root == NULL)
    printf("This list have no elements.\n");
  else {
    if(root->element.id == id) {
      temp = root;
      root = root->next;
      free(temp);
      if(root != NULL)
	deleteNode(id);
    }
    for(counter = root; counter!= NULL; counter = counter->next) {
      if(counter->next == NULL) return;
      if(counter->next->element.id == id) {
	temp = counter->next;
	counter->next = temp->next;
	free(temp);
      }
    }
  }
}

// -------------------------------------------------------------------------
node *searchNode(int id) {
  node *counter;

  if(root == NULL)
    printf("This list have no elements.\n");
  else {
    for(counter = root; counter != NULL; counter = counter->next) {
      if(counter->element.id == id) {
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
int menu() {
  int option;
  printf("\n\t\tMENU\n");
  printf("\t1. Enter information of student\n");
  printf("\t2. Read and sort information of student\n");
  printf("\t3. Edit list and information of student\n");
  printf("\t4. Display the list of students\n");
  printf("\t5. Exit program\n");
  printf("\nWhich option do you like to choose?\n");

  while(scanf("%d", &option) != 1) {
    printf("Wrong input! Please retry.\n");
    while(getchar() != '\n');
  }
  while(getchar() != '\n');

  return option;
}

void getStudentInfo(FILE *f) {
  int id;
  float grade;
  char name[MAXLENGTH];
  elementType buff;

  if(f == NULL) return;

  while(1) {
    printf("Enter the information of student (student ID=0 to end this action):\n");
    printf("Student ID: ");
    while(scanf("%d", &id) != 1) {
      printf("Wrong input! Please retry\n");
      while(getchar() != '\n');
    }
    while(getchar() != '\n');
    if(id == 0) break;
    if(id <0) {
      printf("ID shound not be less than zero\n");
      continue;
    }
    printf("Student name: ");
    gets(name);
    while(1) {
      printf("Student grade: ");
      while(scanf("%f", &grade) != 1) {
	printf("Wrong input! Please retry\n");
	while(getchar() != '\n');
      }
      while(getchar() != '\n');
      if(grade<=10 && grade>=0) break;
      printf("Wrong input! Please retry.\n");
    }
    buff.id = id;
    strcpy(buff.name, name);
    buff.grade = grade;
    fwrite(&buff, sizeof(elementType), 1, f);
  }
}

void sortList() {
  node *iMin;
  node *i, *j;

  for(j = root; j->next != NULL; j = j->next) {
    iMin = j;
    for(i = j->next; i != NULL; i = i->next) {
      if(i->element.grade < iMin->element.grade)
	iMin = i;
    }
    if(iMin->element.id != j->element.id || strcmp(iMin->element.name, j->element.name) != 0 || iMin->element.grade != j->element.grade)
    swap(&iMin->element, &j->element);
  }
}

void editGrade(int id, float newGrade) {
  node *temp;

  temp = searchNode(id);
  temp->element.grade = newGrade;
}

int menu2() {
  int option;
  printf("\n\t\tEDIT MENU\n");
  printf("\t1. Insert new student to list\n");
  printf("\t2. Delete a student in list\n");
  printf("\t3. Edit student grade\n");
  printf("\t4. Display the list of students who have the grade's greater than 7\n");
  printf("\t5. Return\n");
  printf("\nWhich option do you like to choose?\n");

  while(scanf("%d", &option) != 1) {
    printf("Wrong input! Please retry.\n");
    while(getchar() != '\n');
  }
  while(getchar() != '\n');

  return option;
}

void swap(elementType *a, elementType *b) {
  elementType temp = *a;
  *a = *b;
  *b = temp;
}
