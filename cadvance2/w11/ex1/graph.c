#include "graph.h"

Graph* createGraph(int sizemax) {
	Graph* graph;
	int i, j;

	if((graph = myMalloc(sizeof(Graph), 1)) == NULL) {
		return NULL;
	}

	if((graph->matrix = myMalloc(sizeof(int), sizemax * sizemax)) == NULL) {
		return NULL;
	}

	graph->sizemax = sizemax;

	for(i = 0; i < sizemax; i++) {
		for(j = 0; j < sizemax; j++) {
			resetElementAt(graph, i, j);
		}
	}

	return graph;
}

void addEdge(Graph *graph, int v1, int v2) {
	setElementAt(graph, v1, v2);
	setElementAt(graph, v2, v1);
}

int isAdjacent(Graph *graph, int v1, int v2) {
	return getElementAt(graph, v1, v2);
}

int getAdjacentVertices(Graph *graph, int vertex, int *output) {
	int i, j = 0;
	int counter = 0;

	for(i = 0; i < graph->sizemax; i++) {
		if(getElementAt(graph, vertex, i)) {
			output[counter++] = i;
		}
	}
	return counter;
}

void freeGraph(Graph *graph) {
	free(graph->matrix);
	free(graph);
}

/* Private */
void setElementAt(Graph *graph, int v1, int v2) {
	graph->matrix[v1 * graph->sizemax + v2] = 1;
}

void resetElementAt(Graph *graph, int v1, int v2) {
	graph->matrix[v1 * graph->sizemax + v2] = 0;
}

int getElementAt(Graph *graph, int v1, int v2) {
	return graph->matrix[v1 * graph->sizemax + v2];
}