#include "extension_lib.h"

int solve(FILE *f) {
	Graph g;
	int path[SIZE], length, n, i;
	int choice;

	int source, target;

	source = 1;
	target = 3;

	if((g = createGraph()) == NULL) {
		return 1;
	}

  	while(1) {
      choice = menu();

      switch(choice) {
        case 1:
        printf("You choose option %d\n", choice);
		option1(f, g);
        continue;
        case 2:
        printf("You choose option %d\n", choice);
        option2(g);
        continue;
        case 3:
        printf("You choose option %d\n", choice);
        option3(g);
        continue;
        case 4:
        printf("You choose option %d\n", choice);
        option4(g);
        continue;
        case 5:
        printf("You choose option %d\n", choice);
        option5(g);
        continue;
        case 6:
        printf("You choose option %d\n", choice);
        option6(g);
        continue;
        case 7:
        printf("You choose option %d\n", choice);
        option7(g);
        continue;
        case 8:
        printf("You choose option %d\n", choice);
        printf("Bye bye\n");
        break;
        default:
        printf("It is not an option\n");
        continue;
      }
      break;
    }

	dropGraph(g);
	return 0;
}

void readData(FILE *f, Graph graph) {
	String *listOutput;
	String *vertex;
	char temp[SIZE];
	char *vertexName;
	int n, i, j = 0, sizeOfArray, counter = 1;

	int array[SIZE];


	rewind(f);
	fgets(temp, SIZE, f);

	if((listOutput = myMalloc(sizeof(String), SIZE)) == NULL) {
		return;
	}

	sizeOfArray = split(temp, ' ', listOutput);

	rewind(f);

	j = 0;
	while(fgets(temp, SIZE, f) != NULL) {
		if((listOutput = myMalloc(sizeof(String), SIZE)) == NULL) {
			return;
		}

		if(temp[strlen(temp) - 1] == '\n') {
			temp[strlen(temp) - 1] = '\0';
		}
		
		n = split(temp, ' ', listOutput);

		for(i = 0; i < n; i++) {
			if(atoi(listOutput[i].content) == 0) {
				if((vertexName = myMalloc(sizeof(char), SIZE)) == NULL) {
					return;
				}
				sprintf(vertexName, "%d%d", j, i);
				addVertex(graph, counter++, vertexName);
				
			}
			array[j * sizeOfArray + i] = atoi(listOutput[i].content);
		}
		j++;
	}

	rewind(f);

	// printArray(array, sizeOfArray);

	loadToGraph(graph, array, sizeOfArray);

}

void loadToGraph(Graph graph, int *array, int amount) {
	int i, j;

	for(i = 0; i < amount; i++) {
		for(j = 0; j < amount; j++) {
			setUp(graph, array, amount, i, j);
			setDown(graph, array, amount, i, j);
			setLeft(graph, array, amount, i, j);
			setRight(graph, array, amount, i, j);
		}
	}
}

void setUp(Graph graph, int *array, int amount, int iCurrent, int jCurrent) {
	if(iCurrent == 0) {
		return;
	}

	if(getKeyAtPosition(graph, iCurrent - 1, jCurrent) == -1) {
		return;
	}

	addEdge(graph, getKeyAtPosition(graph, iCurrent, jCurrent), getKeyAtPosition(graph, iCurrent - 1, jCurrent), 1);
}

void setDown(Graph graph, int *array, int amount, int iCurrent, int jCurrent) {
	if(iCurrent == 4) {
		return;
	}

	if(getKeyAtPosition(graph, iCurrent + 1, jCurrent) == -1) {
		return;
	}

	addEdge(graph, getKeyAtPosition(graph, iCurrent, jCurrent), getKeyAtPosition(graph, iCurrent + 1, jCurrent), 1);	
}

void setLeft(Graph graph, int *array, int amount, int iCurrent, int jCurrent) {
	if(jCurrent == 0) {
		return;
	}

	if(getKeyAtPosition(graph, iCurrent, jCurrent - 1) == -1) {
		return;
	}

	addEdge(graph, getKeyAtPosition(graph, iCurrent, jCurrent), getKeyAtPosition(graph, iCurrent, jCurrent - 1), 1);
}

