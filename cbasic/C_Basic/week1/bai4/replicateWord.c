/*
Viết 1 chương trình dòng lệnh nhận 1 xâu( không dấu cách) và 1 số nguyên dương n, sau đó hiển thị xâu đó n lần. Ví dụ: ./replicate go 7 -> kết quả: gogogogogogogo
*/

#include<stdio.h>

int main(int argc, char *argv[])
{
  if (argc != 3) 
    {
      printf("\nWrong number of arguments!\n");
      printf("Usage: ./replicateWord <word> <number>\n");
      printf("Please redo.\n\n");
    }
  else
    {
      printf("\n\tReplicate Word Program\n");

      int n = atoi(argv[2]);

      printf("Replicate \"%s\" %d times: ",argv[1],n);
   
      int i;
      for(i = 0; i < n; i++)
		printf("%s",argv[1]);
      printf("\n\n");
    }
  return 0;
}
