;＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
;        トレースするプログラム（中級編）
;        2003.11.19
;         Y.ANDO
;＊＊＊＊ポートの割り当て＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
;
;      RB0～RB2（センサ入力）
;      RB3～RB5（LED出力）
;      RB6～RB7（未使用）
;      RA0～RA1（モータ出力）
;      RA2～RA3（未使用）
;      RA4     （スイッチ入力）
;
;＊＊＊＊使用プロセッサ，ファイルの指定＊＊＊＊＊＊＊＊＊＊＊＊＊
;
        LIST    p=pic16F84a        ;使用プロセッサは PIC16F84A
        INCLUDE <p16F84a.inc>   ;使用ファイル
;
;＊＊＊＊特殊機能設定＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
;
        __CONFIG _CP_OFF & _WDT_OFF & _PWRTE_OFF & _HS_OSC
                                ;コードプロテクトしない
                                ;ウォッチドッグタイマを動作させない
                                ;パワーアップタイマーを起動させない
                                ;オッシレータモードは HS
;
;＊＊＊＊汎用レジスタの割り当て＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
;
        CBLOCK 0Ch              ;0CH番地から割り当てる
        W_COUNT                 ;100μsec用タイマカウンタ
        WM_COUNT                ;  10msec用タイマカウンタ
        WS_COUNT                ;10msec*n用タイマカウンタ
        ENDC                    ;割り当て終了
;
;＊＊＊＊プログラム開始＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
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
;;;;;;;;;;;;;;;;;;;;プログラムの考え方;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;（●○○）反時計まわりに曲率半径の小さな円弧で動かす
;;;;（●●○）反時計まわりに曲率半径の大きな円弧で動かす
;;;;（○○●）時計まわりに曲率半径の小さな円弧で動かす
;;;;（○●●）時計まわりに曲率半径の大きな円弧で動かす
;;;;（○●○）直進
;;;;（○○○）なにもしない
;;;;
;;;;MT_TST    最初のチェック
;;;;C_TST     中センサがライン検出後のチェック
;;;;CCW_SML   反時計まわりに曲率半径の小さな円弧で動かす
;;;;CCW_BIG   反時計まわりに曲率半径の大きな円弧で動かす
;;;;CW_SML    時計まわりに曲率半径の小さな円弧で動かす
;;;;CW_BIG    時計まわりに曲率半径の大きな円弧で動かす
;;;;S_FAST    直進
;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;センサテスト開始;;;;;;;;;;;;;;;;;;;;;;;;;
SENS:	CLRF	PORTB           ;全LEDを消灯（センサテスト開始）
	BTFSC	PORTB,0         ;左センサが0の時，次の行をスキップ
	BSF	PORTB,3         ;左LEDを点灯
	BTFSC	PORTB,1         ;中センサが0の時，次の行をスキップ
	BSF	PORTB,4         ;中LEDを点灯
	BTFSC	PORTB,2         ;右センサが0の時，次の行をスキップ
	BSF	PORTB,5         ;右LEDを点灯
	
	NOP

;;;;;;;;;;;;最初のチェック，全センサに対してライン検出をチェック
MT_TST:	
	BTFSS	PORTB,1         ;中センサが1（白）の時，次の行をスキップ
	GOTO	C_TST	        ;（？●？）中センサがライン検出，次のチェックへ
	BTFSS	PORTB,0         ;左センサが1（白）の時，次の行をスキップ
	GOTO	CCW_SML         ;（●○？）反時計まわりに曲率半径の小さな円弧で動かす
	BTFSS	PORTB,2         ;右センサが1（白）の時，次の行をスキップ
	GOTO	CW_SML		;（○○●）時計まわりに曲率半径の小さな円弧で動かす
	GOTO	SENS            ;（○○○）SENSに戻る

;;;;;;;;;;;;中センサがライン検出後，次のチェック
C_TST:	BTFSS	PORTB,0         ;左センサが1（白）の時，次の行をスキップ
	GOTO	CCW_BIG         ;（●●？）反時計まわりに曲率半径の大きな円弧で動かす
	BTFSS	PORTB,2         ;右センサが1の時，次の行をスキップ
	GOTO	CW_BIG		;（○●●）時計まわりに曲率半径の大きな円弧で動かす
	GOTO	S_FAST          ;（○●○）直線走行

;;;;;;;;;;;;反時計まわりに曲率半径の小さな円弧で動かす
CCW_SML:MOVLW   B'00000011'     ;右モータON，左モータON
        MOVWF   PORTA
        MOVLW   D'3'           ;約0.03secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
;
	MOVLW   B'00000001'     ;右モータON，左モータOFF
        MOVWF   PORTA
        MOVLW   D'3'           ;約0.12secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
;
        MOVLW   B'00000000'     ;両モータOFF
        MOVWF   PORTA
        MOVLW   D'10'            ;約0.05secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
;
	GOTO	SENS            ;戻る

;;;;;;;;;;;;反時計まわりに曲率半径の大きな円弧で動かす
CCW_BIG:MOVLW   B'00000011'     ;右モータON，左モータON
        MOVWF   PORTA
        MOVLW   D'3'           ;約0.06secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
;
	MOVLW   B'00000001'     ;右モータON，左モータOFF
        MOVWF   PORTA
        MOVLW   D'1'           ;約0.09secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
;
        MOVLW   B'00000000'     ;両モータOFF
        MOVWF   PORTA
        MOVLW   D'10'           ;約0.05secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
;
	GOTO	SENS           ;SENSに戻る

;;;;;;;;;;;;時計まわりに曲率半径の小さな円弧で動かす
CW_SML: MOVLW   B'00000011'     ;右モータON，左モータON
        MOVWF   PORTA
        MOVLW   D'3'           ;約0.03secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
;
	MOVLW   B'00000010'     ;左モータON，右モータOFF
        MOVWF   PORTA
        MOVLW   D'3'           ;約0.12secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
;
        MOVLW   B'00000000'     ;両モータOFF
        MOVWF   PORTA
        MOVLW   D'10'            ;約0.05secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
;
	GOTO	SENS            ;SENSに戻る

;;;;;;;;;;;;時計まわりに曲率半径の大きな円弧で動かす
CW_BIG: MOVLW   B'00000011'     ;右モータON，左モータON
        MOVWF   PORTA
        MOVLW   D'3'           ;約0.06secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
;
	MOVLW   B'00000010'     ;左モータON，右モータOFF
        MOVWF   PORTA
        MOVLW   D'1'           ;約0.09secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
;
        MOVLW   B'00000000'     ;両モータOFF
        MOVWF   PORTA
        MOVLW   D'10'           ;約0.05secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
;
	GOTO	SENS           ;SENSに戻る

;;;;;;;;;;;;まっすぐに走行する
S_FAST: MOVLW   B'00000011'     ;右モータON，左モータON
        MOVWF   PORTA
        MOVLW   D'3'           ;約0.09secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
;
        MOVLW   B'00000000'     ;両モータOFF
        MOVWF   PORTA
        MOVLW   D'5'           ;約0.02secタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
;
	GOTO	SENS           ;SENSに戻る

;＊＊＊＊タイマサブルーチン＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
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

