    defb 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff ;
    defb 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff ;
    defb 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff ;
    defb 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0 ;
    defb 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0 ;
    defb 0x0f, 0x0f, 0x0f, 0x0f, 0xf0, 0xf0, 0xf0, 0xf0 ;
    defb 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0 ;
    defb 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff ;

;L3802:  DEFB $01          ; 0 0 0 0 0 0 0 1           X
;        DEFB $03          ; 0 0 0 0 0 0 1 1          XX
;        DEFB $07          ; 0 0 0 0 0 1 1 1         XXX
;        DEFB $0F          ; 0 0 0 0 1 1 1 1        XXXX
;        DEFB $1F          ; 0 0 0 1 1 1 1 1       XXXXX
;        DEFB $3F          ; 0 0 1 1 1 1 1 1      XXXXXX
;        DEFB $7F          ; 0 1 1 1 1 1 1 1     XXXXXXX
;        DEFB $FF          ; 1 1 1 1 1 1 1 1    XXXXXXXX

;        DEFB $FE          ; 1 1 1 1 1 1 1 0    XXXXXXX
;        DEFB $FC          ; 1 1 1 1 1 1 0 0    XXXXXX
;        DEFB $F8          ; 1 1 1 1 1 0 0 0    XXXXX
;        DEFB $F0          ; 1 1 1 1 0 0 0 0    XXXX
;        DEFB $E0          ; 1 1 1 0 0 0 0 0    XXX
;        DEFB $C0          ; 1 1 0 0 0 0 0 0    XX
;        DEFB $80          ; 1 0 0 0 0 0 0 0    X
;        DEFB $00          ; 0 0 0 0 0 0 0 0
