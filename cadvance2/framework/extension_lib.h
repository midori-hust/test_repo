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

#endif