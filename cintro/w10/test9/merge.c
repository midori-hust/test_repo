#include <stdio.h>

void printArray(int a[], int n);
void merge(int a[], int first, int mid, int last);
void mergeSort(int a[], int first, int last);

main() {
    int i, a[100], n;

    printf("\nMax length of array: ");
    scanf("%d", &n);
    // while(getchar()!= '\n');

    printf("\n-----Insert Element-----\n");
    for(i=0; i<n; ++i){
        scanf("%d", &a[i]);
        // while(getchar() != '\n');
    }

    printArray(a, n);
    mergeSort(a, 0, n-1);
    printArray(a, n);
}

void printArray(int a[], int n){
    int i;
    
    for(i=0; i<n ;++i)
        printf(" %d", a[i]);
    
    printf("\n");
}

void merge(int a[], int first, int mid, int last){
    int tempA[100], first1, first2, last1, last2, i;

    first1 = first; last1 = mid;
    first2 = mid+1; last2 = last;
    i = first1;

    for(; (first1 <= last1) && (first2 <= last2); ++i){
        if(a[first1] < a[first2]){
            tempA[i] = a[first1];
            ++first1;
        }
        else{
            tempA[i] = a[first2];
            ++first2;
        }  
    }

    for(; first1 <= last1; ++i, ++first1)
        tempA[i] = a[first1];
    for(;first2 <= last2; ++i, ++first1) // Sai o day!
       tempA[i] = a[first1]; // Sai o day!
    for(i = first; i <= last; ++i)
        a[i] = tempA[i];
}

void mergeSort(int a[], int first, int last){
    int mid;
    printf("%d - %d\n", first, last);

    if(first < last){
        mid = (first + last) / 2;
        mergeSort(a, first, mid);
        mergeSort(a ,mid + 1, last);
        merge(a, first, mid, last);
    }
}
