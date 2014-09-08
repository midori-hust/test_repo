#include "linklist.h"

int main() {
  int option, option2, id, i;
  elementType buff;
  char name[MAXLENGTH];
  float grade;
  node *temp;
  FILE *f1, *f2;
  int flag = 0;
  char filename1[] = "DSSV.dat";
  char filename2[] = "SAPXEP.dat";
  node *counter;

  if((f1 = fopen(filename1, "r+")) == NULL) {
    printf("Cannot open %s\n", filename1);
    return 1;
  }

  if((f2 = fopen(filename2, "w+")) == NULL) {
    printf("Cannot open %s\n", filename2);
    return 1;
  }

  while(1) {
    option = menu();
    switch(option) {

    case 1:
      printf("You choose option #%d\n", option);
      getStudentInfo(f1);
      printf("Save to %s\nDone!\n\n", filename1);
      flag = 1;
      continue;

    case 2:
      printf("You choose option #%d\n", option);
      if(root == NULL) {
	rewind(f1);
	while(1) {
	  fread(&buff, sizeof(elementType), 1, f1);
	  if(feof(f1)) break;
	  insertTop(buff.id, buff.name, buff.grade);
	}
	printf("\nThe list before sorting:\n");
	displayList();
	sortList();
	printf("\n\nThe list after sorting:\n");
	displayList();
	for(counter = root; counter != NULL; counter = counter->next) {
	  fwrite(&counter->element, sizeof(elementType), 1, f2);
	}
	printf("Save to %s\nDone!\n\n", filename2);
	flag = 1;
      }
      else {
	printf("This function was used.\n");
      }
      continue;

    case 3:
      if(root != NULL) {
	printf("You choose option #%d\n", option);
	printf("Enter the student id which you want to edit:\n");
	while(scanf("%d", &id) != 1) {
	  printf("Wrong input! Please retry\n");
	  while(getchar() != '\n');
	}
	while(1) {
	  option2 = menu2();
	  switch(option2) {
	  case 1:
	    while(1) {
	      printf("Enter the information of student (student ID=0 to end this action):\n");
	      printf("Student ID: ");
	      while(scanf("%d", &id) != 1) {
		printf("Wrong input! Please retry\n");
		while(getchar() != '\n');
	      }
	      while(getchar() != '\n');
	      if(id == 0) break;
	      if(id <0) {
		printf("ID shound not be less than zero\n");
		continue;
	      }
	      printf("Student name: ");
	      gets(name);
	      while(1) {
		printf("Student grade: ");
		while(scanf("%f", &grade) != 1) {
		  printf("Wrong input! Please retry\n");
		  while(getchar() != '\n');
		}
		while(getchar() != '\n');
		if(grade<=10 && grade>=0) break;
		printf("Wrong input! Please retry.\n");
	      }
	      insertTop(id, name, grade);
	    }
	    break;
	  case 2:
	    deleteNode(id);
	    break;
	  case 3:
	    while(1) {
	      printf("Please enter the new grade: ");
	      while(scanf("%f", &grade) != 1) {
		printf("Wrong input! Please retry\n");
		while(getchar() != '\n');
	      }
	      while(getchar() != '\n');
	      if(grade<=10 && grade>=0) break;
	      printf("Wrong input! Please retry.\n");
	    }
	    editGrade(id, grade);
	    break;
	  case 4:
	    printf("The members of this list:\n");
	    i=0;
	    for(counter = root; counter != NULL; counter = counter->next) {
	      if(counter->element.grade > 7) {
		printf("Student ID: %d\nStudent name: %s\nStudent grade: %f\n\n", counter->element.id, counter->element.name, counter->element.grade);
		i++;
	      }
	    }
	    printf("There are/is %d student(s) whose grade is greater than 7\n", i);
	    break;
	  case 5:
	    printf("Return to main menu\n");
	    break;
	  default:
	    printf("Wrong option! Please retry\n");
	    continue;
	  }
	  break;
	}
	printf("Done.\n");
      }
      else {
	printf("You must choose the first or second option first\n");
      }
      continue;

    case 4:
      printf("You choose option #%d\n", option);
      displayList();
      continue;

    case 5:
      printf("You choose option #%d\n", option);
      printf("Free list...\n");
      freeList();
      printf("Done.\n");
      fclose(f1);
      fclose(f2);
      printf("Program exit...\n");
      break;

    default:
      printf("You choose wrong option, please retry\n");
      continue;
    }
    break;
  }
  
  printf("CU again!\n");
  return 0;
}
