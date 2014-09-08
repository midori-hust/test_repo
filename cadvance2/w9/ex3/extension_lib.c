#include "extension_lib.h"

int solve() {
	Jval array[SIZE];

	int choice;
	int type = NONE;

	while((type = menuLevel1()) != NONE) {
		handleFunction(array, type);
	}

	printf("Program executes successfully\n");

	return 0;
}

void handleFunction(Jval *array, int type) {
	int choice;
	int isCreate = 0, isSort = 0;
	int n;

	while(1) {
		choice = menuLevel2();

	    switch(choice) {
	    	case 1:
	    	printf("You choose option %d\n", choice);
	      	if((n = createData(array, type)) <= 0) {
	      		printf("Cannot create data\n");
	      		continue;
	      	}
	      	printController(array, n, type);
	      	isCreate = 1;
	      	continue;
	      	case 2:
	      	printf("You choose option %d\n", choice);
	      	if(!isCreate) {
	      		printf("You have to choose option \"Create data\" before this option!\n");
	      		continue;
	      	}
	      	sequentialSearchController(array, n, type);
	      	continue;
	      	case 3:
	     	printf("You choose option %d\n", choice);
	     	if(!isCreate) {
	      		printf("You have to choose option \"Create data\" before this option!\n");
	      		continue;
	      	}
	      	sortController(array, n, type);
	      	isSort = 1;
	        continue;
	        case 4:
	        printf("You choose option %d\n", choice);
	        if(!isCreate) {
	      		printf("You have to choose option \"Create data\" before this option!\n");
	      		continue;
	      	}
	      	if(!isSort) {
	      		printf("You have to choose option \"Sort\" before this option!\n");
	      		continue;
	      	}
	        binarySearchController(array, n, type);
	        continue;
	        case 5:
	        printf("You choose option %d\n", choice);
	        printf("Back to main menu\n");
	        return;
	        default:
	        printf("It is not an option\n");
	        continue;
	    }
	}
}


/* menu */
int menuLevel1() {
    int option;

    printf("\n\t\tMENU\n");
    printf("\t1. Integer data type\n");
    printf("\t2. String\n");
    printf("\t3. Struct\n");
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

int menuLevel2() {
    int option;

    printf("\n\t\tMENU FUNCTIONS\n");
    printf("\t1. Create data\n");
    printf("\t2. Sequential search\n");
    printf("\t3. Sort\n");
    printf("\t4. Binary search\n");
    printf("\t5. Back\n");
    printf("\nWhich option would you like to choose?\n");

    do {
      option = getInt();
      if (option < 0 || option > 5) {
        printf("Invalid option! Please choose again!\n");
      }
    } while (option < 0 || option > 5);

    return option;
}