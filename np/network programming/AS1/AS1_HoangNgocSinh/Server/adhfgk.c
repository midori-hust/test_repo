#include "gtbitio.h"
#include "fgk.c"

void adh_init_first_node( int c );
void adh_encode_symbol ( int c );
int  adh_decode_symbol ( void );

void adh_init_first_node( int c )
{
	//Khoi tao cay
	init_hufflist();
	
	/*
	Khoi tao node 0
	*/
	top = zero_node = create_node();

	aNUMBER = ROOT_NODE_NUMBER; 

	//Cap nhat lai cay
	update_treeFGK( c );
}


//ma hoa ky tu c
void adh_encode_symbol ( int c )
{
	if ( hufflist[c] ){ 
		hcompress( hufflist[c] );
	}
	else {
		hcompress( zero_node );
		put_nbits( c, hsymbol_bit_size );
	}
	update_treeFGK( c );
}


//Giai ma ky tu
int adh_decode_symbol ( void )
{
	int c;

	c = hdecompress( top );

	if ( c == ZERO_NODE_SYMBOL ) {
		c = get_nbits( hsymbol_bit_size );
	}
	update_treeFGK( c ); 
	return c;
}
