/*
Viết 1 chương trình dòng lệnh đọc 1 file đầu vào source.txt, đổi chữ hoa
thành chữ thường và chữ thường thành chữ hoa. In kết quả ra màn hình và 
file sourcestas.txt
*/

#include <stdio.h>

//=======================================

void CharReadWrite(FILE *fin, FILE *fout)
{
  char c;

  while ((c = fgetc(fin)) != EOF)
    {
      if ((c <= 'z')  &&  (c >= 'a')) 
	c = c - 32;
      else
	if ((c <= 'Z')  &&  (c >= 'A')) 
	  c = c + 32;
      putchar(c);	
      fputc(c, fout);    
    }
}

//==============Ham chinh===============//

main(int argc, char *argv[])
 {
   FILE *fptr1, *fptr2;

   if(argc != 3)
     {
       printf("\nWrong arguments!\n");
       printf("Usage: ./changLetter <filename1> <filename2>\n");
       printf("Please redo!\n\n");
     }
   else
     {
       printf("\n\tChange letter program\n");
       printf("Input file: %s\n",argv[1]);
       printf("Output file: %s\n",argv[2]);
       printf("\nLetter after changing:\n");

       if ((fptr1 = fopen(argv[1], "r")) == NULL)
	 printf("Cannot open %s.\n", argv[1]);
       else if ((fptr2 = fopen(argv[2], "w")) == NULL)
	printf("Cannot open %s.\n\n", argv[2]);
       else 
	 {
	   CharReadWrite(fptr1, fptr2);
	   printf("\n");
	   fclose(fptr1);
	   fclose(fptr2);
	 }
     }
   return 0;
}
