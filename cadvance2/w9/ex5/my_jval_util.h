#ifndef __MY_JVAL_UTIL_H__
#define __MY_JVAL_UTIL_H__

#include "jval.h"
#include "my_input_lib.h"

/* Public */

// Sort functions
void quickSort3WayJval(Jval *a, int l, int r, int (*compare)(Jval*, Jval*));

// Search functions
int seqSearchJval(Jval *a, int amount, Jval item, int (*compare)(Jval*, Jval*));
int binarySearchJval(Jval *a, Jval item, int low, int high, int (*compare)(Jval*, Jval*));

/* Private */
void exchangeJval(Jval *a, int i, int j);
int midPoint(int low, int high); // binarySearchJval function's helper

#endif