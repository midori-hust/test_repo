#ifndef __DIRECTED_GRAPH_H__
#define __DIRECTED_GRAPH_H__

#include "my_input_lib.h"
#include "jrb.h"
#include "jval.h"
#include "dllist.h"

typedef struct _Graph {
	JRB edges;
	JRB vertices;
	int MAX_VERTICES;
	int MAX_EDGES;
} *Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char* getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2, int mass);
int hasEdge(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int *output);
int outdegree(Graph graph, int v, int *output);
int getComponents(Graph graph);
void dropGraph(Graph graph);
int getKeyByVal(Graph graph, char* name);
void DAG(Graph graph);
int checkCycle(Graph graph);

/* Private */
void setEdge(Graph graph, int v1, int v2, int mass);
int isInDegree(Graph graph, int v1, int v2);
int isOutDegree(Graph graph, int v1, int v2);
int BFStraverse(Graph graph, int start, JRB visited);
int topologicalSort(Graph graph, int *result);

#endif