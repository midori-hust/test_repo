#include "extension_lib.h"

int solve(FILE *f) {
	Graph g;

	if((g = createGraph()) == NULL) {
		return 1;
	}

	readData(f, g);
	option1(g);
	do {
		option2(g);
		printf("Do you want to continue? Y/N\n");
	} while(getContinueRequest() != 'N');
	option3(g);
	option4(g);
	option5(g);

	dropGraph(g);
	return 0;
}

void readData(FILE *f, Graph graph) {
	String *listOutput, *listOutput2;
	char temp[100];
	int n, i, n2;
	int counter = 1;
	int firstVertex, secondVertex;

	rewind(f);
	while(fgets(temp, SIZE, f) != NULL) {
		if((listOutput = myMalloc(sizeof(String), 10)) == NULL) {
			return;
		}

		if(temp[strlen(temp) - 1] == '\n') {
			temp[strlen(temp) - 1] = '\0';
		}

		n = split(temp, ' ', listOutput);
		addVertex(graph, counter++, listOutput[0].content);
	}

	rewind(f);

	while(fgets(temp, SIZE, f) != NULL) {
		if((listOutput = myMalloc(sizeof(String), 10)) == NULL) {
			return;
		}

		if(temp[strlen(temp) - 1] == '\n') {
			temp[strlen(temp) - 1] = '\0';
		}

		n = split(temp, ' ', listOutput);
		firstVertex = getKeyByVal(graph, listOutput[0].content);

		for(i = 2; i < n; i++) {
			if((listOutput2 = myMalloc(sizeof(String), 2)) == NULL) {
				return;
			}

			n2 = split(listOutput[i].content, '-', listOutput2);
			secondVertex = getKeyByVal(graph, listOutput2[0].content);
			addEdge(graph, secondVertex, firstVertex, atoi(listOutput2[1].content));
		}
	}

	rewind(f);
}

void option1(Graph graph) {
	printf("1.\n");
	printf("\tNumber of verticles: %d\n", graph->MAX_VERTICES);
	printf("\tNumber of edges: %d\n", graph->MAX_EDGES);
}

void option2(Graph graph) {
	char temp[SIZE];
	int source;
	int output[SIZE], n, i;

	printf("2.\n");
	printf("Please enter the job which you want to find out:\n");
	fgets(temp, SIZE, stdin);
	temp[strlen(temp) - 1] = '\0';
	if((source = getKeyByVal(graph, temp)) < 0) {
		printf("This job does not exist\n");
	} else {
		n = indegree(graph, source, output);
		printf("i.\n");
		printf("Number of jobs must be done just before this job: %d\n", n);
		n = topologicalSort(graph, output);
		printf("ii.\n");
		printf("List of jobs must be done before this job:\n");
		for(i = 0; i < n; i++) {
			if(output[i] == source) {
				break;
			}
			printf("Job %s\n", getVertex(graph, output[i]));
		}
	}
}

void option3(Graph graph) {
	printf("3.\n");
	DAG(graph);
}

void option4(Graph graph) {
	char temp[SIZE];
	int path[SIZE], length, n, i;

	printf("4.\n");
	printf("Please enter the job which you want to check out\n");
	fgets(temp, SIZE, stdin);
	temp[strlen(temp) - 1] = '\0';

	// n = shortestPath(graph, 1, getKeyByVal(graph, temp), path, &length);
	n = longestPath(graph, 1, getKeyByVal(graph, temp), path, &length);

	if(n == INFINITIVE_VALUE) {
		printf("There is no way to finish this job\n");
	} else {
		printf("The shortest way to finish this job\n");
		for(i = 0; i < length; i++) {
			printf("Job %d - %s\n", path[i], getVertex(graph, path[i]));
		}
		printf("Total time: %d\n", n);
	}
}

void option5(Graph graph) {
	printf("5.\n");
	if(checkCycle(graph)) {
		printf("This graph has cycle(s)\n");
	} else {
		printf("This graph has no cycle\n");
	}
}