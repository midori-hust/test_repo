#include "extension_lib.h"

int solve(char *fileName) {
	JRB tree;
	JRB anotherTree;
	IS is;
	char *temp;
	int nf;
	int i;

	is = new_inputstruct(fileName);
	tree = make_jrb();

	while((nf = get_line(is)) >= 0) {
		if((temp = myMalloc(sizeof(char), SIZE)) == NULL) {
			return 1;
		}

		for(i = 1; i < nf; i++) {
			sprintf(temp, "%s %s", temp, is->fields[i]);
		}

		(void) jrb_insert_int(tree, atoi(is->fields[0]), 
							   new_jval_s(temp));
	}
	jrb_traverse(anotherTree, tree) {
	    printf("%d - %s\n", jval_i(anotherTree->key), jval_s(anotherTree->val));
	}

	jrb_free_tree(tree);
	return 0;
}