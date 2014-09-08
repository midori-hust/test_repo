#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 100

typedef struct _Student
{
	/* data */
} Student;

typedef Student DataType;

typedef struct _Node
{
	DataType info;
	struct  _Node *l;
	struct  _Node *r;
} Node;

typedef Node *tree;

int menu();
DataType createNode(DataType new);
void insert(tree *T, DataType new);
void search(tree *T, DataType new);
void printTree(tree *T);
void saveFile(tree *T, char *fileName);
void loadFile(tree *T, char *fileName);
void freeTree(tree *T);

int main(int argc, char const *argv[])
{
/*	int frequence[26];
	char input[MAXLENGTH];
	int i, m;

	// Doc o day input

	for(i = 0; i < strlen(input); i++) {
		if(isalpha(input[i])) {
			m = input[i] - 'a';
			frequence[m] = frequence[m] + 1;
		}
	}
*/


	int n;
	tree T;
	T = NULL;
	char fileName[MAXLENGTH];

	if(argc < 2) {
		printf("Ban da nhap thieu tham so dau vao.\n");
		return;
	}

	strcpy(fileName, argv[1]);

	while(1) {
		n = menu();
		switch(n) {
			case 1:
				printf("Ban chon %d\n", n);

				continue;
			case 2:
				printf("Ban chon %d\n", n);

				continue;
			case 3:
				printf("Ban chon %d\n", n);

				continue;
			case 4:
				printf("Ban chon %d\n", n);
				//freeTree(&T);
				printf("Happy new year!\n");
				break;
		}
		break;
	}

	return 0;
}


int menu() {
	int n;
	printf("\t\tMENU\n", );
	printf("1. Chon 1\n", );
	printf("2. Chon 2\n", );
	printf("3. Chon 3\n", );
	printf("4. Thoat\n", );

	do {
		printf("Ban chon?\n");
		scanf("%d", &n);
		while(getchar() != '\n');

		if(n < 1 || n > 4) {
			printf("Ban da nhap sai lua chon.\n");
		}
	} while (n < 1 || n > 4);

	return n;
}

void saveFile(tree *T, char *fileName) {
	FILE *f;

	if(f = fopen(fileName, "w") != NULL) {
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

	if(f = fopen(fileName, "w") != NULL) {
		// TODO
	}
	else {
		printf("Mo file khong thanh cong.\n");
		return;
	}
	fclose(f);
}

void insert(tree *T, DataType new) {
	if(*T == NULL) {
		*T = createNode(new);
	}
}

DataType createNode(DataType new) {
	
}