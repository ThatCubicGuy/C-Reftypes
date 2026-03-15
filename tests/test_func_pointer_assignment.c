#include <stdio.h>

typedef int func1(void*);
typedef int func2(int*);
typedef char func3(int, int);

int print_addr(void* addr)
{
    return (int)addr;
}

int print_addr_2(int* addr)
{
    return (int)addr;
}

int main()
{
    int smh;
    int* a = &smh;
    func1* f1;
    func2* f2;
    f1 = print_addr;
    f2 = print_addr_2;
    printf("Addresses are: %d, %d\n", f1(a), f2(a));
    f2 = (void*)print_addr;
    printf("Addresses are: %d, %d\n", f1(a), f2(a));
    func3* f3 = (void*)print_addr;
    printf("Horrible disaster: %c, %c\n", f3((int)a, (int)a));
    return 0;
}