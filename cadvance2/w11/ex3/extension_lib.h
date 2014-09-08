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

int readFile(FILE *f, Graph g, String *listStationRef, StationInfo *stationList);
int readStationListFromFile(FILE *f, Graph g, String *listStationRef, StationInfo *stationList);
void readMetroLineFromFile(FILE *f, Graph g, String *listStationRef, int amount);
int getIndex(String item, String *listStationRef, int amount);
int getStationInfoIndex(StationInfo *stationList, int amount, char *item);
int split(char *str, char splitChar, String *listString);

#endif