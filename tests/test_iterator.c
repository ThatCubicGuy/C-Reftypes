#define ITERATOR_START static int __controlvar = 0; switch (__controlvar) { case 0:
#define YIELD(ITEM) __controlvar = __LINE__; return ITEM; case __LINE__:
#define ITERATOR_END default: break; }

int smth()
{
    ITERATOR_START
    static int x = 7;
    while (x > 0) {
        YIELD(x)
        x -= 1;
    }
    ITERATOR_END
    return 0;
}

#include <stdio.h>

int main()
{
    int i;
    do {
        i = smth();
        printf("%d ", i);
    } while (i != 0);
    return 0;
}