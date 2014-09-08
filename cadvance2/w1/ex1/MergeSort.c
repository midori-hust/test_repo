#include "MergeSort.h"

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
	int i, j, min, tmp;

	for(i=0; i < n-1; i++) {
		min = i;
		for(j = i+1; j <= n-1; j++) {
			if(a[j] < a[min])
				min = j;
		}
		swap(&a[i], &a[j]);
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

void quickSort(int *a, int left, int right) {
	int pivot, i, j;
	int temp;

	if(left<right) {
		i = left;
		j = right + 1;
		pivot = a[left];

		while(i<j) {
			while((a[i] <= a[pivot]) && i < right)
				i++;
			while(a[j] > a[pivot])
				j--;
			if(i<j)
				swap(&a[i], &a[j]);	
		}
	}
	swap(&a[pivot], &a[j]);
	quickSort(a, left, j-1);
	quickSort(a, j+1, right);
}