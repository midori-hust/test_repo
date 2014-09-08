#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"
#include "file_handle.h"
#include "fields.h"
#include "jrb.h"


#define MAXSIZE 1000
#define SIZE 100
#define TEMPSIZE 50

int solve(char *fileName);
JRB buildTree(char *fileName);
void checkingSpell(JRB tree);
int menuSpellChecking();

#endif