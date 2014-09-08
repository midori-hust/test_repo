#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct _TestStruct {
    int content;
    struct _TestStruct* next;
} TestStruct;

void printLinkList(TestStruct* root);
void insertTop(TestStruct** root, int number);
void deleteLastNode(TestStruct** root);

main() {
    TestStruct* root = NULL;
    int number, i = 0;

    printf("Please enter the list of number!\n");
    while(1){
        printf("Number #%d\n", ++i);
        scanf("%d", &number);
        while(getchar() != '\n');
       	
        if(number == 0) 
        	break;
        insertTop(&root, number);
    }

    printf("Before deleting\n");
    printLinkList(root);
    deleteLastNode(&root);
    printf("After deleting\n");
    printLinkList(root);
}

void printLinkList(TestStruct* root) {
    TestStruct* ptr;

    if(root == NULL) {
    	printf("Empty list\n");
    	return;
    }

    for(ptr = root; ptr != NULL; ptr = ptr->next) {
    	printf("%d\n", ptr->content);
    }
}

void insertTop(TestStruct** root, int number) {
    TestStruct* node;

    if((node = (TestStruct*) malloc(sizeof(TestStruct))) == NULL) {
    	printf("Can not allocate memory!\n");
    	return;
    }

    node->content = number;
    node->next = *root;
    *root = node;
}

void deleteLastNode(TestStruct **root) {
    TestStruct *ptr;

    for(ptr = *root; ptr != NULL; ptr = ptr->next) {
    	if(ptr->next->next == NULL) {
    		ptr->next = ptr->next->next;
    		free(ptr->next);
    	}
    }
}