#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100

char* str_cat(char *s1, char *s2)
{
  int n, i;
  char *str;
  n = strlen(s1) + strlen(s2);

  str = (char*)malloc((n+1)*sizeof(char));
  if(str==NULL)
    {
      printf("Memory allocation failed!\n");
      return NULL;
    }

  for(i=0; i<strlen(s1); i++) str[i]=s1[i];
  for(i=0; i<strlen(s2); i++) str[i+strlen(s1)] = s2[i];
  str[n]='\0';

  return str;
}

int main()
{
  char s1[MAXLENGTH], s2[MAXLENGTH];
  char *str;

  printf("Hay nhap xau s1: "); gets(s1);
  printf("Hay nhap xau s2: "); gets(s2);
  str =  str_cat(s1,s2);
  printf("2 xau tren da duoc gop lai thanh: %s\n", str);
  free(str);
  return 0;
}
