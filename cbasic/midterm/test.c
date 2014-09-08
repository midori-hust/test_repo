#include "midterm.h"

int main()
{
  int i = 0;
  int j;
  BusInfo busList[MAXLENGTH];
  int id;
  char name[MAXLENGTH];
  FILE *f;
  char filename[MAXLENGTH] = "bus.txt";

  if ((f = fopen(filename, "r")) == NULL)
    {
      printf("Khong mo duoc file %s.\n", filename);
      return 1;
    }

  char ch;
  char flag = 0;
  while(1)
    {
      ch = menu();
      switch(ch)
	{
	case '1':
	  printf("Ban chon %c\n", ch);
	  flag = 1;

	  while(1)
	    {
	      fscanf(f, "%d=", &id);
	      fgets(name, MAXLENGTH, f);
	      if(feof(f)) break;
	      name[strlen(name) - 1] = '\0';
	      busList[i].id = id;
	      strcpy(busList[i].name, name);
	      i++;
	      
	    }
	  printf("Da doc xong!\n");

	  //Hien thi danh sach mang
	  for(j=0; j<i; j++)
	    {
	      printf("Chuyen xe bus so: %d\nDiem di, diem ve: %s\n", busList[j].id, busList[j].name);
	    }

	  continue;

	case '2':
	  printf("Ban chon %c\n", ch);
	  if (flag == 0)	    
	    printf("Ban chua thuc hien thao tac 1, xin vui long thuc hien lai thao tac 1 truoc khi thuc hien thao tac nay!\n");
	  else
	    {
	      sortBusID(busList, i);
	      for(j=0; j<i; j++)
		{
		  printf("Chuyen xe bus so: %d\nDiem di, diem ve: %s\n", busList[j].id, busList[j].name);
		}
	    }
	  continue;

	case '3':
	  printf("Ban chon %c\n", ch);
	  if (flag == 0)	    
	    printf("Ban chua thuc hien thao tac 1, xin vui long thuc hien lai thao tac 1 truoc khi thuc hien thao tac nay!\n");
	  else
	    printf("0");
	  continue;

	case '4':
	  printf("Ban chon %c\n", ch);
	  if (flag == 0)	    
	    printf("Ban chua thuc hien thao tac 1, xin vui long thuc hien lai thao tac 1 truoc khi thuc hien thao tac nay!\n");
	  else
	    printf("0");
	  continue;

	case '5':
	  printf("Ban chon %c\n", ch);
	  printf("Chuong trinh ket thuc!\n");
	  break;

	default:
	  printf("Ban da nhap sai yeu cau, vui long an tu 1 toi 5 de nhap lai.\n");
	  continue;
	}
      break;
    }

  fclose(f);
  return 0;
}
