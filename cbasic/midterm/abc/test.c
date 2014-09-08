#include "midterm.h"

int main()
{
  struct bus_info busList[MAXLENGTH];
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
  while(1)
    {
      ch = menu();
      switch(ch)
	{
	case '1':
	  continue;
	case '2':
	  continue;
	case '3':
	  continue;
	case '4':
	  continue;
	case '5':
	  break;


	}
    }


  return 0;
}
