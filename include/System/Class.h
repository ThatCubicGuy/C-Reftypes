#ifndef C_CLASSES
#define C_CLASSES
#include "Macros.h"
#include "VTable.h"

/*
Some notes:
    Classes must have their own separate .h and .c files. Implementations must appear
    only once, but the header may be included anywhere. Any macros with "DEFINE_" go in .h,
    while "IMPLEMENT_" should appear ONLY in a single .c file.
*/

#define storage(REFTYPE) __storage_##REFTYPE
#define refbase(REFTYPE) __underlying_##REFTYPE

#pragma region Initialization
// Calls the constructor for a type. Signature must be specified (empty for no parameters).
#define new(TYPE, ...) CAT(TYPE##__, JOIN(_, ctor, __VA_ARGS__))
// Casts the following initializer to the base struct of the given reference type.
#define init(REF_TYPE) (refbase(REF_TYPE))
// Assembles the given type inside a constructor.
#define assemble(TYPE) TYPE this = TYPE##__asm()

// Calls the parameterless constructor on a new variable with name objname,
// and initializes it with the following initializer.
#define new_init(TYPE, objname) TYPE objname = new(TYPE)(); *objname = init(TYPE)

// Allocates memory for a reference type and returns a pointer to the allocated block.
#define alloc_ref(REF_TYPE) (REF_TYPE)memalloc(refbase(REF_TYPE))
// Allocates memory for a reference type and initializes it with the following initializer.
#define alloc_init(TYPE, objname) TYPE objname = alloc_ref(TYPE); *objname = init(TYPE)

#pragma endregion

// Adds a pointer to an implemented interface VTable inside a class.
#define ADD_IMPL(IMPL) const struct vtable(IMPL)* const __impl_##IMPL;
#define INIT_IMPL(IMPL) *(const struct vtable(IMPL)**)&this->__impl_##IMPL = &IMPL##_VTable;

#pragma region Declarations

// Define a new class with the given fields and methods.
#define class(ID, IMPLEMENTS, FIELDS, METHOD_BUNDLES...) \
struct storage(ID) DEPAREN(FIELDS);                 \
struct vtable(ID);                                  \
typedef struct JOIN(_,__class,ID,line,__LINE__) {   \
    const struct vtable(ID)* const __VTable;        \
    FOREACH(ADD_IMPL, DEPAREN(IMPLEMENTS))          \
    struct storage(ID);                             \
} refbase(ID), *ID;                                 \
typedef struct DEPAREN(FIELDS) storage(ID);         \
DEFINE_VTABLE(ID, IMPLEMENTS, METHOD_BUNDLES)

// Implement a new class with the given fields and methods.
// Individual method implementations are done separately.
#define impl_class(ID, IMPLEMENTS, FIELDS, METHOD_BUNDLES...) \
INIT_VTABLE(ID, IMPLEMENTS, METHOD_BUNDLES)     \
static inline ID ID##__asm()                    \
{                                               \
    ID this = alloc_ref(ID);                    \
    *(const struct vtable(ID)**)&this->__VTable \
        = &ID##_VTable;                         \
    FOREACH(INIT_IMPL, DEPAREN(IMPLEMENTS))     \
    return this;                                \
}

// Defines or implements the primary constructor for a type.
#define primary_ctor(TYPE) TYPE TYPE##__ctor
// Defines an overload for the constructor for a type.
#define define_ctor(TYPE, ARG1, ...) TYPE JOIN(_, TYPE, _ctor, ARG1,##__VA_ARGS__)(ARG1,##__VA_ARGS__);

// Imlpements the constructor for a type. Signature should be specified for overloaded constructors.
#define impl_ctor(TYPE, ARG1, ...) TYPE JOIN(_, TYPE, _ctor, ARG1,##__VA_ARGS__) { TYPE this = TYPE##__asm(); do
#define end_impl_ctor while (0); return this; }
// Helper for declaring a constructor body.
#define ctor_body(TYPE, CODE) {     \
    __CTOR_INIT_HELPER(this);       \
    CODE;                           \
    return this;                    \
}
// Implements a function used by the ctor_body macro.
// Should onlny be used in the implementation file.
#define ctor_init_helper(TYPE, IMPLEMENTS)  \
static void inline __CTOR_INIT_HELPER() {   \
    TYPE this = alloc_ref(TYPE);            \
    *(const vtable(TYPE)**)&this->__VTable  \
        = &TYPE##_VTable;                   \
    FOREACH(DEPAREN(IMPLEMENTS))            \
}

// Implements the base constructor for a class.
#define base_ctor(TYPE,SIG,BODY) define_ctor(TYPE)SIG ctor_body(TYPE, DEPAREN(BODY))
// Implements the base constructor for a class as the empty constructor.
#define empty_ctor(TYPE) base_ctor(TYPE,(),{})

// Defines or implements a non-static method for the given type.
#define method_sig(TYPE, METHOD_NAME, PARAMS) EVAL(TYPE##_##METHOD_NAME(DEFER(TRIMEND)(This(TYPE), DEPAREN(PARAMS))))
// Defines or implements a static method for the given type with the given name.
// This must be declared outside class definitions.
#define static_method(TYPE, METHOD_NAME, PARAMS) EVAL(TYPE##_##METHOD_NAME(DEFER(TRIMEND)(DEPAREN(PARAMS))))

#pragma endregion

/*

// -----> A full class definition [.h]:

// Forward declarations
struct vtable(MyClass);
extern const struct vtable(MyClass) MyClass_VTable;

// Class declaration
typedef struct __class_MyClass {
    const struct vtable(MyClass)* const __VTable;
    struct {
        int MyPublicField;
    };
} refbase(MyClass), *MyClass;

// VTable declaration
struct vtable(MyClass) {
    int (*MyPublicMethod)(This(MyClass), int);
};

// -----> A full class implementation [.c]:

static int MyPublicMethod(This(MyClass), int x) {
    return x + this->MyPublicField;
}

const struct vtable(MyClass) MyClass_VTable = (struct vtable(MyClass)) {
    .MyPublicMethod = MyPublicMethod
};

MyClass MyClass__ctor(int myField)
{
    MyClass this = alloc_ref(MyClass);
    *(const struct vtable(MyClass)**)&this->__VTable = &MyClass_VTable;
    do {
        this->MyPublicField = myField;
    } while(0);
    return this;
}

//*/
#endif