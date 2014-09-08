#include "directed_graph.h"

Graph createGraph() {
	Graph graph;

	if((graph = myMalloc(sizeof(Graph), 1)) == NULL) {
		return NULL;
	}

	graph->vertices = make_jrb();
	graph->edges = make_jrb();
	graph->MAX_VERTICES = 0;
	graph->MAX_EDGES = 0;

	return graph;
}

void addVertex(Graph graph, int id, char* name) {
	if(jrb_find_int(graph->vertices, id) != NULL) {
		return;
	}

	jrb_insert_int(graph->vertices, id, new_jval_s(name));
	graph->MAX_VERTICES++;
}

char* getVertex(Graph graph, int id) {
	JRB res;

	if((res = jrb_find_int(graph->vertices, id)) == NULL) {
		return NULL;
	}

	return jval_s(res->val);
}

void addEdge(Graph graph, int v1, int v2, int mass) {
	if(jrb_find_int(graph->vertices, v1) == NULL) {
		return;
	}

	if(jrb_find_int(graph->vertices, v2) == NULL) {
		return;
	}

	setEdge(graph, v1, v2, mass);
	graph->MAX_EDGES++;
}

int hasEdge(Graph graph, int v1, int v2) {
	JRB tree, node;

	if(jrb_find_int(graph->vertices, v1) == NULL) {
		return 0;
	}

	if(jrb_find_int(graph->vertices, v2) == NULL) {
		return 0;
	}

	if(isInDegree(graph, v1, v2)) {
		return 1;
	}

	if(isInDegree(graph, v2, v1)) {
		return -1;
	}

	return 0;
}

int indegree(Graph graph, int v, int *output) {
	JRB node;
	int total = 0;

	if(jrb_find_int(graph->vertices, v) == NULL) {
		return 0;
	}

	jrb_traverse(node, graph->vertices) {
		if(isInDegree(graph, jval_i(node->key), v)) {
			output[total++] = jval_i(node->key);
		}
	}

	return total;
}

int outdegree(Graph graph, int v, int *output) {
	JRB node;
	int total = 0;

	if(jrb_find_int(graph->vertices, v) == NULL) {
		return 0;
	}

	jrb_traverse(node, graph->vertices) {
		if(isInDegree(graph, v, jval_i(node->key))) {
			output[total++] = jval_i(node->key);
		}
	}

	return total;
}

int getComponents(Graph graph) {
	int counter = 0;
	int numberOfTravesedNode = 0;
	JRB visitedList, node;
	int flag = 0;

	visitedList = make_jrb();

	jrb_traverse(node, graph->vertices) {
		if(jrb_find_int(visitedList, jval_i(node->key)) != NULL) {
			continue;
		}

		numberOfTravesedNode += BFStraverse(graph, jval_i(node->key), visitedList);
		counter++;
		if(numberOfTravesedNode == graph->MAX_VERTICES) {
			break;
		}
	}

	jrb_free_tree(visitedList);

	return counter;
}

int getKeyByVal(Graph graph, char* name) {
	JRB node;

	jrb_traverse(node, graph->vertices) {
		if(strcmp(jval_s(node->val), name) == 0) {
			return jval_i(node->key);
		}
	}

	return -1;
}

int checkCycle(Graph graph) {
	JRB node;

	if(getComponents(graph) != 1) {
		printf("The graph is not connected.\n");
		return 0;
	}

	jrb_traverse(node, graph->vertices) {
		if(DFS(graph, jval_i(node->key), jval_i(node->key))) {
			return 1;
		}
	}

	return 0;
}

void DAG(Graph graph) {
	int n, i;
	int output[100];
	
	n = topologicalSort(graph, output);

	printf("Topological order:\n");
	for(i = 0; i < n; i++) {
		printf("Visit %s\n", getVertex(graph, output[i]));
	}
}

