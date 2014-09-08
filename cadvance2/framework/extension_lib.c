#include "extension_lib.h"

int solve(FILE *f) {
	Graph g;
	int path[SIZE], length, n, i;

	int source, target;

	source = 1;
	target = 3;

	if((g = createGraph()) == NULL) {
		return 1;
	}

	readData(f, g);

	dropGraph(g);
	return 0;
}

void readData(FILE *f, Graph graph) {
	rewind(f);
}