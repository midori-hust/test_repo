#include <stdio.h>
#include <stdlib.h>

void inputArray(int a[], int n){
	int i;

	for(i = 0; i<n ; i++){
		printf("Input element # %d \n", i+1);
		a[i] = getInt();
	}
}


void printfArray(int a[], int n){
	int i;

	printf("List number \n");
	for(i=0 ; i< n; i++)
		printf("%d \t", a[i]);
	printf("\n");
}

int getIntLimit(int low, int high){
	int result;

	while (1){
		result = getInt();
		if((result <high )	&&	( result > low)) 
			return result;
	}
}

int getInt(){
	int i;

	while(1){
		if(scanf("%d", &i)==1) {
			while(getchar() != '\n');	
			return i;
		}
		printf("Input Number Interger\n");
		while(getchar() != '\n');
	}
}

void swapInt(int *a, int *b){
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void reverseArray(int a[], int n){
	int i ;

	for(i= 0 ; i< n/2; i++){
		swapInt(&a[i], &a[n -1 - i]);
	}
}

int main(){
	int *a;
	int n;

	printf("Input size of Array:\n");
	n= getIntLimit(1,100);

	a = (int *) malloc (n*sizeof(int));
	if(a == NULL ) {
		printf("cap phat bo nho khong thanh cong\n");
		return 0;
	}

	inputArray(a, n);
	printfArray(a, n);
	reverseArray(a, n);
	printfArray(a, n);

	free(a);
	return 0;
}