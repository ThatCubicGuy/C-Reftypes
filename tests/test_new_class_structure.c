#include "Defines.h"
#include "Class.h"
#include "Interface.h"
#include "VTable.h"
// #define refbase(TYPE) __underlying_##TYPE
// #define vtable(TYPE) __vtable_##TYPE
// #define This(TYPE) TYPE const this
// #define alloc_ref(TYPE) (TYPE)memalloc(refbase(TYPE))
// #define new(TYPE) TYPE##__ctor
// #undef call
// #define call(obj, METHOD, PARAMS...) (obj)->__VTable->METHOD(obj, PARAMS)
interface(MyIFace, (int,DoSomething,(int)))

class (MyClass, MyIFace, {
    int MyPublicField;
},(int,MyPublicMethod,(int)),(int,DoSomething,(int)))
primary_ctor(MyClass)(int nr);

int main(void)
{
    MyClass smth = new(MyClass)(15);
    printf("My field normally: %d\n", smth->MyPublicField);
    printf("My field after func: %d\n", call(smth,MyPublicMethod,25));
    printf("My field after interface func: %d\n", call(smth,DoSomething,25));
    printf("My field normally again: %d\n", smth->MyPublicField);
    return 0;
}

impl_class(MyClass, MyIFace, {
    int MyPublicField;
}, (int,MyPublicMethod,(int)),(int,DoSomething,(int)))

primary_ctor(MyClass)(int nr)
{
    assemble(MyClass);
    this->MyPublicField = nr;
    return this;
}

impl_method(MyClass, (int,DoSomething,(int x)))
{
    return this->MyPublicField + x * 2;
}

impl_method(MyIFace,(int,MyIFace_DoSomething,(int x)))
{
    return call(as_inheritor(MyClass, MyIFace, this),DoSomething,(x));;
}

impl_for(MyClass, MyIFace) {
    .DoSomething = MyIFace_DoSomething
};

impl_method(MyClass, (int,MyPublicMethod,(int x)))
{
    return this->MyPublicField + x;
}