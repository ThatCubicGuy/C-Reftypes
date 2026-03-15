#include "tests/all.h"
#include "Defines.h"
#include "Class.h"
public class (Human, {
    int age;
})
public empty_ctor(Human)

typedef struct _thing1 {
    int a, b;
} thing1;

typedef struct _thing2 {
    thing1;
    int c, d;
} thing2;

int main(void)
{
    thing2 waaa = (thing2) {
        .a = 2,
        .a = 3
    };
    printf("Numbers are %d %d %d %d", waaa.a, waaa.b, waaa.c, waaa.d);
    // test_big_ass_struct();
}
