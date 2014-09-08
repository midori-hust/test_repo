#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"
#include "file_handle.h"
#include "graph.h"

#define MAXSIZE 100
#define SIZE 100
#define TEMPSIZE 50

typedef struct _StationInfo {
	String code;
	String name;
} StationInfo;

int solve(FILE *f);

int readFile(FILE *f, Graph g, JRB stationList);
int readStationListFromFile(FILE *f, JRB stationList);
void readMetroLineFromFile(FILE *f, Graph graph);
int split(char *str, char splitChar, String *listString);

int stringCompare(Jval a, Jval b);
void myPrint(Jval item);
Jval cloneNode(Jval item);

#endif