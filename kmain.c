
void kmain(void)
{
    // 0 - Black,
    // 1 - Blue,
    // 2 - Green,
    // 3 - Cyan,
    // 4 - Red,
    // 5 - Magenta,
    // 6 - Brown,
    // 7 - Light Grey,
    // 8 - Dark Grey,
    // 9 - Light Blue,
    // 10/a - Light Green,
    // 11/b - Light Cyan,
    // 12/c - Light Red,
    // 13/d - Light Magenta,
    // 14/e - Light Brown,
    // 15/f – White.

    const short color = 0x0A00;
    const char* hello = "Write from C for NotSoft";
    short* vga = (short*)0xb8000;

    for (int i = 0; i < 24; ++i) {
        vga[i + 80] = color | hello[i];
    }

    return;
}

