#ifndef DEFINES
#define DEFINES

// Defines what a generic form of a symbol would be called with the given type parameters.
#define GenericName(ROOT, ...) JOIN(_, ROOT, __VA_ARGS__)

#define memalloc(TYPE) ((TYPE*)malloc(sizeof(TYPE)))
#define memfree(OBJ) free(OBJ)
#define memresize(OBJ, newsize) realloc(OBJ, newsize)
#define memcopy(DEST, SOURCE, SIZE) MemCopy(DEST, SOURCE, SIZE)

#define offset_of(MEMBER, ref) ((object)&((ref)->MEMBER) - (object)(ref))

// I am having too much fun.
#define public
#define internal
#define private static

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Class.h"
#include "Interface.h"
#include "Delegate.h"
#include "Struct.h"
#include "Tuple.h"
#include "Macros.h"

typedef const char* string;
typedef const void* object;
typedef unsigned char byte;

void MemCopy(void* dest, const void* source, size_t size);

void MemCopyWhile(void* dest, const void* source, bool (*predicate)(byte));

bool ValueEquator(size_t itemSize, object item1ref, object item2ref);

bool ReferenceEquator(object item1, object item2);

#endif