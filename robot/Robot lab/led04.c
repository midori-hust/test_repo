/*************************************************/
/*            LEDの約0.2秒毎の速い点滅（C言語） */
/*  　　　　　      　2004.8.20     by AND        */
/*************************************************/
#include <pic.h>
__CONFIG(0xFFFA); /* 初期設定 CP:OFF,PT:OFF,WT:OFF,HS */

wait0(short k)
{
/* 約(k×0.01)秒 のウェイト*/
	short i;
	short j; /* 16 Bit 変数の宣言 */
   	for(j=0;j<k;j++){ /* (k×3000)回の繰り返し */
		for(i=0;i<3000;i++){
		}
	}
}
main(void)
{
	TRISA = 0xFC; /* A 0,1:output, 2,3,4:input */
	TRISB = 0xC7; /* B0,1,2:input, B3,4,5:LEDoutput, other bits input */
	PORTA=0x00;    /*モータOFF */
	while(1){  /* 無限ループ */
		PORTB=0x00;    /* LED消灯 */
		wait0(20); /* 0.2秒ウェイト */
		PORTB=0x38;    /* LED点灯 */
		wait0(20); /*0.2秒ウェイト */
		}
}
