#ifndef STDINT_H
#define STDINT_H

/** Определения различных типов целых чисел.
 */


typedef unsigned long long  uint64;
typedef          long long  sint64;
typedef   signed long long   int64;

typedef unsigned int        uint32;
typedef          int        sint32;
typedef   signed int         int32;

typedef unsigned short      uint16;
typedef          short      sint16;
typedef   signed short       int16;

typedef unsigned char        uint8;
typedef          char        sint8;
typedef   signed char         int8;



// Временно притащил из string чтобы не затаскивать его методы
#ifdef __x86_64__
    typedef uint64 size_t;
#else
    typedef uint32 size_t;
#endif


#endif
