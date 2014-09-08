/* Cau 18: Thong tin ve mot sinh vien gom co: MSSV: xau 10 ky tu, Ho ten: xau 30 ky tu, diemthi: so thuc.
 * Viet chuong trinh thuc hien cong viec:
 * Dinh nghia cau truc SV
 * Nhap 1 so nguyen duong thoa man 2<=n<=10 tu ban phim. Sau do nhap lan luot
 * thong tin cua n sinh vien va luu no vao 1 danh sach lien ket.
 * Sau khi nhap xong hien thi thong tin cac sinh vien nay ra man hinh
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 100

typedef struct Student_ {
	char id[11];
	char name[31];
	float grade;
} Student;

typedef Student DataType;

typedef struct Node_ {
	DataType info;
	struct Node_ *next;
} Node;

Node* root = NULL;
Node* current = NULL;

void append(DataType newData);
void printLinkList();
Node* createNode(DataType newData);
int menu();
void insertTop(DataType newData);
void search(char *id);
void delete(char *id);
void sort();
void saveFile(char *fileName);
void loadFile(char *fileName);

int main(int argc, char const *argv[])
{
	int n;
	char name[MAXLENGTH];
	char id[MAXLENGTH];
	float grade;
	char fileName[MAXLENGTH];

	DataType newData;
	Node* newNode;

	if(argc < 2) {
		printf("Ban nhap thieu file can save!\n");
		printf("Nhap file save theo cu phap: \nrevive filename\n");
		return 1;
	}

	strcpy(fileName, argv[1]);
	//printf("Hay nhap so sinh vien can luu thong tin (2<=n<=10): \n");
	//scanf("%d", &n);

	while(1) {
	n = menu();
	while(getchar() != '\n');
	switch(n) {
		case 1:
			printf("Ban chon %d\n", n);
			printf("Hay nhap thong tin sinh vien\n");
			printf("Ten sinh vien (<= 30 ky tu): ");
			gets(newData.name);
			printf("Ma so sinh vien (<= 10 ky tu): ");
			//gets(newData.id);
			scanf("%s", newData.id);
			
			do {
			printf("Diem thi mon C basic: ");
			scanf("%f", &newData.grade);	
			if(newData.grade < 0 || newData.grade > 10)
				printf("Sai roi! Nhap lai dum cai!\n");
			} while(newData.grade < 0 || newData.grade > 10);
			printf("\n\n");
			insertTop(newData);
			//append(newData);
			continue;
		case 2:
			printf("Ban chon %d\n", n);
			printf("Hay nhap MSSV ban can tim: ");
			scanf("%s", id);
			while(getchar() != '\n');
			search(id);
			continue;
		case 3:
			printf("Ban chon %d\n", n);
			printf("Hay nhap MSSV ban can xoa: ");
			scanf("%s", id);
			while(getchar() != '\n');
			delete(id);
			continue;
		case 4:
			printf("Ban chon %d\n", n);
			printLinkList();
			continue;
		case 5:
			printf("Ban chon %d\n", n);
			printf("Sap xep sinh vien theo diem thi: \n");
			sort();
			continue;
		case 6:
			printf("Ban chon %d\n", n);
			saveFile(fileName);
			continue;
		case 7:	
			printf("Ban chon %d\n", n);
			loadFile(fileName);
			continue;
		case 8:
			printf("Ban chon %d\n", n);
			printf("Happy new year!\n");
			break;
		}
		break;
	}

	//printLinkList();
	return 0;
}


void append(DataType newData) {
	Node* newNode;

	newNode = createNode(newData);
	if (root == NULL) {
		root = newNode;
		current = newNode;
	}
	else {
		current->next = newNode;
		current = newNode;
	}
}

void printLinkList() {
	Node* i;

	if(root != NULL) {
		printf("Danh sach sinh vien: \n");
		for(i = root; i != NULL; i = i->next) {
			printf("Ten sinh vien: %s\nMSSV: %s\nDiem thi: %f\n\n", i->info.name, i->info.id, i->info.grade);
		}
	}
	else {
		printf("Danh sach trong!\n");
	}
}

Node* createNode(DataType newData) {
	Node* newNode;
	newNode =  (Node*)malloc(sizeof(Node));

	newNode->info = newData;
	newNode->next = NULL;
	return newNode;
}

int menu()
{
	int n;
	printf("\n\n\t\tMenu\n");
	printf("1. Nhap thong tin sinh vien\n");
	printf("2. Tim kiem sinh vien\n");
	printf("3. Xoa sinh vien\n");
	printf("4. Hien thi danh sach sinh vien\n");
	printf("5. Sap xep diem thi\n");
	printf("6. Save file\n");
	printf("7. Load file\n");
	printf("8. Thoat\n");
	do{
		printf("Ban chon?\n");
		/*if(scanf("%d", &n) == EOF)	{
			printf("Ban da nhap sai kieu, xin vui long nhap lai %d!\n", n);
			while(getchar() != '\n');
			continue;
		}*/
		scanf("%d", &n);
		if((n < 0) || (n>8))
			printf("Ban da nhap sai lua chon, xin vui long nhap lai!\n");

	} while((n < 0) || (n>8));

	return n;
}

