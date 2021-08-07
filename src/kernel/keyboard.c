#include "interrupts.h"


#define KEYS_COUNT 128


// keyboard layout
static uint8 keyboard_us[KEYS_COUNT] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
static uint8 keyboard_us_shift[KEYS_COUNT] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0,
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};


// keyboard interrupt
void keyboard_handler(registers_t *regs)
{
    uint8 scancode;

    scancode = inportb(0x60);

    keyboard_buffer_scan(scancode);

    if (scancode & 0x80) {
        // released
    } else {
        // pressed
    }
}

// Install keyboard to IRQ_1
void keyboard_init(void)
{
    keyboard_buffer_init();
    irq_install_handler(1, keyboard_handler);
}






static keyboard_buffer_t keyboard_buffer;


void keyboard_buffer_init(void)
{
    keyboard_buffer.head = keyboard_buffer.buffer;
    keyboard_buffer.tail = keyboard_buffer.buffer;
}

void keyboard_buffer_enqueue(uint8 ascii)
{
    if (((keyboard_buffer.head + 1 - keyboard_buffer.buffer) % KEYBOARD_BUF_SIZE) == ((keyboard_buffer.tail - keyboard_buffer.buffer) % KEYBOARD_BUF_SIZE)) {
      /* Keyboard buffer full, ignore key press */
    } else {
      *keyboard_buffer.head = ascii;
      keyboard_buffer.head = keyboard_buffer.buffer + ((keyboard_buffer.head + 1 - keyboard_buffer.buffer) % KEYBOARD_BUF_SIZE);
    }
}

uint8 keyboard_buffer_dequeue(void)
{
    uint8 ascii;

    if (keyboard_buffer.tail == keyboard_buffer.head) {
      return 0;
    } else {
      ascii = *keyboard_buffer.tail;
      keyboard_buffer.tail = keyboard_buffer.buffer + ((keyboard_buffer.tail + 1 - keyboard_buffer.buffer) % KEYBOARD_BUF_SIZE);

      return ascii;
    }
}

void keyboard_buffer_scan(uint8 scancode)
{
    static uint8 shifted = 0;
    
    /* Scancode handling */
    switch(scancode) {
      case 0x01: /* ESC */
        //shutdown();
        break;
  
      case 0x48: /* Up */
        framebuffer_move_screen_offset(0, -1);
        break;
  
      case 0x4B: /* Left */
        framebuffer_move_screen_offset(-1, 0);
        break;
  
      case 0x4D: /* Right */
        framebuffer_move_screen_offset(1, 0);
        break;
  
      case 0x50: /* Down */
        framebuffer_move_screen_offset(0, 1);
        break;
        
      case 0x2A: /* LShift pressed */
      case 0x36: /* Rshift pressed */
        shifted = 1;
        break;
  
      case 0xAA: /* LShift released */
      case 0xB6: /* Rshift released */
        shifted = 0;
        break;
        
      default:   /* All others */
        if (scancode & 0x80) {
          /* No action on released regular keys */
        } else {
          /* Enqueue pressed keys to buffer */
          if (shifted) {
            keyboard_buffer_enqueue(keyboard_us_shift[scancode]);
          } else {
            keyboard_buffer_enqueue(keyboard_us[scancode]);
          }
        }
        break;
    }
}






