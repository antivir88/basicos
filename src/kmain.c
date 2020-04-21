void isr_handler() {
}
void irq_handler() {
}

/* 0 - Black
// 1 - Blue
// 2 - Green
// 3 - Cyan
// 4 - Red
// 5 - Magenta
// 6 - Brown
// 7 - Light Grey
// 8 - Dark Grey
// 9 - Light Blue
// 10/a - Light Green
// 11/b - Light Cyan
// 12/c - Light Red
// 13/d - Light Magenta
// 14/e - Light Brown
// 15/f – White */

int text_length(char* str) {
    int len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}

void write_text(char* text, short color) {
    short* vga = (short*)0xb8000;

    for (int i = 0; i < text_length(text); ++i) {
        vga[i + 80] = color | text[i];
    }
}

void clear_screen() {
    short* vga = (short*)0xb8000;
    for (int i = 0; i < 80 * 25 * 2; i++) {
        vga[i] = 0;
    }
}

int kmain(void) {
    clear_screen();
    write_text("Happy+birthday+!", 0x0F00);
    write_text("Happy+birthday+", 0x0E00);
    write_text("Happy+birthday", 0x0D00);
    write_text("Happy+birthda", 0x0C00);
    write_text("Happy+birthd", 0x0B00);
    write_text("Happy+birth", 0x0A00);
    write_text("Happy+birt", 0x0900);
    write_text("Happy+bir", 0x0800);
    write_text("Happy+bi", 0x0700);
    write_text("Happy+b", 0x0600);
    write_text("Happy+", 0x0500);
    write_text("Happy", 0x0400);
    write_text("Happ", 0x0300);
    write_text("Hap", 0x0200);
    write_text("Ha", 0x0100);
    write_text("H", 0x0000);

    return 0xdeadbaba;
}
