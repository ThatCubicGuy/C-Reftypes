#include "tests/all.h"

#define X(...) X_SELECT(,##__VA_ARGS__, X2, X1, X0)(__VA_ARGS__)

#define X_SELECT(_0, _1, _2, NAME, ...) NAME

#define X0() 100
#define X1(a) ((a) * 5)
#define X2(a, b) ((a) * (b))
#include "Delegate.h"
int main(void)
{
    Func(int, int, char);
    test_big_ass_struct();
}