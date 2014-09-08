#include "extension_lib.h"

int solve() {
	Graph g;
	int output[SIZE], n, i;

	if((g = createGraph()) == NULL) {
		return 1;
	}

	do {
		initData(g);
		printf("Do you want to continue? Y/N\n");
	} while(getContinueRequest() == 'Y');
	
	findTopoClass(g);

	dropGraph(g);

	return 0;
}

void initData(Graph graph) {
	char *temp1, *temp2;

	if((temp1 = myMalloc(sizeof(char), 100)) == NULL) {
		return;
	}

	if((temp2 = myMalloc(sizeof(char), 100)) == NULL) {
		return;
	}

	printf("Please enter the order of 2 item:\n");
	printf("Which one do you want to take on first?\n");
	fgets(temp1, 100, stdin);
	temp1[strlen(temp1) - 1] = '\0';

	printf("Which one do you want to take on after?\n");
	fgets(temp2, 100, stdin);
	temp2[strlen(temp2) - 1] = '\0';

	if(getKeyByVal(graph, temp1) < 0) {
		addVertex(graph, graph->MAX_VERTICES, temp1);	
	}
	if(getKeyByVal(graph, temp2) < 0) {
		addVertex(graph, graph->MAX_VERTICES, temp2);
	}

	addEdge(graph, getKeyByVal(graph, temp1), getKeyByVal(graph, temp2), 1);

	// addVertex(graph, 1, "Shirt");
	// addVertex(graph, 2, "Slacks");
	// addVertex(graph, 3, "Shoes");
	// addVertex(graph, 4, "Socks");
	// addVertex(graph, 5, "Belt");
	// addVertex(graph, 6, "Undergarments");

	// addEdge(graph, 6, 2, 1);
	// addEdge(graph, 6, 1, 1);
	// addEdge(graph, 2, 5, 1);
	// addEdge(graph, 1, 5, 1);
	// addEdge(graph, 4, 3, 1);
	// addEdge(graph, 5, 4, 1);
}

void findTopoClass(Graph graph) {
	char temp[100];
	int i, n, output[100];

	if(checkCycle(graph)) {
		printf("You can not wear in this order!\n");
		return;
	}

	if((n = topologicalSort(graph, output)) == 0) {
		return;	
	}

	printf("The sequence of actions:\n");
	for(i = 0; i < n; i++) {
		printf("\t%d. %s\n", i + 1, getVertex(graph, output[i]));
	}
}