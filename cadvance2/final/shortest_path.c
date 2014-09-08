#include "shortest_path.h"

int shortestPath(Graph graph, int source, int target, int *path, int *length) {
	JRB dist, prev, node;
	JRB queue;

	*length = 0;
	
	int u, v;

	dist = make_jrb();
	prev = make_jrb();
	queue = make_jrb();

	init(graph, source, prev, dist, queue);

	while(!jrb_empty(queue)) {
		u = minDistance(queue);
		if(u == INFINITIVE_VALUE)
			break;
		cloudy(graph, dist, prev, u);
		modifyQueue(queue, dist);
	}

	// Debug
	// jrb_traverse(node, dist) {
	// 	printf("Vertex %d - distance %d\n", jval_i(node->key), jval_i(node->val));
	// }

	jrb_free_tree(queue);

	return solutionForShortestPath(source, target, path, length, dist, prev);
}

int longestPath(Graph graph, int source, int target, int *path, int *length) {	
	JRB dist, prev, node;

	*length = 0;
	
	int u, v;
	int n, i, output[100];

	dist = make_jrb();
	prev = make_jrb();

	initLongestPath(graph, source, prev, dist);

	n = topologicalSort(graph, path);

	for(i = 0; i < n; i++) {
		cloudyLongestPath(graph, dist, prev, path[i]);
	}

	return solutionForLongestPath(source, target, path, length, dist, prev);
}

int minDistance(JRB queue) {
	int res = INFINITIVE_VALUE;
	int index = -1;
	JRB node;

	jrb_traverse(node, queue) {
		if(res > jval_i(node->val)) {
			index = jval_i(node->key);
			res = jval_i(node->val);
		}
	}

	node = jrb_find_int(queue, index);
	if(node != NULL) {
		jrb_delete_node(node);
	}

	if(res == INFINITIVE_VALUE) 
		return INFINITIVE_VALUE;
	// printf("The min distance: %d\n", res);
	return index;
}

void cloudy(Graph graph, JRB distanceList, JRB prevList, int u) {
	JRB node, v, distanceU, distanceV, previous;
	int alt;
	JRB refList;

	node = jrb_find_int(graph->edges, u);
	// printf("Find %d\n", u);
	if(node == NULL)
		return;

	// printf("%d\n", jval_i(node->key));
	refList = jval_v(node->val);

	jrb_traverse(v, refList) {
		distanceU = jrb_find_int(distanceList, u);
		alt = getEdgeMass(graph, u, jval_i(v->key)) + jval_i(distanceU->val);
		// printf("Vertex %d: getEdgeMass: %d, distanceU: %d\n", u, jval_i(v->key), jval_i(distanceU->val));
		distanceV = jrb_find_int(distanceList, jval_i(v->key));

		if(alt < jval_i(distanceV->val)) {
			distanceV->val = new_jval_i(alt);
			previous = jrb_find_int(prevList, jval_i(v->key));
			previous->val = new_jval_i(u);
		}
	}
}

void modifyQueue(JRB queue, JRB distanceList) {
	JRB node, temp;

	jrb_traverse(node, distanceList) {
		temp = jrb_find_int(queue, jval_i(node->key));
		if(temp == NULL)
			continue;
		// printf("Before modify: %d - %d\n", jval_i(temp->val), jval_i(node->val));
		temp->val = new_jval_i(jval_i(node->val));
		// printf("Modify result: %d - %d\n", jval_i(temp->val), jval_i(node->val));
	}
}

void init(Graph graph, int source, JRB previousList, JRB distanceList, JRB queue) {
	JRB node;

	jrb_traverse(node, graph->vertices) {
		jrb_insert_int(previousList, jval_i(node->key), new_jval_i(-1));

		if(jval_i(node->key) == source) {
			jrb_insert_int(distanceList, jval_i(node->key), new_jval_i(0));
			jrb_insert_int(queue, jval_i(node->key), new_jval_i(0));
		} else {
			jrb_insert_int(distanceList, jval_i(node->key), new_jval_i(INFINITIVE_VALUE));
			jrb_insert_int(queue, jval_i(node->key), new_jval_i(INFINITIVE_VALUE));
		}
	}
}

int solutionForShortestPath(int source, int target, int *path, int *length, JRB distanceList, JRB previousList) {
	JRB node;
	int res;

	*length = 0;

	if(target == -1) {
		return INFINITIVE_VALUE;
	}
	
	node = jrb_find_int(distanceList, target);
	res = jval_i(node->val);
	if(res == INFINITIVE_VALUE)
		return INFINITIVE_VALUE;

	path[(*length)++] = target;
	node = jrb_find_int(previousList, target);

	while(jval_i(node->val) != source) {
		// printf("Node: %d - %d\n", jval_i(node->key), jval_i(node->val));
		path[(*length)++] = jval_i(node->val);
		node = jrb_find_int(previousList, path[(*length) - 1]);
	}

	path[(*length)++] = source;
	// printf("Length %d\n", *length);

	reverseArray(path, *length);

	jrb_free_tree(distanceList);
	jrb_free_tree(previousList);

	return res;
}

int reverseArray(int *array, int amount) {
	int i;

	for(i = 0; i < amount / 2; i++) {
		swapInt(&array[i], &array[amount - i - 1]);
	}
}

void swapInt(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


void initLongestPath(Graph graph, int source, JRB previousList, JRB distanceList) {
	JRB node;

	jrb_traverse(node, graph->vertices) {
		jrb_insert_int(previousList, jval_i(node->key), new_jval_i(-1));
		jrb_insert_int(distanceList, jval_i(node->key), new_jval_i(0));
	}
}

void cloudyLongestPath(Graph graph, JRB distanceList, JRB prevList, int u) {
	JRB node, v, distanceU, distanceV, previous;
	int alt;
	JRB refList;

	node = jrb_find_int(graph->edges, u);
	// printf("Find %d\n", u);
	if(node == NULL)
		return;

	// printf("%d\n", jval_i(node->key));
	refList = jval_v(node->val);

	jrb_traverse(v, refList) {
		distanceU = jrb_find_int(distanceList, u);
		alt = getEdgeMass(graph, u, jval_i(v->key)) + jval_i(distanceU->val);
		// printf("Vertex %d: getEdgeMass: %d, distanceU: %d\n", u, jval_i(v->key), jval_i(distanceU->val));
		distanceV = jrb_find_int(distanceList, jval_i(v->key));

		if(alt > jval_i(distanceV->val)) {
			distanceV->val = new_jval_i(alt);
			previous = jrb_find_int(prevList, jval_i(v->key));
			previous->val = new_jval_i(u);
		}
	}
}

int solutionForLongestPath(int source, int target, int *path, int *length, JRB distanceList, JRB previousList) {
	JRB node;
	int res;

	*length = 0;

	node = jrb_find_int(distanceList, target);
	res = jval_i(node->val);
	if(res == INFINITIVE_VALUE)
		return INFINITIVE_VALUE;

	path[(*length)++] = target;
	node = jrb_find_int(previousList, target);

	while(jval_i(node->val) != source) {
		// printf("Node: %d - %d\n", jval_i(node->key), jval_i(node->val));
		path[(*length)++] = jval_i(node->val);
		node = jrb_find_int(previousList, path[(*length) - 1]);
	}

	path[(*length)++] = source;
	// printf("Length %d\n", *length);

	reverseArray(path, *length);

	jrb_free_tree(distanceList);
	jrb_free_tree(previousList);

	return res;
}