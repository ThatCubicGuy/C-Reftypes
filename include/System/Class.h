#ifndef C_CLASSES
#define C_CLASSES

#pragma region Declarations

// Defines a new reference type with the given name and definition.
#define class(NAME, ...) typedef struct __storage_##NAME __VA_ARGS__ *NAME;
// Defines the constructor for a type.
#define define_ctor(TYPE) TYPE TYPE##__ctor

#define as_base(BASE_TYPE, obj) ((BASE_TYPE)obj)

#pragma endregion


#pragma region Initialization

#define alloc_ref(REF_TYPE) (REF_TYPE)memalloc(struct __storage_##REF_TYPE)

// Calls the constructor for a type. Use () after the macro brackets.
#define new(TYPE) TYPE##__ctor
#define init(REF_TYPE) (struct __storage_##REF_TYPE)
// Creates a new variable with name objname and initializes it with the following initializer.
#define new_init(TYPE, objname) TYPE objname = new(TYPE)(); *objname = init(TYPE)

#pragma endregion


#pragma region Members

// Implements a base type for a class.
#define inherits(BASE_TYPE) struct __storage_##BASE_TYPE __base_type
// Implements a method for the given type with the given name.
#define method(TYPE, METHOD_NAME, ...) (*METHOD_NAME)(struct __storage_##TYPE* This,##__VA_ARGS__)

#define method_IEnumerable(...) (*some_name)(struct __storage_IEnumerable* This,##__VA_ARGS__)

#pragma endregion

#endif