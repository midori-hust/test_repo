#include "extension_lib.h"

int solve(FILE *f) {
	Graph g;
	Graph node, valNode;
	Jval output[SIZE];
	int person[5] = {1, 2, 3, 4, 5};
	int friendList[5] = {0, 0, 0, 0, 0};
	int n, i, counter = 0;

	g = createGraph();

	while(1) {
		createData(g);
		printf("Do you want to continue? Y/N\n");
		if(getContinueRequest() == 'N')
			break;
	}

	jrb_traverse(node, g) {
		printf("Person %d:\n", jval_i(node->key));

		for(i = 0; i < getAdjacentVertices(g, node->key, output, intCompare); i++) {
			printf("%d\n", jval_i(output[i]));
			friendList[jval_i(node->key)]++;
		}
	}
	
	for(i = 0; i < 5; i++) {
		printf("Person %d has %d friend(s)\n", i, friendList[i]);
		if(friendList[i] % 2 == 1) {
			counter++;
		}
	}
	printf("So at a party of 5 people, there are two people that have the same number of friends\n");
	printf("There are %d guest who shake hand an odd number of times\n", counter);
	printf("So at a party, the number of guest who shake hand an odd number of times is even.\n");


	freeGraph(g);

	return 0;
}

void createData(Graph g) {
	int i;
	int firstOne, secondOne;

	printf("Please enter the first one index: \n");
	firstOne = getPerson();
	printf("Please enter the second one index (who the first person is shake hand): \n");
	secondOne = getPerson();

	printf("%d - %d\n", firstOne, secondOne);
	addEdge(g, new_jval_i(firstOne), new_jval_i(secondOne), intCompare);
}

int getPerson() {
	int res;

	do {
		res = getInt();
		if(res < 1 || res > 5) {
			printf("The person index is between 1 and 5. Please enter again!\n");
		}
	} while(res < 1 || res > 5);

	return res;
}

int intCompare(Jval a, Jval b) {
	return jval_i(a) - jval_i(b);
}