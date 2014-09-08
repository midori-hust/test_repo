#include "library.h"
#include "stack.h"

int main() {
	int n;
	Stack *stack;
	Key *item;
	item = (Key*) malloc (sizeof(Key));

	int i, j;
	

	printf("Enter the size of square:\n");
	while((n = getInt()) < 2) {
		printf("Please enter an integer which is greater than 1\n");
	}

	stack = makeStack();
	initialize(stack);

	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			item->square[i][j] = 0;
		}
	}

	push(&stack, item);

	doSomething(&stack, n);




	//printSquareContent(pop(&stack), n);



	// for(i = 0; i < 5; i++) {
	// 	a->a = i;
	// 	push(&stack, a);	
	// }

	// printf("\n");
	// while(!isEmpty(stack)) {
	// 	printf("%d\n", pop(&stack)->a);
	// }

	free(item);
	free(stack);
	return 0;
}