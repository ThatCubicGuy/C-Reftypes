#include <stdio.h>

typedef struct _base smth1, *smth2;

struct _base {
    int a, b;
};

int main()
{
    smth1 amogus = (smth1) {
        .a = 2,
        .b = 3
    };
    smth2 amongi = &amogus;
    printf("%d %d\n", amongi->a, amongi->b);
}