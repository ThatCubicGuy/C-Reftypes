#ifndef C_CLASSES
#define C_CLASSES
#include "Macros.h"
#include "VTable.h"

/*
Some notes:
    Classes must have their own separate .h and .c files. Implementations must appear
    only once, but the header may be included anywhere. Any macros with "DEFINE_" 
*/

#define storage(REFTYPE) __storage_##REFTYPE
#define refbase(REFTYPE) __underlying_##REFTYPE

#pragma region Initialization
// Calls the constructor for a type. Signature must be specified (empty for no parameters).
#define new(TYPE, ...) CAT(TYPE##__, JOIN(_, ctor, __VA_ARGS__))
// Casts the following initializer to the base struct of the given reference type.
#define init(REF_TYPE) (refbase(REF_TYPE))

// Calls the parameterless constructor on a new variable with name objname,
// and initializes it with the following initializer.
#define new_init(TYPE, objname) TYPE objname = new(TYPE)(); *objname = init(TYPE)

// Allocates memory for a reference type and returns a pointer to the allocated block.
#define alloc_ref(REF_TYPE) (REF_TYPE)memalloc(refbase(REF_TYPE))
// Allocates memory for a reference type and initializes it with the following initializer.
#define alloc_init(TYPE, objname) TYPE objname = alloc_ref(TYPE); *objname = init(TYPE)

#pragma endregion


#pragma region Declarations

#define FWD_DECLARE_STORAGE(ID) struct CAT(__internal_storage_##ID##_line_, __LINE__); typedef struct CAT(__internal_struct_, __LINE__) storage(ID);
#define FWD_DECLARE_CLASS(ID) struct CAT(__class_##ID##_line_, __LINE__); typedef struct CAT(__class_##ID##_line_, __LINE__) refbase(ID), *ID;

#define DEFINE_STORAGE(ID, FIELDS...) typedef struct CAT(__internal_struct_, __LINE__) FIELDS storage(ID);

#define DEFINE_CLASS(ID, IMPLEMENTS)                    \
struct CAT(__class_##ID##_line_, __LINE__) {            \
    const vtable(ID)* const __VTable;                   \
    storage(ID);                                        \
};

#define INHERIT_CLASS(ID, BASE)                         \
typedef struct CAT(__class_##ID##_line_, __LINE__) {    \
    const vtable(ID)* const __VTable;                   \
    storage(BASE);                                      \
    storage(ID);                                        \
} refbase(ID), *ID;

// Define a new class with the given fields and methods.
#define class(ID, IMPLEMENTS, FIELDS, METHODS...) \
FWD_DECLARE_CLASS(ID)                   \
DEFINE_VTABLES(ID, IMPLEMENTS, METHODS) \
DEFINE_STORAGE(ID, FIELDS)              \
DEFINE_CLASS(ID)
// Define an abstract class with the given fields and methods.
#define abstract_class(ID, IMPLEMENTS, FIELDS, METHODS...) \
FWD_DECLARE_CLASS(ID)                   \
DEFINE_VTABLES(ID, IMPLEMENTS, METHODS) \
DEFINE_STORAGE(ID, FIELDS)              \
DEFINE_CLASS(ID)
// Define a new subclass that inherits from the given base.
#define subclass(ID, BASE, FIELDS, METHODS...) \
INHERIT_VTABLE(ID, BASE, METHODS)       \
DEFINE_STORAGE(ID, FIELDS)              \
INHERIT_CLASS(ID, BASE)                 \
INIT_INHERITED_VTABLE(ID, BASE, METHODS)
// Define an abstract subclass that inherits from the given base.
#define abstract_subclass(ID, BASE, FIELDS, METHODS...) \
INHERIT_VTABLE(ID, BASE, METHODS)       \
DEFINE_STORAGE(ID, FIELDS)              \
INHERIT_CLASS(ID, BASE)

// Defines the constructor for a type. Signature should be specified for overloaded constructors.
#define define_ctor(TYPE, ...) TYPE CAT(TYPE##__, JOIN(_, ctor, __VA_ARGS__))
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
    FOREACH(DEPAREN(IMPLEMENTS))\
}

// Defines the base constructor for a class.
#define base_ctor(TYPE,SIG,BODY) define_ctor(TYPE)SIG ctor_body(TYPE, DEPAREN(BODY))
// Defines the base constructor for a class as being the empty constructor.
#define empty_ctor(TYPE) base_ctor(TYPE,(),{})

// Defines or implements a non-static method for the given type.
#define method_sig(TYPE, METHOD_NAME, PARAMS) EVAL(TYPE##_##METHOD_NAME(DEFER(TRIMEND)(This(TYPE), DEPAREN(PARAMS))))
// Defines or implements a static method for the given type with the given name.
// This must be declared outside class definitions.
#define static_method(TYPE, METHOD_NAME, PARAMS) EVAL(TYPE##_##METHOD_NAME(DEFER(TRIMEND)(DEPAREN(PARAMS))))

#pragma endregion

class (MyClass, MyTrait, {
    int MyField;
}, ((void,MyMethod,())));


#endif