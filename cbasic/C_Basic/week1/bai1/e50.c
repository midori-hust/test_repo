/*
Viết 1 chương trình dòng lệnh e50 để tính e^x có dạng:  ./e50 <number>
*/

#include<stdio.h>
#include<math.h>

main(int argc, char* argv[])
{
  double x;

  if (argc != 2) 
    {
      printf("\nWrong number of arguments!\n");
      printf("usage: ./e50 <number>\n");
      printf("Please redo.\n\n");
    }
  else 
    {
      printf("\n\tCaculate e^x program\n");
      x = atoi(argv[1]);
      printf("e^%.0lf = %lf\n\n",x,exp(x));
    }  
  return 0;
}
