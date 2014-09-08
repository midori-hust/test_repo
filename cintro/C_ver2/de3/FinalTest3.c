#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
	char maSo[9];
	char tieuDe[50];
	int thoiLuong;
	int giaThue;
}DVD;

int menu();
int getInt();
void getString(char *s);
int nhapSoDia();
void nhapMS(char *s);
int nhapTL();
void nhapLieu(DVD *arrayDVD, int *n);
void in(DVD *arrayDVD, int n);
void sortArrayDVDTL(DVD *list, int amount);
void swap(DVD *a, DVD *b);
int timDia(DVD *arrayDVD, int n, char *ms);
void suaThongTin(DVD *arrayDVD, int n);
void sortArrayDVDTieuDe(DVD *list, int amount);
void timTieuDeMax(DVD *arrayDVD, int n);

int main() {
	int choice, n;
	DVD arrayDVD[100];
	
	while(1) {
		choice = menu();
	
		switch (choice) {
			case 1:	// Option 1
					nhapLieu(arrayDVD, &n);
					continue;
			case 2: // Option 2
					in(arrayDVD, n);
					continue;		
			case 3: // Option 3
					sortArrayDVDTL(arrayDVD, n);
					in(arrayDVD, n);
					continue;
			case 4: suaThongTin(arrayDVD, n);
					continue;
			case 5: timTieuDeMax(arrayDVD, n);
					continue;						
			case 6: printf("Exit\n");
					break;							
		}
		break;
	}
	
	return 0;
}

int menu() {
	int choice;
	
	printf("\nMediaMax - Chuong trinh quan ly dia DVD\n");
	printf("1. Nhap so lieu\n");
	printf("2. Danh sach dia\n");
	printf("3. Sap xep theo thoi luong\n");
	printf("4. Sua thong tin dia\n");
	printf("5. Sap xep theo tieu de\n");
	printf("6. Thoat\n");
	printf("Hay nhap lua chon: ");

	do {
		choice = getInt();
		if((choice < 1) || (choice > 6)) printf("Ban chi duoc phep nhap tu 1 den 6. Moi ban nhap lai\n");
	}while((choice < 1) || (choice > 6));
	
	return choice;
}

int getInt() {
	
	int number;
	
	while(scanf("%d", &number) != 1) {
		printf("Ban da nhap sai. Moi ban nhap lai. \n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	return number;
}

void getString(char *s) {
	fgets(s, 100, stdin);
	s[strlen(s) - 1] = '\0';
}

int nhapSoDia() {
	int n;

	do {
		n = getInt();
		if(n < 1 || n > 100) printf("So dia chi nam trong doan tu 1 den 100. Moi ban nhap lai\n");
	} while(n < 1 || n > 100);

	return n;
}

void nhapMS(char *s) {
	int i, check;

	do {
		check = 1;
		getString(s);

		if((s[0] != '0') && (s[0] != '1')) check =0;

		for(i = 1; i < 4; i++) {
			if(s[i] < 'A' || s[i] > 'Z') check = 0;
		}

		for(i = 4; i < 7; i++) {
			if(s[i] < '1' || s[i] > '9') check = 0;
		}

		if(strlen(s) != 8) check = 0;

		if(check == 0) printf("Nhap sai dinh dang ma so dia. Moi ban nhap lai.\n");
	} while(check == 0);
}

int nhapTL() {
	int n;

	do {
		n = getInt();
		if(n < 60 || n > 180) printf("Thoi luong chi nam trong doan tu 60 den 180. Moi ban nhap lai\n");
	} while(n < 60 || n > 180);

	return n;
}

void nhapLieu(DVD *arrayDVD, int *n) {
	int i;

	printf("\nNhap so luong dia: ");
	*n = nhapSoDia();
	printf("\nNhap thong tin dia\n");

	for(i = 0; i < *n; i++) {
		printf("\nThong tin dia thu %d: \n", i + 1);
		printf("Nhap ma so dia: ");
		nhapMS(arrayDVD[i].maSo);
		printf("Nhap tieu de: ");
		getString(arrayDVD[i].tieuDe);
		printf("Nhap thoi luong cua dia: ");
		arrayDVD[i].thoiLuong = nhapTL();
		if(arrayDVD[i].maSo[0] == '0') arrayDVD[i].giaThue = 5000;
		else arrayDVD[i].giaThue = 2000;
	}
}

void in(DVD *arrayDVD, int n) {
	int i;

	printf("\n%-10s%-20s%-15s%-10s\n", "Ma so", "Tieu de", "Thoi luong", "Gia thue");

	for(i = 0; i < n; i++) {
		printf("%-10s%-20s%-15d%-10d\n", arrayDVD[i].maSo, arrayDVD[i].tieuDe, arrayDVD[i].thoiLuong, arrayDVD[i].giaThue);
	}
}

void sortArrayDVDTL(DVD *list, int amount) {
	int i, j;
	int iMin;

	for(j = 0; j < amount - 1; j++) {
		iMin = j;
		for(i = j + 1; i < amount; i++) {
			if(list[i].thoiLuong < list[iMin].thoiLuong)
				iMin = i;
		}

		if (iMin != j)
			swap(&list[j], &list[iMin]);
	}
}

void swap(DVD *a, DVD *b) {
	DVD temp;

	memcpy(&temp, a, sizeof(DVD));
	memcpy(a, b, sizeof(DVD));
	memcpy(b, &temp, sizeof(DVD));
}

int timDia(DVD *arrayDVD, int n, char *ms) {
	int i;

	for(i = 0; i < n; i++) {
		if(strcmp(arrayDVD[i].maSo, ms) == 0) return i;
	}

	return -1;
}

void suaThongTin(DVD *arrayDVD, int n) {
	char maSODia[9];

	printf("\nNhap ma so dia can sua: ");
	getString(maSODia);

	if(timDia(arrayDVD, n, maSODia) < 0) {
		printf("\nKhong co dia voi ma so nhu vay.\n");
		return;
	}
	else {
		printf("\nNhap tieu de moi: ");
		getString(arrayDVD[timDia(arrayDVD, n, maSODia)].tieuDe);
		printf("Nhap thoi luong moi: ")	;
		arrayDVD[timDia(arrayDVD, n, maSODia)].thoiLuong = nhapTL();
		return;
	}
}

void sortArrayDVDTieuDe(DVD *list, int amount) {
	int i, j;
	int iMin;

	for(j = 0; j < amount - 1; j++) {
		iMin = j;
		for(i = j + 1; i < amount; i++) {
			if(strlen(list[i].tieuDe) > strlen(list[iMin].tieuDe))
				iMin = i;
		}

		if (iMin != j)
			swap(&list[j], &list[iMin]);
	}
}

void timTieuDeMax(DVD *arrayDVD, int n) {
	int i;

	sortArrayDVDTieuDe(arrayDVD, n);

	printf("\nThong tin cua DVD co tieu de dai nhat\n");

	printf("\n%-10s%-20s%-15s%-10s\n", "Ma so", "Tieu de", "Thoi luong", "Gia thue");

	for(i = 0; (i < n) && (strlen(arrayDVD[i].tieuDe) == strlen(arrayDVD[0].tieuDe)); i++) {
		printf("%-10s%-20s%-15d%-10d\n", arrayDVD[i].maSo, arrayDVD[i].tieuDe, arrayDVD[i].thoiLuong, arrayDVD[i].giaThue);
	}
}