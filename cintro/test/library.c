#include "library.h"

int solve() {
  int choice;
  int n = 0;
  Result athletic[MAXLENGTH];
  int flag = 0, flag2 = 0;

  
  while(1) {
      choice = menu();

      switch(choice) {
        case 1:
        printf("You choose option %d\n", choice);

        if(flag) {
        	printf("You cannot sign up again!\n");
        	continue;
        }
        flag = 1;
		printf("How many athletic sign up for this game?\n");
		n = getInt();
        signUp(athletic, n);
        printList(athletic, n);
        continue;
        case 2:
        printf("You choose option %d\n", choice);

        if(!flag) {
        	printf("You must choose option 1 first!\n");
        	continue;
        }

        flag2 = 1;

        gameOn(athletic, n);
        printResult(athletic, n);
        continue;
        case 3:
        printf("You choose option %d\n", choice);

        if(!flag || !flag2) {
        	printf("You must choose option 1 and option 2 first!\n");
        	continue;
        }

        printf("\n\tReward!!!\n");
        giveReward(athletic, n);
        continue;
        case 4:
        printf("You choose option %d\n", choice);
        if(!flag) {
        	printf("You must choose option 1 first!\n");
        	continue;
        }
        findSuperSniper(athletic, n);
        continue;
        case 5:
        printf("You choose option %d\n", choice);
        printf("Bye bye\n");
        break;
        default:
        printf("It is not an option\n");
        continue;
      }
      break;
    }
  
	return 0;
}

void signUp(Result *athletic, int amount) {
	int i;
	int j;

	for(i = 0; i < amount; i++) {
		printf("Athletic %d:\n", i + 1);
		printf("Please enter the name of the athletic:\n");
		fgets(athletic[i].name, MAXLENGTH, stdin);
		athletic[i].name[strlen(athletic[i].name) - 1] = '\0';
		athletic[i].sumPoint = 0;
	}
}

void gameOn(Result *athletic, int amount) {
	int i, j;

	for(i = 0; i < amount; i++) {
		printf("Athletic %d:\n", i + 1);
		printf("Please enter the point of the athletic\n");
		for(j = 0; j < 5; j++) {
			printf("Point %d\n", j + 1);
			athletic[i].point[j] = getInt();
			athletic[i].sumPoint += athletic[i].point[j];
		}
	}
}

void printList(Result *athletic, int amount) {
	int i;
	int j;

	if(amount <= 0) {
		printf("There is no member in this list!\n");
	}

	for(i = 0; i < amount; i++) {
		printf("Athletic %d:\n\tName: %s\n", i, athletic[i].name);
	}
}

void printResult(Result *athletic, int amount) {
	int i;
	int j;

	if(amount <= 0) {
		printf("There is no member in this list!\n");
	}

	printf("%-20s\t%5d\t%5d\t%5d\t%5d\t%5d\n", "Athletic's name", 1, 2, 3, 4, 5);
	for(i = 0; i < amount; i++) {
		printf("%-20s", athletic[i].name);
		for(j = 0; j < 5; j++) {
			printf("\t%5d", athletic[i].point[j]);
		}
		printf("\n");
	}
}

void giveReward(Result *athletic, int amount) {
	int count = 3;
	int flag = 0;
	int i, j;

	for(i = 50; i >= 0; i--) {
		for(j = 0; j < amount; j++) {
			if(athletic[j].sumPoint == i) {
				giveAward(count, athletic, j);
				flag = 1;
			}
		}

		if(flag) {
			if(--count == 0) {
				break;
			}
			flag = 0;
		}
	}
}

void giveAward(int medal, Result *athletic, int position) {
	if(medal == 3) {
		printf("%-15s\t%7s\t%5d\n", athletic[position].name, "Gold", athletic[position].sumPoint);
		return;
	}

	if(medal == 2) {
		printf("%-15s\t%7s\t%5d\n", athletic[position].name, "Silve", athletic[position].sumPoint);
		return;
	}

	if(medal == 1) {
		printf("%-15s\t%7s\t%5d\n", athletic[position].name, "Bronze", athletic[position].sumPoint);
		return;
	}
}

void findSuperSniper(Result *athletic, int amount) {
	int i, j;
	int stage = 0;

	for(i = 0; i < amount; i++) {
		for(j = 0; j < 5; j++) {
			switch(stage) {
				case 0:
				if(athletic[i].point[j] == 10)
					stage = 1;
				break;
				case 1:
				if(athletic[i].point[j] == 10)
					stage = 2;
				else stage = 0;
				break;
				case 2:
				if(athletic[i].point[j] == 10) {
					printf("%-20s\t%5d\t%5d\t%5d\t%5d\t%5d\n", 
						athletic[i].name, 
						athletic[i].point[0], 
						athletic[i].point[1], 
						athletic[i].point[2], 
						athletic[i].point[3], 
						athletic[i].point[4]);
				}
				stage = 0;
				break;
			}
		}

		if(stage == 2) {
			stage = 0;
		}
	}
}
