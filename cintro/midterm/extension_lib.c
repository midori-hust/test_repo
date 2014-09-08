#include "extension_lib.h"

/* 
*  Ham main gia
*
*/
int solve() {
	Student studentList[SIZE];

	int choice;
	int n;

  	while(1) {
      choice = menu();

      switch(choice) {
        case 1:
        printf("You choose option %d\n", choice);
        printf("Please enter the number of students\n");
        do {
        	n = getInt();
        	if(n < 1) {
        		printf("Please enter again\n");
        	}
        } while(n < 1);

        getData(studentList, n);
        printList(studentList, n);
        continue;
        case 2:
        printf("You choose option %d\n", choice);
        searchFunct(studentList, n);
        continue;
        case 3:
        printf("You choose option %d\n", choice);
        sortFunct(studentList, n);
        continue;
        case 4:
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

/* 
* Thu thap du lieu vao danh sach sinh vien
* @param: *studentList - danh sach sinh vien
* @oaramL amount - so luong phan tu cua danh sach sinh vien
*/
void getData(Student *studentList, int amount) {
	int i, temp;

	for(i = 0; i < amount; i++) {
		printf("Please enter the student id:\n");
		fgets(studentList[i].id, SIZE, stdin);
		studentList[i].id[strlen(studentList[i].id) - 1] = '\0';
		printf("Please enter the student name:\n");
		fgets(studentList[i].name, SIZE, stdin);
		studentList[i].name[strlen(studentList[i].name) - 1] = '\0';
		printf("Please enter the grade:\n");
		printf("Math:\n");
		do {
			temp = getInt();
			if(temp < 0 || temp > 10) {
				printf("Please enter the grade in [0, 10]\n");
			}
		} while(temp < 0 || temp > 10);
		studentList[i].math = temp;

		printf("Literature:\n");
		do {
			temp = getInt();
			if(temp < 0 || temp > 10) {
				printf("Please enter the grade in [0, 10]\n");
			}
		} while(temp < 0 || temp > 10);
		studentList[i].literature = temp;
		studentList[i].total = studentList[i].math + studentList[i].literature;
	}
}

/* 
* Ham menu tim kiem
* @return: Tra ve option nguoi dung chon
*/

int searchMenu() {
    int option;

    printf("\n\t\tSEARCH FUNCTIONS\n");
    printf("\t1. Search by name\n");
    printf("\t2. Search by total grade\n");
    printf("\t3. Search the pass student\n");
    printf("\t4. Back to main menu\n");
    printf("\nWhich option would you like to choose?\n");

    do {
      option = getInt();
      if (option < 0 || option > 4) {
        printf("Invalid option! Please choose again!\n");
      }
    } while (option < 0 || option > 4);

    return option;
}

/* 
* Chuc nang tim kiem
* @param studentList danh sach sinh vien
* @param amount so phan tu cua danh sach sinh vien
*/
void searchFunct(Student *studentList, int amount) {
	int choice;

  	while(1) {
      choice = searchMenu();

      switch(choice) {
        case 1:
        printf("You choose option %d\n", choice);
        search(studentList, amount, BY_NAME);
        continue;
        case 2:
        printf("You choose option %d\n", choice);
        search(studentList, amount, BY_TOTAL);
        continue;
        case 3:
        printf("You choose option %d\n", choice);
        search(studentList, amount, PASS);
        continue;
        case 4:
        printf("You choose option %d\n", choice);
        printf("Bye bye\n");
        break;
        default:
        printf("It is not an option\n");
        continue;
      }
      break;
    }
}

/* 
* menu chuc nang sap xep
* @return: tra ve lua chon cua nguoi dung
*/
int sortMenu() {
    int option;

    printf("\n\t\tSORT FUNCTIONS\n");
    printf("\t1. Sort by total grade\n");
    printf("\t2. Sort by name\n");
    printf("\t3. Back to main menu\n");
    printf("\nWhich option would you like to choose?\n");

    do {
      option = getInt();
      if (option < 0 || option > 3) {
        printf("Invalid option! Please choose again!\n");
      }
    } while (option < 0 || option > 3);

    return option;
}

/* 
* Chuc nang sap xep
* @param studentList danh sach sinh vien
* @param amount so phan tu cua danh sach sinh vien
*/
void sortFunct(Student *studentList, int amount) {
	int choice;

  	while(1) {
      choice = sortMenu();

      switch(choice) {
        case 1:
        printf("You choose option %d\n", choice);
        sorting(studentList, amount, BY_TOTAL);
        printf("After sorting\n");
        printList(studentList, amount);
        continue;
        case 2:
        printf("You choose option %d\n", choice);
        sorting(studentList, amount, BY_NAME);
        printf("After sorting\n");
        printList(studentList, amount);
        continue;
        case 3:
        printf("You choose option %d\n", choice);
        printf("Bye bye\n");
        break;
        default:
        printf("It is not an option\n");
        continue;
      }
      break;
    }
}

/* 
* In ra danh sach cac phan tu cua danh sach sinh vien
* @param studentList danh sach sinh vien
* @param amount so luong phan tu cua danh sach sinh vien
*/
void printList(Student *studentList, int amount) {
	int i;

	printf("\n");
	printf("%-6s%-15s%15s%15s%10s\n", "ID", "Name", "Math", "Literature", "Total");
	for(i = 0; i < amount; i++) {
		// printf("%-6s%-15s%15d%15d%10d\n", studentList[i].id, studentList[i].name, studentList[i].math, studentList[i].literature, studentList[i].total);
		printFrame(studentList[i]);
	}
}

/* 
* Khung in 1 sinh vien
* @param student sinh vien muon in ra man hinh
*/
void printFrame(Student student) {
	printf("%-6s%-15s%15d%15d%10d\n", student.id, student.name, student.math, student.literature, student.total);
}

/* 
* search controller
* @param option lua chon kieu search cua nguoi dung
*/
void search(Student *studentList, int amount, int option) {
	char name[SIZE];
	int grade;

	switch(option) {
		case BY_NAME:
		printf("Please enter the name of the student:\n");
		fgets(name, SIZE, stdin);
		name[strlen(name) - 1] = '\0';
		printf("Search result:\n");
		if(!searchByName(studentList, amount, name)) {
			printf("Cannot find this student\n");
		}
		break;
		case BY_TOTAL:
		printf("Please enter the grade of the student:\n");
		grade = getInt();
		name[strlen(name) - 1] = '\0';
		printf("Search result:\n");
		if(!searchByGrade(studentList, amount, grade)) {
			printf("Cannot find this student\n");
		}
		break;
		case PASS:
		printf("Search result: The pass students:\n");
		if(!searchPass(studentList, amount)) {
			printf("There is no student pass T.T\n");
		}
		break;
		default:
		printf("Out of order\n");
		break;
	}
}

/* 
* tim kiem voi ten
* @param name ten nguoi can tim kiem
* @return tim kiem thanh cong (1) hay that bai (0)
*/
int searchByName(Student *studentList, int amount, char *name) {
	int i;
	int flag = 0;

	for(i = 0; i < amount; i++) {
		if(strstr(studentList[i].name, name) != NULL) {
			printFrame(studentList[i]);
			flag = 1;
		}
	}

	return flag;
}

/* 
* tim kiem voi tong diem
* @param grade tong diem cua nguoi can tim kiem
* @return tim kiem thanh cong (1) hay that bai(0)
*/
int searchByGrade(Student *studentList, int amount, int grade) {
	int i;
	int flag = 0;

	for(i = 0; i < amount; i++) {
		if(studentList[i].total == grade) {
			printFrame(studentList[i]);
			flag = 1;
		}
	}

	return flag;
}

/* 
* Tim kiem nguoi qua bai thi
* @return tim kiem thanh cong (1) hay that bai (0)
*/
int searchPass(Student *studentList, int amount) {
	int i;
	int flag = 0;

	for(i = 0; i < amount; i++) {
		if(studentList[i].total > 10 && studentList[i].math >= 4 && studentList[i].literature >= 4) {
			printFrame(studentList[i]);
			flag = 1;
		}
	}

	return flag;
}

/* 
* Sort controller
* @param option lua chon kieu sap xep cua nguoi dung
*/
void sorting(Student *studentList, int amount, int option) {
	switch(option) {
		case BY_TOTAL:
		sortByTotal(studentList, amount);
		break;
		case BY_NAME:
		sortByName(studentList, amount);
		break;
		default:
		printf("Out of order\n");
		break;
	}
}

/* 
* Sap xep theo ten
*
*/
void sortByName(Student *studentList, int amount) {
	// Prototype:
	// void qsort(void *base, size_t numberMemb, size_t size, int (*compare)(const void*, const void*))
	// @param1 Truyen vao con tro tro toi mang can sap xep
	// @param2 Truyen vao so phan tu cua mang can sap xep
	// @param3 Truyen vao kich thuoc 1 phan tu cua mang can sap xep
	// @param4 Truyen vao ham so sanh 2 phan tu (Phai theo dung prototype int (*compare)(const void*, const void*) moi truyen vao duoc)
	qsort(studentList, amount, sizeof(Student), nameCompare);

}

/* 
* Sap xep theo tong diem
*
*/
void sortByTotal(Student *studentList, int amount) {
	qsort(studentList, amount, sizeof(Student), intCompare);
}

/* 
* Con tro ham so sanh theo ten
* @return neu a < b: tra ve gia tri < 0, nguoc lai tra ve gia tri > 0. Neu a = b, tra lai gia tri 0
*/
int nameCompare(const void* a, const void* b) {
	Student *x = (Student*)a;
	Student *y = (Student*)b;

	String output1[SIZE], output2[SIZE];
	int n1, n2;

	n1 = split(x->name, ' ', output1);
	n2 = split(y->name, ' ', output2);

	return strcmp(output1[n1 - 1].content, output2[n2 - 1].content);
}

/* 
* Con tro ham so sanh theo tong diem
* @return neu a < b: tra ve gia tri < 0, nguoc lai tra ve gia tri > 0. Neu a = b, tra lai gia tri 0
*/
int intCompare(const void* a, const void* b) {
	Student *x = (Student*)a;
	Student *y = (Student*)b;

	return x->total - y->total;
}

/* 
* Ham cat xau: Cat xau str bang ky tu splitChar, ket qua luu vao danh sach listString
* @param str xau can cat
* @param splitChar ky tu de cat
* @param listString danh sach cac xau la ket qua cua phep cat str bang splitChar
* @return so xau duoc cat
*/
int split(char *str, char splitChar, String *listString) {
  int counter = 0;
  int i;
  char *ptr, *temp;

  if(str == NULL) {
    return -1;
  }

  temp = myMalloc(sizeof(String), 1);
  strcpy(temp, str);
  ptr = temp;

  for(i = 0; i <= strlen(str); i++) {
    if(temp[i] == splitChar || temp[i] == '\0') {
      temp[i] = '\0';
      strcpy(listString[counter++].content, ptr);
      ptr = temp + i + 1;
    }
  }

  return counter;
}
