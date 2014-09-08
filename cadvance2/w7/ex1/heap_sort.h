#ifndef __HEAP_SORT_H__
#define __HEAP_SORT_H__

#include <stdio.h>

void exch(void *buf, int i, int j, size_t size);
void heapSort(void* buf, size_t size, size_t total, int (*compare)(void const* a, void const* b));
void siftDown(void* buf, size_t size, int start, int end, int (*compare)(void const* a, void const* b));

#endif