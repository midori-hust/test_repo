#ifndef __SHORTEST_PATH_H__
#define __SHORTEST_PATH_H__

#include "directed_graph.h"

int shortestPath(Graph graph, int source, int target, int *path, int *length);
int minDistance(JRB queue);
void cloudy(Graph graph, JRB distanceList, JRB prevList, int u);
void modifyQueue(JRB queue, JRB distanceList);
void init(Graph graph, int source, JRB previousList, JRB distanceList, JRB queue);
int solutionForSortestPath(int source, int target, int *path, int *length, JRB distanceList, JRB previousList);
int reverseArray(int *array, int amount);
void swapInt(int *a, int *b);

#endif