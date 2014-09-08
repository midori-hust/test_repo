/*
Viết chương trình dòng lệnh đọc 1 file và hiển thị nội dung file lên màn hình theo 2 cách:
+ Hiển thị toàn bộ file: ./mycat <filename>
+ Hiển thị theo trang:  ./mycat <file name> <-p>   (25 dòng/trang)
*/

#include <stdio.h>

//====================================

void cat(FILE *fin)
{
  char buff[80]; 

  while (fgets(buff, 80, fin) != NULL)
    printf("%s", buff);	
  rewind(fin);
}

//====================================

void catp(FILE *fin)
{
  char buff[80]; 
  int dem = 0;

  while (fgets(buff, 80, fin) != NULL)
    {
      if((dem % 25) == 0) 
	printf("\nPage %d:\n\n",dem/25 + 1);
      printf("%s", buff);	
      dem++;
    }
  rewind(fin);
}

//========Ham chinh========//

main(int argc, char *argv[])
{
  FILE *fptr;
  int dem = 0;
  
  if((argc > 3) || (argc ==1)) 
    {
      printf("\nWrong arguments!\n");
      printf("   usage: ./mycp <FileName>\n");
      printf("or usage: ./mycp <FileName> <-p>\n");
      printf("Please redo!\n\n");
    }

  else
    {
      printf("\n\tMycat Program\n");
      printf("Input file: %s\n\n",argv[1]);
      if ((fptr = fopen(argv[1], "r")) == NULL)
	printf("Cannot open %s.\n\n", argv[1]);
      else
	{
	  if(argc == 2) cat(fptr);
	  else if(strcmp(argv[2],"-p") != 0) 
	    printf("Wrong argument! \n usage: ./mycat <FileName> <-p>\n");
	  else catp(fptr);
	  fclose(fptr);	
	}
    }
  return 0;
 }
