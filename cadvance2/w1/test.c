#include "bst.h"

int main() {
	int choice;
	char filename[MAXLENGTH] = "BongDa.txt", filenameResult[MAXLENGTH] = "KetQua.txt";
	FILE *f, *fResult;
	Node *root;

	char tmp1[MAXLENGTH], tmp2[MAXLENGTH], str[MAXLENGTH];
	int home, away;
	int result1, result2;
	Node *node;

	root = NULL;

	if ((f = fopen(filename, "r+")) == NULL) {
		printf("Cannot open file %s\n", filename);
		return 1;
	}

	if ((fResult = fopen(filenameResult, "r+")) == NULL) {
		printf("Cannot open file %s\n", filenameResult);
		return 1;
	}

	while(1) {
		choice = menu();

		switch(choice) {
			case 1:
			printf("You choose option %d\n", choice);
			while(fscanf(f, "%s\t%s\t%d\t%d\n", tmp1, tmp2, &home, &away) != EOF) {
				printf("%s %s %d %d\n", tmp1, tmp2, home, away);

				if(home < away) {
					InsertNode(tmp1, &root, 0);
					InsertNode(tmp2, &root, 3);
				} else if(home > away) {
					InsertNode(tmp1, &root, 3);
					InsertNode(tmp2, &root, 0);
				} else {
					InsertNode(tmp1, &root, 1);
					InsertNode(tmp2, &root, 1);
				}
			}
			display(root);
			continue;
			case 2:
			printf("You choose option %d\n", choice);
			display(root);
			continue;
			case 3:
			printf("You choose option %d\n", choice);
			printf("Which football club do you want to search?\n");
			scanf("%s", str);
			node = Search(str, root);
			if (node == NULL) {
				printf("This football doesn't exist\n");
			} else {
				printf("Club's information:\nName: %s\nScore: %d\n", node->name, node->point);
			}
			continue;
			case 4:
			printf("You choose option %d\n", choice);
			break;
			case 5:
			printf("You choose option %d\n", choice);
			genResultFile(fResult, root);
			printf("Generating file: success\n");
			continue;
			case 6:
			printf("You choose option %d\n", choice);
			printf("Bye bye\n");
			freeTree(root);
			fclose(f);
			fclose(fResult);
			break;
			default:
			printf("It is not an option\n");
			continue;
		}
		break;
	}

	return 0;
}