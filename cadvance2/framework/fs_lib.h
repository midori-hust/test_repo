#ifndef __FS_LIB_H__
#define __FS_LIB_H__

#include "directed_graph.h"

typedef struct _IntArray {
	int content[100];
} IntArray;

int findAll(Graph graph, int start, int stop, IntArray *result);
int DFS_findAll(Graph graph, int start, int stop, IntArray path, int length, IntArray *result, int *theCounter);

int solutionDFS(Graph graph, IntArray path, int length, IntArray *result, int *theCounter);
int hasElement(IntArray path, int length, int element);

#endif