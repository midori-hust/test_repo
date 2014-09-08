#include "sort_lib.h"

void merge(int *a, int low, int mid, int high) {
	int b[MAXLENGTH];
	int i = low, j = mid + 1, k = 0;

	while ( i<=mid && j<=high ) {
		if(a[i] <= a[j]) {
			b[k++] = a[i++];
		} else {
			b[k++] = a[j++];
		}
	}

	while (i<=mid) {
		b[k++] = a[i++];
	}

	while (j<=high) {
		b[k++] = a[j++];
	}

	k--;
	while(k>=0) {
		a[low+k] = b[k];
		k--;
	}
}

void mergeSort(int *a, int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		mergeSort(a, low, mid);
		mergeSort(a, mid + 1, high);
		merge(a, low, mid, high);
	}
}

void selection(int *a, int n) {
	int i, j;
	int iMin;

	for(j = 0; j < n - 1; j++) {
		iMin = j;
		for(i = j + 1; i < n; i++) {
			if(a[i] < a[iMin])
				iMin = i;
		}

		if(iMin != j)
			swap(&a[j], &a[iMin]);
	}
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(int *a, int n) {
	int tmp;
	int i, j;

	for(i=0; i<n; i++) {
		for(j=0; j < (n-i-1); j++) {
			if(a[j] > a[j+1]) 
				swap(&a[j], &a[j+1]);
		}
	}
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

void printArray(int *a, int n) {
	int i;

	printf("The array's elements:\n");
	for(i = 0; i < n; i++) {
		printf("a[%d] = %d\n", i, a[i]);
	}
}