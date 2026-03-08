#ifndef C_INTERFACES
#define C_INTERFACES

// Defines a new interface with the given name and definition.
#define interface(NAME, ...) typedef struct __interface_##NAME __VA_ARGS__ *NAME;
// Implements an interface inside a type.
#define implements(INTERFACE) struct __interface_##INTERFACE __impl_##INTERFACE

#define as_interface(INTERFACE, obj) (&obj->__impl_##INTERFACE)

#endif