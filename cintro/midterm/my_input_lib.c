#include "my_input_lib.h"

int menu() {
    int option;

    printf("\n\t\tMENU\n");
    printf("\t1. Get student data\n");
    printf("\t2. Search\n");
    printf("\t3. Sort\n");
    printf("\t4. Exit program\n");
    printf("\nWhich option would you like to choose?\n");

    do {
      option = getInt();
      if (option < 0 || option > 4) {
        printf("Invalid option! Please choose again!\n");
      }
    } while (option < 0 || option > 4);

    return option;
}

int getInt() {
  int result;

  while(scanf("%d",&result) != 1) {
    printf("This is not an integer number. Please retype the input: ");
    while(getchar() != '\n');
  }
  while(getchar() != '\n');

  return result;
}

float getFloat() {
  float result;

  while(scanf("%f",&result) != 1) {
    printf("This is not a float number. Please retype the input: ");
    while(getchar() != '\n');
  }
  while(getchar() != '\n');
  
  return result;
}

int getContinueRequest() {
  char result;

  do {
    result = getchar();
    while(getchar() != '\n');
  } while(result != 'Y' 
    && result != 'N' 
    && result != 'y' 
    && result != 'n');

  if(result == 'Y' || result == 'y')
    return 'Y';
  if(result == 'N' || result == 'n')
    return 'N';

  return 0;
}

void* myMalloc(size_t size, size_t total) {
  char *result;

  if((result = (char*) malloc((total + 1) * size * sizeof(char))) == NULL) {
    printf("Cannot allocated memory\n");
    return NULL;
  }

  return result;
}

void handleMenu() {
  // Just the pattern
  int choice;

  while(1) {
      choice = menu();

      switch(choice) {
        case 1:
        printf("You choose option %d\n", choice);
        // TODO: Handle option
        continue;
        case 2:
        printf("You choose option %d\n", choice);
        // TODO: Handle option
        continue;
        case 3:
        printf("You choose option %d\n", choice);
        // TODO: Handle option
        continue;
        case 4:
        printf("You choose option %d\n", choice);
        // TODO: Handle option
        continue;
        case 5:
        printf("You choose option %d\n", choice);
        printf("Bye bye\n");
        // TODO: Handle option
        break;
        default:
        printf("It is not an option\n");
        continue;
      }
      break;
    }
}