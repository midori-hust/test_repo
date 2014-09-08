#include "heap_sort.h"

void exch(void *buf, int i, int j, size_t size) {
	char* temp;

	if((temp = myMalloc(sizeof(char), size)) == NULL) {
		return;
	}

	memcpy(temp, buf + i * size, size);
	memcpy(buf + i * size, buf + j * size, size);
	memcpy(buf + j * size, temp, size);

	free(temp);
}

void heapSort(void* buf, size_t size, size_t total, int (*compare)(void const* a, void const* b)) {
	int start, end;

	for(start = (total - 2) / 2; start >= 0; start--) {
		siftDown(buf, size, start, total, compare);
	}

	for(end = total - 1; end > 0; end--) {
		exch(buf, end, 0, size);
		siftDown(buf, size, 0, end, compare);
	}
}

// Private
void siftDown(void* buf, size_t size, int start, int end, int (*compare)(void const* a, void const* b)) {
	int root = start;
	int child;

	while(root * 2 + 1 < end) {
		child = 2 * root + 1;
		if((child + 1 < end) 
			&& compare((char*)buf + child * size, 
				(char*)buf + (child + 1) * size) < 0) {
			child++;
		}

		if(compare((char*)buf + root * size, (char*)buf + child * size) < 0) {
			exch(buf, child, root, size);
			root = child;
		} else {
			return;
		}
	}
}