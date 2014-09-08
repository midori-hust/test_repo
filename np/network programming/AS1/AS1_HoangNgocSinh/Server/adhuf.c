#include "huf.h"

#define ZERO_NODE_SYMBOL  -2
#define INTERNAL_NODE     -1
#define ROOT_NODE_NUMBER  (H_MAX*2)

#define huffnode_t listnode_t

int hc; //danh dau ky tu hien thoi
//node 0                       
huffnode_t *zero_node = NULL;  
huffnode_t *numbers[ H_MAX * 2 + 1 ];

int aNUMBER = ROOT_NODE_NUMBER;

//tao node moi
void create_new_zero_node( int c );
//doi cho 2 node
void swap_nodes( huffnode_t *a, huffnode_t *b );

/*
	Tao node 0
*/
void create_new_zero_node( int c )
{
	//Tao con moi cua zero_node
	zero_node->child_1 = create_node();
	zero_node->child_2 = create_node();

	zero_node->child_1->parent = zero_node;
	zero_node->child_2->parent = zero_node;

	zero_node->ch = INTERNAL_NODE;

	/* new symbol's node is child_2 or "right." */
	hufflist[c] = zero_node->child_2;
	hufflist[c]->ch = c;

	/* Number the nodes. */
	zero_node->number = aNUMBER--;
	hufflist[c]->number = aNUMBER--;

	/*
		Store them in the hash array indexed by
		the node numbers. Perfect hash again.
	*/
	numbers[ zero_node->number ] = zero_node;
	numbers[ hufflist[c]->number ] = hufflist[c];

	/* new zero node is child_1 or "left." */
	zero_node = zero_node->child_1;
	zero_node->ch = ZERO_NODE_SYMBOL;
}
/*
	Doi cho 2 node
	
*/
void swap_nodes( huffnode_t *a, huffnode_t *b )
{
	huffnode_t *parent, *temp = NULL;
	int i = 0;
	if ( a->parent == b->parent ) {
		parent = a->parent;
		if ( parent->child_1 == a ) {
			parent->child_1 = b;
			parent->child_2 = a;
		}
		else {
			parent->child_1 = a;
			parent->child_2 = b;
		}

		goto numbers_stuff;
	}

	if ( a->parent->child_1 == a ) {
		a->parent->child_1 = b;
	}
	else {
		a->parent->child_2 = b;
	}

	if ( b->parent->child_1 == b ) {
		b->parent->child_1 = a;
	}
	else {
		b->parent->child_2 = a;
	}

	parent = a->parent;
	a->parent = b->parent;
	b->parent = parent;

	numbers_stuff:
	temp = numbers[ a->number ];
	numbers[ a->number ] = numbers[ b->number ];
	numbers[ b->number ] = temp;

	i = a->number;
	a->number = b->number;
	b->number = i;
}
