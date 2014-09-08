#include "generic_lib.h"

/* Generic functions */
int findMax(void *buf, size_t size, size_t total, int (*compare)(void const*, void const*)) {
	int i, res, iMax = 0;
	void* item;

	if(total == 0 || size < 0 || buf == NULL)
		return -1; // Cannot find the item element

	if((item = myMalloc(size, sizeof(char))) == NULL) {
		return -1;
	}

	memcpy(item, (char*)buf, size);

	for(i = 0; i < total; i++) {
		res = compare(item, (char*)buf + (size * i));
		if(res > 0) {
			memcpy(item, (char*)buf + (size * i), size);
			iMax = i;
		}
	}

	free(item);
	return iMax;
}

void reverseArray(void *buf, size_t size, size_t total) {
	int i;

	for(i = 0; i < total / 2; i++) {
		exch(buf, i, total - i - 1, size);
	}
}

void mySort(void *buf, size_t size, size_t total, int (*compare)(void const *, void const *)) {
	q3sort(buf, size, 0, total - 1, compare);
}

void q3sort(void *buf, size_t size, int l, int r, int (*compare)(void const *, void const *)) {
	if(r <= l)
		return;
	int i = l - 1, j = r;
	int p = l - 1, q = r;
	int k;

	while(1) {
		i++;
		while(compare((char*)buf + size * i, (char*)buf + size * r) < 0) { // Swap me
			i++;
		}
		j--;
		while(compare((char*)buf + size * r, (char*)buf + size * j) < 0) {
			if(j == l) {
				break;
			}
			j--;
		}

		if(i >= j) break; // Out of order

		exch(buf, i, j, size);
		if(compare((char*)buf + size * i, (char*)buf + size * r) == 0) {
			exch(buf, ++p, i, size);
		}
		if(compare((char*)buf + size * j, (char*)buf + size * r) == 0) {
			exch(buf, --q, j, size);
		}
	}

	exch(buf, i, r, size);
	j = i - 1;
	i = i + 1;
	
	for(k = l; k <= p; k++)
		exch(buf, k, j--, size);
	for(k = r - 1; k >= q; k--)
		exch(buf, k, i++, size);
	q3sort(buf, size, l, j, compare);
	q3sort(buf, size, i, r, compare);
}

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

void* findMaxSizeOfDuplicateSet(void *buf, size_t size, size_t total, int (*compare)(void const *a, void const *b)) {
	char *temp, *result;
	int counter = 0, i, maxCount = -1;

	if(total == 0 || size < 0 || buf == NULL)
		return NULL; // Cannot find the item element

	if((temp = myMalloc(size, total)) == NULL) {
		return NULL;
	}

	if((result = myMalloc(size, total)) == NULL) {
		return NULL;
	}

	mySort(buf, size, total, compare);

	memcpy(temp, buf, size);

	for(i = 0; i < total; i++) {
		if(compare(buf + i * size, temp) == 0) {
			counter++;
		} else {
			memcpy(temp, buf + i * size, size);
			counter = 1;
		}

		if(counter > maxCount) {
			maxCount = counter;
			memcpy(result, buf + i * size, size);
		}
	}

	free(temp);
	return result;
}

int* findMaxDuplicateSet(void *buf, size_t size, size_t total, int *counter, 
	void const *maxNumber, int (*compare)(void const *a, void const *b)) {

	int* result;
	int i;

	*counter = 0;

	if(total == 0 || size < 0 || buf == NULL)
		return NULL; // Cannot find the item element

	if((result = myMalloc(size, total)) == NULL)
		return NULL;

	mySort(buf, size, total, compare);

	for(i = 0; i < total; i++) {
		if(compare(buf + i * size, maxNumber) == 0) {
			result[(*counter)++] = i;
		}
	}

	return result;
}