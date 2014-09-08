#include "graph.h"

Graph createGraph() {
	Graph graph;
	
	graph = make_jrb();

	return graph;
}

void addEdge(Graph graph, int v1, int v2) {
	setEdge(graph, v1, v2);
	setEdge(graph, v2, v1);
}

int isAdjacent(Graph graph, int v1, int v2) {
	// On Processing
	Graph node;
	Graph tree;

	if((node = jrb_find_int(graph, v1)) == NULL) {
		return 0;
	}

	tree = jval_v(node->val);

	if((node = jrb_find_int(tree, v2)) == NULL) {
		return 0;
	}

	return 1;
}

int getAdjacentVertices(Graph graph, int vertex, int *output) {
	Graph node, tree;
	int counter = 0;
	
	if((node = jrb_find_int(graph, vertex)) == NULL) {
		return counter;
	}

	tree = jval_v(node->val);

	jrb_traverse(node, tree) {
		output[counter++] = jval_i(node->key);
	}

	return counter;
}

void freeGraph(Graph graph) {
	Graph node;

	jrb_traverse(node, graph) {
		jrb_free_tree(jval_v(node->val));
	}

	jrb_free_tree(graph);
}

/* Private */
void setEdge(Graph graph, int v1, int v2) {
	Graph tree, node;

	if((node = jrb_find_int(graph, v1)) == NULL) {
		tree = make_jrb();
		jrb_insert_int(graph, v1, new_jval_v(tree));
	} else {
		tree = jval_v(node->val);
	}

	if(jrb_find_int(tree, v2) != NULL) {
		return;
	}

	jrb_insert_int(tree, v2, new_jval_i(1));
}