#include "extension_lib.h"

int solve(FILE *f) {
	Graph g;
	JRB stationList;

	String startName, stopName;
	JRB startCode, stopCode, node;
	int n;
	Jval output[SIZE];

	g = createGraph();
	stationList = make_jrb();

	if(readFile(f, g, stationList) == -1) {
		return 1;
	}

	printf("Please enter the start station name:\n");
	fscanf(stdin, "%[^\n]", startName.content);
	while(getchar() != '\n');

	printf("Please enter the stop station name:\n");
	fscanf(stdin, "%[^\n]", stopName.content);
	while(getchar() != '\n');

	if((startCode = jrb_find_gen(stationList, new_jval_v(&startName), stringCompare)) == NULL) {
		return 1;
	}

	if((stopCode = jrb_find_gen(stationList, new_jval_v(&stopName), stringCompare)) == NULL) {
		return 1;
	}

	printf("Movement between station \"%s\" to station \"%s\"\n", startName.content, stopName.content);
	n = UShortestPath(g, startCode->val, stopCode->val, cloneNode, stringCompare, myPrint);

	if(n == 0) {
		printf("Cannot move from station \"%s\" to station \"%s\"\n", startName.content, stopName.content);
	} else {
		printf("Path length between station \"%s\" to station \"%s\": %d\n", startName.content, stopName.content, n);
	}


	freeGraph(g);
	jrb_free_tree(stationList);
	return 0;
}

int readFile(FILE *f, Graph graph, JRB stationList) {
	int n;

	if(f == NULL) {
		printf("Cannot read file\n");
		return -1;
	}

	rewind(f);
	n = readStationListFromFile(f, stationList);
	readMetroLineFromFile(f, graph);
	rewind(f);

	return n;
}

int readStationListFromFile(FILE *f, JRB stationList) {
	String temp;
	StationInfo *station;
	int n = 0;
	
	printf("Station list: \n");
	rewind(f);
	fgets(temp.content, SIZE, f);
	while(fscanf(f, "%[^=]=", temp.content) != EOF) {
		if(strstr(temp.content, "[LINES]") != NULL) {
			break;
		}

		if((station = myMalloc(sizeof(StationInfo), 1)) == NULL) {
			return -1;
		}

		strcpy(station->code.content, temp.content);
		fgets(temp.content, SIZE, f);
		temp.content[strlen(temp.content) - 1] = '\0';
		strcpy(station->name.content, temp.content);

		jrb_insert_gen(stationList, new_jval_v(&station->name), new_jval_v(&station->code), stringCompare);

		printf("Station name: \"%s\" - \"%s\"\n", station->name.content, station->code.content);
	}
	return n;
}

void readMetroLineFromFile(FILE *f, Graph graph) {
	String temp;
	String tmpList[SIZE];
	String *list;
	int i;
	int n;

	rewind(f);
	while(fgets(temp.content, SIZE, f) != NULL) {
		if(strstr(temp.content, "[LINES]") != NULL) {
			break;
		}
	}

	while(fscanf(f, "%[^=]=", temp.content) != EOF) {
		fscanf(f, "%[^\n]\n", temp.content);
		if((n = split(temp.content, ' ', tmpList)) == -1) {
			return;
		}
 
		if((list = myMalloc(sizeof(String), n)) == NULL) {
			return;
		}

		strcpy(list[0].content, tmpList[0].content);
		for(i = 1; i < n; i++) {
			strcpy(list[i].content, tmpList[i].content);
			addEdge(graph, new_jval_v(&list[i - 1]), new_jval_v(&list[i]), stringCompare);
			printf("%s - %s\n", list[i - 1].content, list[i].content);
		}
	}
	rewind(f);
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

int stringCompare(Jval a, Jval b) {
	String *x, *y;

	x = jval_v(a);
	y = jval_v(b);

	return strcmp(x->content, y->content);
}

void myPrint(Jval item) {
	String *temp;

	temp = jval_v(item);

	printf("Station %s\n", temp->content);
}

Jval cloneNode(Jval item) {
	String *newItem;
	String *temp;

	if((newItem = myMalloc(sizeof(String), 1)) == NULL) {
		printf("Cannot clone node!\n");
		exit(1);
	}

	temp = jval_v(item);

	strcpy(newItem->content, temp->content);

	return new_jval_v(newItem);
}