#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"
#include "file_handle.h"
#include "graph.h"

#include <ctype.h>

#define MAXSIZE 100
#define SIZE 100
#define TEMPSIZE 50


typedef struct _Person {
	String name;
	int relationshipLevel;
} Person;

int solve(FILE *f);

void readFile(FILE *f, Graph g);
void addListToGraph(Graph g, String tempPerson, String *list, int amount);
int personCompare(Jval a, Jval b);
int split(char *str, char splitChar, String *listString);
int intCompare(Jval a, Jval b);

#endif