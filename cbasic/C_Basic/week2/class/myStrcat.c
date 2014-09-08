/*
Viết 1 chương trình nối 2 chuỗi của riêng bạn.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 25

//==============================================

char *myStrcat(char *str1, char *str2)
{
  int len1,len2;
  char *result;

  len1 = strlen(str1);
  len2 = strlen(str2);

  result = (char*)malloc((len1 + len2 + 1)*sizeof(char));
  strcpy(result,str1);
  strcpy(result + len1, str2);

  return result;
}

//==================Ham chinh===================//

main()
{
  char str1[MAX_LEN + 1], str2[MAX_LEN + 1];
  char *cat_str;
  char ch;

  printf("\n\tString Strcat Program\n ");
  printf("Please enter two strings:\n");
  
  printf("String 1: ");
  scanf("%[^\n]",str1);
  
  printf("String 2: ");
  getchar();
  scanf("%[^\n]",str2);
  
  cat_str = myStrcat(str1, str2);
  if (cat_str == NULL)
    {
      printf("Error!\n");
      return 1;
    }
  printf("The concatenation of \"%s\" and \"%s\" is:  %s\n\n", str1, str2, cat_str);     
  
  free(cat_str);
  return 0;
}
