#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct 
{
	/* data */
	char hoTen[25];
	float suggest[4];
	float doLech;
	char ten[10];
} result;

int menu();
int getInt();
void getString(char *s);
float getFloat();
float nhapSoThuc();
int nhapSoNguoiChoi();
void nhapTen(char *s);
void tachTen(result *a);
void nhapSL(result *a, int *total, float *n);
void choiDoanSo(result *a, int total, float n);
void inDS(result *a, int total, float n);
float tinhDoLech(float n, float soDoan);
void sortArrayResult(result *list, int amount);
void swap(result *a, result *b);
void inSapXep(result *a, int n);
void timNguoiChoi(result *a, int n);

int main() {
	int choice, total;
	float n;
	result a[5];
	while(1) {
		choice = menu();
	
		switch (choice) {
			case 1:	// Option 1
					nhapSL(a, &total, &n);
					continue;
			case 2: // Option 2
					choiDoanSo(a, total, n);
					inDS(a, total, n);
					continue;		
			case 3: // Option 3
					sortArrayResult(a, total);
					inSapXep(a, total);
					continue;	
			case 4: timNguoiChoi(a, total);
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
	printf("1. Khoi dong tro choi\n");
	printf("2. Choi doan so\n");
	printf("3. Tong hop ket qua\n");
	printf("4. Tim nguoi choi\n");
	printf("5. Exit\n");
	printf("Moi ban nhap lua chon: ");

	do {
		choice = getInt();
		if((choice < 1) || (choice > 5)) printf("Ban chi duoc phep nhap tu 1 den 5. Moi ban nhap lai\n");
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

float getFloat() {
	
	float number;
	
	while(scanf("%f", &number) != 1) {
		printf("Ban da nhap sai. Moi ban nhap lai. \n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	return number;
}

float nhapSoThuc() {
	float n;

	do {
		n = getFloat();
		if(n < 1 || n > 100) printf("So thuc chi nam trong doan tu 1 toi 100. Moi ban nhap lai.\n");
	} while(n < 1 || n > 100);

	return n;
}

void getString(char *s) {
	fgets(s, 100, stdin);
	s[strlen(s) - 1] = '\0';
}

int nhapSoNguoiChoi() {
	int n;

	do {
		n = getInt();
		if(n < 1 || n > 5) printf("So nguoi choi chi nam trong doan tu 1 toi 5. Moi ban nhap lai.\n");
	} while(n < 1 || n > 5);

	return n;
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

void tachTen(result *a) {
	int i, j = 0;
	char temp[10];

	for(i = strlen((*a).hoTen) - 1; (i >= 0) && (isspace((*a).hoTen[i]) == 0); i--) {
		temp[j] = (*a).hoTen[i];
		j++;
	}
	temp[j] = '\0';

	j = 0;
	for(i = strlen(temp) - 1; i >= 0; i--) {
		(*a).ten[j] = temp[i];
		j++;
	}
	(*a).ten[j] = '\0';
}

void nhapSL(result *a, int *total, float *n) {
	int i;

	printf("\nNhap so thuc N: ");
	*n = nhapSoThuc();

	printf("\nNhap so nguoi choi: ");
	*total = nhapSoNguoiChoi();

	printf("\nNhap thong tin nguoi choi\n");
	for(i = 0; i < *total; i++) {
		printf("\nHo ten nguoi choi thu %d: ", i + 1);
		nhapTen(a[i].hoTen);
		tachTen(&(a[i]));
	}

	printf("\nDanh sach nguoi choi\n");
	for(i = 0; i < *total; i++) {
		printf("%d. %s\n", i + 1, a[i].hoTen);
	}
}

void choiDoanSo(result *a, int total, float n) {
	int i, j;

	for(i = 0; i < total; i++) {
		printf("\nNguoi choi thu %d choi\n", i + 1);
		for(j = 0; j < 4; j++) {
			printf("Lan %d: ", j + 1);
			a[i].suggest[j] = getFloat();
			if(a[i].suggest[j] == n) {
				printf("Ban da doan dung!\n");
				break;
			}
			else if(a[i].suggest[j] > n) printf("So ban vua doan lon hon so can tim\n");
			else printf("So ban vua doan nho hon so can tim\n");
		}
	}
}

void inDS(result *a, int total, float n) {
	int i, j;

	printf("\n%-25s%-6s%-6s%-6s%-6s\n", "Ho va ten", "L1", "L2", "L3", " L4");
	for(i = 0; i < total; i++) {
		printf("%-25s", a[i].hoTen);
		for(j = 0; j < 4; j++) {
			printf("%-6.1f", a[i].suggest[j]);
			a[i].doLech = tinhDoLech(n, a[i].suggest[j]);
			if(a[i].doLech == 0) break;
		}
		printf("\n");
	}
}

float tinhDoLech(float n, float soDoan) {
	float doLech;


	doLech = soDoan / n - 1;

	if(doLech < 0) doLech = -doLech;

	return doLech;
}

void sortArrayResult(result *list, int amount) {
	int i, j;
	int iMin;

	for(j = 0; j < amount - 1; j++) {
		iMin = j;
		for(i = j + 1; i < amount; i++) {
			if(list[i].doLech < list[iMin].doLech)
				iMin = i;
		}

		if (iMin != j)
			swap(&list[j], &list[iMin]);
	}
}

void swap(result *a, result *b) {
	result temp;

	memcpy(&temp, a, sizeof(result));
	memcpy(a, b, sizeof(result));
	memcpy(b, &temp, sizeof(result));
}

void inSapXep(result *a, int n) {
	int i;

	printf("\n%-5s%-25s%-s\n", "STT", "Ho va ten", "Do sai lech");
	for(i = 0; i < n; i++) {
		printf("%-5d%-25s%-.1f%%\n", i + 1, a[i].hoTen, a[i].doLech * 100);
	}
}

void timNguoiChoi(result *a, int n) {
	char s[10];
	float k, check = 0;
	int i;

	printf("\nNhap ten nguoi choi: ");
	getString(s);

	printf("Nhap so thuc: ");
	k = nhapSoThuc();

	printf("\nDanh sach nhung nguoi choi co ten nhu vay va gia tri do sai lech nho hon %4.1f%%\n", k);
	for(i = 0 ; i < n; i++) {
		if((strcmp(a[i].ten, s) == 0) && ((a[i].doLech * 100) < k)) {
			printf("%s\n", a[i].hoTen);
			check = 1;	
		}
	}
	if(check == 0) printf("Khong co nguoi choi thoa man yeu cau cua ban.\n");
}