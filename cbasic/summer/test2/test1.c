/* Thong tin ve 1 sinh vien gom: */
/* MSSV: 10 ky tu */
/* Hoten: 30 ky tu */
/* Diemthi: so thuc */
/* Menu: */
/* 1. Nhap tu ban phim thong tin 1 SV, chen dau danh sach */
/* 2. Nhap tu ban phim MSSV tim kiem, neu co hien thi */
/*   thong tin, neu khong in thong bao */
/* 3. Xoa SV */
/* 4. Hien thi list */
/* 5. Thoat */

#include "linklist.h"

int main() {
  int option;
  int id;
  char name[MAXLENGTH];
  float grade;
  node *temp;

  while(1) {
    option = menu();
    switch(option) {

    case 1:
      printf("You choose option #%d\n", option);
      printf("Enter the information of student:\n");
      printf("Student ID: ");
      while(scanf("%d", &id) != 1) {
	printf("Wrong input! Please retry\n");
	while(getchar() != '\n');
      }
      while(getchar() != '\n');
      printf("Student name: ");
      gets(name);
      printf("Student grade: ");
      while(scanf("%f", &grade) != 1) {
	printf("Wrong input! Please retry\n");
	while(getchar() != '\n');
      }
      while(getchar() != '\n');
      insertTop(id, name, grade);
      printf("Done.\n");
      continue;

    case 2:
      printf("You choose option #%d\n", option);
      printf("Enter the student id which you want to search:\n");
      while(scanf("%d", &id) != 1) {
	printf("Wrong input! Please retry\n");
	while(getchar() != '\n');
      }
      temp = searchNode(id);
      if(temp != NULL) {
	printf("The student information:\n");
	printf("Student ID: %d\nStudent name: %s\nStudent grade: %f\n\n", temp->element.id, temp->element.name, temp->element.grade);
      }
      continue;

    case 3:
      printf("You choose option #%d\n", option);
      printf("Enter the student id which you want to delete:\n");
      while(scanf("%d", &id) != 1) {
	printf("Wrong input! Please retry\n");
	while(getchar() != '\n');
      }
      deleteNode(id);
      printf("Done.\n");
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
