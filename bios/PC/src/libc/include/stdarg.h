#ifndef STDARG_H
#define STDARG_H

/**
 * Для доступа к различному числу аргументов, переданных функциям.
 */

// DEFINITIONS

#define _AUPBND 1
#define _ADNBND 1

typedef char* va_list;


// METHODS

#define va_start(ap, A) \
 (void)((ap) = (char*)&(A) + _Bnd(A, _AUPBND))

#define va_arg(ap, T) \
 (*(T*)(((ap) += _Bnd(T, _AUPBND)) - _Bnd(T, _ADNBND)))

// va_copy

#define va_end(ap) \
 (void)0

#define _Bnd(X, bnd) \
 (sizeof(X)  + (bnd) & ~(bnd))


#endif
