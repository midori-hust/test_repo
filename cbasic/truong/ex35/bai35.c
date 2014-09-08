#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct _BstNode{
	char user[20];
	char pass[20];
	struct _BstNode * left;
	struct _BstNode * right;
}BstNode;

int checkUser(char user[]){
	int i;
	for(i = 0; i<strlen(user); ++i)
		if(user[i] == ' ')
			return 0;
	return 1;
}
int checkCharacter(char c){
	if( ((c >= 48)&&(c <= 57)) || ((c >= 65)&&(c<=90)) || ((c>= 97)&&(c <= 122)) ||( c == 95)||(c == 36))
		return 1;
	return 0;
	
}
int checkPass(char pass[]){
	int i;
	if(strlen(pass) < 6)
		return 0;
	for(i = 0; i <strlen(pass); ++i)
		if( !(checkCharacter(pass[i]) ) )
			return 0;
	return 1;

}
BstNode* makeNode(char user[], char pass[]){
	BstNode* new_node;
	new_node = (BstNode*)malloc(sizeof(BstNode));
	if(new_node == NULL)
		printf("\nNot enuogh memory");
	else{
		new_node->left = new_node->right =NULL;
		strcpy(new_node->user, user);
		strcpy(new_node->pass, pass);
	}
	return new_node;
}
BstNode* insert(BstNode* root, char user[], char pass[]){
	if(root == NULL)
		root = makeNode(user,pass);
	else if(strcmp(user, root->user) < 0)
		root->left = insert( root->left, user, pass);
	else
		root->right = insert(root->right, user, pass);
	return root;
}
BstNode* search(BstNode* root, char user[]){
	if(root == NULL)
		return NULL;
	else if(strcmp(root->user, user) == 0)
		return root;
	else if (strcmp(root->user, user) > 0)
		return search(root->left, user);
	else
		return search(root->right, user);
}

int check(BstNode* root, char user[], char pass[]){
	BstNode * p;
	p = search(root, user);
	if( (p != NULL) && (strcmp(p->pass, pass) == 0) )
		return 1;	
	return 0;
}
BstNode* findMin(BstNode* root){
	
	if(root == NULL)
		return NULL;
	else if(root->left == NULL)
		return root;
	return findMin(root->left);
}
BstNode* deleteNode(BstNode* root, char user[]){
	if(strcmp(user, root->user) < 0)
		root->left = deleteNode(root->left, user);
	else if(strcmp(user, root->user) > 0)
		root->right = deleteNode(root->right, user);
	else{
		if((root->left == NULL)&&(root->right == NULL)){
			free(root);
			root = NULL;
			
		}
			
		else if(root->left == NULL){
			BstNode * temp_node = root;
			root= root->right;
			free(temp_node);
			
		}
		else if(root->right == NULL){
			BstNode* temp_node = root;
			root = root->left;
			free(temp_node);
			
		}
		else{
			BstNode* p;
			p = findMin(root->right);
			strcpy(root->user, p->user);
			strcpy(root->pass, p->pass);
			root->right=deleteNode(root->right, user);

		}
	}
	return root;


}
void writeFile(BstNode *root, FILE *f){
	if(root == NULL)
		return;
	fprintf(f,"%s\t%s",root->user, root->pass);
	fputc(10,f);
	writeFile(root->left, f);
	writeFile(root->right, f);
}
void printTree(BstNode* root){
	if(root == NULL)
		return;
	printf("\n%s--------%s", root->user, root->pass);
	printTree(root->left);
	printTree(root->right);
}
void changePass(BstNode* root, char user[]){
	BstNode * p;
	char pass[20];

	p = search(root, user);
	printf("\nNew Password: ");
	gets(pass);
	if(checkPass(pass)){
		strcpy(p->pass, pass);	
	}
	else{
		printf("\nPass khong hop le");
	}
}

BstNode* readFile (FILE *f, BstNode* root){
	char user[20], pass[20];
	while(fscanf(f,"%s", user) > 0){
		fgetc(f);
		fgets(pass, 20,f);
		pass[strlen(pass)-1] = '\0';
		root = insert(root, user, pass);
	}
	return root;

}
main(){
	int i, j, k,count;
	char user[20], pass[20];
	BstNode* root = NULL;
	FILE *f;
	f = fopen("/home/truong/c/userpass.txt","rb");
	root = readFile (f, root);
	fclose(f);
	do{
		printf("\n1. Dang nhap\n2. Exit");
		printf("\nChose: ");
		scanf("%d", &i); while(getchar()!= '\n');
		switch(i){
			case 1:	count = 0;do{	
						printf("\nUser: "); gets(user);
						printf("\nPassword: "); gets(pass); ++count;
					}while(!(check(root,user,pass))&&(count!=3));
					if(check(root,user,pass))
						if(strcmp(user, "admin") != 0)
							do{
								printf("\n1. Doi mat khau\n2. Write to File\n3. Exit");
								printf("\nChose: ");
								scanf("%d", &j); while(getchar()!= '\n');
								switch(j){
									case 1: changePass(root, user);
											break;
									case 2:	f = fopen("/home/truong/c/userpass.txt", "wb");
											writeFile(root, f);
											fclose(f);
											break;

								}
							}while(j != 3);

						if(strcmp(user, "admin") == 0)
							do{
								printf("\n1. Creat new user\n2. Change Pass user\n3. Delete user\n4. Print List User\n5. writeFile\n6. Exit");
								printf("\nChose: ");
								scanf("%d", &k); while(getchar()!= '\n');
								switch(k){
									case 1:	printf("\nUser: "); gets(user);
											printf("\nPass: "); gets(pass);
											if(checkUser(user) && checkPass(pass))
												root = insert(root, user, pass);
											else
												printf("User or Pass khong hop le!");
											break;
									case 2: printf("\nUser: "); gets(user);
											changePass(root, user);
											break;
									case 3: printf("\nUser: "); gets(user);
											root = deleteNode(root, user);
											break;
									case 4: printTree(root);
											break;
									case 5: f = fopen("/home/truong/c/userpass.txt", "wb");
											writeFile(root, f);
											fclose(f);
											break;

								}
							}while(k != 6);

		}
	}while(i != 2);

}