    include "lib/vars.asm";
    ;include "lib/keyboard.asm"; 597

    org 0

BOOT:
    di
    xor a
    ld de, $ffff
    ; зачищаем экран выбранным цветом
    ld      a, 0x08 + 7
    call    CLS
    ;
    ld a, $03
    call BORDER
    ;
    jp START


RunBIOS:
    defb "BIOS (BREAK)",0
LabelOS:
    defb "Basic_OS",0
RunOS:
    defb "Press any key to start CLI",0
RunCLI:
    defb "[/]$ cat /etc/hostname",0
RunCLI2:
    defb "BasicOS",0
RunCLI3:
    defb "[/]$ ",0

START:
    ; пишем строку
    LD bc, $0114 // y-01 x-20
    LD hl, RunBIOS
    call PSTR
    ; пишем строку
    LD bc, $0a0a // y-12 x-12
    LD hl, LabelOS
    call PSTR
    ; пишем строку
    LD bc, $1602 // y-22 x-02
    LD hl, RunOS
    call PSTR

    call START
    jr $

START2:
    ; пишем строку
    LD bc, $0000 // y-00 x-00
    LD hl, RunCLI
    call PSTR
    LD bc, $0100 // y-00 x-00
    LD hl, RunCLI2
    call PSTR
    LD bc, $0200 // y-00 x-00
    LD hl, RunCLI3
    call PSTR

    call START2
    jr $



KEY:
    xor a
    in a, (#fe)
    cpl
    and 31
    jr z, KEY
    ; key pressed




;RAM_CHECK:
;    ld h, d
;    ld l, e

;RAM_FILL:
;    ld (hl), $02
;    dec hl
;    cp h
;    jr NZ, RAM_FILL



    ; зачищаем экран выбранным цветом
;    ld      a, 0x08 + 7
;    call    CLS

    ; пишем строку
;    LD bc, $0000 // y-0b x-02
;    LD hl, DFSTR
;    call PSTR

;    ld bc, $0100
;    ld hl, DFSTR2
;    call PSTR

;    ld a, $03
;    call BORDER

;    call START
;    jr $


;DFSTR:
;    defb "Hello, World! ",$7F,0
;DFSTR2:
;    defb "Delta-S users",0



; ==============================================
; Смена цвета бордюра , A
;
BORDER:
    out ($fe), a
    ret



; ==============================================
; Печать строки на экран , X-C Y-B
;
PSTR:
    ld a, (hl)
    and a
    ret z
    call PCHAR
    inc c
    inc hl
    jr PSTR



; ==============================================
; Печать символа
;
PCHAR:
    push bc
    push de
    push hl
    call SYMADDR ; находим символ для отрисовки
    ex de, hl
    call ACURSOR ; находим курсор
    ld b, 8
.pc1 ld a, (de)
    ld (hl), a
    inc h
    inc de
    djnz .pc1
    pop hl
    pop de
    pop bc
    ret



; ==============================================
; Выборка символа
;
SYMADDR:
    push    de
    sub     0x20
    ld      h, 0
    ld      l, a
    add     hl, hl
    add     hl, hl
    add     hl, hl
    ld      de, FONT
    add     hl, de
    pop     de
    ret



; ==============================================
; Позиция курсора
;
ACURSOR:
    ld      a, c
    and     0x1f
    ld      l, a
    ld      a, b
    and     0x07
    rrca
    rrca
    rrca
    or      l
    ld      l, a
    ld      a, b
    and     0x18
    or      0x40
    ld      h, a
    ret



; ==============================================
; Очистить экран в цвет A
;
CLS:    ld      bc, 0x02FF
        ld      hl, 0x5800  ; Отсюда копировать
        ld      de, 0x5801  ; Сюда
        ld      (hl), a     ; Байт инициализации
        rrca
        rrca
        rrca
        out     (254), a    ; Цвет бордера
        ldir                ; Копировать из (HL) -> (DE), HL++, DE++
        xor     a
        ld      hl, 0x4000
        ld      de, 0x4001
        ld      bc, 0x17FF
        ldir                ; Очистить графическую область
        ret



; ==============================================
; Вкрапления меток, для упрощения файла
;
TOKENS: include "lib/tokens.asm";
UDG: include "lib/udg.asm";
MESSAGES: include "lib/messages.asm";
FONT: include "lib/font.asm";
