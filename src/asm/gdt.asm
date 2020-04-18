global gdt_flush      ; Позволяет коду на C обращаться gdt_flush().
gdt_flush:
    mov eax, [esp+4]  ; Берет указатель на таблицу GDT, переданную в качестве параметра.
    lgdt [eax]        ; Загружает новый указатель GDT
    mov ax, 0x10      ; 0x10 является смещением, находящимся в таблице GDT и указываемым на наш сегмент данных
    mov ds, ax        ; Загрузка переключателей всех сегментов данных
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush   ; 0x08 является смещением на наш сегмент кода: Длинный переход!
.flush:
    ret


global idt_flush      ; Позволяет коду на C обращаться idt_flush().
idt_flush:
    mov eax, [esp+4]  ; Берет указатель на IDT, передаваемый в качестве параметра.
    lidt [eax]        ; Загружает указатель IDT.
    ret


global tss_flush      ; Позволяет коду на C обращаться tss_flush().
tss_flush:
    mov ax, 0x2b      ; Load the index of our TSS
                      ; The index is 0x28, as it is the 5th selector and each is 8 bytes long,
                      ; but we set the bottom two bits (making 0x2B) so that it has an RPL of 3, not zero.
    ltr ax            ; Load 0x2B into the task state register
    ret

