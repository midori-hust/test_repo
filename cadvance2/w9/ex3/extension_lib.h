#ifndef __EXTENSION_LIB_H__
#define __EXTENSION_LIB_H__

#include <time.h>

#include "my_input_lib.h"
#include "file_handle.h"
#include "my_jval_util.h"
#include "controller.h"

#define MAXSIZE 1000
#define SIZE 100
#define TEMPSIZE 50


int solve();
void handleFunction(Jval *array, int type);


/* MENU */
int menuLevel1();
int menuLevel2();

#endif