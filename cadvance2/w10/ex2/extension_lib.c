#include "extension_lib.h"

int solve(char *fileName) {
	JRB tree;
	int choice;
	int case1Flag = 0;

	JRB anotherTree;

  	while(1) {
      choice = menuSpellChecking();

      switch(choice) {
        case 1:
        printf("You choose option %d\n", choice);
        if(case1Flag) {
        	printf("You already choose this option\n");
        	continue;
        }
        if((tree = buildTree(fileName)) == NULL) {
			return 1;
		}
		printf("Build tree successfully.\n");

		jrb_traverse(anotherTree, tree) {
		    printf("%s - %s\n", jval_s(anotherTree->key), jval_s(anotherTree->val));
		}
        case1Flag = 1;
        continue;
        case 2:
        printf("You choose option %d\n", choice);
        if(!case1Flag) {
        	printf("Please enter the first option first!\n");
        	continue;
        }
		checkingSpell(tree);
        continue;
        case 3:
        printf("You choose option %d\n", choice);
        printf("Bye bye\n");
        if(case1Flag) {
			jrb_free_tree(tree);
        }
        break;
        default:
        printf("It is not an option\n");
        continue;
      }
      break;
    }

	return 0;
}

JRB buildTree(char *fileName) {
	JRB tree;
	IS is;
	char *temp, *tempWord;
	int nf;
	int i;

	is = new_inputstruct(fileName);
	tree = make_jrb();

	while((nf = get_line(is)) >= 0) {
		if((temp = myMalloc(sizeof(char), SIZE)) == NULL) {
			return NULL;
		}
		if((tempWord = myMalloc(sizeof(char), SIZE)) == NULL) {
			return NULL;
		}

		sprintf(tempWord, "%s", is->fields[0]);
		for(i = 1; i < nf; i++) {
			sprintf(temp, "%s %s", temp, is->fields[i]);
		}

		(void) jrb_insert_str(tree, tempWord, 
							   new_jval_s(temp));
	}

	
	return tree;
}

void checkingSpell(JRB tree) {
	char *temp;
	JRB res;

	if((temp = myMalloc(sizeof(char), SIZE)) == NULL) {
		return;
	}

	printf("Please enter the string: \n");
	fgets(temp, SIZE, stdin);
	temp[strlen(temp) - 1] = '\0';

	if((res = jrb_find_str(tree, temp)) != NULL) {
		printf("This is misspelling, dumbass!\n");
		printf("The right way: %s\n", jval_s(res->val));
		return;
	}
	printf("Correct spelling\n");
}

int menuSpellChecking() {
    int option;

    printf("\n\t\tMENU\n");
    printf("\t1. Build tree from data file\n");
    printf("\t2. Spell checking\n");
    printf("\t3. Exit program\n");
    printf("\nWhich option would you like to choose?\n");

    do {
      option = getInt();
      if (option < 0 || option > 3) {
        printf("Invalid option! Please choose again!\n");
      }
    } while (option < 0 || option > 3);

    return option;
}