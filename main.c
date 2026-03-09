#include "tests/all.h"

#define X(...) X_SELECT(,##__VA_ARGS__, X3, X2, X1, X0)(__VA_ARGS__)

#define X_SELECT(_0, _1, _2, _3, NAME, ...) NAME

#define X0()
#define X1(a)
#define X2(a, b)
#define X3(a, b, c) DECLARE_METHOD(a, b, c)
typedef union thing_t {
    union thing_t h;
    struct {
        int a, b, c;
    };
    int v[3];
} thing;
typedef union __interface_IEnumerator { union __interface_IEnumerator __impl_IEnumerator;
    struct {
        int (*MoveNext)(struct __storage_IEnumerator const* This);
        void (*Reset)(struct __storage_IEnumerator const* This);
        void (*Dispose)(struct __storage_IEnumerator const* This);
        int Current;
    };
} *IEnumerator;
int main(void)
{
    union thing_t a;
    // Func(int, int, char);
    test_big_ass_struct();
}