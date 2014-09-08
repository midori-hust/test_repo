#include "fs_lib.h"

void BFS(Graph graph, Jval start, Jval stop, 
	Jval (*cloneFunc)(Jval), int (*compare)(Jval, Jval), void (*reportFunc)(Jval)) {
	Dllist node, queue;
	JRB visited;
	Jval *output;
	Jval temp, tmp;

	int i, n;

	visited = make_jrb();
	queue = new_dllist();
	dll_append(queue, start);

	if((output = myMalloc(sizeof(Jval), 100)) == NULL) {
		return;
	}

	while(!dll_empty(queue)) {
		node = dll_first(queue);
		temp = cloneFunc(node->val);
		dll_delete_node(node);

		if(jrb_find_gen(visited, temp, compare) == NULL) {
			reportFunc(temp);
			jrb_insert_gen(visited, temp, temp, compare);
			
			if(compare(temp, stop) == 0) {
				jrb_free_tree(visited);
				free_dllist(queue);
				free(output);
				return;
			}

			n = getAdjacentVertices(graph, temp, output, compare);
			for(i = 0; i < n; i++) {
				if(jrb_find_gen(visited, output[i], compare) == NULL) {
					dll_append(queue, output[i]);
				}
			}
		}
	}
}

int BFStraverse(Graph graph, Jval start,
	Jval (*cloneFunc)(Jval), int (*compare)(Jval, Jval), void (*reportFunc)(Jval)) {
	
	Dllist node, queue;
	JRB visited;
	Jval *output;
	Jval temp, tmp;

	int i, n, counter = 0;

	visited = make_jrb();
	queue = new_dllist();
	dll_append(queue, start);

	if((output = myMalloc(sizeof(Jval), 100)) == NULL) {
		return counter;
	}

	while(!dll_empty(queue)) {
		node = dll_first(queue);
		temp = cloneFunc(node->val);
		dll_delete_node(node);

		if(jrb_find_gen(visited, temp, compare) == NULL) {
			counter++;
			reportFunc(temp);
			jrb_insert_gen(visited, temp, temp, compare);
			
			n = getAdjacentVertices(graph, temp, output, compare);
			for(i = 0; i < n; i++) {
				if(jrb_find_gen(visited, output[i], compare) == NULL) {
					dll_append(queue, output[i]);
				}
			}
		}
	}

	return counter;
}

int UShortestPath(Graph graph, Jval start, Jval stop, 
	Jval (*cloneFunc)(Jval), int (*compare)(Jval, Jval), void (*reportFunc)(Jval)) {

	Dllist node, queue, stackVisit;
	JRB visited;
	Jval *output;
	Jval temp, tmp;

	int i, n;

	visited = make_jrb();
	queue = new_dllist();
	stackVisit = new_dllist();
	dll_append(queue, start);

	if((output = myMalloc(sizeof(Jval), 100)) == NULL) {
		return 0;
	}

	while(!dll_empty(queue)) {
		node = dll_first(queue);
		temp = cloneFunc(node->val);
		dll_delete_node(node);

		if(jrb_find_gen(visited, temp, compare) == NULL) {
			jrb_insert_gen(visited, temp, temp, compare);
			dll_prepend(stackVisit, temp);
			
			if(compare(temp, stop) == 0) {
				return solution(graph, start, stop, stackVisit, cloneFunc, compare, reportFunc);
			}

			n = getAdjacentVertices(graph, temp, output, compare);
			for(i = 0; i < n; i++) {
				if(jrb_find_gen(visited, output[i], compare) == NULL) {
					dll_append(queue, output[i]);
				}
			}
		}
	}

	return -1;
}

int solution(Graph graph, Jval start, Jval stop, Dllist stackVisit, Jval (*cloneFunc)(Jval),
	int (*compare)(Jval, Jval), void (*reportFunc)(Jval)) {

	Dllist stackRes;
	Dllist node;
	Jval nowNode, temp;
	int counter = 0;

	stackRes = new_dllist();
	node = dll_first(stackVisit);
	nowNode = cloneFunc(node->val);
	dll_delete_node(node);
	dll_prepend(stackRes, nowNode);

	while(!dll_empty(stackVisit)) {
		if(isAdjacent(graph, nowNode, start, compare)) {
			dll_prepend(stackRes, start);
			counter++;
			break;
		}

		do {
			node = dll_first(stackVisit);
			temp = cloneFunc(node->val);
			dll_delete_node(node);	

			if(isAdjacent(graph, nowNode, temp, compare)) {
				dll_prepend(stackRes, temp);
				nowNode = temp;
				counter++;
				break;
			}
		} while(!dll_empty(stackVisit));
	}

	printf("Solution: The shortest path between two node: \n");

	while(!dll_empty(stackRes)) {
		node = dll_first(stackRes);
		reportFunc(node->val);
		dll_delete_node(node);
	}

	free_dllist(stackVisit);

	return counter;
}

void DFS(Graph graph, Jval start, Jval stop, 
	Jval (*cloneFunc)(Jval), int (*compare)(Jval, Jval), void (*reportFunc)(Jval)) {
	Dllist node, stack;
	JRB visited;
	Jval *output;
	Jval temp, tmp;

	int i, n;

	visited = make_jrb();
	stack = new_dllist();
	dll_prepend(stack, start);

	if((output = myMalloc(sizeof(Jval), 100)) == NULL) {
		return;
	}

	while(!dll_empty(stack)) {
		node = dll_first(stack);
		temp = cloneFunc(node->val);
		dll_delete_node(node);

		if(jrb_find_gen(visited, temp, compare) == NULL) {
			reportFunc(temp);
			jrb_insert_gen(visited, temp, temp, compare);
			
			if(compare(temp, stop) == 0) {
				jrb_free_tree(visited);
				free_dllist(stack);
				free(output);
				return;
			}

			n = getAdjacentVertices(graph, temp, output, compare);
			for(i = 0; i < n; i++) {
				if(jrb_find_gen(visited, output[i], compare) == NULL) {
					dll_prepend(stack, output[i]);
				}
			}
		}
	}
}

int DFStraverse(Graph graph, Jval start, 
	Jval (*cloneFunc)(Jval), int (*compare)(Jval, Jval), void (*reportFunc)(Jval)) {
	Dllist node, stack;
	JRB visited;
	Jval *output;
	Jval temp, tmp;

	int i, n, counter = 0;

	visited = make_jrb();
	stack = new_dllist();
	dll_prepend(stack, start);

	if((output = myMalloc(sizeof(Jval), 100)) == NULL) {
		return counter;
	}

	while(!dll_empty(stack)) {
		node = dll_first(stack);
		temp = cloneFunc(node->val);
		dll_delete_node(node);

		if(jrb_find_gen(visited, temp, compare) == NULL) {
			counter++;
			reportFunc(temp);
			jrb_insert_gen(visited, temp, temp, compare);
			
			n = getAdjacentVertices(graph, temp, output, compare);
			for(i = 0; i < n; i++) {
				if(jrb_find_gen(visited, output[i], compare) == NULL) {
					dll_prepend(stack, output[i]);
				}
			}
		}
	}

	return counter;
}

int checkConnectivity(Graph graph, Jval start, Jval (*cloneFunc)(Jval), int (*compare)(Jval, Jval)) {

}