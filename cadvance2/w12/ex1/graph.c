#include "graph.h"

Graph createGraph() {
	Graph graph;
	
	graph = make_jrb();

	return graph;
}

void addEdge(Graph graph, Jval v1, Jval v2, int (*compare)(Jval, Jval)) {
	setEdge(graph, v1, v2, compare);
	setEdge(graph, v2, v1, compare);
}

int isAdjacent(Graph graph, Jval v1, Jval v2, int (*compare)(Jval, Jval)) {
	// On Processing
	Graph node;
	Graph tree;

	if((node = jrb_find_gen(graph, v1, compare)) == NULL) {
		return 0;
	}

	tree = jval_v(node->val);

	if((node = jrb_find_gen(tree, v2, compare)) == NULL) {
		return 0;
	}

	return 1;
}

int getAdjacentVertices(Graph graph, Jval vertex, Jval *output, int (*compare)(Jval, Jval)) {
	Graph node, tree;
	int counter = 0;
	
	if((node = jrb_find_gen(graph, vertex, compare)) == NULL) {
		return counter;
	}

	tree = jval_v(node->val);

	jrb_traverse(node, tree) {
		output[counter++] = (Jval)jval_v(node->key);
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
void setEdge(Graph graph, Jval v1, Jval v2, int (*compare)(Jval, Jval)) {
	Graph tree, node;

	if((node = jrb_find_gen(graph, v1, compare)) == NULL) {
		tree = make_jrb();
		jrb_insert_gen(graph, v1, new_jval_v(tree), compare);
	} else {
		tree = jval_v(node->val);
	}

	if(jrb_find_gen(tree, v2, compare) != NULL) {
		return;
	}

	jrb_insert_gen(tree, v2, new_jval_i(1), compare);
}