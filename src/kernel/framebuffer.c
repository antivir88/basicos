#include "interrupts.h"


uint16 *textMemPtr;
int attributes = 0x0f;
int screen_x = 0, screen_y = 0;


void framebuffer_scroll(void)
{
    uint32 blank, temp;

    blank = 0x20 | (attributes << 8);

    if (screen_y >= 25) {
        temp = screen_y - 25 + 1;

        memcpy(textMemPtr, textMemPtr + temp * 80, (25 - temp) * 80 * 2);
        memsetw(textMemPtr + (25 - temp) * 80, blank, 80);

        screen_y = 25 - 1;
    }
}

void framebuffer_moveScreen(void)
{
    unsigned temp;

    temp = screen_y * 80 + screen_x;

    // http://www.brackeen.com/home/vga
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void framebuffer_move_screen_offset(int x, int y)
{
    screen_x += x;
    screen_y += y;

    if (screen_x < 0) {
      if (screen_y > 0) {
        screen_y--;
        screen_x = 80 - 1;
      } else {
        screen_x = 0;
      }
    }

    if (screen_x >= 80) {
      if (screen_y < (25 - 1)) {
        screen_x = 0;
        screen_y++;
      } else {
        screen_x = 80 - 1;
      }
    }

    if (screen_y < 0) {
      screen_y = 0;
    }

    if (screen_y >= 25) {
      screen_y = 25 - 1;
    }

    framebuffer_moveScreen();
}

void framebuffer_clear(void)
{
    unsigned blank;
    int i;

    blank = 0x20 | (attributes << 8);

    for(i = 0; i < 25; i++) {
        memsetw(textMemPtr + i * 80, blank, 80);
    }

    screen_x = 0;
    screen_y = 0;

    framebuffer_moveScreen();
}

void framebuffer_putHex(uint32 n)
{
    sint32 tmp;
	framebuffer_write("0x");

	char noZeroes = 1;

	int i;
	for(i = 28; i > 0; i -= 4) {
		tmp = (n>>i) & 0xF;
		if(tmp == 0 && noZeroes != 0) {
			continue;
		}

		if(tmp >= 0xA) {
			noZeroes = 0;
			framebuffer_putChar(tmp - 0xA+'a');
		} else {
			noZeroes = 0;
			framebuffer_putChar(tmp+'0');
		}
	}

	tmp = n & 0xF;
	if( tmp >= 0xA ) {
		framebuffer_putChar(tmp-0xA+'a');
	} else {
		framebuffer_putChar(tmp+'0');
    }
}

void framebuffer_putDec(uint32 n)
{
    if (n == 0) {
		framebuffer_putChar('0');
		return;
	}

	sint32 acc = n;
	char c[32];
	int i = 0;
	while(acc > 0) {
		c[i] = '0' + acc%10;
		acc /= 10;
		++i;
	}
	c[i] = 0;

	char c2[32];
	c2[i--] = 0;
	int j = 0;
	while(i >= 0) {
		c2[i--] = c[j++];
        }

	framebuffer_write(c2);
}

void framebuffer_write(char* c)
{
    int i = 0;

    while (c[i]) {
        framebuffer_putChar(c[i++]);
    }
}

void framebuffer_putChar(char c)
{
    uint16 *where;
    unsigned att = attributes << 8;

    if(c == 0x08) {
        if(screen_x != 0) {
            screen_x--;
        }
    } else if(c == 0x09) {
        screen_x = (screen_x + 8) & ~(8 - 1);

    } else if(c == '\r') {
        screen_x = 0;

    } else if(c == '\n') {
        screen_x = 0;
        screen_y++;

    } else if(c >= ' ') {
        where = textMemPtr + (screen_y * 80 + screen_x);
        *where = c | att;
        screen_x++;
    }

    if(screen_x >= 80) {
        screen_x = 0;
        screen_y++;
    }

    framebuffer_scroll();
    framebuffer_moveScreen();
}

int framebuffer_putString(char *text)
{
    size_t i;

    for (i = 0; i < strlen(text); i++) {
        framebuffer_putChar(text[i]);
    }

    framebuffer_putChar('\n');

    return i;
}

void framebuffer_setTextColor(uint8 foregraundColor, uint8 backgroundColor)
{
    attributes = (backgroundColor << 4) | (foregraundColor & 0x0F);
}

void framebuffer_init(void)
{
    outportb(0x03c8, 0x03); // FOREGROUND
    outportb(0x03c9, 0x72 >> 2);
    outportb(0x03c9, 0x9f >> 2);
    outportb(0x03c9, 0xcf >> 2);

    outportb(0x03c8, 0x01); // BACKGROUND
    outportb(0x03c9, 0x34 >> 2);
    outportb(0x03c9, 0x65 >> 2);
    outportb(0x03c9, 0xA4 >> 2);

    framebuffer_setTextColor(0x03, 0x01);

    textMemPtr = (uint16 *)0xB8000;

    framebuffer_clear();
}