void setRight(Graph graph, int *array, int amount, int iCurrent, int jCurrent) {
	if(jCurrent == 4) {
		return;
	}

	if(getKeyAtPosition(graph, iCurrent, jCurrent + 1) == -1) {
		return;
	}

	addEdge(graph, getKeyAtPosition(graph, iCurrent, jCurrent), getKeyAtPosition(graph, iCurrent, jCurrent + 1), 1);
}

void printArray(int *array, int amount) {
	int i, j;

	for(i = 0; i < amount; i++) {
		for(j = 0; j < amount; j++) {
			printf("%d ", array[i * amount + j]);
		}
		printf("\n");
	}
}

int getKeyAtPosition(Graph graph, int i, int j) {
	char temp[100];

	sprintf(temp, "%d%d", i, j);
	return getKeyByVal(graph, temp);
}

void option1(FILE *f, Graph graph) {
	JRB node;
	int n, i, j;

	readData(f, graph);

	printf("The matrix:\n");
	for(i = 0; i < 5; i++) {
		for(j = 0; j < 5; j++) {

			n = getKeyAtPosition(graph, i, j);
			if(n != -1) {
				printf("0 ");
			} else {
				printf("1 ");
			}
		}
		printf("\n");
	}
}

void option2(Graph graph) {
	printf("Number of edges: %d\n", graph->MAX_EDGES / 2);
	printf("Number of verticles: %d\n", graph->MAX_VERTICES);
}

void option3(Graph graph) {
	char temp[SIZE];
	int output[SIZE];
	int n, i;

	printf("Please enter the node which you want to check:\n");
	fgets(temp, SIZE, stdin);
	temp[strlen(temp) - 1] = '\0';

	n = indegree(graph, getKeyByVal(graph, temp), output);
	if(n > 0) {
		printf("The list of nodes which is adjacent to this node:\n");
		for(i = 0; i < n; i++) {
			printf("%s\n", getVertex(graph, output[i]));
		}
	} else {
		printf("There is no adjacent node\n");
	}
}

void option4(Graph graph) {
	JRB node;
	int n, output[100];

	printf("The list of nodes which have a biggest number of adjacent nodes:\n");
	jrb_traverse(node, graph->edges) {
		if((n = indegree(graph, jval_i(node->key), output)) == 3) {
			printf("Node %s\n", getVertex(graph, jval_i(node->key)));
		}
	}

}

void option5(Graph graph) {
	JRB node;
	int n, output[100];

	printf("The list of island:\n");
	jrb_traverse(node, graph->vertices) {
		if((n = indegree(graph, jval_i(node->key), output)) == 0) {
			printf("Node %s\n", getVertex(graph, jval_i(node->key)));
		}
	}
}

void option6(Graph graph) {
	int n, i;
	int path[SIZE], length;
	char src[SIZE], des[SIZE];

	printf("Please enter the source node:\n");
	fgets(src, SIZE, stdin);
	src[strlen(src) - 1] = '\0';

	printf("Please enter the destinate node:\n");
	fgets(des, SIZE, stdin);
	des[strlen(des) - 1] = '\0';

	n = shortestPath(graph, getKeyByVal(graph, src), getKeyByVal(graph, des), path, &length);
	if(n == INFINITIVE_VALUE) {
		printf("There is no way to get there\n");
		return;
	}

	printf("The shortest path:\n");
	for(i = 1; i < length; i++) {
		// printf("Room %d - Length %d\n", path[i], getEdgeMass(graph, path[i], path[i - 1]));
		printf("Node %d\n", path[i]);
	}
}

void option7(Graph graph) {
	int n, i, j = 0;
	int path[SIZE], length;
	char src[SIZE], des[SIZE];
	IntArray res[SIZE];

	printf("Please enter the source node:\n");
	fgets(src, SIZE, stdin);
	src[strlen(src) - 1] = '\0';

	printf("Please enter the destinate node:\n");
	fgets(des, SIZE, stdin);
	des[strlen(des) - 1] = '\0';

	n = findAll(graph, getKeyByVal(graph, src), getKeyByVal(graph, des), res);

	if(n == 0) {
		printf("No way to get there\n");
		return;
	}

	for(i = 0; i < n; i++) {
		printf("Solution %d\n", i + 1);
		while(res[i].content[j] != -1) {
			printf("Visit %s\n", getVertex(graph, res[i].content[j++]));
		}
		j = 0;
	}
}