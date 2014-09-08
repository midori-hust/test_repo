#include <stdio.h>

typedef struct _BstNode{
	char c;
	int count;
	struct _BstNode * left;
	struct _BstNode * right;
}BstNode;

int checkCharacter(char c);
BstNode* readFile(FILE* f, BstNode* root);
BstNode* makeNode(char c, int count);
BstNode* insert(BstNode * root, char c, int count);
void printCount(BstNode* root, char c);
void printThongKe(BstNode* root);

main(){
	BstNode* root = NULL;
	int  i;
	FILE* f;
	char c;
	do{
		printf("\n1. Print File and Make Tree\n2. Print Count \n3. Print Thong Ke\n4. Exit");
		printf("\nChose: ");
		scanf("%d", &i); while(getchar()!= '\n');
		switch(i){
			case 1: root = readFile(f, root);
					break;
			case 2: printf("\nChar: ");
					scanf("%c", &c);while(getchar()!= '\n');
					printCount(root,c); break;
			case 3: printThongKe(root); break;
		}
	}while(i!= 4);

}

int checkCharacter(char c){
	if( ((c >= 48)&&(c <= 57)) || ((c >= 65)&&(c<=90)) || ((c>= 97)&&(c <= 122)) )
		return 1;
	return 0;
	
}

BstNode* readFile(FILE* f, BstNode* root){
	char c;
	char s[30];
	int A[256], i;
	for(i = 0; i <259; A[i] = 0,++i);
	printf("\nNhap Dduong dan FIle: ");
	gets(s);
	f= fopen(s, "rb");

	printf("\nFile:\n");
	while( (c = fgetc(f)) != EOF){
		printf("%c", c);
			if(checkCharacter(c))
				++A[c];		
	}
	printf("\n");
	fclose(f);
	
	for( i = 0; i< 256 ; ++i){
		if(A[i] > 0){
			root = insert(root, i,A[i]);
			printf("\n%c: %d", i, A[i]);
		}
	}
	return root;
}

BstNode* makeNode(char c, int count){
	BstNode* new_node;
	new_node = (BstNode*)malloc(sizeof(BstNode));
	if(new_node == NULL)
		printf("\nNot enough memory!");
	else{
		new_node->c= c;
		new_node->count= count;
		new_node->left= new_node->right= NULL;
	}

	return new_node;
}
BstNode* insert(BstNode * root, char c, int count){
	if(root == NULL)
		root=makeNode(c, count);
	else if( c < root->c)
		root->left=insert(root->left, c, count);
	else
		root->right=insert(root->right, c, count);
	return root;
}
void printCount(BstNode* root, char c){
	if (root == NULL)
		printf("\nKhong co");
	else if(root->c == c){
		printf("\nCount of %c : %d", root->c, root->count);
	}
	else if(c < root->c)
		printCount(root->left, c);
	else
		printCount(root->right, c);

}
void printThongKe(BstNode* root){
	if( root == NULL)
		return;
	else{
		printf("\n%c-------%d", root->c, root->count);
		printThongKe(root->left);
		printThongKe(root->right);
	}
}
