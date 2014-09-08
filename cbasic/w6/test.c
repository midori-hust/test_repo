#include<stdio.h>

typedef int ElementType;
int BinarySearch(ElementType A[], ElementType X, int N)
{
  int Low, Mid, High;
  Low = 0;
  High = N-1;
  while(Low <= High)
    {
      Mid = (Low + High)/2;
      if(A[Mid] <  X) Low = Mid + 1;
      else if(A[Mid] > X) High = Mid - 1;
      else return Mid; /*Found*/
    }
  return -1;
}

int main()
{
  static int A[] = {1,3,5,7,9,13,15};
  int SizeofA = sizeof(A)/sizeof(A[0]);
  int i;
  for(i=0; i<20; i++)
    printf("Binary Search of %d return %d\n", BinarySearch(A,i,SizeofA));
  return 0;

}
