#include <stdio.h>

void printArray(int A[], int n);
int paratiton(int A[], int left, int right);
void swap (int *p1, int *p2);
void quickSort(int A[], int left, int right);

main(){
	int A[100],i, n;

	printf("\nMax length = ");
	scanf("%d", &n);
	printf("\nInsert Elemet of Array\n ");

	for(i = 0; i < n; scanf("%d", &A[i]), ++i);

	printArray(A,n);
	quickSort(A,0,n-1);
	printArray(A,n);
	
}

void printArray(int A[], int n){
	int i;

	for(i = 0; i < n; ++i)
		printf(" %d", A[i]);

	printf("\n");
	
}

void swap(int *p1, int *p2){
	int p = *p1;
	*p1 = *p2;
	*p2 = p;
}

int paratiton(int A[], int left, int right ){
	int pivot;
	int i, j;

	pivot = A[left];
	
	i = left + 1;
	j = right;
	while(i < j){
		while((i < j)  && (A[i] < pivot)) ++i;//tim phan tu >= pivot
		
		while((j > i) && (A[j] > pivot)) --j;//tim phan tu <= pivot
		
		swap(&A[i],&A[j]);
		++i;
		--j;
	}
	
	swap(&A[left], &A[j]);

	return j;
}

void quickSort(int A[], int left, int right){
	int pivot;

	pivot = paratiton(A, left, right);

	if(left < pivot)
		quickSort(A, left, pivot - 1);
	if(right > pivot)
		quickSort(A, pivot + 1, right);

}