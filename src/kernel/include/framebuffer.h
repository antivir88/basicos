#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

/** Фреймбуфер - аппаратно-независимый уровень абстракции для вывода графики
 *  на монитор, обычно через консоль.
 *
 * /dev/fd0 - Область видеопамяти
 * fbui - Подсистема окон FrameBufferUI, представляющая базовую
 *        2D-функциональность с небольшим потреблением памяти.
 */

#include "stdint.h"


void framebuffer_init(void);
void framebuffer_setTextColor(uint8 foregraundColor, uint8 backgroundColor);
void framebuffer_write(char* c);
int  framebuffer_putString(char *text);
void framebuffer_putChar(char ch);
void framebuffer_putHex(uint32 n);
void framebuffer_putDec(uint32 n);
void framebuffer_clear(void);
void framebuffer_moveScreen(void);
void framebuffer_scroll(void);

void framebuffer_move_screen_offset(int x, int y);


#endif
