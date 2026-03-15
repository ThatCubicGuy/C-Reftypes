#ifndef DEFINES
#define DEFINES


/**
 * Notes:
 *    In general, macros that are only part of other macros and never intended to be used
 *    are marked with __SCREAMING_SNAKE_CASE and the two underscores at the beginning.
 * 
 *    Macros used only with other macros but not exclusive to one place are marked with
 *    SCREAMING_SNAKE_CASE, sans the double underscores.
 * 
 *    Macros that I use in this library but don't see as being useful outside
 *    might be marked with PascalCase.
 * 
 *    Macros for use outside this library are in lowercase/snake_case.
 */

#include "Macros.h"
// Defines what a generic form of a symbol would be called with the given type parameters.
#define Generic(ROOT, ...) JOIN(_, ROOT, __VA_ARGS__)

#define memalloc(TYPE) ((TYPE*)malloc(sizeof(TYPE)))
#define memfree(OBJ) free(OBJ)
#define memresize(OBJ, newsize) realloc(OBJ, newsize)
#define memcopy(DEST, SOURCE, SIZE) MemCopy(DEST, SOURCE, SIZE)

#define offset_of(MEMBER, ref) ((object)&((ref)->MEMBER) - (object)(ref))

// I am having too much fun.
#define var auto
#define public
#define internal
#define private static
#define ref(T) T*
#define out(T) T* const

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef const char* string;
typedef const void* object;
typedef unsigned char byte;

void MemCopy(void* dest, const void* source, size_t size);

void MemCopyWhile(void* dest, const void* source, bool (*predicate)(byte));

bool ValueEquator(size_t itemSize, object item1ref, object item2ref);

bool ReferenceEquator(object item1, object item2);

#endif