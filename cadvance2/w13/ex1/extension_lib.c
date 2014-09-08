#include "extension_lib.h"

int solve() {
	Graph g;
	int output[SIZE], n, i;

	if((g = createGraph()) == NULL) {
		return 1;
	}

	addVertex(g, 1, "1");
	addVertex(g, 2, "2");
	addVertex(g, 3, "3");
	addVertex(g, 4, "4");
	addVertex(g, 5, "5");
	addVertex(g, 6, "6");
	addVertex(g, 7, "7");
	// addVertex(g, 8, "8");
	// addVertex(g, 9, "9");
	// addVertex(g, 10, "10");
	// addVertex(g, 11, "11");
	// addVertex(g, 12, "12");

	addEdge(g, 1, 2, 1);
	// addEdge(g, 2, 3, 1);
	// addEdge(g, 3, 1, 1);
	// addEdge(g, 1, 4, 1);
	// addEdge(g, 5, 1, 1);
	addEdge(g, 7, 1, 1);
	addEdge(g, 2, 5, 1);
	addEdge(g, 6, 3, 1);
	addEdge(g, 3, 2, 1);
	// addEdge(g, 7, 12, 1);
	// addEdge(g, 1, 5, 1);
	addEdge(g, 4, 5, 1);


	if(checkCycle(g)) {
		printf("Cycle here\n");
	} else {
		printf("No cycle here\n");
	}

	// printf("%s\n", getVertex(g, 7));
	// printf("The value of %s is %d\n", "11", getKeyByVal(g, "11"));

	// n = indegree(g, 1, output);

	// printf("In degree list:\n");
	// for(i = 0; i < n; i++) {
	// 	printf("%d\n", output[i]);
	// }

	// n = outdegree(g, 1, output);

	// printf("Out degree list:\n");
	// for(i = 0; i < n; i++) {
	// 	printf("%d\n", output[i]);
	// }

	// printf("The number of components: %d\n", getComponents(g));

	DAG(g);
	
	dropGraph(g);

	return 0;
}