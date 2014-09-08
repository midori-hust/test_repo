#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

typedef struct 
{
	char hoten[30];
	int diem[5];
	int tongdiem;
	int checkSieuXaThu;
} ketquathidau;

ketquathidau vdv[MAX];

int menu();
int getInt();
void getString(char *s);
int nhapSoVDV();
void dangKy(ketquathidau *vdv, int *n);
int nhapDiem();
void thiDau(ketquathidau *vdv, int n);
void inKetQua(ketquathidau *vdv, int n);
void sortArrayVDV(ketquathidau *vdv, int amount);
void swap(ketquathidau *a, ketquathidau *b);
void xepHang(ketquathidau *vdv, int n);
void sieuXaTHu(ketquathidau *vdv, int n);

int main() {
	int choice, n;
	
	while(1) {
		choice = menu();
	
		switch (choice) {
			case 1:	// Option 1
					dangKy(vdv, &n);
					continue;
			case 2: // Option 2
					thiDau(vdv, n);
					continue;		
			case 3: // Option 3
					xepHang(vdv, n);
					continue;
			case 4: sieuXaTHu(vdv, n);
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
	printf("Menu\n");
	printf("1. Dang ky van dong vien\n");
	printf("2. Thi dau\n");
	printf("3. Xep hang\n");
	printf("4. Sieu xa thu\n");
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

int nhapSoVDV() {
	int n;

	do {
		n = getInt();
		if(n < 1 || n > 10) printf("So van dong vien chi nam trong doan tu 1 den 10. Moi ban nhap lai.\n");		
	} while (n < 1 || n > 10);

	return n;
}

void dangKy(ketquathidau *vdv, int *n) {
	int i;

	printf("\nNhap so van dong vien: ");
	*n = nhapSoVDV();
	printf("\nNhap ho ten van dong vien:\n");
	for(i = 0; i < *n; i++) {
		printf("\nHo ten van dong vien thu %d: ", i + 1);
		getString(vdv[i].hoten);
		vdv[i].tongdiem = 0;
		vdv[i].checkSieuXaThu = 0;
	}

	printf("\nIn danh sach cac van dong vien\n");
	for(i = 0; i < *n; i++) {
		printf("%d. %s\n", i + 1, vdv[i].hoten);
	}
}

int nhapDiem() {
	int n;

	do{
		n = getInt();
		if(n < 0 || n > 10) printf("Diem chi nam trong doan 0 den 10. Moi ban nhap lai\n");
	} while(n < 0 || n > 10);

	return n;
}

void thiDau(ketquathidau *vdv, int n) {
	int i, j;

	for(i = 0; i < 5; i++) {
		printf("\nLuot thu %d\n", i + 1);
		for(j = 0; j < n; j++) {
			printf("Diem cua %s: ", vdv[j].hoten);
			vdv[j].diem[i] = nhapDiem();
			vdv[j].tongdiem += vdv[j].diem[i];
		}
	}

	printf("\nIn ket qua tran dau\n");
	inKetQua(vdv, n);
}

void inKetQua(ketquathidau *vdv, int n) {
	int i;

	printf("\n%-25s%-5s%-5s%-5s%-5s%-5s\n", "Ho ten", "1", "2", "3", "4", "5");
	for(i = 0; i < n; i++) {
		printf("%-25s%-5d%-5d%-5d%-5d%-5d\n", vdv[i].hoten, vdv[i].diem[0], vdv[i].diem[1], vdv[i].diem[2], vdv[i].diem[3], vdv[i].diem[4]);
	}
}

void sortArrayVDV(ketquathidau *vdv, int amount) {
	int i, j;
	int iMin;

	for(j = 0; j < amount - 1; j++) {
		iMin = j;
		for(i = j + 1; i < amount; i++) {
			if(vdv[i].tongdiem > vdv[iMin].tongdiem)
				iMin = i;
		}

		if (iMin != j)
			swap(&vdv[j], &vdv[iMin]);
	}
}

void swap(ketquathidau *a, ketquathidau *b) {
	ketquathidau temp;

	memcpy(&temp, a, sizeof(ketquathidau));
	memcpy(a, b, sizeof(ketquathidau));
	memcpy(b, &temp, sizeof(ketquathidau));
}

void xepHang(ketquathidau *vdv, int n) {
	int i, j, k;
	sortArrayVDV(vdv, n);

	printf("\n%-25s%-10s%-5d\n", vdv[0].hoten, "Gold", vdv[0].tongdiem);
	for(i = 1; (i < n) && (vdv[i].tongdiem == vdv[0].tongdiem); i++) {
		printf("%-25s%-10s%-5d\n", vdv[i].hoten, "Gold", vdv[i].tongdiem);
	}
	printf("%-25s%-10s%-5d\n", vdv[i].hoten, "Silver", vdv[i].tongdiem);
	for(j = i + 1; (j < n) && (vdv[j].tongdiem == vdv[i].tongdiem); j++) {
		printf("%-25s%-10s%-5d\n", vdv[j].hoten, "Silver", vdv[j].tongdiem);
	}
	printf("%-25s%-10s%-5d\n", vdv[j].hoten, "Bronze", vdv[j].tongdiem);
	for(k = j + 1; (k < n) && (vdv[k].tongdiem == vdv[j].tongdiem); k++) {
		printf("%-25s%-10s%-5d\n", vdv[k].hoten, "Bronze", vdv[k].tongdiem);
	}
}

void sieuXaTHu(ketquathidau *vdv, int n) {
	int i, j, dem;

	for(i = 0; i < n; i++) {
		dem = 0;
		for(j = 0; j < 5; j++) {
			if(vdv[i].diem[j] == 10) dem++;
			else dem = 0;
			if(dem == 3) vdv[i].checkSieuXaThu = 1;
		}
	}

	printf("\nDanh sach sieu xa thu: \n");
	for(i = 0; i < n; i++) {
		if(vdv[i].checkSieuXaThu == 1) printf("%s\n", vdv[i].hoten);
	}
}