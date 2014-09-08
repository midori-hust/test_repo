;＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
;        LED全点灯プログラム
;        2005.7.16
;         Y.ANDO
;＊＊＊＊ポートの割り当て＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
;
;＊＊＊＊（1）使用プロセッサ，ファイルの指定＊＊＊＊＊＊＊＊＊＊
;
        LIST    p=pic16F84a        ;使用プロセッサは PIC16F84A
        INCLUDE <p16F84a.inc>   ;使用ファイル
;
;＊＊＊＊（2）特殊機能設定＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
;
        __CONFIG _CP_OFF & _WDT_OFF & _PWRTE_OFF & _HS_OSC
                                ;コードプロテクトしない
                                ;ウォッチドッグタイマを動作させない
                                ;パワーアップタイマーを起動させない
                                ;オッシレータモードは HS
;
;＊＊＊＊（3）汎用レジスタの割り当て＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
;
        CBLOCK 0Ch              ;0CH番地から割り当てる
        W_COUNT                 ;100μsec用タイマカウンタ
        WM_COUNT                ;  10msec用タイマカウンタ
        WS_COUNT                ;10msec*n用タイマカウンタ
        ENDC                    ;割り当て終了
;
;＊＊＊＊（4）プログラム開始＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
;
        ORG     0               ;プログラムスタート番地
        GOTO    MAIN            ;メインルーチンへ
        ORG     4
        GOTO    INT             ;割り込み飛び先
        ORG     8
;
MAIN:   BCF     INTCON,GIE      ;割り込み全て禁止
        CLRF    PORTA           ;Aポートのラッチクリア
        CLRF    PORTB           ;Bポートのラッチクリア
;
        BSF     STATUS,RP0      ;Bank→1
;
        MOVLW   B'11111100'     ;Aポート,RA0とRA1は出力，他全て入力
        MOVWF   TRISA
        MOVLW   B'00000111'     ;Bポート,RB0,RB1,RB2は入力，他全て出力
        MOVWF   TRISB
;
        BCF     STATUS,RP0      ;Bank→0
;

;＊＊＊＊（5）LED点滅＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
LED:	
        MOVLW   B'00000000'     ;PORTBにB3,B4,B5にゼロを出力
        MOVWF   PORTB           ;LED消灯

        MOVLW   D'50'           ;約0.50secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s

	CALL	WAIT
        MOVLW   B'00111000'     ;PORTBのB3,B4,B5に1を出力
        MOVWF   PORTB           ;LED点灯

        MOVLW   D'50'           ;約0.50secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s

	GOTO	LED		;LEDに飛ぶ


;＊＊＊＊（6）タイマサブルーチン＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
;
;100μsecタイマ
;                               ;サイクル数 (CALL WAITで 2)
WAIT:   MOVLW   D'165'          ;1
        MOVWF   W_COUNT         ;1
        DECFSZ  W_COUNT,F       ;1*164+2
        GOTO    $-1             ;2*164
        RETURN                  ;2
                                ;計　500サイクル*0.2μsec=100μsec
                                ;これをサブルーチンとして使用するときは
                                ;MOVLW  D'164' とすると誤差が少ない
;
;10msecタイマ
WAIT_m: MOVLW   D'100'          ;繰り返し回数100
        MOVWF   WM_COUNT
        CALL    WAIT            ;100μsecタイマ
        DECFSZ  WM_COUNT,F      ;WM_COUNT-1が0なら2行下へ
        GOTO    $-2             ;2行上の命令に飛ぶ
        RETURN
;
;10msec*nのタイマ作成(1<n<255)
;WS_COUNTにnの値を入れてタイムを調整
WAIT_s: CALL    WAIT_m
        DECFSZ  WS_COUNT,F
        GOTO    WAIT_s
        RETURN
;割り込みは未使用
INT:    RETFIE
        END