void insertTop(DataType newData) {
	Node* newNode;

	newNode = createNode(newData);
	if (root == NULL) {
		root = newNode;
		current = newNode;
	}
	else {
		newNode->next = root;
		root = newNode;
	}
}

void search(char *id) {
	Node* i;
	int count = 0;

	if(root != NULL){
		for(i = root; i != NULL; i = i->next) {
			if(strcmp((i->info.id), id) == 0) {
				printf("Ten sinh vien: %s\nMSSV: %s\nDiem thi: %f\n\n", i->info.name, i->info.id, i->info.grade);
				count++;
			}
		}
	}
	else
		printf("Danh sach trong!\n");

	if(count == 0)
		printf("Khong tim thay MSSV can tim.\n");

}

void delete(char *id) {
	Node *i;
	Node *temp;
	Node *prev;

	if(root == NULL) {
		printf("Danh sach rong.\n");
		return;
	}

	for(i = root; i != NULL; i = i->next) {
		if(strcmp(i->info.id, id) == 0) {
			if(i == root) {
				temp = root;
				root = temp->next;
				free(temp);
			}
			else {
				for(prev = root; prev->next != NULL; prev = prev->next) {
					if(prev->next == i)
						break;
				}
				temp = i;
				prev->next = temp->next;
				free(temp);
				if(prev->next == NULL) current = prev;
			}
		}
	}
	printf("Da xoa xong!\n");

}

void sort() {
	Node* i;
	Node* j;
	DataType temp;

	if(root == NULL) {
		printf("Danh sach trong.\n");
		return;
	}

	for(j = root; j->next != NULL; j = j->next) {
		for(i = root; i->next != NULL; i = i->next) {
			if(i->info.grade > i->next->info.grade) {
				temp = i->info;
				i->info = i->next->info;
				i->next->info = temp;
			}
		}		
	}

}

void saveFile(char *fileName) {
	FILE *f;
	Node *i;

	if((f = fopen(fileName, "wb")) != NULL) {
		for(i = root; i != NULL; i = i->next) {
			fwrite(&(i->info), sizeof(DataType), 1, f);
		}
	}
	else {
		printf("Mo file khong thanh cong.\n");
		return;
	}
	fclose(f);
}

void loadFile(char *fileName) {
	FILE *f;
	DataType temp;

	if((f = fopen(fileName, "rb")) != NULL) {
		while(1) {
			fread(&temp, sizeof(DataType), 1, f);
			if(feof(f)) break;
			printf("aaaa%s\n%s\n%f\n", temp.name, temp.id, temp.grade);
		}
	}
	else {
		printf("Mo file khong thanh cong.\n");
		return;
	}
	fclose(f);
}