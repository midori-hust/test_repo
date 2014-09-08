/* Cau 34
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLENGTH 100

typedef struct _Dictionary
{
	char word[20];
	char mean[MAXLENGTH];
} Dictionary;

typedef Dictionary DataType;

typedef struct _Node
{
	DataType info;
	struct _Node *l;
	struct _Node *r;
} Node;

typedef Node *tree;

void printTree(tree T);
int menu();
void save(tree *T, FILE *f);
void saveFile(tree *T, char *fileName);
void loadFile(tree *T, char *fileName);
Node* createNode(DataType new);
void insert(tree *T, DataType new);
void search(tree *T, char *key);
void translate(tree *T, char *input);

int main(int argc, char const *argv[])
{
	int n;
	char fileName[MAXLENGTH];
	char input[MAXLENGTH];
	tree T;
	T = NULL;

	if(argc < 2) {
		printf("Ban da nhap thieu tham so dau vao\n");
		return 1;
	}

	strcpy(fileName, argv[1]);

	while(1) {
		n = menu();
		switch(n) {
			case 1:
				printf("Ban chon %d\n", n);
				loadFile(&T, fileName);
				continue;
			case 2:
				printf("Ban chon %d\n", n);
				printTree(T);
				continue;
			case 3:
				printf("Ban chon %d\n", n);
				printf("Hay nhap vao xau ban can dich: \n");
				while(getchar() != '\n');
				gets(input);
				translate(&T, input);
				continue;
			case 4:
				printf("Ban chon %d\n", n);
				saveFile(&T, fileName);
				printf("Happy new year!\n");
				break;
		}
		break;
	}

	return 0;
}

void printTree(tree T) {
	if(T == NULL) return;
	printTree(T->l);
	printf("%s\t%s\n", T->info.word, T->info.mean);
	printTree(T->r);
}

int menu() {
	int n;

	printf("\n\n\t\tMenu\n");
	printf("1. Doc file tu dien\n");
	printf("2. Hien thi tu dien\n");
	printf("3. Dich thuat\n");
	printf("4. Thoat\n");

	do {
		printf("Ban chon?\n");
		scanf("%d", &n);

		if ((n<0) || (n>4))
		{
			printf("Ban da nhap sai lua chon, vui long nhap lai.\n");
		}


	} while((n<0) || (n>4));
	return n;
}

void save(tree *T, FILE *f) {
	if(*T == NULL) return;
	save(&(*T)->l, f);
	fprintf(f, "%s\t%s\n", (*T)->info.word, (*T)->info.mean);
	save(&(*T)->r, f);
}

void saveFile(tree *T, char *fileName) {
	FILE *f;

	if((f = fopen(fileName, "w")) != NULL) {
		if(*T == NULL) {
			printf("Cay rong.\n");
			fclose(f);
			return;
		}
		else {
			save(&(*T), f);
		}
	}

	fclose(f);
}

void loadFile(tree *T, char *fileName) {
	FILE *f;
	DataType temp;
	char ch;

	if((f = fopen(fileName, "r")) != NULL) {
		while(1) {
			fscanf(f, "%s", temp.word);
			if(feof(f)) break;
			ch = fgetc(f);
			fgets(temp.mean, MAXLENGTH, f);
			if(temp.mean[strlen(temp.mean) -1] == '\n') temp.mean[strlen(temp.mean) -1] = '\0';
			
			insert(&(*T), temp);
		}

	}
	else {
		printf("Khong doc duoc file.\n");
		return;
	}
	fclose(f);
}

Node* createNode(DataType new) {
	Node* node;
	node = (Node*)malloc(sizeof(Node));
	node->info = new;
	node->r = NULL;
	node->l = NULL;
}

void insert(tree *T, DataType new) {
	if((*T) == NULL)
		(*T) = createNode(new);
	else if(strcmp((*T)->info.word, new.word) < 0) insert(&(*T)->r, new);
	else if(strcmp((*T)->info.word, new.word) > 0) insert(&(*T)->l, new);
	else if(strcmp((*T)->info.word, new.word) == 0) return;
}

void search(tree *T, char *key) {
	DataType new;

	if((*T) == NULL) {
		printf("Khong tim duoc gia tri can tim.\n");
		printf("Xin hay nhap nghia cua tu nay vao tu dien: \n");
		gets(new.mean);
		strcpy(new.word, key);
		insert(&(*T), new);

		return;
	}
	if(strcmp((*T)->info.word, key) < 0) search(&(*T)->r, key);
	else if(strcmp((*T)->info.word, key) > 0) search(&(*T)->l, key);
	else printf("%s ", (*T)->info.mean);
}

void translate(tree *T, char *input) {
	char token[20];
	int i;
	int j = 0;
	int flag = 0;

	for(i=0; i<=strlen(input); i++) {
		if(isalpha(input[i])) {
			input[i] = tolower(input[i]);
		}

		if(i == 0 && input[i] == ' ') {
			flag = 1;
			continue;
		}

		if(input[i] != ' ') {
			flag = 0;
			token[j] = input[i];
			j++;
		}
		else if (input[i] == ' ' || input[i] == '\0') {
			if(flag == 0) {
				flag = 1;
				token[j] = '\0';
				j = 0;
				search(&(*T), token);
			}
		}
	}
	if(input[strlen(input) - 1] != ' ')
		search(&(*T), token);
	printf("\n");

}