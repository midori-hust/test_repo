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
    printf("\t2. Search information of student\n");
    printf("\t3. Delete information of student\n");
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
