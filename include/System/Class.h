#ifndef C_CLASSES
#define C_CLASSES

#define storage(REFTYPE) struct __storage_##REFTYPE
#define call(obj, METHOD_NAME, ...) (obj)->METHOD_NAME(obj,##__VA_ARGS__)

#pragma region Declarations

// Defines a new class type with the given name and definition.
#define class(NAME, ...) storage(NAME) __VA_ARGS__; \
typedef union __class_##NAME { storage(NAME) __this; storage(NAME); } *NAME;

// Defines a new subclass with the given name that inherits from the specified parent.
#define subclass(NAME, PARENT, ...) class(NAME, { storage(PARENT); struct __VA_ARGS__; })
#define abstract_class(NAME, ...) class(NAME, __VA_ARGS__)
// Implements a base type for a class.
// #define inherits(BASE_TYPE) union { storage(BASE_TYPE) __base_type; storage(BASE_TYPE); }
// Defines the constructor for a type.
#define define_ctor(TYPE) TYPE TYPE##__ctor
// Defines or implements a method for the given type with the given name.
// This must be declared outside class definitions.
#define final_method(TYPE, METHOD_NAME, ...) TYPE##_##METHOD_NAME(storage(TYPE) const* This,##__VA_ARGS__)
// Defines or implements a static method for the given type with the given name.
// This must be declared outside class definitions.
#define static_method(TYPE, METHOD_NAME, ...) TYPE##_Static_##METHOD_NAME(__VA_ARGS__)
// Defines an abstract method for the given type with the given name.
// This must be declared inside class definitions.
#define abstract_method(TYPE, METHOD_NAME, ...) (*METHOD_NAME)(storage(TYPE) const* This,##__VA_ARGS__)

#pragma endregion


#pragma region Initialization

// Calls the constructor for a type. Use () after the macro brackets.
#define new(TYPE) TYPE##__ctor
#define init(REF_TYPE) (storage(REF_TYPE))

// Calls the parameterless constructor on a new variable with name objname,
// and initializes it with the following initializer.
#define new_init(TYPE, objname) TYPE objname = new(TYPE)(); *objname = init(TYPE)

#define alloc_ref(REF_TYPE) (REF_TYPE)memalloc(storage(REF_TYPE))
#define alloc_init(TYPE, objname) TYPE objname = alloc_ref(TYPE); objname->__this = init(TYPE)
// ^ All reference types should have a __this that points necessarily to a
// struct __storage_<TYPE NAME> for initialization purposes.
#pragma endregion

#endif