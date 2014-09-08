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
	String *listOutput, *listOutput2;
	char temp[100];
	char *roomName;
	int n, i, j = 1;
	int counter = 1;
	int firstVertex, secondVertex;


	rewind(f);

	fgets(temp, SIZE, f);
	if((listOutput = myMalloc(sizeof(String), 10)) == NULL) {
		return;
	}

	if(temp[strlen(temp) - 1] == '\n') {
		temp[strlen(temp) - 1] = '\0';
	}

	n = split(temp, ' ', listOutput);
	for(i = 0; i < n; i++) {
		if((roomName = myMalloc(sizeof(char), SIZE)) == NULL) {
			return;
		}
		sprintf(roomName, "Room %d", i + 1);
		addVertex(graph, i + 1, roomName);
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
		for(i = 0; i < n; i++) {
			if((i + 1) == j)
				continue;
			addEdge(graph, i + 1, j, atoi(listOutput[i].content));
		}
		j++;
	}

	rewind(f);
}

void option1(FILE *f, Graph graph) {
	JRB node;
	int n, i, j;

	readData(f, graph);

	printf("The matrix:\n");
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			n = getEdgeMass(graph, i + 1, j + 1);
			if(n == INFINITIVE_VALUE) {
				printf("%d ", 0);
			} else {
				printf("%d ", n);
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

	printf("Please enter the room which you want to check:\n");
	fgets(temp, SIZE, stdin);
	temp[strlen(temp) - 1] = '\0';

	n = indegree(graph, getKeyByVal(graph, temp), output);
	if(n > 0) {
		printf("The list of rooms which have wire to this room:\n");
		for(i = 0; i < n; i++) {
			printf("%s\n", getVertex(graph, output[i]));
		}
	} else {
		printf("There is no room which has wire to this room\n");
	}
}

void option4(Graph graph) {
	char temp1[SIZE], temp2[SIZE];

	printf("Please enter the 2 rooms which you want to check connectivity\n");
	printf("The first:\n");
	fgets(temp1, SIZE, stdin);
	temp1[strlen(temp1) - 1] = '\0';

	printf("The second:\n");
	fgets(temp2, SIZE, stdin);
	temp2[strlen(temp2) - 1] = '\0';

	if(DFS(graph, getKeyByVal(graph, temp1), getKeyByVal(graph, temp2))) {
		printf("There is a way from room %s to room %s\n", temp1, temp2);
	} else {
		printf("There is no way from room %s to room %s\n", temp1, temp2);
	}
}

void option5(Graph graph) {
	int n;

	n = getComponents(graph);

	if(n == 1) {
		printf("This graph is connected\n");
	} else {
		printf("There is %d component in this graph\n", n);
	}
}

void option6(Graph graph) {
	int n, i, j = 0;

	IntArray *result;

	if((result = myMalloc(sizeof(IntArray), SIZE)) == NULL) {
		return;
	}

	n = findAll(graph, 1, 4, result);

	for(i = 0; i < n; i++) {
		printf("Path %d\n", i + 1);
		while(result[i].content[j] != -1) {
			printf("\tVisit %d\n", result[i].content[j++]);
		}
		j = 0;
	}

}