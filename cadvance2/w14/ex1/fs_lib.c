#include "fs_lib.h"

int searchController(Graph graph, int start, int stop, int option) {
	Dllist close;
	Dllist node;

	close = new_dllist();

	switch(option) {
		case BFS_SEARCH:
		breathFirstSearch(graph, start, stop, close);
		break;
		case BFS_TRAVERSE:
		traverseBFS(graph, start, close);
		break;
		case DFS_SEARCH:
		deepFirstSearch(graph, start, stop, close);
		break;
		case DFS_TRAVERSE:
		traverseDFS(graph, start, close);
		break;
		default:
		printf("This is not an option\n");
		free_dllist(close);
		return;
	}

	node = dll_first(close);
	printf("Visit %d\n", jval_i(node->val));

	free_dllist(close);
}


int breathFirstSearch(Graph graph, int start, int stop, Dllist close) {
	Dllist node, queue;
	JRB visited;
	int output[100];
	int temp;

	int i, n;

	visited = make_jrb();
	queue = new_dllist();
	dll_append(queue, new_jval_i(start));

	while(!dll_empty(queue)) {
		node = dll_first(queue);
		temp = jval_i(node->val);
		dll_delete_node(node);

		if(jrb_find_int(visited, temp) == NULL) {
			// reportFunc(temp);
			dll_append(close, new_jval_i(temp));
			jrb_insert_int(visited, temp, new_jval_i(temp));
			
			if(temp == stop) {
				jrb_free_tree(visited);
				free_dllist(queue);
				return 1;
			}

			n = outdegree(graph, temp, output);
			for(i = 0; i < n; i++) {
				if(jrb_find_int(visited, output[i]) == NULL) {
					dll_append(queue, new_jval_i(output[i]));
				}
			}
		}
	}

	jrb_free_tree(visited);
	free_dllist(queue);
	return 0;
}

int traverseBFS(Graph graph, int start, Dllist close) {
	Dllist node, queue;
	JRB visited;
	int *output;
	int temp;

	int i, n, counter = 0;

	visited = make_jrb();
	queue = new_dllist();
	dll_append(queue, new_jval_i(start));

	while(!dll_empty(queue)) {
		node = dll_first(queue);
		temp = jval_i(node->val);
		dll_delete_node(node);

		if(jrb_find_int(visited, temp) == NULL) {
			counter++;
			// reportFunc(temp);
			jrb_insert_int(visited, temp, new_jval_i(temp));
			
			n = outdegree(graph, temp, output);
			for(i = 0; i < n; i++) {
				if(jrb_find_int(visited, output[i]) == NULL) {
					dll_append(queue, new_jval_i(output[i]));
				}
			}
		}
	}

	return counter;
}

int UShortestPath(Graph graph, int start, int stop, Dllist close) {
	Dllist node, queue, stackVisit;
	JRB visited;
	int output[100];
	int temp;

	int i, n;

	visited = make_jrb();
	queue = new_dllist();
	stackVisit = new_dllist();
	dll_append(queue, new_jval_i(start));

	while(!dll_empty(queue)) {
		node = dll_first(queue);
		temp = jval_i(node->val);
		dll_delete_node(node);

		if(jrb_find_int(visited, temp) == NULL) {
			jrb_insert_int(visited, temp, new_jval_i(temp));
			dll_prepend(stackVisit, new_jval_i(temp));
			
			if(temp == stop) {
				return solution(graph, start, stop, stackVisit, close);
			}

			n = outdegree(graph, temp, output);
			for(i = 0; i < n; i++) {
				if(jrb_find_int(visited, output[i]) == NULL) {
					dll_append(queue, new_jval_i(output[i]));
				}
			}
		}
	}

	return -1;
}

int searchSolution(Graph graph, int start, int stop, Dllist stackVisit, Dllist close) {
	Dllist stackRes;
	Dllist node;
	int nowNode, temp;
	int counter = 0;

	// stackRes = new_dllist();
	// node = dll_first(stackVisit);
	// nowNode = jval_i(node->val);
	// dll_delete_node(node);
	// dll_prepend(stackRes, new_jval_i(nowNode));

	// while(!dll_empty(stackVisit)) {
	// 	if(isAdjacent(graph, nowNode, start, compare)) {
	// 		dll_prepend(stackRes, start);
	// 		counter++;
	// 		break;
	// 	}

	// 	do {
	// 		node = dll_first(stackVisit);
	// 		temp = cloneFunc(node->val);
	// 		dll_delete_node(node);	

	// 		if(isAdjacent(graph, nowNode, temp, compare)) {
	// 			dll_prepend(stackRes, temp);
	// 			nowNode = temp;
	// 			counter++;
	// 			break;
	// 		}
	// 	} while(!dll_empty(stackVisit));
	// }

	// printf("Solution: The shortest path between two node: \n");

	// while(!dll_empty(stackRes)) {
	// 	node = dll_first(stackRes);
	// 	reportFunc(node->val);
	// 	dll_delete_node(node);
	// }

	// free_dllist(stackVisit);

	return counter;
}

int deepFirstSearch(Graph graph, int start, int stop, Dllist close) {
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
			// reportFunc(temp);
			dll_append(close, new_jval_i(temp));
			jrb_insert_int(visited, temp, new_jval_i(temp));
			
			if(compare(temp, stop) == 0) {
				jrb_free_tree(visited);
				free_dllist(stack);
				return 1;
			}

			n = outdegree(graph, temp, output);
			for(i = 0; i < n; i++) {
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

int traverseDFS(Graph graph, int start, Dllist close) {
	Dllist node, stack;
	JRB visited;
	int output[100];
	int temp;

	int i, n, counter = 0;

	visited = make_jrb();
	stack = new_dllist();
	dll_prepend(stack, new_jval_i(start));

	while(!dll_empty(stack)) {
		node = dll_first(stack);
		temp = jval_i(node->val);
		dll_delete_node(node);

		if(jrb_find_int(visited, temp) == NULL) {
			counter++;
			// reportFunc(temp);
			dll_append(close, new_jval_i(temp));
			jrb_insert_int(visited, temp, new_jval_i(temp));
			
			n = outdegree(graph, temp, output);
			for(i = 0; i < n; i++) {
				if(jrb_find_int(visited, output[i]) == NULL) {
					dll_prepend(stack, new_jval_i(output[i]));
				}
			}
		}
	}

	return counter;
}