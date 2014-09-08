#ifndef __FS_LIB_H__
#define __FS_LIB_H__

#include "graph.h"

void BFS(Graph graph, Jval start, Jval stop, Jval (*cloneFunc)(Jval), int (*compare)(Jval, Jval), void (*reportFunc)(Jval));
int BFStraverse(Graph graph, Jval start, Jval (*cloneFunc)(Jval), int (*compare)(Jval, Jval), void (*reportFunc)(Jval));
void DFS(Graph graph, Jval start, Jval stop, Jval (*cloneFunc)(Jval), int (*compare)(Jval, Jval), void (*reportFunc)(Jval));
int DFStraverse(Graph graph, Jval start, Jval (*cloneFunc)(Jval), int (*compare)(Jval, Jval), void (*reportFunc)(Jval));
void getDistance(Graph graph, Jval start, Jval stop, Jval (*cloneFunc)(Jval), int (*compare)(Jval, Jval), void (*reportFunc)(Jval));
int findPath(Graph graph, Jval start, Jval stop, Jval (*cloneFunc)(Jval), int (*compare)(Jval, Jval), void (*reportFunc)(Jval));

int UShortestPath(Graph graph, Jval start, Jval stop, Jval (*cloneFunc)(Jval), int (*compare)(Jval, Jval), void (*reportFunc)(Jval));
int solution(Graph graph, Jval start, Jval stop, Dllist stackVisit, Jval (*cloneFunc)(Jval), int (*compare)(Jval, Jval), void (*reportFunc)(Jval));

#endif