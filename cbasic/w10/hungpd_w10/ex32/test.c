
#include "midterm.h"

int main()
{
  ProductInfo buffer;
  ProductInfo productList[MAXLENGTH];
  int id;
  char name[MAXLENGTH];
  char decription[MAXLENGTH];
  char ch2;
  int i = 0;
  int flag = 0;
  int j;
  int result;
  int last = 100;

  FILE *f;
  char filename[MAXLENGTH] = "sanpham.txt";

  if ((f = fopen(filename, "r+")) == NULL)
    {
      printf("Khong mo duoc file %s.\n", filename);
      return 1;
    }

  char ch;
  while(1)
    {
      ch = menu();
      switch(ch)
	{
	case '1':
	  printf("Ban chon %c.\n", ch);
	  while(1)
	    {
	      printf("Nhap vao ban phim thong tin cua 1 san pham (nhap khac so o ma san pham de ket thuc):\n\n");
	      printf("Nhap tu ban phim ma san pham (trong pham vi 101 toi 500, san pham sau co ma san pham cao hon san pham truoc): ");
	      if(scanf("%d", &id) == 0)
		{
		  while((ch2 = getchar()) != '\n');
		  break;
		}
	      if((id < 101) || (id > 500) || (id < last))
		{
		  printf("Ban da nhap trai dieu kien ma san pham.\n\n");
		  continue;
		}
	      else last = id;
	       
	      printf("Ten san pham: ");
	      while((ch2 = getchar()) != '\n');
	      gets(name);
	     
	      printf("Mo ta san pham: ");
	      gets(decription);

	      fprintf(f, "%d\n", id);
	      fputs(name, f);
	      fputs("\n", f);
	      fputs(decription, f);
	      fputs("\n", f);
	    }
	  rewind(f);
	  continue;

	case '2':
	  printf("Ban chon %c.\n", ch);
 	  printf("Danh sach cac phan tu trong file: \n");
	  while(1)
	    {
	      fscanf(f, "%d\n", &productList[i].id);
	      fgets(productList[i].name, MAXLENGTH, f);
	      fgets(productList[i].decription, MAXLENGTH, f);

	      productList[i].name[strlen(productList[i].name)-1] = '\0';
	      productList[i].decription[strlen(productList[i].decription)-1] = '\0';
	      if(feof(f)) break;
	      i++;
	      flag = 1;
	    }
	
	  if(flag == 0) 
	    {
	      printf("File trong!\n");
	    }
	  else
	    {
	      for(j=0; j<i; j++)
		{
		  printf("%d\n%s\n%s\n\n", productList[j].id, productList[j].name, productList[j].decription);
		}
	      flag = 0;
	    }
	  rewind(f);
	  continue;

	case '3':
	  printf("Ban chon %c.\n", ch);
	  printf("Hay nhap vao ma san pham ma ban can tim: ");
	  if(scanf("%d", &id) != 0)
	    {
	      while((ch2 = getchar()) != '\n');
	      result = BinarySearch(productList, id, i);
	      if(result == -1) printf("Khong tim thay!\n");
	      else
		{
		  printf("San pham ma ban can tim:\nTen: %s\nID: %d\nMo ta: %s\n", productList[result].name, productList[result].id, productList[result].decription);
		}
	    }
	  else
	    {
	      while((ch2 = getchar()) != '\n');
	      printf("Ban da nhap sai ID.\n");
	    }
	  continue;

	case '4':
	  printf("Ban chon %c.\n", ch);
	  printf("Chuong trinh ket thuc!\n");
	  break;

	default:
	  printf("Ban da chon sai lua chon, xin vui long chon lai!\n");
	  continue;
	}
      break;
    }

  fclose(f);
  return 0;
}
