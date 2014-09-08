#include <stdio.h>

//==========================================

void merge(FILE *fin1,FILE *fin2, FILE *fout)
{
  char s1[80],s2[80];

  do
    {
      if (fgets(s1, 81, fin1) == NULL)
	s1[0] = '\0';
      if (fgets(s2, 82, fin2) == NULL)
	s2[0] = '\0';
      fprintf(fout, "%s%s", s1, s2);
    } while ((s1[0] != '\0') || (s2[0] != '\0'));
}

//============Ham chinh===========//
	
main(int argc, char *argv[])
 {
   FILE *fptr1,*fptr2,*fptr3;

   if(argc !=4)
     printf("Wrong arguments!\n");
   else
     {
       if ((fptr1 = fopen(argv[1], "r")) == NULL)
	 printf("Cannot open %s.\n", argv[1]);
       else
	 if ((fptr2 = fopen(argv[2], "r")) == NULL)
	   printf("Cannot open %s.\n", argv[2]);
	 else
	   if ((fptr3 = fopen(argv[3], "w")) == NULL)
	     printf("Cannot open %s.\n", argv[3]);
	   else
	     merge(fptr1,fptr2,fptr3);
     }
   fclose(fptr1);
   fclose(fptr2);	
   fclose(fptr3);
   return 0;
 }
