
#include "Global.h"

boolean checkUser(char *username ,char *password )
{
  FILE * pFile;
  long lSize;
  char  *buffer;
  size_t result;
  _loginStr client[200];
  int i=0;
  int j=-1;
  char *ch=(char*)malloc(sizeof(100));
  
  pFile = fopen ("/home/anhlht/gtk-rungchuongvang1/src/Database.txt","r");
  if (pFile==NULL) {fputs ("File error",stderr); 
  }
  // obtain file size:
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);
  // allocate memory to contain the whole file:
  buffer = (char*) malloc (sizeof(char)*lSize);
  if (buffer == NULL) {
  fputs ("Memory error",stderr);
  }
  // copy the file into the buffer:
  result = fread (buffer,1,lSize,pFile);
  if (result != lSize) {
  fputs ("Reading error",stderr); 
  }
  
  printf("%s fdfd",buffer);
  // Get Information
 // ch=strtok(buffer," |\n");
  
  /*while(ch!=NULL)
    {
	 printf(" %s ",ch);	
	/* if(i%2==0)
	    j++;  
	 if(i%2==0)
	   strcpy(client[j].username,ch);
	 else
	   strcpy(client[j].password,ch);
	   i++;
	   printf(" %d ",j);
	   printf(" %s", client[j].username);*/
	// ch = strtok (NULL, " |\n");
   //}
   
  int k=0;
  for(k=0;k<j;k++)
    {
	  printf(" %s -> %s ",client[k].username,client[k].password);   
    }
  fclose (pFile);
  free (buffer);

   return true;

 }
