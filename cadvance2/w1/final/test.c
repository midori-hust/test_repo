#include "bst.h"

int main() {
	int choice;
	char filename[MAXLENGTH] = "BongDa.txt", filenameResult[MAXLENGTH] = "KetQua.txt";
	FILE *f, *fResult;
	Node *root;
	Node *temp_node;

	char tmp1[MAXLENGTH], tmp2[MAXLENGTH], str[MAXLENGTH];
	int home, away;
	int result1, result2;
	Node *node;

	int i = 0;
	int pnt;
	Key temp_key1, temp_key2;
	int flag1 = 0, flag4 = 0;

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

				strcpy(temp_key1.name, tmp1);
				strcpy(temp_key2.name, tmp2);

				if(home < away) {
					temp_key1.point = 0;
					temp_key2.point = 3;
				} else if (home > away) {
					temp_key1.point = 3;
					temp_key2.point = 0;
				} else {
					temp_key1.point = 1;
					temp_key2.point = 1;
				}

				InsertNode(&temp_key1, &root);
				InsertNode(&temp_key2, &root);
				flag1 = 1;
			}
			display(root);
			continue;

			case 2:
			printf("You choose option %d\n", choice);
			if (!flag1) {
				printf("Please choose option 1 first\n");
				continue;
			}
			display(root);
			continue;
			
			case 3:
			printf("You choose option %d\n", choice);
			if (!flag1) {
				printf("Please choose option 1 first\n");
				continue;
			}
			printf("Which football club do you want to search?\n");
			while(getchar() != '\n');
			//scanf("%s", str);
			fgets(str, MAXLENGTH, stdin);
			str[strlen(str) - 1] = '\0';
			node = Search(str, root);
			if (node == NULL) {
				printf("This football doesn't exist\n");
			} else {
				printf("Club's information:\nName: %s\nScore: %d\n", node->content.name, node->content.point);
			}
			continue;

			case 4:
			printf("You choose option %d\n", choice);
			if (!flag1) {
				printf("Please choose option 1 first\n");
				continue;
			}
			printf("Enter the relegated point: ");
			pnt = getInt();
			for(i=0; i<=pnt; i++) {
				while ((temp_node = searchForRelegated(i, root)) != NULL) {
					DeleteNode(&temp_node->content, &root);
				}
			}
			display(root);
			flag4 = 1;
			continue;

			case 5:
			printf("You choose option %d\n", choice);
			if (!flag1) {
				printf("Please choose option 1 first\n");
				continue;
			}
			if (!flag4) {
				printf("Please choose option 4 first\n");
				continue;
			}
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