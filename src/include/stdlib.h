#ifndef STDLIB_H
#define STDLIB_H


#define NULL ((void*)0)
#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))


typedef enum { false = 0, true = 1 } bool;

typedef unsigned long long uint64;
typedef   signed long long  int64;
typedef unsigned int       uint32;
typedef   signed int        int32;
typedef unsigned short     uint16;
typedef   signed short      int16;
typedef unsigned char       uint8;
typedef   signed char        int8;


#ifdef __x86_64__
	typedef uint64 size_t;
#else
	typedef uint32 size_t;
#endif


void outb(uint16 port, uint8 value);
void outw(uint16 port, uint8 value);
void outl(uint16 port, uint8 value);
uint8  inb(uint16 port);
uint16 inw(uint16 port);
uint32 inl(uint16 port);

void memcpy(void *dest, void *src, uint32 len);
void memset(uint8 *dest, uint8 val, uint32 len);
void memset_word(void *mem, uint16 value, size_t count);

int strcmp(char *str1, char *str2);
void strcpy(char *dest, const char *src);
char* strcat(char *dest, const char *src);
int strlen(char *src);


#endif
