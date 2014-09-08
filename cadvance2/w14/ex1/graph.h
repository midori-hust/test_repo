#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "my_input_lib.h"
#include "jrb.h"
#include "jval.h"

typedef JRB Graph;

Graph createGraph();
void addEdge(Graph graph, int v1, int v2);
int isAdjacent(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int vertex, int *output); // Return the number of connected vertices
void freeGraph(Graph graph);

/* Private */
void setEdge(Graph graph, int v1, int v2);

#endif