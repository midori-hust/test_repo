#include "my_input_lib.h"

int menu() {
    int option;

    printf("\n\t\tMENU\n");
    printf("\t1. Generate new data\n");
    printf("\t2. The biggest set of linear points\n");
    printf("\t3. The biggest set of same position points\n");
    printf("\t4. Reload data\n");
    printf("\t5. Exit program\n");
    printf("\nWhich option would you like to choose?\n");

    do {
      option = getInt();
      if (option < 0 || option > 5) {
        printf("Invalid option! Please choose again!\n");
      }
    } while (option < 0 || option > 5);

    return option;
}

int getInt() {
  int result;

  while(scanf("%d",&result) != 1) {
    printf("This is not an integer number. Please retype the input: ");
    while(getchar() != '\n');
  }

  return result;
}

float getFloat() {
  float result;

  while(scanf("%f",&result) != 1) {
    printf("This is not a float number. Please retype the input:\n ");
    while(getchar() != '\n');
  }

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

int* mallocIntArray(int amount) {
  int *array;

  if((array = (int*) malloc((amount + 1) * sizeof(int))) == NULL) {
    printf("Cannot allocated memory\n");
    return NULL;
  }
  return array;
}

char* mallocString(int amount) {
  char *str;

  if((str = (char*) malloc((amount + 1) * sizeof(char))) == NULL) {
    printf("Cannot allocated memory\n");
    return NULL;
  }
  return str;
}

FILE* openFile(char *filename, char *extension) {
  FILE *fileStream;
  if((fileStream = fopen(filename, extension)) == NULL) {
    printf("Cannot open file %s\n", filename);
    return NULL;
  }
  return fileStream;
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