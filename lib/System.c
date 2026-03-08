#include "Defines.h"

#define b(PTR) ((byte*)PTR)

public bool ValueEquator(size_t itemSize, object item1ref, object item2ref)
{
    for (int i = 0; i < itemSize; ++i) {
        if (b(item1ref)[i] != b(item2ref)[i]) return false;
    }
    return true;
}

public bool ReferenceEquator(object item1, object item2)
{
    return item1 == item2;
}

public void MemCopy(void* dest, const void* source, size_t size)
{
    for (int i = 0; i < size; ++i) {
        b(dest)[i] = b(source)[i];
    }
}

private bool IsNotNull(byte b) { return b; }

public void MemCopyWhile(void* dest, const void* source, bool (*predicate)(byte))
{
    int i;
    if (predicate == NULL || predicate == !NULL) predicate = IsNotNull;
    for (i = 0; predicate(b(source)[i]); ++i) {
        b(dest)[i] = b(source)[i];
    }
    b(dest)[i] = 0;
}