#ifndef C_STRUCTS_ADVANCED
#define C_STRUCTS_ADVANCED

// Defines the constructor for a type.
#define define_ctor(TYPE) TYPE TYPE##__ctor

// Defines a new reference type with the given name and definition.
// A parameterless constructor definition may be added at the end.
#define struct(NAME, ...) typedef struct __struct_##NAME __VA_ARGS__ NAME;   \
define_ctor(NAME)() // Define the default parameterless constructor.

// Boxes the given value type and returns a pointer to its location in memory.
#define box(VALUE_TYPE) (VALUE_TYPE*)memalloc(VALUE_TYPE)
// Returns the default (zero-initialized) value of type T.
#define default(T) ((T){0})

#endif