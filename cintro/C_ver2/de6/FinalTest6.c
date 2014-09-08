#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define XANH 0
#define VANG 1
#define DO 2

typedef struct {
	char hoTen[100];
	int mau;
	int diem;
} player;

int menu();
int getInt();
void getString(char *s);
int nhapMau();
void taoMaTran(int a[][3], int x);
void inMaTran(int a[][3], int x);
int nhapHang();
int nhapCot();
void thayDoiMaTran(int a[][3], int x);
void thucHienChoi(int a[][3], int x, player *b, int z);
void chinhTen(char *s);
void nhapTen(char *s);
void hienThiKetQua(player *a, int x);
void sortArrayStruct(player *list, int amount);
void swap(player *a, player *b);

int main() {
	int choice, x = 5, y = 3, z = 4;
	int maTranMau[5][3];
	player arrayPlayer[4];
	
	while(1) {
		choice = menu();
	
		switch (choice) {
			case 1:	// Option 1
					taoMaTran(maTranMau, x);
					continue;
			case 2: // Option 2
					thayDoiMaTran(maTranMau, x);
					continue;		
			case 3: // Option 3
					thucHienChoi(maTranMau, x, arrayPlayer, z);
					continue;	
			case 4: hienThiKetQua(arrayPlayer, z);
					continue;					
			case 5: printf("Exit\n");
					break;							
		}
		break;
	}
	
	return 0;
}

