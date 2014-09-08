#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "my_input_lib.h"
#include "jrb.h"
#include "jval.h"
#include "dllist.h"

typedef JRB Graph;

Graph createGraph();
void addEdge(Graph graph, Jval v1, Jval v2, int (*compare)(Jval, Jval));
int isAdjacent(Graph graph, Jval v1, Jval v2, int (*compare)(Jval, Jval));
int getAdjacentVertices(Graph graph, Jval vertex, Jval *output, int (*compare)(Jval, Jval)); // Return the number of connected vertices
void freeGraph(Graph graph);

/* Private */
void setEdge(Graph graph, Jval v1, Jval v2, int (*compare)(Jval, Jval));


#endif