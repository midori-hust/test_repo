#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 100

typedef int DataType;

typedef struct _Node {
	DataType info;
	struct _Node *l;
	struct _Node *r;
	int count;
} Node;

typedef Node *tree;

Node* createNode(DataType new);
void insert(tree *T, DataType new);
void search(tree *T, DataType new);
DataType deleteLeftMostChild(tree *T);
void deleteNode(tree *T, DataType new);
void printTree(tree T);
void freeTree(tree *T);
int menu();
void saveFile(char *fileName);
void loadFile(tree *T, char *fileName);

int main(int argc, char const *argv[])
{
	int temp;
	int n;
	tree T;
	T = NULL;

	char fileName[MAXLENGTH];

	if(argc < 2) {
		printf("Ban nhap thieu file can save!\n");
		printf("Nhap file save theo cu phap: \nrevive filename\n");
		return 1;
	}

	strcpy(fileName, argv[1]);

	while(1) {
	n = menu();
	while(getchar() != '\n');
	switch(n) {
		case 1:
			printf("Ban chon %d\n", n);
			printf("Hay nhap so ban muon chen vao: \n");
			scanf("%d", &temp);
			while(getchar() != '\n');
			insert(&T, temp);
			continue;
		case 2:
			printf("Ban chon %d\n", n);
			printf("Hay nhap vao gia tri can tim kiem\n");
			scanf("%d", &temp);
			while(getchar() != '\n');
			search(&T, temp);
			continue;
		case 3:
			printf("Ban chon %d\n", n);
			printf("Hay nhap vao gia tri can xoa\n");
			scanf("%d", &temp);
			while(getchar() != '\n');
			deleteNode(&T, temp);
			continue;
		case 4:
			printf("Ban chon %d\n", n);
			printTree(T);
			continue;
		case 5:
			printf("Ban chon %d\n", n);
			freeTree(&T);
			continue;
		case 6:
			printf("Ban chon %d\n", n);
			loadFile(&T, fileName);
			continue;
		case 7:	
			printf("Ban chon %d\n", n);
			deleteLeftMostChild(&T);
			continue;
		case 8:
			printf("Ban chon %d\n", n);
			freeTree(&T);
			printf("Happy new year!\n");
			break;
		}
		break;
	}

	return 0;
}

Node* createNode(DataType new) {
	Node* newNode;

	newNode = (Node*)malloc(sizeof(Node));
	newNode->info = new;
	newNode->count = 1;
	newNode->l = NULL;
	newNode->r = NULL;
	return newNode;
}

void insert(tree *T, DataType new) {
	if((*T) == NULL)
		(*T) = createNode(new);
	else if(new < (*T)->info ) insert(&(*T)->l, new);
	else if(new > (*T)->info ) insert (&(*T)->r, new);
	else (*T)->count++;
}

void search(tree *T, DataType new) {
	if((*T) == NULL) {
		printf("Cay rong.\n");
		return;
	}
	if((*T)->info < new) search(&(*T)->l, new);
	else if((*T)->info > new) search (&(*T)->r, new);
	else printf("%d, %d\n", (*T)->info, (*T)->count);
}

DataType deleteLeftMostChild(tree *T) {
	DataType key;
	Node* temp;

	if((*T) == NULL) {
		printf("Cay rong.\n");
	}
	if((*T)->l == NULL) {
		temp = (*T);
		key = (*T)->info;
		(*T) = (*T)->r;
		free(temp);
		return key;
	}
	else {
		return deleteLeftMostChild(&(*T)->l);
	}
}

void deleteNode(tree *T, DataType new) {
	//Node* temp;
	if((*T) != NULL) {
		if(new < (*T)->info) deleteNode(&(*T)->l, new);
		else if(new > (*T)->info) deleteNode(&(*T)->r, new);
		else if(((*T)->l == NULL) && ((*T)->r == NULL)) {
			//free(*T);
			(*T) = NULL;
		}
		else if((*T)->l == NULL) {
			//temp = (*T);
			(*T) = (*T)->r;
			//free(temp);
		}
		else if((*T)->r == NULL) {
			//temp = (*T);
			(*T) = (*T)->l;
			//free(temp);
		}
			(*T)->info = deleteLeftMostChild(&(*T)->r);
	}
	else {
		printf("Khong tim thay.\n");
		return;
	}
}

void printTree(tree T) {
	if(T == NULL) return;
	printTree(T->l);
	printf("%d, %d\n", T->info, T->count);
	printTree(T->r);
}

void freeTree(tree *T) {
	if((*T) == NULL) return;
	freeTree(&(*T)->l);
	freeTree(&(*T)->r);
	free(*T);
	*T = NULL;
}

int menu() {
	int n;
	printf("\n\n\t\tMenu\n");
	printf("1. Nhap so can chen vao cay\n");
	printf("2. Tim kiem 1 gia tri\n");
	printf("3. Xoa gia tri\n");
	printf("4. Hien thi cay\n");
	printf("5. Free cay\n");
	printf("6. Load file\n");
	printf("7. Test deleteLeftMostChild\n");
	printf("8. Thoat\n");
	do{
		printf("Ban chon?\n");
		scanf("%d", &n);
		if((n < 0) || (n>8))
			printf("Ban da nhap sai lua chon, xin vui long nhap lai!\n");

	} while((n < 0) || (n>8));

	return n;
}

void saveFile(char *fileName) {
	FILE *f;

	if((f = fopen(fileName, "wt")) != NULL) {
		// TODO
	}
	else {
		printf("Mo file khong thanh cong.\n");
		return;
	}
	fclose(f);
}

void loadFile(tree *T, char *fileName) {
	FILE *f;
	DataType temp;

	if((f = fopen(fileName, "r")) != NULL) {
		// TODO
		while(1) {
			fscanf(f, "%d", &temp);
			if(feof(f)) break;
			insert(&(*T), temp);
		}
		
	}
	else {
		printf("Mo file khong thanh cong.\n");
		return;
	}
	fclose(f);
}
