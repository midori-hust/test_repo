#include <stdio.h>

void ma_hoa(FILE *fin, int k)
{
  char c;
  
  while ((c=fgetc(fin)) != EOF)
    {
      if ((c <= 'z')  &&  (c >= 'a')) 
	{
	  c= c + k;
	  if(c > 'z') 
	    c = c-'z'-1 +'a';
	}
      else if ((c <= 'Z')  &&  (c >= 'A')) 
	{
	  c= c + k;
	  if(c>'Z') 
	    c = c-'Z'-1 +'A';
	}
      putchar(c);	 
    }
}

main(int argc, char *argv[])
{
  FILE *fptr; 

  if(argc != 3)
    printf("Wrong arguments!\n");
  else
    {
      if ((fptr = fopen(argv[1], "r")) == NULL)
	printf("Cannot open %s.\n",argv[1]);
      else  ma_hoa(fptr,atoi(argv[2]));
    }
  fclose(fptr);
  return 0;
}
