/*
Viết 1 chương trình dòng lệnh đọc 1 file văn bản và thêm 1 dòng trống
giữa các dòng của file văn bản đó rồi hiển thị kết quả lên màn hình.
*/

#include <stdio.h>

//===============================

void enter(FILE *fin,FILE *fout)
{
  int c;

  while ((c = fgetc(fin)) != EOF)
    {
      fputc(c, fout);
      if(c == '\n') 
	fputc(c, fout);
    }
}

//============Ham chinh==========//

main(int argc, char *argv[])
{
  FILE *fptr1,*fptr2;

  if(argc != 3)
    {
      printf("\nWrong arguments!\n");
      printf("Usage: ./spaceLine <filename1> <filename2>\n");
      printf("Please redo.\n\n");
    }
  else
    {    
      printf("\n\tSapce Line Program\n");
      printf("The contents of infile will be double-spaced, and written to outfile.\n");
      printf("Input file: %s\n",argv[1]); 
      printf("Output file: %s\n\n",argv[2]); 

      if ((fptr1 = fopen(argv[1], "r")) == NULL)
	printf("Cannot open %s.\n", argv[1]);
      else 
        if ((fptr2 = fopen(argv[2], "w")) == NULL)
	  printf("Cannot open %s.\n\n", argv[2]);
	else
	  {
	    enter(fptr1,fptr2);
	    fclose(fptr1);
	    fclose(fptr2);  
	  }
    }	
  return 0;
}
  
