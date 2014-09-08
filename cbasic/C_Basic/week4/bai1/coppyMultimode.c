/*
Viết chương trình coppy-multimode với giao diện dòng lệnh cho phép:
+ Sao chép theo kí tự
+ Sao chép theo dòng
+ Sao chép theo block – kích thước tùy chọn(3byte, 5byte,…)
Sau khi kết thúc, in ra thời gian để so sánh.
*Chú ý: chọn file nguồn là file văn bản lớn(640kb trở lên).
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//=================================

void charReadWrite(FILE *fin,FILE *fout)
{
  char c;

  while((c = fgetc(fin)) != EOF)
    fputc(c,fout);    
  rewind(fin);
}

//====================================

void lineReadWrite(FILE *fin,FILE *fout)
{
  char s[81];

  while(fgets(s,80,fin) != NULL)
     fputs(s,fout);
  rewind(fin);
}

//======================================= 

void BlockReadWrite(FILE *fin, FILE *fout,int n)
{
  int num;
  char buff[n + 1];

  while (!feof(fin))
    {
      num = fread(buff, sizeof(char),n, fin);
      buff[num * sizeof(char)] = '\0';
      fwrite(buff, sizeof(char), num, fout);
    }
  rewind(fin);
}

//===========================

int menu()
{
  int c;

  printf("\n\t==========================");
  printf("\n\tCoppy-multimode program");
  printf("\n\t\t1. Coppy with char.");
  printf("\n\t\t2. Coppy with line.");
  printf("\n\t\t3. Coppy with Block.");
  printf("\n\t\t4. Exit.");
  printf("\n\t==========================");
  printf("\n\tYou choose:.......");
  scanf("%d",&c);

  return c;
}

//============Ham chinh===========//

main()
{
  FILE *f1,*f2;
  int quit = 0,choice,n;
  clock_t start,finish;
  double time;
  
  if((f1 = fopen("source.txt","r")) == NULL)
    printf("Cannot open file %s.\n","source.txt");
  else
    {
      if((f2 = fopen("result.txt","w")) == NULL)
	printf("Cannot open file %s.\n","result.txt");
      else
	{
	  while(quit == 0)
	    {
	      choice = menu();
	      switch(choice)
		{
		  
		case 1: start = clock();
		        charReadWrite(f1,f2);
		        finish = clock();
			time = ((double)(finish - start)) / CLOCKS_PER_SEC;
			printf("Time to coppy by char: %.2lf\n", time);
			time = 0;
			break;

		case 2: start = clock();
                        lineReadWrite(f1,f2);
			finish = clock();
			time = ((double)(finish - start)) / CLOCKS_PER_SEC;
			printf("Time to coppy by line: %.2lf\n", time);
			time = 0;
			break;

		case 3:  printf("How many bytes do you want to coppy? ");
		         scanf("%d",&n);
			 start = clock();
			 BlockReadWrite(f1,f2,n);
			 finish = clock();
			 time = ((double)(finish - start)) / CLOCKS_PER_SEC;
			 printf("Time to run this process: %.2lf\n", time);
			 time = 0;
			 break;

		case 4:  printf("Have funny times!!\n");quit++;break;
		  
		default: printf("Please choose from 1 to 4.\n");

		}
	    }
	  fclose(f1);
	  fclose(f2);
	}
    }
  return 0;
}
