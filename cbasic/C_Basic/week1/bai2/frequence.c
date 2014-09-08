/*
Viết 1 chương trình dòng lệnh, nhập vào 1 chuỗi không có khoảng trắng và đếm tần suất xuất hiện của các chữ cái trong chuỗi đó.
*/

#include<stdio.h>
#include<string.h>

#define ALPHABET_LEN 26

int main (int argc, char *argv[])
{
  int i = 0;
  int count[ALPHABET_LEN] = {};
  char s[100];

  if (argc != 2)
    { 
      printf("\nWrong numbers of arguments! \n");
      printf("Usage: ./frequence <string>\n");
      printf("Please redo.\n\n");
    }
  else
    {
      printf("\n\tLetter Frequence Program");
      printf("\n  String \"%s\":\n",argv[1]);
      
      strcpy(s,argv[1]);

      for(i = 0; i < 26; i++)
	{
	  if (s[i] <= 'z' && s[i] >= 'a')
	    ++count[s[i]-'a'];
	  if (s[i] <= 'Z' && s[i] >= 'A')
	    ++count[s[i]-'A'];
	}
    }
  for(i = 0; i < 26; i++)
    {
      if (count[i] != 0)
		printf("\'%c\' appears %d times\n", i+'a', count[i]);
    }
  return 0;
}
