#ifndef C_CLASSES
#define C_CLASSES
#include "Macros.h"

#define storage(REFTYPE) __storage_##REFTYPE
#define def_vtable(REFTYPE, ...) struct __vtable_##REFTYPE __VA_ARGS__ REFTYPE##VTable
#define def_storage(REFTYPE, ...) typedef struct { void* __methods; struct __VA_ARGS__; } storage(REFTYPE)

#define refbase(REFTYPE) union __underlying_##REFTYPE

#pragma region Declarations

// Defines a new class type with the given name, fields, and VTable.
#define class(NAME, FIELDS, VTABLE) def_storage(NAME, { IFNEMPTY(struct FIELDS;, FIELDS) }); def_vtable(NAME, { IFNEMPTY(struct VTABLE;, VTABLE) }); \
typedef refbase(NAME) { storage(NAME); } *NAME;

// Defines a new subclass with the given name that inherits from the specified parent.
#define subclass(NAME, PARENT, ...) class(NAME, { refbase(PARENT); struct __VA_ARGS__; })
#define abstract_class(NAME, ...) class(NAME, __VA_ARGS__)
// Implements a base type for a class.
// #define inherits(BASE_TYPE) union { refbase(BASE_TYPE) __base_type; refbase(BASE_TYPE); }
// Defines the constructor for a type Signature must be specified.
#define define_ctor(TYPE, ...) TYPE CAT(TYPE##__, JOIN(_, ctor, __VA_ARGS__))
// Defines or implements a method for the given type with the given name.
// This must be declared outside class definitions.
#define final_method(TYPE, METHOD_NAME, ...) TYPE##_##METHOD_NAME(refbase(TYPE) const* This,##__VA_ARGS__)
// Defines or implements a static method for the given type with the given name.
// This must be declared outside class definitions.
#define static_method(TYPE, METHOD_NAME, ...) TYPE##_Static_##METHOD_NAME(__VA_ARGS__)
// Defines an abstract method for the given type with the given name.
// This must be declared inside class definitions.
#define abstract_method(TYPE, METHOD_NAME, ...) (*METHOD_NAME)(refbase(TYPE)* This,##__VA_ARGS__)

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
class (Something, {
    int x;
    int y;
},{
    void abstract_method(Something, Dispose);
})
#endif