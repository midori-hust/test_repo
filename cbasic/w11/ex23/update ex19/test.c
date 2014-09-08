/* Dinh nghia cau truc sinh vien, sau do xay dung chuong trinh co giao dien menu thuc hien cong viec */
/* Khi an 1 cho phep nhap tu ban phim thong tin cua 1 sinh vien, sau do chen vao dau danh sach */
/* Khi an 2 cho phep nhap tu ban phim ma so SV can tim kiem, neu co hien thi tat ca thong tin ve sv, nguoc lai thong bao khong tim thay. */
/* Khi an 3 cho phep nhat tu ban phim ma so SV can xoa. Neu khong co SV nay thi thong bao xoa khong thanh cong vi ton tai SV nhu vay */
/* Khi an 4 cho phep hien thi tat ca thong tin SV trong danh sach */
/* Khi an 5 cho phep thoat khoi chuong trinh */

#include "midterm.h"

int main()
{
  int id;
  char name[MAXLENGTH];
  float mark;
  char ch2;
  StudentList *new_node;

  FILE *f;
  char filename[MAXLENGTH] = "student.dat";

  if ((f = fopen(filename, "wb")) == NULL)
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
	  printf("Ban chon %c.\n", ch);
	  printf("Nhap vao ban phim thong tin cua 1 sinh vien:\n");
	  printf("Ma so sinh vien: ");
	  if(scanf("%d", &id) == 0)
	    {
	      printf("Nhap vao khong thanh cong. Ban da nhap MSSV sai (phai nhap so nguyen).\n");
	      continue;
	    }
	  printf("Ten sinh vien: ");
	  while((ch2 = getchar()) != '\n');
	  gets(name);
	  if(strlen(name) > 30)
	    {
	      printf("Nhap vao khong thanh cong. Ban da nhap ten sinh vien qua 30 ky tu.\n");
	      continue;
	    }
	  printf("Diem thi cua sinh vien: ");
	  if(scanf("%f", &mark) == 0)
	    {
	      printf("Nhap vao khong thanh cong. Ban da nhap diem sai (phai nhap so thuc).\n");
	      continue;
	    }
	  while((ch2 = getchar()) != '\n');
	  new_node = newStudent(id, name, mark);
	  insertTop(new_node);
	  displayList();
	  continue;

	case '2':
	  printf("Ban chon %c.\n", ch);
 	  printf("Hay nhap MSSV cua sinh vien ban can tim: ");
	  if(scanf("%d", &id) == 0)
	    {
	      printf("Nhap khong thanh cong. Ban da nhap sai MSSV.\n");
	      continue;
	    }
	  searchStudent(id);
	  while((ch2 = getchar()) != '\n');
	  continue;

	case '3':
	  printf("Ban chon %c.\n", ch);
	  printf("Hay nhap MSSV cua sinh vien ban can xoa: "); 
	  if(scanf("%d", &id) == 0)
	    {
	      printf("Nhap khong thanh cong. Ban da nhap sai MSSV.\n");
	      continue;
	    }
	  deleteStudent(id);
	  while((ch2 = getchar()) != '\n');
	  continue;

	case '4':
	  printf("Ban chon %c.\n", ch);
	  displayList();
	  saveFile(f);
	  printf("Da save xong.\n");
	  continue;

	case '5':
	  printf("Ban chon %c.\n", ch);
	  freeList();
	  printf("Chuong trinh ket thuc!\n");
	  //	  displayList();
	  break;

	default:
	  printf("Ban da chon sai lua chon, xin vui long chon lai!\n");
	  continue;
	}
      break;
    }

  fclose(f);
  return 0;
}
