#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLENGTH 100

int main()
{
  int i, n;
  char str[MAXLENGTH];
  int a[26];
  for(i=0; i<26; i++) a[i] = 0;

  printf("Hay nhap chuoi cac ky tu chu cai: "); gets(str);
  n = strlen(str);
  for(i=0; i<n; i++)
    {
      if(isalpha(str[i]))
	{
	  str[i] = toupper(str[i]);
	  a[str[i] - 'A']++;
	}
    }
  for(i=0; i<26; i++)
    if(a[i] != 0) printf("Chu cai %c xuat hien %d lan.\n", 'A'+i, a[i]);
  return 0;
}
