#ifndef C_CLASSES
#define C_CLASSES

#define storage(REFTYPE) struct __storage_##REFTYPE

#pragma region Declarations

// Defines a new reference type with the given name and definition.
#define class(NAME, ...) typedef storage(NAME) __VA_ARGS__ *NAME;
// Cooking something up w this: typedef union { storage(NAME) __VA_ARGS__; } *NAME;
// Implements a base type for a class.
#define inherits(BASE_TYPE) storage(BASE_TYPE) __base_type
// Defines the constructor for a type.
#define define_ctor(TYPE) TYPE TYPE##__ctor
// Defines or implements a method for the given type with the given name.
// This must be declared outside class definitions.
#define method(TYPE, METHOD_NAME, ...) TYPE##_##METHOD_NAME(storage(TYPE) const* This,##__VA_ARGS__)
// Defines or implements a static method for the given type with the given name.
// This must be declared outside class definitions.
#define static_method(TYPE, METHOD_NAME, ...) TYPE##_Static_##METHOD_NAME(__VA_ARGS__)
// Defines an abstract method for the given type with the given name.
// This must be declared inside class definitions.
#define abstract_method(TYPE, METHOD_NAME, ...) (*METHOD_NAME)(storage(TYPE) const* This,##__VA_ARGS__)

#pragma endregion


#pragma region Initialization

#define alloc_ref(REF_TYPE) (REF_TYPE)memalloc(storage(REF_TYPE))

// Calls the constructor for a type. Use () after the macro brackets.
#define new(TYPE) TYPE##__ctor
#define init(REF_TYPE) (storage(REF_TYPE))
// Calls the parameterless constructor on a new variable with name objname,
// and initializes it with the following initializer.
#define new_init(TYPE, objname) TYPE objname = new(TYPE)(); *objname = init(TYPE)

#pragma endregion

#endif