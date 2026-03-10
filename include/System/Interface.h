#ifndef C_INTERFACES
#define C_INTERFACES

#include "Defines.h"
#include "Macros.h"

// Implements an interface inside a type.
#define implements(INTERFACE) union { storage(INTERFACE) __impl_##INTERFACE; storage(INTERFACE); }
// Defines a new interface with the given name and definition.
#define interface(NAME, ...) def_storage(NAME, __VA_ARGS__); \
typedef union CAT(__internal_union_, __LINE__) { implements(NAME); } refbase(NAME), *NAME;

// Returns the implementation of INTERFACE in obj.
#define as_interface(INTERFACE, obj) ((INTERFACE)(&(obj)->__impl_##INTERFACE))

#define as_inheritor(INTERFACE, CURRENT_TYPE, obj) ((INTERFACE)((object)(obj) - offset_of(__impl_##CURRENT_TYPE, (INTERFACE)(obj))))

#endif