section .text

extern isr_handler
extern irq_handler

extern gdt_ptr
extern idt_ptr


global load_gdt
global load_idt


global load_tss


; Загрузчик GDT векторов
load_gdt:
    lgdt [gdt_ptr]     ; Загружает новый указатель GDT
    mov ax, 0x10       ; 0x10 является смещением, находящимся в таблице GDT и указываемым на наш сегмент данных
    mov ds, ax         ; Загрузка переключателей всех сегментов данных
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush    ; 0x08 является смещением на наш сегмент кода: Длинный переход!
.flush:
    ret


; Загрузчик IDT векторов
load_idt:
    lidt [idt_ptr]     ; Загружает указатель IDT.
    ret

; Загрузчик TSS
load_tss:
    mov ax, 0x2b
    ltr ax
    ret


; IRQ sender to C
irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    call irq_handler ; Дёргаем обработчик IRQ
    ;mov eax, irq_handler
    ;call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp,8
    iret

; ISR sender to C
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    call isr_handler ; Дёргаем обработчик ISR
    ;mov eax, isr_handler
    ;call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret


; macro for ISR noerror
%macro ISR_NOERRCODE 1
global isr%1
isr%1:
  cli
  push byte 0
  push byte %1
  jmp isr_common_stub
%endmacro

; macro for ISR error
%macro ISR_ERRCODE 1
global isr%1
isr%1:
  cli
  push byte %1
  jmp isr_common_stub
%endmacro

; macro for IRQ
%macro IRQ 2
global irq%1
irq%1:
  cli
  push byte 0
  push byte %2
  jmp irq_common_stub
%endmacro


; ISR definitions
ISR_NOERRCODE 0  ;  0: Divide By Zero Exception
ISR_NOERRCODE 1  ;  1: Debug Exception
ISR_NOERRCODE 2  ;  2: Non Maskable Interrupt Exception
ISR_NOERRCODE 3  ;  3: Int 3 Exception
ISR_NOERRCODE 4  ;  4: INTO Exception
ISR_NOERRCODE 5  ;  5: Out of Bounds Exception
ISR_NOERRCODE 6  ;  6: Invalid Opcode Exception
ISR_NOERRCODE 7  ;  7: Coprocessor Not Available Exception
ISR_ERRCODE 8    ;  8: Double Fault Exception (With Error Code!)
ISR_NOERRCODE 9  ;  9: Coprocessor Segment Overrun Exception
ISR_ERRCODE 10   ; 10: Bad TSS Exception (With Error Code!)
ISR_ERRCODE 11   ; 11: Segment Not Present Exception (With Error Code!)
ISR_ERRCODE 12   ; 12: Stack Fault Exception (With Error Code!)
ISR_ERRCODE 13   ; 13: General Protection Fault Exception (With Error Code!)
ISR_ERRCODE 14   ; 14: Page Fault Exception (With Error Code!)
ISR_NOERRCODE 15 ; 15: Reserved Exception
ISR_NOERRCODE 16 ; 16: Floating Point Exception
ISR_NOERRCODE 17 ; 17: Alignment Check Exception
ISR_NOERRCODE 18 ; 18: Machine Check Exception
ISR_NOERRCODE 19 ; 19: Reserved
ISR_NOERRCODE 20 ; 20: Reserved
ISR_NOERRCODE 21 ; 21: Reserved
ISR_NOERRCODE 22 ; 22: Reserved
ISR_NOERRCODE 23 ; 23: Reserved
ISR_NOERRCODE 24 ; 24: Reserved
ISR_NOERRCODE 25 ; 25: Reserved
ISR_NOERRCODE 26 ; 26: Reserved
ISR_NOERRCODE 27 ; 27: Reserved
ISR_NOERRCODE 28 ; 28: Reserved
ISR_NOERRCODE 29 ; 29: Reserved
ISR_NOERRCODE 30 ; 30: Reserved
ISR_NOERRCODE 31 ; 31: Reserved


; IRQs definitions
IRQ 0,  32 ; IRQ0 - timer PIT
IRQ 1,  33 ; IRQ1 - keyboard
IRQ 2,  34 ; IRQ2 - !cascade!
IRQ 3,  35 ; IRQ3 - com2
IRQ 4,  36 ; IRQ4 - com1
IRQ 5,  37 ; IRQ5 - lpt2
IRQ 6,  38 ; IRQ6 - floppy
IRQ 7,  39 ; IRQ7 - lpt1
IRQ 8,  40 ; IRQ8  - CMOS clock
IRQ 9,  41 ; IRQ9  - free
IRQ 10, 42 ; IRQ10 - free
IRQ 11, 43 ; IRQ11 - free
IRQ 12, 44 ; IRQ12 - PS/2 mouse
IRQ 13, 45 ; IRQ13 - FPU
IRQ 14, 46 ; IRQ14 - Prim. ATA h.disk
IRQ 15, 47 ; IRQ15 - Sec. ATA h.disk
