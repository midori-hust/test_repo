#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct  PhuongAn {
	char p_a[30];
} PhuongAn;

typedef struct qt {
	char cauhoi[128];
	PhuongAn pa[3];
	int dapan;
} qt_type;

typedef struct Player {
	char name[100];
	int cauhoi[3];
	int paLuaChon[3];
	int Diem[3];
	int TongDiem;
} Player;

int menu();
int getInt();
void getString(char *s);
void taoCauHoi(qt_type *CauHoi, int *n);
void inCauHoi(qt_type *CauHoi, int n, int SoHieu);
int nhapSoHieuCauHoi(int n);
int nhapSoHieuDapAn();
void swap(char *a, char *b) ;
void daoDapAn(qt_type *CauHoi, int n);
void nhapBaCauHoi(int *a, int *b, int *c, int n);
void choi(qt_type *CauHoi, int n);


int main() {
	int choice, n, SoHieuCauHoi;
	qt_type CauHoi[100];
	
	while(1) {
		choice = menu();
	
		switch (choice) {
			case 1:	// Option 1
					taoCauHoi(CauHoi, &n);
					continue;
			case 2: // Option 2
					printf("\nNhap so hieu cau hoi can in: ");
					SoHieuCauHoi = nhapSoHieuCauHoi(n);
					inCauHoi(CauHoi, n, SoHieuCauHoi);
					continue;		
			case 3: // Option 3
					daoDapAn(CauHoi, n);
					continue;						
			case 4: choi(CauHoi, n);
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
	printf("Menu gameshow Toi yeu the thao\n");
	printf("1. Tao cau hoi\n");
	printf("2. In cau hoi\n");
	printf("3. Dao dap an\n");
	printf("4. Thuc hien choi\n");
	printf("5. Exit\n");
	printf("Moi ban nhap lua chon: ");

	do {
		choice = getInt();
		if((choice < 1) || (choice > 5)) printf("Ban chi duoc phep nhap tu 1 den 4. Moi ban nhap lai\n");
	} while((choice < 1) || (choice > 5));
	
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

void taoCauHoi(qt_type *CauHoi, int *n) {
	int i, j;

	printf("\nNhap so luong cau hoi: ");
	*n = getInt();

	printf("\nNhap noi dung cua cac cau hoi:\n");

	for(i = 0; i < *n; i++) {
		printf("\nCau hoi %d: ", i + 1);
		getString(CauHoi[i].cauhoi);

		for(j = 0; j < 3; j++) {
			printf("\nDap an %d: ", j + 1);
			getString(CauHoi[i].pa[j].p_a);
		}

		printf("\nDap an: ");
		CauHoi[i].dapan = getInt();
	}
}

void inCauHoi(qt_type *CauHoi, int n, int SoHieu) {
	int i, j;

	printf("\nCau hoi: %s\n", CauHoi[SoHieu - 1].cauhoi);
	printf("Cau tra loi:\n");

	for(j = 0; j < 3; j++) {
		printf("%d. %s\n", j + 1, CauHoi[SoHieu - 1].pa[j].p_a);
	}
}

int nhapSoHieuCauHoi(int n) {
	int SoHieu;
	
	do {
		SoHieu = getInt();
		if((SoHieu > n) || (SoHieu < 1)) printf("Khong co so hieu cau hoi do trong danh sach. Moi ban nhap lai\n");
	} while((SoHieu > n) || (SoHieu < 1));

	return SoHieu;
}

int nhapSoHieuDapAn() {
	int SoHieu;
	
	do {
		SoHieu = getInt();
		if((SoHieu > 3) || (SoHieu < 1)) printf("Khong co so hieu dap an do trong danh sach. Moi ban nhap lai\n");
	} while((SoHieu > 3) || (SoHieu < 1));

	return SoHieu;
}

void swap(char *a, char *b) {
	char temp[30];

	strcpy(temp, a);
	strcpy(a, b);
	strcpy(b, temp);
}

void daoDapAn(qt_type *CauHoi, int n) {
	int SoHieuCauHoi, SoHieuDapAn, j;

	printf("\nNhap so hieu cau hoi muon sua: ");
	SoHieuCauHoi = nhapSoHieuCauHoi(n);

	printf("\nNhap so hieu dap an: ");
	do {
		SoHieuDapAn = nhapSoHieuDapAn();

		if(CauHoi[SoHieuCauHoi - 1].dapan == SoHieuDapAn) printf("So hieu dap an da nhap trung voi dap an cu. Moi ban nhap lai\n");
		else swap(CauHoi[SoHieuCauHoi - 1].pa[SoHieuDapAn - 1].p_a, CauHoi[SoHieuCauHoi - 1].pa[CauHoi[SoHieuCauHoi - 1].dapan - 1].p_a);
	} while(CauHoi[SoHieuCauHoi - 1].dapan == SoHieuDapAn);

	printf("\nCap nhat lai cau hoi da sua: \n");
	inCauHoi(CauHoi, n, SoHieuCauHoi);

	CauHoi[SoHieuCauHoi - 1].dapan = SoHieuDapAn;
}

void nhapBaCauHoi(int *a, int *b, int *c, int n) {

	do {
		while(scanf("%d %d %d", a, b, c) != 3) {
			printf("Ban da nhap sai dinh dang. Moi ban nhap lai. \n");
			while(getchar() != '\n');
		}
		while(getchar() != '\n');
		if((*a == *b) || (*b == *c) || (*c == *a)) printf("Co hai cau hoi trung nhau. Moi ban nhap lai\n");
		if((*a < 1) || (*a > n) || (*b < 1) || (*b > n) || (*c < 1) || (*c > n)) printf("Co cau hoi khong nam trong danh sach. Moi ban nhap lai\n");
	} while(((*a == *b) || (*b == *c) || (*c == *a)) || ((*a < 1) || (*a > n) || (*b < 1) || (*b > n) || (*c < 1) || (*c > n)));
}

void choi(qt_type *CauHoi, int n) {
	Player player[3];
	int i, j;

	for(i = 0; i < 3; i++) {
		printf("\nNguoi choi thu %d\n", i +1);
		printf("\nNhap ten ban: ");
		getString(player[i].name);
		printf("\nNhap so hieu 3 cau hoi: ");
		nhapBaCauHoi(&(player[i].cauhoi[0]), &(player[i].cauhoi[1]), &(player[i].cauhoi[2]), n);

		player[i].TongDiem = 0;

		for(j = 0; j < 3; j++) {
			inCauHoi(CauHoi, n, player[i].cauhoi[j]);
			printf("\nMoi ban nhap dap an: ");
			player[i].paLuaChon[j] = nhapSoHieuDapAn();

			if(player[i].paLuaChon[j] == CauHoi[player[i].cauhoi[j] - 1].dapan){
				player[i].Diem[j] = 1;
				(player[i].TongDiem)++;
			}
			else player[i].Diem[j] = 0;
		}

		printf("\nIn ket qua\n");
		printf("Nguoi choi: %s - Tong diem: %d\n", player[i].name, player[i].TongDiem);

		printf("%-10s%-20s%-15s%-10s\n", "Cau hoi", "P/a lua chon", "P/a dung", "Diem");
		for(j = 0; j < 3; j++) {
			printf("%-10d%-20d%-15d%-10d\n", j + 1, player[i].paLuaChon[j], CauHoi[player[i].cauhoi[j] - 1].dapan, player[i].Diem[j]);
		}

	}
}