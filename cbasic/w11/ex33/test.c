#include "bst.h"

int main(int argc, char* argv[])
{
  FILE *f;
  char buffer[MAXLENGTH];
  Node *Root;
  Root = NULL;
  Node *item;
  char str[MAXLENGTH];
  int i;
  int flag = 0;

  if ((f = fopen(argv[1], "r+")) == NULL)
    {
      printf("Khong mo duoc file %s.\n", argv[1]);
      return 1;
    }

  printf("\nNoi dung cua file %s:\n", argv[1]);
  while(!feof(f))
    {
      fgets(buffer, MAXLENGTH, f);
      if(feof(f)) 
       	{ 
       	  printf("\n"); 
       	  break; 
	} 
      printf("%s", buffer);
    }
  
  rewind(f);
  while((fscanf(f, "%s", buffer)) != EOF)
    {
      for(i=0; i<strlen(buffer); i++)
	{
	  if(!isalnum(buffer[i]))
	    {
	      flag = 1;
	      break;
	    }
	}
      if(flag == 0)
	InsertNode(buffer, &Root);
      else
	{
	  flag = 0;
	  continue;
	}
    }

  printf("Hay nhap vao 1 tu can tim kiem: ");
  scanf("%s", str);
  char ch;
  while((ch = getchar()) != '\n');
  item = Search(str, Root);
  if(item != NULL)
    {
      printf("Tu ban can tim co so lan xuat hien la %d lan.\n", item->frequency);
    }
  else
    {
      printf("Khong tim thay tu ban nhap vao.\n");
    }

  printf("Press enter to continue...");
  while((ch = getchar()) != '\n');
  printf("\nDanh sach cac tu trong file:\n");
  display(Root);

  freeTree(Root);
  fclose(f);
  return 0;
}
