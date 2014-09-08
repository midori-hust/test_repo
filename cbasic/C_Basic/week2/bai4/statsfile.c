/*
Viết chương trình dòng lệnh đọc 1 file văn bản và in ra tần suất
xuất hiện của các chữ cái trong file văn bản đó.
*/

#include <stdio.h>

#define ALPHABET_LEN 26

//========================================

void countCharacter(FILE *fin, FILE *fout)
{
  int i = 0; 
  int count[ALPHABET_LEN] = {}; 
  char c;
  
  while ((c=fgetc(fin)) != EOF)
    {
      if (c <= 'z'  &&  c >= 'a')
	++count[c - 'a'];
 	if (c <= 'Z'  &&  c >= 'A')
	  ++count[c - 'A'];
    }
  
  for (i = 0; i < 26; ++i)
    if (count[i] > 0)
      fprintf(fout,"The letter '%c' appears %d time(s).\n", 'a' + i, count[i]);
}

//================Ham chinh===============//

main(int argc, char *argv[])
 {
   FILE *fptr1, *fptr2;
   
   if(argc != 3)
     {
       printf("\nWrong arguments!\n");
       printf("Usage: ./statsfile <filename1> <filename2>\n");
       printf("Please redo!\n\n");
     }
   else
     {
       printf("\n\tStatsfile Program\n");
       printf("All letter-frequence of file '%s' is in file '%s'.\n\n",argv[1],argv[2]);
       if ((fptr1 = fopen(argv[1], "r")) == NULL)
	 printf("Cannot open %s.\n", argv[1]);
       else if ((fptr2 = fopen(argv[2], "w")) == NULL)
	 printf("Cannot open %s.\n\n",argv[2]);
       else
	 {
	   countCharacter(fptr1, fptr2);
	   fclose(fptr1);
	   fclose(fptr2);
	 }
     }
   return 0;
}
