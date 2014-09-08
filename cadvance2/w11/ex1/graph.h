#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "my_input_lib.h"

typedef struct _Graph {
	int *matrix;
	int sizemax;
} Graph;

Graph* createGraph(int sizemax);
void addEdge(Graph *graph, int v1, int v2);
int isAdjacent(Graph *graph, int v1, int v2);
int getAdjacentVertices(Graph *graph, int vertex, int *output); // Return the number of connected vertices
void freeGraph(Graph *graph);

/* Private */
void setElementAt(Graph *graph, int v1, int v2);
void resetElementAt(Graph *graph, int v1, int v2);
int getElementAt(Graph *graph, int v1, int v2);

#endif