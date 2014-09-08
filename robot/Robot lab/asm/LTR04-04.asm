; 「ライントレースロボット LTR04－04」　ファイル名：LTR04-04.asm
;
;  サマーセミナー用　ラインから脱線しても復帰する（ラインは黒）
;  ツインモータAタイプ用
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
        WQ_COUNT                ; 0.2msecタイマ用カウンタ
        WH_COUNT                ; 0.5msecタイマ用カウンタ
        WM_COUNT                ;  10msecタイマ用カウンタ
        WS_COUNT                ;10msec*nタイマ用カウンタ
        LE_COUNT                ;LED点滅用カウンタ
        LED_OUT                 ;LED表示用レジスタ
        SENSOR                  ;センサレジスタ
        SENFR                   ;センサフラグ右
        SENFL                   ;センサフラグ左
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
        MOVLW   B'00000000'     ;センサ表示LED消灯
        MOVWF   PORTB
;
        CLRF    SENSOR          ;センサレジスタクリア
        CLRF    SENFR           ;センサフラグ右クリア
        CLRF    SENFL           ;センサフラグ左クリア
;
;――――《センサ入力およびスイッチ入力チェック》――――――――――――
;
SW:     CALL    SENS            ;センサ入力チェック
;
        BTFSC   PORTA,4         ;スイッチ入力？
        GOTO    SW              ;スイッチ入力なし→SWへ
SW1:    BTFSS   PORTA,4         ;スイッチ入力あり,スイッチ離した？
        GOTO    SW1             ;スイッチ離していない→SW1へ
;
        CALL    T500            ;スイッチ離した→0.5sec待つ
;
;――――《ＬＥＤ点滅》―――――――――――――――――――――――――
;
        MOVLW   D'5'            ; 5回点滅
        MOVWF   LE_COUNT
LED:    MOVLW   B'00000000'     ;LED消灯
        MOVWF   PORTB
        CALL    T200            ;200msec
        MOVLW   B'00111000'     ;LED点灯
        MOVWF   PORTB
        CALL    T200            ;200msec
        DECFSZ  LE_COUNT
        GOTO    LED
;
        CALL    T500            ; 0.5sec待つ
;
;――――《ライントレース開始》―――――――――――――――――――――
;
MAIN2:  CALL    GO              ;左右のモータ回転　0.5msec
        CALL    SS              ;            停止　0.5msec
        CALL    SS
;
;――――《センサチェックおよび走行制御》――――――――――――――――――――
;                                ライン(黒)上ではセンサからの入力はゼロ,
;                                ＬＥＤ表示はビット反転して点灯している
;
SEN:    CALL    SENS            ;センサ入力
        BTFSS   SENSOR,1        ;×？×　中センサ？
        GOTO    SEN1            ;×0×　　　　　あり
        GOTO    SEN2            ;×1×　　　　　なし　右センサ？(SEN2)へ
;
SEN1:   BTFSS   SENSOR,0        ;？0×　左センサ？
        GOTO    SEN1_1          ;00×　　　　　あり
        GOTO    SEN1_2          ;10×　　　　　なし　右センサ？(SEN1_2)へ
;
SEN1_1: BTFSS   SENSOR,2        ;00？  右センサ？
        GOTO    MAIN2           ;000　　　　　あり　全部あり　　とりあえず直進
        CALL    L1              ;001　　　　　なし　やや右寄り　やや左へ
        GOTO    SEN
;
SEN1_2: BTFSC   SENSOR,2        ;10？  右センサ？
        GOTO    MAIN2           ;101　　　　　なし　正常　　　　直進
        CALL    R1              ;100　　　　　あり　やや左寄り　やや右へ
        GOTO    SEN
;
SEN2:   BTFSS   SENSOR,2        ;×1？　右センサ？
        GOTO    SEN2_1          ;×10　　　　　あり　左センサ？(SEN2_1)へ
        GOTO    SEN2_2          ;×11　　　　　なし　左センサ？(SEN2_2)へ
;
SEN2_1: BTFSS   SENSOR,0        ;？10  左センサ？
        GOTO    MAIN2           ;010　　　　　あり　あり得ない　とりあえず直進
        CLRF    SENFR           ;110　　　　　なし　左寄り　　　右フラグクリア
        BSF     SENFL,0         ;110　　　　　左フラグを立てる(0ビット目を1にする)
        CALL    R2              ;　　　　　　　　　　　左寄り　　　右へ
        GOTO    SEN
;
SEN2_2  BTFSC   SENSOR,0        ;？11  左センサ？
        GOTO    SEN3            ;111　　　　　なし　全部はずれた→SEN3へ
        CLRF    SENFL           ;011　　　　　あり　右寄り　　　左フラグクリア
        BSF     SENFR,0         ;011　　　　　右フラグを立てる(0ビット目を1にする)
        CALL    L2              ;        　　　　　　　右寄り　　　左へ
        GOTO    SEN
