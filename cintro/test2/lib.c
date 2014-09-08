#include "lib.h"

int solve() {
	int choice;
	Result person[MAXLENGTH];
	int n;
	int case1 = 0;
	int currentIndex = 0;

	while(1) {
		switch(choice = menu()) {
			case 1:
			printf("You choose option %d\n", choice);
			getStudentInformation(person, &currentIndex);
			printStudentList(person, currentIndex);
			case1 = 1;
			continue;
			case 2:
			printf("You choose option %d\n", choice);
			if(!case1) {
				printf("Please choose case 1 first!\n");
				continue;
			}
			searching(person, currentIndex);
			continue;
			case 3:
			printf("You choose option %d\n", choice);
			if(!case1) {
				printf("Please choose case 1 first!\n");
				continue;
			}
			findScholashipStudent(person, currentIndex);
			printStudentList(person, currentIndex);
			continue;
			case 4:
			printf("You choose option %d\n", choice);
			if(!case1) {
				printf("Please choose case 1 first!\n");
				continue;
			}
			fixGrade(person, currentIndex);
			printStudentList(person, currentIndex);
			continue;
			case 5:
			printf("You choose option %d\n", choice);
			if(!case1) {
				printf("Please choose case 1 first!\n");
				continue;
			}
			deleteStudent(person, &currentIndex);
			printStudentList(person, currentIndex);
			continue;
			case 6:
			printf("You choose option %d\n", choice);
			break;
			default:
			printf("Invalid choice!\n");
			continue;
		}
		break;
	}

	return 0;
}

void getStudentInformation(Result *person, int *currentIndex) {
	int i;
	float tempGrade, tempAverage = 0;

	printf("Please enter the student ID:\n");
	fgets(person[*currentIndex].id.content, MAXLENGTH, stdin);
	person[*currentIndex].id.content[strlen(person[*currentIndex].id.content) - 1] = '\0';

	printf("Please enter the student's name:\n");
	fgets(person[*currentIndex].name.content, MAXLENGTH, stdin);
	person[*currentIndex].name.content[strlen(person[*currentIndex].name.content) - 1] = '\0';

	printf("Please enter the student's class:\n");
	fgets(person[*currentIndex].className.content, MAXLENGTH, stdin);
	person[*currentIndex].className.content[strlen(person[*currentIndex].className.content) - 1] = '\0';

	printf("Please enter the student's grade:\n");
	for(i = 0; i < 5; i++) {
		do {
			printf("Grade %d\n", i + 1);
			tempGrade = getFloat();
			if(tempGrade < 0 || tempGrade > 10) {
				printf("Please enter another grade!\n");
			}
		} while(tempGrade < 0 || tempGrade > 10);

		person[*currentIndex].score[i] = tempGrade;
	}

	calculateAverage(person, *currentIndex);
	(*currentIndex)++;
}

void searching(Result *person, int amount) {
	int choice;

	while(1) {
		switch(choice = subMenu()) {
			case 1:
			if(!searchByName(person, amount)) {
				printf("Cannot find this person\n");
			}
			continue;
			case 2:
			if(!searchByClass(person, amount)) {
				printf("Cannot find this person\n");
			}
			continue;
			case 3:
			if(!searchByAverage(person, amount)) {
				printf("Cannot find this person\n");
			}
			continue;
			case 4:
			break;
		}
		break;
	}
}

int searchByName(Result *person, int amount) {
	String tempName;
	int flag = 0;
	int i;

	printf("Please enter the student's name who you want to find\n");
	fgets(tempName.content, MAXLENGTH, stdin);
	tempName.content[strlen(tempName.content) - 1] = '\0';

	for(i = 0; i < amount; i++) {
		if(strcmp(tempName.content, person[i].name.content) == 0) {
			printf("Found!\nThe student's name: %s\n", person[i].name.content);
			printf("The average: %f\n", person[i].average);
			flag = 1;
		}
	}

	return flag;
}

int searchByClass(Result *person, int amount) {
	String tempClass;
	int flag = 0;
	int i;

	printf("Please enter the student's class which you want to find\n");
	fgets(tempClass.content, MAXLENGTH, stdin);
	tempClass.content[strlen(tempClass.content) - 1] = '\0';

	for(i = 0; i < amount; i++) {
		if(strcmp(tempClass.content, person[i].className.content) == 0) {
			printf("Found!\nThe student's name: %s\n", person[i].name.content);
			printf("The average: %f\n", person[i].average);
			flag = 1;
		}
	}

	return flag;
}

int searchByAverage(Result *person, int amount) {
	float tempGrade;
	int flag = 0;
	int i;

	printf("Please enter the student's average grade which you want to find\n");
	tempGrade = getFloat();

	for(i = 0; i < amount; i++) {
		if(tempGrade >= person[i].average) {
			printf("Found!\nThe student's name: %s\n", person[i].name.content);
			printf("The average: %f\n", person[i].average);
			flag = 1;
		}
	}

	return flag;
}

