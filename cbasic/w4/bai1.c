/* 1. Tao danh sach lien ket don luu tru danh ba dien thoai */
/* 2. Viet ham chen vao dau danh sach thong tin cua mot nguoi moi */
/* 3. Viet ham chen vao cuoi danh sach thong tin cua mot nguoi moi */
/* 4. Viet ham duyet danh sach */
/* 5. Viet ham cho phep nhap vao ten cua 1 nguoi, va loai bo nguoi nay khoi danh sach */
/* 6. Kiem tra cac ham tren */


#include "phonelist.h"

AddressList* root = NULL;
AddressList* cur = NULL;
AddressList* prev = NULL;

int main()
{
  char name[MAXLENGTH], email[MAXLENGTH];
  int tel;
  AddressList* new;
  char ch;

  printf("Hay nhap danh sach danh ba dien thoai cua ban (nhap @ de ket thuc)!\n");
  while(1)
    {
      printf("Ten nguoi dung: "); gets(name);
      if(strcmp(name,"@") == 0) break;
      printf("SDT: "); scanf("%d", &tel);
      ch = getchar();
      printf("Email: "); gets(email);
      if(root == NULL)
	{
	  root = newAddress(name, tel, email);
	  cur = root;
	}
      else
	{
	new = newAddress(name, tel, email);
	cur->next = new;
	cur = new;
	}
    }
  printf("Da nhap xong danh ba.\n\n");
  printf("------------------------------------------------------");
  printf("Danh ba dien thoai hien tai cua ban:\n");
  displayList();
  printf("------------------------------------------------------");
  printf("Hay nhap them 1 nguoi dung moi de nhet no vao dau danh ba:\n");
  printf("Ten nguoi dung: "); gets(name);
  printf("SDT: "); scanf("%d", &tel);
  ch = getchar();
  printf("Email: "); gets(email);
  new = newAddress(name, tel, email);
  insertTop(new);
  printf("Danh ba dien thoai hien tai cua ban:\n");
  displayList();
  printf("------------------------------------------------------");
  printf("Hay nhap them 1 nguoi dung moi de nhet no vao cuoi danh ba:\n");
  printf("Ten nguoi dung: "); gets(name);
  printf("SDT: "); scanf("%d", &tel);
  ch = getchar();
  printf("Email: "); gets(email);
  new = newAddress(name, tel, email);
  insert(new);
  printf("Danh ba dien thoai hien tai cua ban:\n");
  displayList();
  printf("------------------------------------------------------");
  delete();
  printf("Danh ba dien thoai hien tai cua ban:\n");
  displayList();
  printf("------------------------------------------------------");
  return 0;
}
