#include "extension_lib.h"

int solve(FILE *f) {
	int i, n, output[SIZE], itemIndex;
	String listStationRef[SIZE];
	String item;
	int res;
	StationInfo *stationList;

	Graph g;

	g = createGraph();

	if((stationList = myMalloc(sizeof(StationInfo), SIZE)) == NULL) {
		return 1;
	}

	if((n = readFile(f, g, listStationRef, stationList)) == -1) {
		return 1;
	}

	printf("Please enter the station which you want to find the adjacent stations\n");
	fgets(item.content, SIZE, stdin);
	item.content[strlen(item.content) - 1] = '\0';

	itemIndex = getIndex(item, listStationRef, n);

	if((res = getAdjacentVertices(g, itemIndex, output)) == 0) {
		printf("No adjacent vertices of node %s\n", listStationRef[itemIndex].content);
	} else {
		printf("Adjacent vertices of node %s\n", listStationRef[itemIndex].content);
		for(i = 0; i < res; i++) {
			printf("%5s ", listStationRef[output[i]].content);
			printf("(Station name: %s)\n", 
				stationList[getStationInfoIndex(stationList, n, listStationRef[output[i]].content)].name.content);
		}
	}

	freeGraph(g);

	return 0;
}

int readFile(FILE *f, Graph g, String *listStationRef, StationInfo *stationList) {
	int n;

	if(f == NULL) {
		printf("Cannot read file\n");
		return -1;
	}

	rewind(f);
	n = readStationListFromFile(f, g, listStationRef, stationList);
	readMetroLineFromFile(f, g, listStationRef, n);
	rewind(f);

	return n;
}

int readStationListFromFile(FILE *f, Graph g, String *listStationRef, StationInfo *stationList) {
	String temp;
	int n = 0;
	
	rewind(f);
	fgets(temp.content, SIZE, f);
	while(fscanf(f, "%[^=]=", temp.content) != EOF) {
		strcpy(listStationRef[n++].content, temp.content);
		if(strstr(temp.content, "[LINES]") != NULL) {
			break;
		}
		strcpy(stationList[n-1].code.content, temp.content);
		fgets(temp.content, SIZE, f);
		temp.content[strlen(temp.content) - 1] = '\0';
		strcpy(stationList[n-1].name.content, temp.content);
	} 
	return n;
}

void readMetroLineFromFile(FILE *f, Graph g, String *listStationRef, int amount) {
	String temp;
	String tmpList[SIZE];
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
		for(i = 1; i < n; i++) {
			addEdge(g, getIndex(tmpList[i - 1], listStationRef, amount), getIndex(tmpList[i], listStationRef, amount));
		}
	}
}

int getIndex(String item, String *listStationRef, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		if(strcmp(listStationRef[i].content, item.content) == 0) {
			return i;
		}
	}

	return -1;
}

int getStationInfoIndex(StationInfo *stationList, int amount, char *item) {
	int i;

	for(i = 0; i < amount; i++) {
		if(strcmp(stationList[i].code.content, item) == 0) {
			return i;
		}
	}
	return -1;
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