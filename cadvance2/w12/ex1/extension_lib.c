#include "extension_lib.h"

int solve(FILE *f) {
	Graph g;
	int first, second;

	g = createGraph();

	getData(g);

	printf("Enter the first number:\n");
	first = getInt();
	printf("Enter the second number:\n");
	second = getInt();

	printf("Ushortest path length: %d\n", UShortestPath(g, new_jval_i(first), new_jval_i(second), 
		cloneNode, compareFunc, myPrint));

	printf("BFS\n");
	BFS(g, new_jval_i(first), new_jval_i(second), cloneNode, compareFunc, myPrint);
	
	printf("DFS\n");
	DFS(g, new_jval_i(first), new_jval_i(second), cloneNode, compareFunc, myPrint);
	
	printf("BFS Traverse\n");
	BFStraverse(g, new_jval_i(first), cloneNode, compareFunc, myPrint);

	printf("DFS Traverse\n");
	DFStraverse(g, new_jval_i(first), cloneNode, compareFunc, myPrint);

	freeGraph(g);

	return 0;
}

void getData(Graph graph) {
	addEdge(graph, new_jval_i(0), new_jval_i(2), compareFunc);
	addEdge(graph, new_jval_i(2), new_jval_i(4), compareFunc);
	addEdge(graph, new_jval_i(5), new_jval_i(0), compareFunc);
	addEdge(graph, new_jval_i(2), new_jval_i(1), compareFunc);
	addEdge(graph, new_jval_i(3), new_jval_i(2), compareFunc);
	addEdge(graph, new_jval_i(1), new_jval_i(4), compareFunc);
	addEdge(graph, new_jval_i(1), new_jval_i(6), compareFunc);
	addEdge(graph, new_jval_i(5), new_jval_i(2), compareFunc);
	addEdge(graph, new_jval_i(6), new_jval_i(0), compareFunc);
	addEdge(graph, new_jval_i(7), new_jval_i(5), compareFunc);
	addEdge(graph, new_jval_i(8), new_jval_i(3), compareFunc);
	addEdge(graph, new_jval_i(9), new_jval_i(2), compareFunc);
	addEdge(graph, new_jval_i(4), new_jval_i(6), compareFunc);
	addEdge(graph, new_jval_i(0), new_jval_i(1), compareFunc);
}


void myPrint(Jval item) {
	printf("Visited %d\n", jval_i(item));
}

Jval cloneNode(Jval item) {
	return new_jval_i(jval_i(item));
}

int compareFunc(Jval a, Jval b) {
	return jval_i(a) - jval_i(b);
}