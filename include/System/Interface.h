#ifndef C_INTERFACES
#define C_INTERFACES

#include "Defines.h"
#include "Macros.h"
#include "VTable.h"

#define impl(INTERFACE) __impl_##INTERFACE

/*  ---INTERFACE IMPLEMENTATION---
VTABLE DEFINITION:
    struct __vtable_myclass {
        TReturn FuncName(void* const this, ...);
        union {
            struct __vtable_interface1;
            struct __vtable_interface1 __impl_interface1;
        };
        union {
            struct __vtable_interface2;
            struct __vtable_interface2 __impl_interface2;
        };
    };
STORAGE DEFINITION:
    struct __storage_myclass {
        T1 FieldName;
    };
TYPE DEFINITION:
    struct __class {
        const struct __vtable_myclass* const VTable;
        struct __storage_myclass;
        union {
            struct __storage_interface1;
            struct __storage_interface1 __impl_interface1;
        };
        union {
            struct __storage_interface2;
            struct __storage_interface2 __impl_interface2;
        };
    } *MyClass;
VTABLE SIGNATURES:
    TReturn FuncName(MyClass const this, ...);
VTABLE INIT:
    struct __vtable_myclass MyClassVTable = {
        .FuncName = (void*)FuncName
    };

*/

#define DEFINE_INTERFACE(ID)                            \
typedef struct CAT(__interface_##ID##_line_,__LINE__) { \
    const vtable(ID)* const VTable;                     \
} refbase(ID), *ID;


// Defines a new interface with the given name and definition.
#define interface(NAME, METHOD_BUNDLES...)  \
DEFINE_VTABLE(ID, METHOD_BUNDLES)           \
DEFINE_INTERFACE(ID)

// Returns the implementation of INTERFACE in obj.
#define as_interface(INTERFACE, obj) ((INTERFACE)(&(obj)->impl(INTERFACE)))

#define as_inheritor(INTERFACE, CURRENT_TYPE, obj) ((INTERFACE)((object)(obj) - offset_of(impl(CURRENT_TYPE), (INTERFACE)(obj))))

#endif