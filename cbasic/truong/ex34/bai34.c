#include <stdio.h>
#include <string.h>
typedef struct _BstNode{
	char E[20], V[20];
	struct _BstNode *left;
	struct _BstNode *right;
}BstNode;
typedef struct{
	char string[20];
}StrArray;
BstNode* makeNode(char E[], char V[]);
BstNode* insert(BstNode* root, char E[], char V[]);
BstNode* readFile(FILE * f, BstNode * root);
void printTree(BstNode* root);
void search(BstNode * root, char S[]);
void translate(BstNode* root);

main(){
	int i;
	BstNode * root= NULL;
	FILE *f;
	do{
		printf("\n1. Read File to Tree\n2. Print Tree\n3. Translate English to Vietnamese\n4. Exit");
		printf("\nChose: ");
		scanf("%d", &i);
		while(getchar()!= '\n');
		switch(i){
			case 1 : root = readFile(f, root); break;
			case 2 : printTree(root); break;
			case 3 : translate(root); break;
		}
	}while(i != 4);
}
BstNode* makeNode(char E[], char V[]){
	BstNode* new_node;
	new_node = (BstNode*)malloc(sizeof(BstNode));
	if(new_node == NULL)
		printf("\nNot enough memory");
	else{
		strcpy(new_node->E, E);
		strcpy(new_node->V, V);
		new_node->left = new_node->right = NULL;

	}
	return new_node;
}
BstNode* insert(BstNode* root, char E[], char V[]){
	if (root == NULL)
		root = makeNode(E, V);
	else if (strcmp(E, root->E) < 0)
		root->left = insert(root->left, E, V);
	else
		root->right = insert(root->right, E, V);
	return root;
}
BstNode* readFile(FILE * f, BstNode * root){
	char E[20], V[20];
	f = fopen("/home/truong/c/data.txt", "rb");
	if(f == NULL)
		printf("\nFile No exist");
	while(fscanf(f, "%s", E) > 0){
		
		fgetc(f);
		fgets(V, 20, f);
		root = insert ( root, E, V);
	}
	fclose(f);
	return root;
}
void printTree(BstNode* root){
	if(root == NULL)
		return ;
	else{
		printf("\n%s---------%s", root->E, root->V);
		printTree(root->left);
		printTree(root->right);
	}
}
void translate(BstNode* root){
	StrArray S[100];
	char str[100];
	int i = 0 ,k = 0, j = 0;

	printf("\nString want translate: ");
	gets(str);
	for( j = 0; j < strlen(str); ++j){
		if(str[j] == ' '){
			S[i].string[k]= '\0';
			++i;
			k = 0;
			continue;
		}
		S[i].string[k] = str[j];
		++k;
	}
	S[i].string[k]= '\0';
	printf("\nResuft\n");
	for( j = 0; j<= i; ++j){
		
		search(root, S[j].string);
	}
}
void search(BstNode * root, char S[]){
	if(root == NULL)
		printf("\n%s------Thieu tu", S);
	else if(strcmp(S, root->E) == 0)
		printf("\n%s-------%s", root->E, root->V);
	else if(strcmp(S, root->E) < 0)
		search(root->left, S);
	else
		search(root->right, S);
}