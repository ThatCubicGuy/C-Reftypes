#include "Interface.h"
#include "Class.h"
#include "Struct.h"
#include "Defines.h"
#include "String.h"
#include "all.h"

struct(BigAssStruct, {
    long long a, b, c, d, e, f, g;
    object x, y, z, t, w, m, n, p;
})
{
    return default(BigAssStruct);
}

void test_big_ass_struct(void) {
    BigAssStruct bass = new(BigAssStruct)();
    printf("Big struct stuff: %lld %lld %lld %lld %lld %lld %lld %p %p %p %p %p %p %p %p\n",
        bass.a, bass.b, bass.c, bass.d, bass.e, bass.f, bass.g,
        bass.x, bass.y, bass.z, bass.t, bass.w, bass.m, bass.n, bass.p);
}