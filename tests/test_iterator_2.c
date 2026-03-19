#define ITERATOR_START static int __controlvar = 0; switch(__controlvar) { case 0:
#define ITERATOR_END default: break; } return false;
#define yield_return(ITEM) do { __controlvar = __LINE__; this->Current = ITEM; return true; case __LINE__: } while(0)
#define yield_break do { __controlvar = __LINE__; case __LINE__: return false; } while(0)
#define iterator(NAME, TYPE) bool NAME(TYPE const this)

typedef struct iter_s { int Current; } *iter;
iterator(MyIter, iter)
{
    ITERATOR_START
    yield_return(15);
    if (2 < 1) yield_break;
    else yield_return(2);
    static int x = 6;
    while (x > 0) {
        yield_return(x);
        x -= 1;
    }
    yield_break;
    ITERATOR_END
}

#include <stdio.h>

int main()
{
    struct iter_s x;
    while(MyIter(&x)) {
        printf("%d ", x.Current);
    }
}