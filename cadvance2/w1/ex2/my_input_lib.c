#include "my_input_lib.h"

int menu() {
    int option;

    printf("\n\t\tMENU\n");
    printf("\t1. Option 1\n");
    printf("\t2. Option 2\n");
    printf("\t3. Option 3\n");
    printf("\t4. Option 4\n");
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
    printf("This is not a float number. Please retype the input: ");
    while(getchar() != '\n');
  }

  return result;
}

void handleMenu() {
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