#include "swap.h"

void swap(int *p1, int *p2){
    int p = *p1;
    *p1 = *p2;
    *p2 = p;
}
