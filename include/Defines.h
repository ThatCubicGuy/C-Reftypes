#ifndef DEFINES
#define DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef const char* string;
typedef const void* object;
typedef unsigned char byte;

#define memalloc(TYPE) (TYPE*)malloc(sizeof(TYPE))
#define memfree(OBJ) free(OBJ)
#define memresize(OBJ, newsize) realloc(OBJ, newsize)
#define memcopy(DEST, SOURCE, SIZE) MemCopy(DEST, SOURCE, SIZE)

#define public
#define private static

bool ValueEquator(size_t itemSize, object item1ref, object item2ref);

bool ReferenceEquator(object item1, object item2);

void MemCopy(void* dest, const void* source, size_t size);

void MemCopyWhile(void* dest, const void* source, bool (*predicate)(byte));

#endif