#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>
#include <ctype.h>

#include "my_input_lib.h"
#include "file_handle.h"
#include "fs_lib.h"
#include "shortest_path.h"

#define MAXSIZE 100
#define SIZE 100
#define TEMPSIZE 50

int solve(FILE *f);

void readData(FILE *f, Graph graph);
void option1(Graph graph);
void option2(Graph graph);
void option3(Graph graph);
void option4(Graph graph);
void option5(Graph graph);

#endif