;
;――――《全部はずれたので,前の状態を調べる（111）》――――――――――――――
;
SEN3:   BTFSS   SENFR,0         ;右へずれた？
        GOTO    SEN3_2          ;右フラグ0（右ではない）→SEN3_2へ
SEN3_1: CALL    L2              ;右フラグ1（右へはずれた）→左へ
        CALL    SENS
        BTFSC   SENSOR,0        ;左センサ入ったか？
        GOTO    SEN3_1          ;1なら入るまでL2を実行
SEN3_3: CALL    L1              ;0ならやや左へ（左センサ入った）011
        CALL    SENS
        BTFSC   SENSOR,1        ;中センサ入ったか？
        GOTO    SEN3_3          ;1なら入るまでL1を実行　011
        BCF     SENFR,0         ;0　フラグを0にする　  001
        GOTO    SEN             ;SENへ
SEN3_2: BTFSS   SENFL,0         ;左へずれた？
        GOTO    STP             ;左フラグ0　左でもない（右でもない）→停止
SEN3_4: CALL    R2              ;左フラグ1（左へはずれた）→右へ
        CALL    SENS
        BTFSC   SENSOR,2        ;右センサ入ったか？
        GOTO    SEN3_4          ;1なら入るまでR2を実行
SEN3_5: CALL    R1              ;0ならやや右へ（右センサ入った）110
        CALL    SENS
        BTFSC   SENSOR,1        ;中センサ入ったか？
        GOTO    SEN3_5          ;1なら入るまでR1を実行　110
        BCF     SENFL,0         ;0　フラグを0にする　  100
        GOTO    SEN             ;SENへ
;
;――――《センサ入力のサブルーチン》――――――――――――――――――
;
SENS:   MOVF    PORTB,W         ;センサ入力
        MOVWF   SENSOR          ;SENSORに格納(姿勢制御用)
        MOVWF   LED_OUT         ;LED_OUTに格納(LED点灯用)
        RLF     LED_OUT         ;1ビット左へシフト
        RLF     LED_OUT         ;1ビット左へシフト
        RLF     LED_OUT         ;1ビット左へシフト
        COMF    LED_OUT         ;ビット反転
        MOVF    LED_OUT,W       ;LED_OUTに格納
        MOVWF   PORTB           ;LED点灯
        RETURN
;
;――――《モータ駆動のサブルーチン》――――――――――――――――――
;
GO:     MOVLW   B'00000011'     ;直進　0.5msec
        MOVWF   PORTA
        CALL    WAIT_h
        RETURN
;
R1:     MOVLW   B'00000010'     ;やや右へ
        MOVWF   PORTA           ;0.2msec 右停止
        CALL    WAIT_q
        CALL    SS
        CALL    SS
        RETURN
;
L1:     MOVLW   B'00000001'     ;やや左へ
        MOVWF   PORTA           ;0.2msec 左停止
        CALL    WAIT_q
        CALL    SS
        CALL    SS
        RETURN
;
R2:     MOVLW   B'00000010'     ;右へ
        MOVWF   PORTA           ;0.5msec 右停止
        CALL    WAIT_h
        CALL    SS
        CALL    SS
        RETURN
;
L2:     MOVLW   B'00000001'     ;左へ
        MOVWF   PORTA           ;0.5msec 左停止
        CALL    WAIT_h
        CALL    SS
        CALL    SS
        RETURN
;
SS:     MOVLW   B'00000000'     ;停止　0.5msec
        MOVWF   PORTA
        CALL    WAIT_h
        RETURN
;
STP:    MOVLW   B'00000000'     ;停止
        MOVWF   PORTA
        GOTO    STP
;
;――――《タイマのサブルーチン　》―――――――――――――――――――
;
WAIT:   MOVLW   D'164'          ;100μsecのタイマ
        MOVWF   W_COUNT         
        DECFSZ  W_COUNT,F      
        GOTO    $-1             
        RETURN                  
;
WAIT_h: MOVLW   D'5'            ;0.5msecのタイマ
        MOVWF   WH_COUNT
        CALL    WAIT
        DECFSZ  WH_COUNT,F
        GOTO    $-2
        RETURN
;
WAIT_q: MOVLW   D'2'            ;0.2msecのタイマ
        MOVWF   WQ_COUNT
        CALL    WAIT
        DECFSZ  WQ_COUNT,F
        GOTO    $-2
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
T500:   MOVLW   D'50'           ;500msecのタイマ
        MOVWF   WS_COUNT
        CALL    WAIT_s
        RETURN
;
;――――――――――――――――――――――――――――――――――――
;割り込みは未使用
INT:    RETFIE
        END

