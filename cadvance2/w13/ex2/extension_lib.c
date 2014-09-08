#include "extension_lib.h"

int solve(FILE *f) {
	Graph g;
	int output[SIZE], n, i;

	if((g = createGraph()) == NULL) {
		return 1;
	}

	readData(f, g);

	findTopoClass(g);

	dropGraph(g);

	return 0;
}

void readData(FILE *f, Graph graph) {
	char temp[100];
	String *listString;
	char *saveContent;
	int n, i, counter = 1, classId, refId;

	if((listString = myMalloc(sizeof(String), 5)) == NULL) {
		return;
	}

	while(fgets(temp, SIZE, f) != NULL) {
		temp[strlen(temp) - 1] = '\0';
		n = split(temp, ' ', listString);

		if(strstr(temp, "CLASS") != NULL) {
			if((saveContent = myMalloc(sizeof(char), 100)) == NULL) {
				return;
			}
			strcpy(saveContent, listString[1].content);

			classId = counter;
			addVertex(graph, counter++, saveContent);

			// printf("Class: %s\n", saveContent);
			continue;
		}

		if(strstr(temp, "PREREQ") != NULL) {
			if((saveContent = myMalloc(sizeof(char), 100)) == NULL) {
				return;
			}
			strcpy(saveContent, listString[1].content);

			refId = counter;
			addVertex(graph, counter++, saveContent);
			addEdge(graph, classId, refId, 1);

			// printf("Prereq: %s\n", saveContent);
			continue;
		}

		if((listString = myMalloc(sizeof(String), 5)) == NULL) {
			return;
		}
	}
}

void findTopoClass(Graph graph) {
	char temp[100];
	int i, n, output[100];

	if((n = topologicalSort(graph, output)) == 0) {
		return;	
	}

	printf("The topological sort:\n");
	for(i = 0; i < n; i++) {
		printf("%s\n", getVertex(graph, output[i]));
	}
}