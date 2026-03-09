#ifndef C_INTERFACES
#define C_INTERFACES

#include "Defines.h"
// Implements an interface inside a type.
#define implements(INTERFACE) union { storage(INTERFACE) __impl_##INTERFACE; storage(INTERFACE); }
// Defines a new interface with the given name and definition.
#define interface(NAME, ...) storage(NAME) __VA_ARGS__; \
typedef union __interface_##NAME { storage(NAME) __this; implements(NAME); } *NAME;
// Returns the implementation of INTERFACE in obj.
#define as_interface(INTERFACE, obj) ((INTERFACE)(&(obj)->__impl_##INTERFACE))
#define as_inheritor(INTERFACE, CURRENT_TYPE, obj) ((INTERFACE)((object)(obj) - offset_of(__impl_##CURRENT_TYPE, (INTERFACE)(obj))))

#endif