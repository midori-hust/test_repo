/* De quan li thong tin ve cac san pham, nguoi ta luu tru vao file cac ban ghi san pham */
/*   gom ma san pham (maSP-int, co gia tri trong khoang tu 101 toi 500), ten san pham  */
/*   (tenSP-kieu xau), mo ta san pham (motaSP - kieu xau), gia (giaSP - kieu int), so luong (SL - kieu int). Viet chuong trinh (giao */
/* 															     dien menu) co cac chuc nang sau */
/*   +Khong dung mang, hay nhap thong tin ve cac san pham theo thu tu tang dan */
/*   cua ma san pham va ghi vao file "SANPHAM.TXT" (1d). Qua trinh nhap lieu co kiem tra ma san pham trong khoang tu 101 toi 500 */
/* Qua trinh nhap lieu ket thuc khi ma san pham khong phai la so */
/* Doc du lieu tu file "SANPHAM.TXT" ra 1 mang */
/* Tim ban ghi voi maSP nhap tu ban phim va in ra man hinh ban ghi do. */
/* Hay viet thuat toan tim kiem hieu qua nhat de thuc hien cong viec nay */
/* In ra man hinh so phep so sanh can thuc hien de tim duoc ban ghi nay. */


#include "midterm.h"

int main()
{
  prodInfo product[MAXLENGTH];
  int id;
  char name[MAXLENGTH];
  int price;
  char description[MAXLENGTH];
  int quantity;
  int i = 0;
  int j;

  FILE *f;
  char filename[MAXLENGTH] = "product.txt";

  if ((f = fopen(filename, "w+")) == NULL)
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
	  nhapThongTin(f);
	  continue;
	case '2':
	  printf("Ban chon %c.\n", ch);
	  rewind(f);
	  while(1)
	    {
	      if ((fscanf(f, "%d\n", &id)) == EOF) break;
	      fgets(name, MAXLENGTH, f);
	      name[strlen(name) -1] = '\0';
	      fscanf(f, "%d\t%d\n", &price, &quantity);
	      fgets(description, MAXLENGTH, f);
	      description[strlen(description) -1] = '\0';
	      product[i].id = id;
	      product[i].price = price;
	      product[i].quantity = quantity;
	      strcpy(product[i].name, name);
	      strcpy(product[i].description, description);
	      i++;
	    }
	  printf("Da doc xong.\n");
	  printf("Danh sach cac phan tu trong mang:\n");
	  if(i == 0) printf("Khong co phan tu nao trong mang.\n");
	  else
	    {
	      for(j=0; j<i; j++)
		printf("ID: %d\nName: %s\nPrice: %d\tQuantity: %d\nDescription: %s\n\n", product[j].id, product[j].name, product[j].price, product[j].quantity, product[j].description);
	    }
	  continue;
	case '3':
	  printf("Ban chon %c.\n", ch);

	  continue;
	case '4':
	  printf("Ban chon %c.\n", ch);
	  break;
	default:
	  printf("Ban da nhap sai, xin vui long nhap lai!\n");
	  continue;
	}
      break;
    }

  fclose(f);
  return 0;
}
