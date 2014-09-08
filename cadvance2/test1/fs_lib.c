#include "fs_lib.h"

int findAll(Graph graph, int start, int stop, IntArray *result) {
	int length = 0;
	Dllist stack;
	IntArray path;

	int counter = 0;

	return DFS_findAll(graph, start, stop, path, length, result, &counter);
}

int DFS_findAll(Graph graph, int start, int stop, IntArray path, int length, IntArray *result, int *theCounter) {
	int counter = 0;

	path.content[length++] = start;

	if(start == stop) {
		return solutionDFS(graph, path, length, result, theCounter);
	}

	int n, output[100], i;

	n = outdegree(graph, start, output);

	for(i = 0; i < n; i++) {
		if(!hasElement(path, length, output[i])) {
			counter += DFS_findAll(graph, output[i], stop, path, length, result, theCounter);
		}
	}

	return counter;
}

int solutionDFS(Graph graph, IntArray path, int length, IntArray *result, int *theCounter) {
	int i;

	printf("Solution:\n");
	for(i = 0; i < length; i++) {
		printf("Visit %d\n", path.content[i]);
		result[*theCounter].content[i] = path.content[i];
	}
	result[*theCounter].content[i] = -1;
	printf("Debug: counter = %d\n", *theCounter);

	(*theCounter)++;

	return 1;
}

int hasElement(IntArray path, int length, int element) {
	int i;

	for(i = 0; i < length; i++) {
		if(path.content[i] == element)
			return 1;
	}

	return 0;
}