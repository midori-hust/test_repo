#include "extension_lib.h"

int solve(FILE *f) {
	Graph g;
	Graph node, valNode;
	Jval output[100];
	int i = 0, n;
	Person *res;

	g = createGraph();

	readFile(f, g);

	jrb_traverse(node, g) {
		res = jval_v(node->key);
		printf("Person #%d:\n\tPerson's name: %s\n", i++, res->name.content);
		n = getAdjacentVertices(g, node->key, output, personCompare);
		if(n == 0) {
			continue;
		}

		for(i = 0; i < n; i++) {
			res = jval_v(output[i]);
			printf("\tFriend's name: %s, relationship level: %d\n", res->name.content, res->relationshipLevel);
		}
	}

	freeGraph(g);

	return 0;
}

void readFile(FILE *f, Graph g) {
	String tempPerson;
	String tempFriend;
	String *tempList;
	int returnNum;

	if((tempList = myMalloc(sizeof(String), SIZE)) == NULL) {
		return;
	}

	rewind(f);

	while(fscanf(f, "%[^:]:", tempPerson.content) != EOF) {

		fscanf(f, "%[^\n]\n", tempFriend.content);
		if((returnNum = split(tempFriend.content, ',', tempList)) == -1) {
			return;
		}
		
		addListToGraph(g, tempPerson, tempList, returnNum);
	}
	rewind(f);
}


void addListToGraph(Graph g, String tempPerson, String *list, int amount) {
	int i;
	String *temp;
	int res;
	Person *person1, *person2;

	if(amount <= 0)
		return;

	for(i = 0; i < amount; i++) {
		if((person1 = myMalloc(sizeof(Person), 1)) == NULL) {
			return;
		}
		if((person2 = myMalloc(sizeof(Person), 1)) == NULL) {
			return;
		}

		split(list[i].content, ' ', temp);
		strcpy(person1->name.content, temp[1].content);
		person1->relationshipLevel = atoi(temp[2].content);

		strcpy(person2->name.content, tempPerson.content);
		person2->relationshipLevel = atoi(temp[2].content);
		addEdge(g, new_jval_v(person1), new_jval_v(person2), personCompare);
	}
}

int personCompare(Jval a, Jval b) {
	Person *x, *y;

	x = jval_v(a);
	y = jval_v(b);

	return strcmp(x->name.content, y->name.content);
}

int split(char *str, char splitChar, String *listString) {
	int counter = 0;
	int i;
	char *ptr, *temp;

	if(str == NULL) {
		return -1;
	}

	temp = myMalloc(sizeof(String), 1);
	strcpy(temp, str);
	ptr = temp;

	for(i = 0; i <= strlen(str); i++) {
		if(temp[i] == splitChar || temp[i] == '\0') {
			temp[i] = '\0';
			strcpy(listString[counter++].content, ptr);
			ptr = temp + i + 1;
		}
	}

	return counter;
}