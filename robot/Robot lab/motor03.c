/*************************************************/
/*         モータ駆動プログラム(C言語)  　　　　　*/
/*  　　　　　（右車輪だけをまわす）  　　        */
/*　　    2004.8.23     by AND           	　*/
/*************************************************/
#include <pic.h>
__CONFIG(0xFFFA); /* 初期設定 CP:OFF,PT:OFF,WT:OFF,HS */

wait00(short k)
{
/* 約(k×0.01)ミリ秒 のウェイト(k×0.01msec wait)*/
	short i;
	short j; /* 16 Bit 変数の宣言 */
   	for(j=0;j<k;j++){ /* (k×3)回の繰り返し */
		for(i=0;i<3;i++){
		}
	
	}
	return 0;
}

main(void){   /* ---- rotate right motor and stop left motor ---- */
	TRISA = 0xFC; /* A 0,1:output, 2,3,4:input */
	TRISB = 0xC7; /* B0,1,2:input, B3,4,5:LEDoutput, other bits input */
	PORTA=0x00;    /*モータOFF */
	while(1){  /* 無限ループ */
		PORTA=0x01; /* right motor on */
		wait00(30);   /* 0.30msec wait */
		PORTA=0x00; /* both motor off */
		wait00(70);   /* 0.70msec wait */
	}
}
