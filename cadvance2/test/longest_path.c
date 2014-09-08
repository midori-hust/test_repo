#include "longest_path.h"

int longestPath(Graph graph, int source, int target, int *path, int *length) {
	int n, i;
	int path[100];

	n = topologicalSort(graph, path);

	for(i = 0; i < n; i++) {
		
	}
}