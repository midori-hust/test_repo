#include "extension_lib.h"

int solve() {
	Graph g;
	int path[SIZE], length, n, i;

	int source, target;

	source = 1;
	target = 3;

	if((g = createGraph()) == NULL) {
		return 1;
	}

	addVertex(g, 1, "Blah");
	addVertex(g, 2, "Blah blah");
	addVertex(g, 3, "Blah blah");
	addVertex(g, 4, "Blah blah");
	addVertex(g, 5, "Blah blah");
	addVertex(g, 6, "Blah blah");
	// addVertex(g, 7, "Blah blah");

	addEdge(g, 1, 2, 1);
	addEdge(g, 1, 4, 1);
	addEdge(g, 2, 3, 1);
	addEdge(g, 4, 6, 1);
	addEdge(g, 5, 6, 1);
	addEdge(g, 6, 3, 1);
	// addEdge(g, 3, 4, 1);

	if(checkCycle(g)) {
		printf("The graph has a cycle\n");
	} else {
		printf("The graph has no cycle\n");
	}

	int weight;
	weight = shortestPath(g, source, target, path, &length);

	if(weight == INFINITIVE_VALUE)
		printf("No path between %d and %d\n", source, target);
	else {
		printf("Path between %d and %d\n", source, target);
		for(i = 0; i < length; i++)
			printf("%4d\n", path[i]);
		printf("Total weight: %d\n", weight);
	}

	dropGraph(g);

	return 0;
}