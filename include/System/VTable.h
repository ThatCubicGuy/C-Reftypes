#ifndef C_VTABLES
#define C_VTABLES
#include "Macros.h"

// Returns the type name of REFTYPE's VTable.
#define vtable(REFTYPE) __vtable_##REFTYPE

// WARNING: obj parameter is used twice.
#define call(obj, METHOD_NAME, ARGS) (obj)->__VTable->METHOD_NAME(DEPAREN(PREPEND(obj,ARGS)))

// Represents the self parameter in any non-static method.
#define This(TYPE) TYPE const this

#define __TO_FIELD(TYPE, RETURN, NAME, ARGS) RETURN (*NAME)PREPEND(This(void*),ARGS);
#define __TO_SIG(TYPE, RETURN, NAME, ARGS) RETURN TYPE##_##NAME PREPEND(This(TYPE),ARGS)
#define __TO_DECL(TYPE, RETURN, NAME, ARGS) __TO_SIG(TYPE, RETURN, NAME, ARGS);
#define __TO_INIT(TYPE, RETURN, NAME, ARGS) .NAME = (void*)TYPE##_##NAME,
#define __TO_VTABLE(IMPL) union { vtable(IMPL) __impl##IMPL; vtable(IMPL); };
#define __INIT_VTABLE(BASE, IMPL) const vtable(IMPL) BASE##_##IMPL##_VTable = *(vtable(IMPL)*)&BASE##_VTable.__impl##IMPL;

/*
The theory:
    VTables will contain the methods of every single thing they inherit. No doubt about it.
        typedef struct __whatever_internal_but_non_anonymous_thing_you_wanna_call_this {
            T1Return Foonc(MyClass const this, T1, T2, ...); // Class method
            T2Return Barnc(MyClass const this, T3, T4, ...); // Interface method
        } vtable(MyClass); // Macro that translates to: __vtable_MyClass
    This must be this way so we can use a call macro that does something like
        (obj)->Foonc(obj, ...);
        (obj)->Barnc(obj, ...);
    
    The class will contain a pointer to its VTable, but also pointers to the VTables of every
    interface it implements.
        typedef struct __another_internal_thing_we_dont_care_about {
            const vtable(MyClass)* const VTable;
            storage(MyClass); // Macro that expands to __storage_MyClass. This contains every instance field.
        } refbase(MyClass), *MyClass; // refbase(ID) is used for initializations mostly.
    This must be this way so we can cast with a macro similar to
        (INTERFACE)&((obj)->__impl_##INTERFACE)
    
    The VTable declarations is where we get creative. We will declare a VTable for the class:
        struct __MyClass_VTable MyClass_VTable = {OwnMethod, IMethod};
    ...but also a VTable for the class' implementation of each interface:
        struct __MyInterface_VTable MyClass_MyInterface_VTable = {IMethod};
    This adds some global overhead unfortunately, but makes it possible to do what I wanted
    and has the side effect of allowing explicit interface implementations!
*/

// Defines a VTable that implements the given types. Base class must come first.
#define DEFINE_VTABLES(ID, IMPLEMENTS, METHOD_BUNDLES...)\
typedef struct CAT(__vtable_, ID, _line_, __LINE__) {   \
    FOREACH(__TO_VTABLE, DEPAREN(IMPLEMENTS))           \
    FOREACH_WITH_ARGS(__TO_FIELD, ID, METHOD_BUNDLES)   \
} vtable(ID);                                           \
FOREACH_WITH_ARGS(__DEFINE_IMPL,ID,DEPAREN(IMPLEMENTS))

#define INIT_VTABLE(ID, IMPLEMENTS, METHOD_BUNDLES...)  \
FOREACH_WITH_ARGS(__TO_DECL, ID, METHOD_BUNDLES)        \
const vtable(ID) ID##_VTable = (vtable(ID)) {           \
    FOREACH_WITH_ARGS(__TO_INIT, ID, METHOD_BUNDLES)    \
};

#define implement_vtable(TYPE, METHOD_BUNDLE) EVAL(DEFER(__TO_SIG)(TYPE,DEPAREN(METHOD_BUNDLE)))

#endif