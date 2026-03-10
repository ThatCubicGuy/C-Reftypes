#ifndef C_CLASSES
#define C_CLASSES
#include "Macros.h"

#define storage(REFTYPE) __storage_##REFTYPE
#define def_storage(REFTYPE, ...) typedef struct CAT(__internal_struct_, __LINE__) __VA_ARGS__ storage(REFTYPE)

#define refbase(REFTYPE) __underlying_##REFTYPE

#pragma region Declarations

#define This void const* this

// Defines a new class type with the given name, fields, and VTable.
#define class(NAME, ...) def_storage(NAME, __VA_ARGS__); \
typedef union CAT(__internal_union_, __LINE__) { storage(NAME); } refbase(NAME), *NAME;

// Defines a new subclass with the given name that inherits from the specified parent.
#define subclass(NAME, PARENT, ...) class(NAME, { refbase(PARENT); struct __VA_ARGS__; })
#define abstract_class(NAME, ...) class(NAME, __VA_ARGS__)
// Defines the constructor for a type Signature must be specified.
#define define_ctor(TYPE, ...) TYPE CAT(TYPE##__, JOIN(_, ctor, __VA_ARGS__))
// Helper for declaring a constructor body.
#define ctor_body(TYPE, code) {     \
    TYPE this = alloc_ref(TYPE);    \
    code;                           \
    return this;                    \
}
// Helper for inheriting a parent constructor.
#define inherit_ctor(BASE_TYPE, CTOR_ARGS) { \
    BASE_TYPE CAT(__result_, __LINE__) = new(BASE_TYPE)CTOR_ARGS; \
    memcopy(this, CAT(__result_, __LINE__), sizeof(refbase(BASE_TYPE))); \
    memfree(CAT(__result_, __LINE__)); \
}
// Defines or implements a method that cannot be overridden for the given type with the given name.
// This must be declared outside class definitions.
#define final_method(TYPE, METHOD_NAME, ...) TYPE##_##METHOD_NAME(This,##__VA_ARGS__)
// Defines or implements a static method for the given type with the given name.
// This must be declared outside class definitions.
#define static_method(TYPE, METHOD_NAME, ...) TYPE##_##METHOD_NAME(__VA_ARGS__)
// Defines an abstract method for the given type with the given name.
// This must be declared inside class definitions.
#define abstract_method(METHOD_NAME, ...) (*METHOD_NAME)(This,##__VA_ARGS__)

#pragma endregion

#pragma region Initialization
// Calls the constructor for a type. Signature must be specified (empty for no parameters).
#define new(TYPE, ...) CAT(TYPE##__, JOIN(_, ctor, __VA_ARGS__))
#define init(REF_TYPE) (refbase(REF_TYPE))

// Calls the parameterless constructor on a new variable with name objname,
// and initializes it with the following initializer.
#define new_init(TYPE, objname) TYPE objname = new(TYPE)(); *objname = init(TYPE)

#define alloc_ref(REF_TYPE) (REF_TYPE)memalloc(refbase(REF_TYPE))
#define alloc_init(TYPE, objname) TYPE objname = alloc_ref(TYPE); *objname = init(TYPE)
// ^ All reference types should have a __this that points necessarily to a
// struct __storage_<TYPE NAME> for initialization purposes.
#pragma endregion


#pragma region More

#define ref(T) T*
#define out(T) T*

#pragma endregion

#endif