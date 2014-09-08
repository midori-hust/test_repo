; 「ライントレースロボット LTR04－01」　ファイル名：LTR04-01.asm
;
;  サマーセミナー用　LEDの点滅
;
;――――《ポートの割り当て》――――――――――――――――――――――
;
;Aポート
;   A7     A6     A5     A4     A3     A2     A1     A0
;   ―     ―     ―      3      2      1     18     17   ← ピン番号
;   ―     ―     ―    ｽﾀｰﾄ　   　　　　　 左ﾓｰﾀ  右ﾓｰﾀ　← 用途
;   ―     ―     ―    入力　　　　   　　　出力　 出力　← 入出力
;    1      1      1      1      1      1      0      0   ← 初期設定
;
;Bポート
;   B7     B6     B5     B4     B3     B2     B1     B0
;   13     12     11     10      9      8      7      6   ← ピン番号
;  ﾗｲﾀ　  ﾗｲﾀ   右LED  中LED  左LED  右ｾﾝｻ  中ｾﾝｻ  左ｾﾝｻ  ← 用途
;  入力   入力　 出力　 出力　 出力　 入力　 入力　 入力　← 入出力
;    1      1      0      0      0      1      1      1   ← 初期設定
;
;――――《使用プロセッサ,ファイルの措定》―――――――――――――――
;
        LIST    p=16F84a        ;使用プロセッサは PIC16F84A
        INCLUDE <p16F84a.inc>   ;使用ファイル
;
;――――《特殊機能設定》――――――――――――――――――――――――
;
        __CONFIG _CP_OFF & _WDT_OFF & _PWRTE_OFF & _HS_OSC
                                ;コードプロテクトしない
                                ;ウォッチドッグタイマを動作させない
                                ;パワーアップタイマを起動させない
                                ;オッシレータモードは HS
;
;――――《汎用レジスタの割り当て》―――――――――――――――――――
;
        CBLOCK 0Ch              ; 0CH番地から割り当てる
        W_COUNT                 ;100μsecタイマ用カウンタ
        WM_COUNT                ;  10msecタイマ用カウンタ
        WS_COUNT                ;10msec*nタイマ用カウンタ
        ENDC                    ;割り当て終了(CBLOCKの最後につける)
;
;――――《プログラム開始》―――――――――――――――――――――――
;
        ORG     0               ;プログラムスタート番地
        GOTO    MAIN            ;メインルーチンへ
        ORG     4
        GOTO    INT             ;割り込み飛び先
        ORG     8
;
;――――《初期設定,初期状態設定》―――――――――――――――――――
;
MAIN:   BCF     INTCON,GIE      ;割り込み全て禁止
　　　  CLRF    PORTA           ;Aポートのラッチクリア
        CLRF    PORTB           ;Bポートのラッチクリア
;
        BSF     STATUS,RP0      ;Bank→1
;
        MOVLW   B'11111100'     ;Aポート初期設定 0:出力 1:入力
        MOVWF   TRISA
        MOVLW   B'11000111'     ;Bポート初期設定
        MOVWF   TRISB
;
        BCF     STATUS,RP0      ;Bank→0
;
        MOVLW   B'00000000'     ;モータの回転停止
        MOVWF   PORTA
;
        MOVLW   B'00000000'     ;LED消灯
        MOVWF   PORTB
;
;――――《スイッチ入力》――――――――――――――――――――――――
;
SW:     BTFSC   PORTA,4         ;スイッチ入力？
        GOTO    SW              ;スイッチ入力なし→SWへ
SW1:    BTFSS   PORTA,4         ;スイッチ入力あり,スイッチ離した？
        GOTO    SW1             ;スイッチ離していない→SW1へ
;
        CALL    T500            ;スイッチ離した→0.5sec待つ
;
;――――《ＬＥＤ点滅》―――――――――――――――――――――――――
;
LED:    MOVLW   B'00000000'     ;LED消灯
        MOVWF   PORTB
        CALL    T200            ;200msec
        MOVLW   B'00111000'     ;LED点灯
        MOVWF   PORTB
        CALL    T200            ;200msec
        GOTO    LED
;
;――――《タイマのサブルーチン　》―――――――――――――――――――
;
WAIT:   MOVLW   D'164'          ;100μsecのタイマ
        MOVWF   W_COUNT         
        DECFSZ  W_COUNT,F      
        GOTO    $-1             
        RETURN                  
;
WAIT_m: MOVLW   D'100'          ;10msecのタイマ
        MOVWF   WM_COUNT
        CALL    WAIT
        DECFSZ  WM_COUNT,F
        GOTO    $-2
        RETURN
;
WAIT_s: CALL    WAIT_m          ;10msec×nのタイマ    
        DECFSZ  WS_COUNT,F      ;WS_COUNT ← n
        GOTO    WAIT_s
        RETURN
;
T200:   MOVLW   D'20'           ;200msecのタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
        RETURN
;
T500    MOVLW   D'50'           ;500msecのタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
        RETURN
;
;――――――――――――――――――――――――――――――――――――
;割り込みは未使用
INT:    RETFIE
        END