int menu() {
	int choice;
	
	printf("\n**********\n");
	printf("Menu gameshow Hanh khach cuoi cung\n");
	printf("1. Tao ma tran o mau\n");
	printf("2. Thay doi ma tran\n");
	printf("3. Thuc hien choi\n");
	printf("4. Hien thi ket qua\n");
	printf("5. Exit\n");
	printf("Moi ban nhap lua chon: ");

	do {
		choice = getInt();
		if((choice < 1) || (choice > 5)) printf("Ban chi duoc phep nhap tu 1 den 4. Moi ban nhap lai\n");
	}while((choice < 1) || (choice > 5));
	
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

int nhapMau() {
	int mau;

	do {
		mau = getInt();
		if(mau < 0 || mau > 2) printf("Gia tri mau chi nhan ba gia tri 0, 1, 2. Moi ban nhap lai.\n");
	} while(mau < 0 || mau > 2);

	return mau;
}

void taoMaTran(int a[][3], int x) {
	int i , j;

	printf("\nNhap mau cho cac o trong ma tran mau. Trong do 0 - Xanh, 1 - Vang, 2 - Do\n");
	for(i = 0; i < x; i++) {
		printf("\nHang thu %d:\n", i + 1);
		for(j = 0; j < 3; j++) {
			printf("\tCot thu %d: ", j + 1);
			a[i][j] = nhapMau();
		}
	}

	inMaTran(a, x);
}

void inMaTran(int a[][3], int x) {
	int i, j;

	printf("\nIn ma tran mau:\n");
	for(i = x - 1; i >= 0; i--) {
		printf("\n");
		for(j = 0; j < 3; j++){
			if(a[i][j] == XANH) printf("%-10s", "Xanh");
			else if(a[i][j] == VANG) printf("%-10s", "Vang");
			else printf("%-10s", "Do");
		}
	}
	printf("\n");
}

int nhapHang() {
	int hang;

	do{
		hang = getInt();
		if(hang < 1 || hang > 5) printf("Gia tri cua hang chi nhan tu 1 den 5. Moi ban nhap lai.\n");
	}while(hang < 1 || hang > 5);

	return hang;
}

int nhapCot() {
	int cot;

	do{
		cot = getInt();
		if(cot < 1 || cot > 3) printf("Gia tri cua cot chi nhan tu 1 den 3. Moi ban nhap lai.\n");
	}while(cot < 1 || cot > 3);

	return cot;
}

void thayDoiMaTran(int a[][3], int x) {
	int mau, hang, cot, temp, j;

	printf("\nNhap hang cua o can doi mau: ");
	hang = nhapHang();
	printf("\nNhap cot cua o can doi mau: ");
	cot = nhapCot();
	printf("\nNhap mau muon doi (0 - Xanh, 1 - Vang, 2 - Do): ");
	do {
		mau = nhapMau();
		if(mau == a[hang - 1][cot - 1]) printf("Trung voi mau trong o. Moi ban nhap lai.\n");
	} while(mau == a[hang - 1][cot - 1]);

	temp = a[hang - 1][cot - 1];

	for(j = 0; j < 3; j++) {
		if(a[hang - 1][j] == mau) {
			a[hang - 1][cot - 1] = a[hang - 1][j];
			a[hang - 1][j] = temp;
			break;
		}
	}

	inMaTran(a, x);
}

void thucHienChoi(int a[][3], int x, player *b, int z) {
	int i, j, o;

	for(i = 0; i < z; i++) {
		printf("\nNguoi choi thu %d:\n", i + 1);
		printf("\nHo va ten: ");
		nhapTen(b[i].hoTen);
		chinhTen(b[i].hoTen);
		b[i].diem = 0;
		printf("\nLua chon mau (0 - Xanh, 1 - Vang, 2 - Do): ");
		b[i].mau = nhapMau();

		for(j = 0; j < x; j++) {
			printf("\nHang thu %d:\n", j + 1);
			printf("Chon o thu: ");
			o = nhapCot();
			if(a[j][o - 1] == b[i].mau) (b[i].diem)++;
			else break;
		}
	}
}

void chinhTen(char *s) {
	int i;

	if(s[0] >= 'a' && s[0] <= 'z') s[0] = s[0] + 'A' - 'a';

	for(i = 1; i < strlen(s); i++) {
		if(s[i - 1] == ' '){
			if(s[i] >= 'a' && s[i] <= 'z') s[i] = s[i] + 'A' - 'a';
		}
	}
}

void nhapTen(char *s) {
	int check, i;
	do {
		check = 0;
		getString(s);

		for(i = 0; i < strlen(s); i++) {
			if(isspace(s[i]) != 0) check = 1;
		}

		if(check == 0) printf("Giua ho va ten phai co khoang trang. Moi ban nhap lai.\n");	
	} while(check == 0);
}

void hienThiKetQua(player *a, int x) {
	int i, min = 0, max = 0;

	printf("\n%-10s%-30s%-15s%-5s\n", "Luot choi", "Nguoi choi", "Mau lua chon", "Diem");
	for(i = 0; i < x; i++) {
		printf("%-10d%-30s", i + 1, a[i].hoTen);
		if(a[i].mau == XANH) printf("%-15s", "Xanh");
		else if(a[i].mau == VANG) printf("%-15s", "Vang");
		else printf("%-15s", "Do");
		printf("%-5d\n", a[i].diem);
	}

	sortArrayStruct(a, x);

	printf("\nNguoi choi co diem thap nhat:\n");
	for(i = 0; i < x && a[i].diem == a[0].diem; i++)
		printf("%s - Diem: %d\n", a[i].hoTen, a[i].diem);
	printf("\nNguoi choi co diem cao nhat:\n");
	for(i = x - 1; i >= 0 && a[i].diem == a[x - 1].diem; i--)
		printf("%s - Diem: %d\n", a[i].hoTen, a[i].diem);
}

void sortArrayStruct(player *list, int amount) {
	int i, j;
	int iMin;

	for(j = 0; j < amount - 1; j++) {
		iMin = j;
		for(i = j + 1; i < amount; i++) {
			if(list[i].diem < list[iMin].diem)
				iMin = i;
		}

		if (iMin != j)
			swap(&list[j], &list[iMin]);
	}
}

void swap(player *a, player *b) {
	player temp;

	memcpy(&temp, a, sizeof(player));
	memcpy(a, b, sizeof(player));
	memcpy(b, &temp, sizeof(player));
}