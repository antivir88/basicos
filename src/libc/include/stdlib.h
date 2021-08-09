#ifndef STDLIB_H
#define STDLIB_H

/**
 * Для выполнения множества операций, включая конвертацию, генерацию
 * псевдослучайных чисел, выделение памяти, контроль процессов, окружения,
 * сигналов, поиска и сортировки.
 */

// DEFINITIONS

#ifdef __x86_64__
	typedef uint64 size_t;
#else
	typedef uint32 size_t;
#endif


// METHODS

#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))

void memcpy(void *dest, void *src, uint32 len);
void memset(uint8 *dest, uint8 val, uint32 len);
void memset_word(void *mem, uint16 value, size_t count);

int strcmp(char *str1, char *str2);
void strcpy(char *dest, const char *src);
char* strcat(char *dest, const char *src);
int strlen(char *src);


#endif
