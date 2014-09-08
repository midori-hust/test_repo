#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define max 10000
#define maxlength 100
#define maxlengthword 50

 

main()
{
  char* input = "Toi la Pham Duy hung";
  char buff[maxlength]; 
  int compare_result; 
  int j=0;
  int i;
  printf("0");
  FILE *f;  
  char filename3[] = "stopw.txt";  
  printf("0"); 
  if((f = fopen(filename3,"r")) == NULL)  
    {  
      printf("Can not open %s!\n", filename3);  
      return 0;  
    }  
  printf("0");
  int n=strlen(input);   
  for(j=0; j<n-1; j++)
    {
      if (input[j]>='A' && input[j]<='Z') input[j]+=32;
    }
  printf("%s", input); 
  /* while (!feof(f))   */
  /*   {   */
  /*     fscanf(f, "%s", buff);  */
  /*     compare_result = strcmp(input, buff);  */
  /*   }   */
  /* fclose(f);  */
  /* return 0; */
       

  /* check =  instopwords(input); */
  /* printf("%d", check); */
  /* return 0; */
}

/* int instopwords(char* input)  */
/*  {  */

/*        return compare_result; */
/*  } */ 
