
#include "Global.h"

int checkUser( )
{
  FILE * pFile;
  long lSize;
  char * buffer;
  size_t result;

  pFile = fopen ("/home/anhlht/gtk-rungchuongvang1/src/Database.txt", "r" );
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
  printf(" %s ",buffer);
  /* the whole file is now loaded in the memory buffer. */

  // terminate
  fclose (pFile);
  free (buffer);

   

 }
