#ifndef C_INTERFACES
#define C_INTERFACES

// Defines a new interface with the given name and definition.
#define interface(NAME, ...) storage(NAME) __VA_ARGS__; \
typedef union __interface_##NAME { implements(NAME); struct __VA_ARGS__; } *NAME;
// Implements an interface inside a type.
#define implements(INTERFACE) storage(INTERFACE) __impl_##INTERFACE
// Returns the implementation of INTERFACE in obj.
#define as_interface(INTERFACE, obj) (&obj->__impl_##INTERFACE)

#endif