#include "extension_lib.h"

int solve() {
	int i, n, output[100];

	Graph *g;
	g = createGraph(100);
	addEdge(g, 0, 1);
	addEdge(g, 0, 2);
	addEdge(g, 1, 2);
	addEdge(g, 1, 3);

	if((n = getAdjacentVertices(g, 1, output)) == 0) {
		printf("No adjacent vertices of node %d\n", 1);
	} else {
		printf("Adjacent vertices of node %d\n", 1);
		for(i = 0; i < n; i++) {
			printf("%5d\n", output[i]);
		}
	}

	freeGraph(g);

	return 0;
}