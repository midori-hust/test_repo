/*
Viết chương trình dòng lệnh đọc 1 file và hiển thị nội dung file đó ra màn hình, đầu mỗi dòng hiển thị có ghi số thứ tự của dòng.
*/

#include <stdio.h>

//================================

void numbering(FILE *fin)
{
  char buff[25]; 
  int count = 0;

  while (fgets(buff,25, fin) != NULL) 
    {
      count++;
      printf("%d %s", count, buff);
    }	
}

//============Ham chinh===========//

main(int argc, char *argv[])
 {
   FILE *fptr;

   if(argc != 2)
     {
       printf("\nWrong arguments!\n");
       printf("Usage: ./indicateLine <filename>");
       printf("\nPlease redo.\n\n");
     }
   else
     {
       printf("\n\tIndicate Line Program\n");
       printf("Input file: %s\n\n", argv[1]);

       if ((fptr = fopen(argv[1], "r")) == NULL)
	 printf("Cannot open %s.\n\n", argv[1]);
       else 
		{
		  numbering(fptr);
		  fclose(fptr);
		}	
     }

   return 0;

}
