MAIN_KEYS:
    DEFB $42 ; B
    DEFB $48 ; H
    DEFB $59 ; Y
    DEFB $36 ; 6
    DEFB $35 ; 5
    DEFB $54 ; T
    DEFB $47 ; G
    DEFB $56 ; V
    DEFB $4E ; N
    DEFB $4A ; J
    DEFB $55 ; U
    DEFB $37 ; 7
    DEFB $34 ; 4
    DEFB $52 ; R
    DEFB $46 ; F
    DEFB $43 ; C
    DEFB $4D ; M
    DEFB $4B ; K
    DEFB $49 ; I
    DEFB $38 ; 8
    DEFB $33 ; 3
    DEFB $45 ; E
    DEFB $44 ; D
    DEFB $58 ; X
    DEFB $0E ; SYMBOL SHIFT
    DEFB $4C ; L
    DEFB $4F ; O
    DEFB $39 ; 9
    DEFB $32 ; 2
    DEFB $57 ; W
    DEFB $53 ; S
    DEFB $5A ; Z
    DEFB $20 ; SPACE
    DEFB $0D ; ENTER
    DEFB $50 ; P
    DEFB $30 ; 0
    DEFB $31 ; 1
    DEFB $51 ; Q
    DEFB $41 ; A

E_UNSHIFT:
    DEFB $E3 ; READ
    DEFB $C4 ; BIN
    DEFB $E0 ; LPRINT
    DEFB $E4 ; DATA
    DEFB $B4 ; TAN
    DEFB $BC ; SGN
    DEFB $BD ; ABS
    DEFB $BB ; SQR
    DEFB $AF ; CODE
    DEFB $B0 ; VAL
    DEFB $B1 ; LEN
    DEFB $C0 ; USR
    DEFB $A7 ; PI
    DEFB $A6 ; INKEY$
    DEFB $BE ; PEEK
    DEFB $AD ; TAB
    DEFB $B2 ; SIN
    DEFB $BA ; INT
    DEFB $E5 ; RESTORE
    DEFB $A5 ; RND
    DEFB $C2 ; CHR$
    DEFB $E1 ; LLIST
    DEFB $B3 ; COS
    DEFB $B9 ; EXP
    DEFB $C1 ; STR$
    DEFB $B8 ; LN

EXT_SHIFT:
    DEFB $7E ; ~
    DEFB $DC ; BRIGHT
    DEFB $DA ; PAPER
    DEFB $5C ; \ ;
    DEFB $B7 ; ATN
    DEFB $7B ; {
    DEFB $7D ; }
    DEFB $D8 ; CIRCLE
    DEFB $BF ; IN
    DEFB $AE ; VAL$
    DEFB $AA ; SCREEN$
    DEFB $AB ; ATTR
    DEFB $DD ; INVERSE
    DEFB $DE ; OVER
    DEFB $DF ; OUT
    DEFB $7F ; (Copyright character)
    DEFB $B5 ; ASN
    DEFB $D6 ; VERIFY
    DEFB $7C ; |
    DEFB $D5 ; MERGE
    DEFB $5D ; ]
    DEFB $DB ; FLASH
    DEFB $B6 ; ACS
    DEFB $D9 ; INK
    DEFB $5B ; [
    DEFB $D7 ; BEEP

CTL_CODES:
    DEFB $0C ; DELETE
    DEFB $07 ; EDIT
    DEFB $06 ; CAPS LOCK
    DEFB $04 ; TRUE VIDEO
    DEFB $05 ; INVERSE VIDEO
    DEFB $08 ; CURSOR LEFT
    DEFB $0A ; CURSOR DOWN
    DEFB $0B ; CURSOR UP
    DEFB $09 ; CURSOR RIGHT
    DEFB $0F ; GRAPHICS

SYM_CODES:
    DEFB $E2 ; STOP
    DEFB $2A ; *
    DEFB $3F ; ?
    DEFB $CD ; STEP
    DEFB $C8 ; >=
    DEFB $CC ; TO
    DEFB $CB ; THEN
    DEFB $5E ; ^
    DEFB $AC ; AT
    DEFB $2D ; -
    DEFB $2B ; +
    DEFB $3D ; =
    DEFB $2E ; .
    DEFB $2C ; ,
    DEFB $3B ; ;
    DEFB $22 ; "
    DEFB $C7 ; <=
    DEFB $3C ; <
    DEFB $C3 ; NOT
    DEFB $3E ; >
    DEFB $C5 ; OR
    DEFB $2F ; /
    DEFB $C9 ; <>
    DEFB $60 ; pound
    DEFB $C6 ; AND
    DEFB $3A ; :

E_DIGITS:
    DEFB $D0 ; FORMAT
    DEFB $CE ; DEF FN
    DEFB $A8 ; FN
    DEFB $CA ; LINE
    DEFB $D3 ; OPEN#
    DEFB $D4 ; CLOSE#
    DEFB $D1 ; MOVE
    DEFB $D2 ; ERASE
    DEFB $A9 ; POINT
    DEFB $CF ; CAT

