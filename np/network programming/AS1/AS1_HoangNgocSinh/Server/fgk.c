#include "adhuf.c"

huffnode_t *get_highest_equal_node( huffnode_t *node );
huffnode_t *get_highest_equal_LEAF_FGK( huffnode_t *node );
huffnode_t *get_highest_equal_nodeFGK( huffnode_t *node );
void update_treeFGK( int c );
//Tim node xa nhat
huffnode_t *get_highest_equal_node( huffnode_t *node )
{
	huffnode_t *highest = NULL;

	if ( node->parent->child_1 == node &&
			node->freq == node->parent->child_2->freq ) {
		highest = node->parent->child_2;
	}

	//Hieu chinh tinh chat sibling
	if (
		node->parent->parent &&
		node->parent->parent->child_1 == node->parent &&
		node->parent->parent->child_2 	
		&& node->freq == node->parent->parent->child_2->freq
		){
		highest = node->parent->parent->child_2;
	}
	else if (
		node->parent->parent &&
		node->parent->parent->child_2 == node->parent &&
		node->parent->parent->child_1	
		&& node->freq == node->parent->parent->child_1->freq
		){
		highest = node->parent->parent->child_1;
	}

	return highest;
}

huffnode_t *get_highest_equal_LEAF_FGK( huffnode_t *node )
{
	huffnode_t *highest = NULL;
	int i;

	/* start from the next numbered node. */
	for ( i = node->number + 1; i < ROOT_NODE_NUMBER; i++ ) {
		if (	/* Equal count? */
					node->freq == numbers[i]->freq ) {
			if (
					/* "leaf" nodes only! */
					numbers[i]->ch != INTERNAL_NODE
				)
				highest = numbers[i];
		}
		else break;
	}
	return highest;
}

/*
	tim node y xa nhat
*/
huffnode_t *get_highest_equal_nodeFGK( huffnode_t *node )
{
	huffnode_t *highest = NULL;
	int i;

	/* start from the next numbered node. */
	for ( i = node->number + 1; i < ROOT_NODE_NUMBER; i++ ) {
		/* Equal count? */
		if (	node->freq == numbers[i]->freq )
			highest = numbers[i];
		else break;
	}

	return highest;
}

/*
	Cap nhat lai cay
*/
void update_treeFGK( int c )
{
	huffnode_t *highest = NULL, *node = hufflist[c];
	//Khoi tao node 0 neu chua co
	if ( node == NULL ) {
		create_new_zero_node( c );
		node = hufflist[ c ];	
	}

	//Kiem tra tinh chat anh em
	if ( node->parent == zero_node->parent ) {
		highest = get_highest_equal_LEAF_FGK( node );
		if ( highest ){
			swap_nodes( node, highest );
		}

		//Tang trong so cua node
		node->freq++;

		//Duyet cho den node cha
		node = node->parent;
	}
	//Tim node y xa nhat
	while( node != top ) {
		highest = get_highest_equal_nodeFGK( node );
		if ( highest ){
			swap_nodes( node, highest );
		}

		//Cap nhat lai trong so
		node->freq++;

		//Duyet cho den node cha
		node = node->parent;
	}
}