int topologicalSort(Graph graph, int *result) {
	Dllist queue, tempDllNode;
	JRB visited, indegreeList;
	JRB node;
	int output[100], counter = 0;
	int visit, numOfInDegree;

	queue = new_dllist();
	visited = make_jrb();
	indegreeList = make_jrb();

	jrb_traverse(node, graph->vertices) {
		if((numOfInDegree = indegree(graph, jval_i(node->key), output)) == 0) {
			dll_append(queue, new_jval_i(jval_i(node->key)));
		}

		jrb_insert_int(indegreeList, jval_i(node->key), new_jval_i(numOfInDegree));

	}

	while(!dll_empty(queue)) {
		tempDllNode = dll_first(queue);
		visit = jval_i(tempDllNode->val);
		dll_delete_node(tempDllNode);

		result[counter++] = visit;
		printf("%d\n", visit);
		jrb_insert_int(visited, visit, new_jval_i(visit));

		jrb_traverse(node, indegreeList) {
			if(!isInDegree(graph, visit, jval_i(node->key))) {
				continue;	
			}

			node->val = new_jval_i(jval_i(node->val) - 1);

			if(jval_i(node->val) == 0) {
				if(jrb_find_int(visited, jval_i(node->key)) == NULL) {
					dll_append(queue, node->key);
				}
			}
		}
	}

	jrb_free_tree(visited);
	free_dllist(queue);

	return counter;
}

int getEdgeMass(Graph graph, int v1, int v2) {
	JRB res, temp;

	if((temp = jrb_find_int(graph->edges, v1)) == NULL) {
		return INFINITIVE_VALUE;
	}

	if((res = jrb_find_int(jval_v(temp->val), v2)) == NULL) {
		return INFINITIVE_VALUE;
	}

	return jval_i(res->val);
}

void dropGraph(Graph graph) {
	jrb_free_tree(graph->edges);
	jrb_free_tree(graph->vertices);
}

/* Private */
void setEdge(Graph graph, int v1, int v2, int mass) {
	JRB tree, node;

	if((node = jrb_find_int(graph->edges, v1)) == NULL) {
		tree = make_jrb();
		jrb_insert_int(graph->edges, v1, new_jval_v(tree));
	} else {
		tree = jval_v(node->val);
	}

	if(jrb_find_int(tree, v2) != NULL) {
		return;
	}

	jrb_insert_int(tree, v2, new_jval_i(mass));
}

int isInDegree(Graph graph, int v1, int v2) {
	JRB tree, node;

	if((node = jrb_find_int(graph->edges, v1)) == NULL) {
		return 0;
	}

	tree = jval_v(node->val);
	if(jrb_find_int(tree, v2) != NULL) {
		return 1;
	}

	return 0;
}

int BFStraverse(Graph graph, int start, JRB visited) {
	Dllist node, queue;
	int output[100];
	int temp;

	int i, n, counter = 0;

	queue = new_dllist();
	dll_append(queue, new_jval_i(start));

	while(!dll_empty(queue)) {
		node = dll_first(queue);
		temp = jval_i(node->val);
		dll_delete_node(node);

		if(jrb_find_int(visited, temp) == NULL) {
			counter++;
			jrb_insert_int(visited, temp, new_jval_i(temp));
			
			n = outdegree(graph, temp, output);
			for(i = 0; i < n; i++) {
				if(jrb_find_int(visited, output[i]) == NULL) {
					dll_append(queue, new_jval_i(output[i]));
				}
			}

			n = indegree(graph, temp, output);
			for(i = 0; i < n; i++) {
				if(jrb_find_int(visited, output[i]) == NULL) {
					dll_append(queue, new_jval_i(output[i]));
				}
			}
		}
	}

	return counter;
}

int DFS(Graph graph, int start, int stop) {
	Dllist node, stack;
	JRB visited;
	int output[100];
	int temp;

	int i, n;

	visited = make_jrb();
	stack = new_dllist();
	dll_prepend(stack, new_jval_i(start));

	while(!dll_empty(stack)) {
		node = dll_first(stack);
		temp = jval_i(node->val);
		dll_delete_node(node);

		if(jrb_find_int(visited, temp) == NULL) {
			jrb_insert_int(visited, temp, new_jval_i(temp));

			n = outdegree(graph, temp, output);
			for(i = 0; i < n; i++) {
				if(output[i] == stop) {
					jrb_free_tree(visited);
					free_dllist(stack);
					return 1;
				}

				if(jrb_find_int(visited, output[i]) == NULL) {
					dll_prepend(stack, new_jval_i(output[i]));
				}
			}
		}
	}

	jrb_free_tree(visited);
	free_dllist(stack);
	return 0;
}