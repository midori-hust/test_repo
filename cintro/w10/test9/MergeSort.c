#include <stdio.h>

void printArray(int A[], int n);
void merge(int A[], int first, int mid, int last);
void mergeSort(int A[], int first, int last);

main(){
	int n, i, A[100];
	
	printf("\nMax length = ");
	scanf("%d", &n);
	
	printf("\nInsert Elememt of Array:\n");
	for(i=0; i < n; ++i) 
		scanf("%d", &A[i]);

	printArray(A, n);
	mergeSort(A, 0, n-1);
	printArray(A, n);
}

void printArray(int A[], int n){
	int i;

	for(i = 0; i < n; ++i)
		printf(" %d", A[i]);
	
	printf("\n");
}

void merge(int A[], int first, int mid, int last){
	int first1, last1, first2, last2, i, tempA[100];
	
	first1 = first; last1 = mid;
	first2 = mid + 1; last2 = last;
	i = first1;

	for(; (first1 <= last1) && (first2 <= last2); ++i) {
		if(A[first1] < A[first2]){
			tempA[i] = A[first1];
			++first1;
		}
		else{
			tempA[i] = A[first2];
			++first2;
		}
	} 

	for(;first1 <= last1; ++i, ++first1)
		tempA[i] = A[first1];
	for(;first2 <= last2; ++i, ++first2)
		tempA[i] = A[first2];
	for(i = first; i <= last; ++i)
		A[i] = tempA[i];
}

void mergeSort(int A[], int first, int last){
	int mid;
	if(first < last){
		mid = (first + last)/2;
		mergeSort(A, first, mid);
		mergeSort(A, mid + 1, last);
		merge(A, first, mid, last);
	}
}