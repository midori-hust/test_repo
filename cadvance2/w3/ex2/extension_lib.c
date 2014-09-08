#include "extension_lib.h"

void sort(int *a, int l, int r) {
	// We choose the most right element as pivot

	if(r <= l)
		return;
	int i = l - 1, j = r;
	int p = l - 1, q = r;
	int k;

	while(1) {
		while(a[++i] < a[r]); // Swap me
		while(a[r] < a[--j])
			if(j == l)
				break;

		if(i >= j) break; // Out of order

		exch(a, i, j);
		if(a[i] == a[r]) 
			exch(a, ++p, i);
		if(a[j] == a[r]) 
			exch(a, --q, j);
	}

	exch(a, i, r);
	j = i - 1;
	i = i + 1;
	
	for(k = l; k <= p; k++)
		exch(a, k, j--);
	for(k = r - 1; k >= q; k--)
		exch(a, k, i++);
	sort(a, l, j);
	sort(a, i, r);
}

void exch(int *a, int i, int j) {
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void genTestData(int *a, int amount) {
	int i;

	srand(time(NULL));
	for(i = 0; i < amount; i++) {
		a[i] = rand() % RANDOM_RANGE;
	}
}

void printArray(int *a, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("a[%d] = %d\n", i, a[i]);
	}
}

int* mallocIntArray(int amount) {
	int *array;

	if((array = (int*) malloc((amount + 1) * sizeof(int))) == NULL) {
		printf("Cannot allocated memory\n");
		return NULL;
	}
	return array;
}

int intCompare(void const* x, void const* y) {
	int m, n;

	m = *((int*)x);
	n = *((int*)y);

	if(m == n)
		return 0;
	return m < n ? 1 : -1;
}

int solve() {
	int *array;
	clock_t begin, end; 
	double measureTime;

	if((array = mallocIntArray(MAX)) == NULL) {
		return 1;
	}
	printf("The size of data: %d\n", MAX);

	genTestData(array, MAX);
	begin = clock();
	sort(array, 0, MAX - 1);
	end = clock();
	printf("Quick sort three-ways' execute time: %f s\n", (double)(end - begin) / CLOCKS_PER_SEC);
	// printArray(array, MAX);

	genTestData(array, MAX);
	begin = clock();
	qsort(array, MAX, sizeof(int), intCompare);
	// quicksortViet(array, 0, MAX -1);
	// quickSort(array, 0, MAX - 1);
	// quickSortMedian(array, 0, MAX - 1);
	end = clock();
	printf("Quick sort two-ways' execute time: %f s\n", (double)(end - begin) / CLOCKS_PER_SEC);

	free(array);
	return 0;
}

int choosePivot(int left, int right) {
	return (left + right) / 2;
}

void quickSort(int *a, int left, int right) {
	int pivot, i, j;

	if(left < right) {
		swap(&a[left], &a[choosePivot(left, right)]);
		pivot = a[left];
		i = left + 1;
		j = right;

		while(i <= j) {
			while((a[i] <= pivot) && (i <= right))
				i++;
			while((a[j] > pivot) && (j >= left))
				j--;
			if(i < j)
				swap(&a[i], &a[j]);	
		}
		swap(&a[left], &a[j]);
		quickSort(a, left, j - 1);
		quickSort(a, j + 1, right);
	}
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void quickSortMedian(int *a, int left, int right) {
	int pivot, i, j;
	int temp;

	if (left + 10 <= right) {
		pivot = a[median3(a, left, right)];
		i = left + 1;
		j = right;

		while(i <= j) {
			while((a[i] <= pivot) && (i <= right))
				i++;
			while((a[j] > pivot) && (j >= left))
				j--;
			if(i < j)
				swap(&a[i], &a[j]);	
		}
		swap(&a[left], &a[j]);
		quickSort(a, left, j - 1);
		quickSort(a, j + 1, right);

	} else {
		insertionSort(a, right - left + 1);
	}
}

int median3(int *a, int left, int right) {
	int center = (left + right) / 2;
	if(a[center] < a[left])
		swap(&a[left], &a[center]);
	if(a[right] < a[left])
		swap(&a[left], &a[right]);
	if(a[right] < a[center])
		swap(&a[center], &a[right]);

	//swap(&a[center], &a[right - 1]);
	swap(&a[center], &a[left]);
	return left;
}

void insertionSort(int *a, int n) {
	int i, j;

	for(i = 1; i < n; i++) {
		j = i;
		while ((j > 0) && (a[j-1] > a[j])) {
			swap(&a[j], &a[j-1]);
			j--;
		}
	}
}

void quicksortViet(int a[], int l, int r) {
  int key = a[(l + r)/2];
  int i = l, j = r;

  while(i <= j) {
    while(a[i] < key) i++;
    while(a[j] > key) j--;

    if(i <= j) {
      if (i < j)
          exch(a, i, j);
      i++;
      j--;
    }
  }

  if (l < j) quicksortViet(a, l, j);
  if (i < r) quicksortViet(a, i, r);
}