void calculateAverage(Result *person, int studentIndex) {
	person[studentIndex].average = (2 * person[studentIndex].score[0] +
				2 * person[studentIndex].score[1] +
				3 * person[studentIndex].score[2] +
				2 * person[studentIndex].score[3] +
				3 * person[studentIndex].score[4]) / 12;
}

void findScholashipStudent(Result *person, int amount) {
	int i, j, counter = 0;
	int flag = 0;

	printf("\nScholaship student list:\n");
	for(j = 10; j >= 8; j--) {
		for(i = 0; i < amount; i++) {
			if(person[i].average >= j && person[i].average < j + 1) {
				if(!hasFailSubject(person, i)) {
					printf("Student %s who has average %f\n", person[i].name.content, person[i].average);
					counter++;
					flag = 1;
				}
			}

			if(counter == 5) {
				break;
			}
		}
	}

	if(!flag) {
		printf("There is no student\n");
	}
}

int hasFailSubject(Result *person, int studentIndex) {
	int i;

	for(i = 0; i < 5; i++) {
		if(person[studentIndex].score[i] < 4) {
			return 1;
		}
	}

	return 0;
}

void fixGrade(Result *person, int amount) {
	String tempId;
	int i = 0;
	int newGrade;

	printf("Please enter the student id which you want to fix grade\n");
	fgets(tempId.content, MAXLENGTH, stdin);
	tempId.content[strlen(tempId.content) - 1] = '\0';

	do {
		printf("Please enter the subject which you want to fix grade (in range [1, 5])\n");
		i = getInt();
		if(i < 1 || i > 5) {
			printf("You must enter an integer in range [1, 5]\n");
		}
	} while(i < 1 || i > 5);
	
	do {
		printf("Please enter the new grade(in range [0, 10])\n");
		newGrade = getFloat();
		if(newGrade < 0 || newGrade > 10) {
			printf("You must enter a real number in range [0, 10]\n");
		}
	} while(newGrade < 0 || newGrade > 10);
	
	if(fix(person, amount, tempId, i-1, newGrade)) {
		printf("Sorry, we can not fix this grade, because the grade is less than 4 or the id is not exist\n");
	} else {
		printf("Fix the grade successfully\n");
	}
}

int fix(Result *person, int amount, String id, int subjectIndex, float newGrade) {
	int i;

	if(newGrade <= 4) {
		return 1;
	}

	for(i = 0; i < amount; i++) {
		if(strcmp(id.content, person[i].id.content) == 0) {
			if(person[i].score[subjectIndex] > newGrade) {
				return 1;
			}

			person[i].score[subjectIndex] = newGrade;
			calculateAverage(person, i);
			return 0;
		}
	}

	return 1;
}

void deleteStudent(Result *person, int *amount) {

}

void swap(Result *a, Result *b) {
	Result *temp;
	temp = a;
	a = b;
	b = temp;
}

void printStudentList(Result *person, int amount) {
	int i, j;

	printf("\n\tThe student list:\n");
	printf("%-20s%5s%5s%5s%5s%5s%10s\n", "Student's name", "1st", "2nd", "3rd", "4th", "5th", "Average");
	for(i = 0; i < amount; i++) {
		printf("%-20s", person[i].name.content);
		for(j = 0; j < 5; j++) {
			printf("%5.1f", person[i].score[j]);
		}
		printf("%10f\n", person[i].average);
	}

	printf("\n\n");
}
/**/

float myAbs(float number) {
	return number < 0 ? 0 - number : number;
}

int getInt() {
	int result;

	while(scanf("%d", &result) != 1) {
		printf("Invalid input! Please try again\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	return result;
}

float getFloat() {
	float result;

	while(scanf("%f", &result) != 1) {
		printf("Invalid input! Please try again\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	return result;
}

int menu() {
	int choice;

	printf("\tMENU\n");
	printf("1. Get class information\n");
	printf("2. Search\n");
	printf("3. Find scholaship students\n");
	printf("4. Change grade\n");
	printf("5. Delete student\n");
	printf("6. Exit program\n");

	do {
		printf("What do you want?\n");
		choice = getInt();
		if(choice < 1 || choice > 6) {
			printf("Please enter the number in [1, 6]\n");
		}
	} while(choice < 1 || choice > 6);

	return choice;
}

int subMenu() {
	int choice;

	printf("\tSEARCH MENU\n");
	printf("1. Search by name\n");
	printf("2. Search by class\n");
	printf("3. Search by average\n");
	printf("4. Back to main menu\n");

	do {
		printf("What do you want?\n");
		choice = getInt();
		if(choice < 1 || choice > 4) {
			printf("Please enter the number in [1, 4]\n");
		}
	} while(choice < 1 || choice > 4);

	return choice;
}