#ifndef __FS_LIB_H__
#define __FS_LIB_H__

#include "directed_graph.h"

enum {
	BFS_SEARCH = 0,
	BFS_TRAVERSE = 1,
	DFS_SEARCH = 3,
	DFS_TRAVERSE = 4,
	U_SHORTEST_PATH = 5,
};

int searchController(Graph graph, int start, int stop, int option);

int breathFirstSearch(Graph graph, int start, int stop, Dllist close);
int traverseBFS(Graph graph, int start, Dllist close);
int deepFirstSearch(Graph graph, int start, int stop, Dllist close);
int traverseDFS(Graph graph, int start, Dllist close);

int UShortestPath(Graph graph, int start, int stop, Dllist close);
int searchSolution(Graph graph, int start, int stop, Dllist stackVisit, Dllist close);

#endif