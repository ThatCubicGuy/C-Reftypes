#ifndef C_DELEGATES
#define C_DELEGATES
#include "Defines.h"

#define delegate typedef
#define __FUNC_SELECT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, NAME, ...) NAME
// Defines a function that takes a certain number of parameters and returns a value.
#define Func(TReturn, ...) __typeof__(__FUNC_SELECT(,##__VA_ARGS__, __FUNC16, __FUNC15, __FUNC14, __FUNC13, __FUNC12, __FUNC11, __FUNC10, __FUNC9, __FUNC8, __FUNC7, __FUNC6, __FUNC5, __FUNC4, __FUNC3, __FUNC2, __FUNC1, __FUNC0)(TReturn,##__VA_ARGS__))
// Defines a function that takes no parameters and returns a value.
#define __FUNC0(TReturn) TReturn (*Generic(Func, TReturn))(void)
// Defines a function that takes one parameter and returns a value.
#define __FUNC1(TReturn, T1) TReturn (*Generic(Func, TReturn, T1))(T1)
// Defines a function that takes two parameters and returns a value.
#define __FUNC2(TReturn, T1, T2) TReturn (*Generic(Func, TReturn, T1, T2))(T1, T2)
// Defines a function that takes three parameters and returns a value.
#define __FUNC3(TReturn, T1, T2, T3) TReturn (*Generic(Func, TReturn, T1, T2, T3))(T1, T2, T3)
// Defines a function that takes four parameters and returns a value.
#define __FUNC4(TReturn, T1, T2, T3, T4) TReturn (*Generic(Func, TReturn, T1, T2, T3, T4))(T1, T2, T3, T4)
// Defines a function that takes five parameters and returns a value.
#define __FUNC5(TReturn, T1, T2, T3, T4, T5) TReturn (*Generic(Func, TReturn, T1, T2, T3, T4, T5))(T1, T2, T3, T4, T5)
// Defines a function that takes six parameters and returns a value.
#define __FUNC6(TReturn, T1, T2, T3, T4, T5, T6) TReturn (*Generic(Func, TReturn, T1, T2, T3, T4, T5, T6))(T1, T2, T3, T4, T5, T6)
// Defines a function that takes seven parameters and returns a value.
#define __FUNC7(TReturn, T1, T2, T3, T4, T5, T6, T7) TReturn (*Generic(Func, TReturn, T1, T2, T3, T4, T5, T6, T7))(T1, T2, T3, T4, T5, T6, T7)
// Defines a function that takes eight parameters and returns a value.
#define __FUNC8(TReturn, T1, T2, T3, T4, T5, T6, T7, T8) TReturn (*Generic(Func, TReturn, T1, T2, T3, T4, T5, T6, T7, T8))(T1, T2, T3, T4, T5, T6, T7, T8)
// Defines a function that takes nine parameters and returns a value.
#define __FUNC9(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9) TReturn (*Generic(Func, TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9))(T1, T2, T3, T4, T5, T6, T7, T8, T9)
// Defines a function that takes ten parameters and returns a value.
#define __FUNC10(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) TReturn (*Generic(Func, TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10))(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)
// Defines a function that takes eleven parameters and returns a value.
#define __FUNC11(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) TReturn (*Generic(Func, TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11))(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11)
// Defines a function that takes twelve parameters and returns a value.
#define __FUNC12(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) TReturn (*Generic(Func, TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12))(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12)
// Defines a function that takes thirteen parameters and returns a value.
#define __FUNC13(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) TReturn (*Generic(Func, TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13))(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13)
// Defines a function that takes fourteen parameters and returns a value.
#define __FUNC14(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) TReturn (*Generic(Func, TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14))(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14)
// Defines a function that takes fifteen parameters and returns a value.
#define __FUNC15(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) TReturn (*Generic(Func, TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15))(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15)
// Defines a function that takes sixteen parameters and returns a value.
#define __FUNC16(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) TReturn (*Generic(Func, TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16))(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16)

#define __ACTION_SELECT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, NAME, ...) NAME
// Defines a function that takes a certain number of parameters and does not return a value.
#define Action(...) __ACTION_SELECT(,##__VA_ARGS__, __ACTION16, __ACTION15, __ACTION14, __ACTION13, __ACTION12, __ACTION11, __ACTION10, __ACTION9, __ACTION8, __ACTION7, __ACTION6, __ACTION5, __ACTION4, __ACTION3, __ACTION2, __ACTION1, __ACTION0)(__VA_ARGS__)
// Defines a function that takes no parameters and does not return a value.
#define __ACTION0() void (*Generic(Action))()
// Defines a function that takes one parameter and does not return a value.
#define __ACTION1(T1) void (*Generic(Action, T1))(T1)
// Defines a function that takes two parameters and does not return a value.
#define __ACTION2(T1, T2) void (*Generic(Action, T1, T2))(T1, T2)
// Defines a function that takes three parameters and does not return a value.
#define __ACTION3(T1, T2, T3) void (*Generic(Action, T1, T2, T3))(T1, T2, T3)
// Defines a function that takes four parameters and does not return a value.
#define __ACTION4(T1, T2, T3, T4) void (*Generic(Action, T1, T2, T3, T4))(T1, T2, T3, T4)
// Defines a function that takes five parameters and does not return a value.
#define __ACTION5(T1, T2, T3, T4, T5) void (*Generic(Action, T1, T2, T3, T4, T5))(T1, T2, T3, T4, T5)
// Defines a function that takes six parameters and does not return a value.
#define __ACTION6(T1, T2, T3, T4, T5, T6) void (*Generic(Action, T1, T2, T3, T4, T5, T6))(T1, T2, T3, T4, T5, T6)
// Defines a function that takes seven parameters and does not return a value.
#define __ACTION7(T1, T2, T3, T4, T5, T6, T7) void (*Generic(Action, T1, T2, T3, T4, T5, T6, T7))(T1, T2, T3, T4, T5, T6, T7)
// Defines a function that takes eight parameters and does not return a value.
#define __ACTION8(T1, T2, T3, T4, T5, T6, T7, T8) void (*Generic(Action, T1, T2, T3, T4, T5, T6, T7, T8))(T1, T2, T3, T4, T5, T6, T7, T8)
// Defines a function that takes nine parameters and does not return a value.
#define __ACTION9(T1, T2, T3, T4, T5, T6, T7, T8, T9) void (*Generic(Action, T1, T2, T3, T4, T5, T6, T7, T8, T9))(T1, T2, T3, T4, T5, T6, T7, T8, T9)
// Defines a function that takes ten parameters and does not return a value.
#define __ACTION10(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) void (*Generic(Action, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10))(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)
// Defines a function that takes eleven parameters and does not return a value.
#define __ACTION11(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) void (*Generic(Action, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11))(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11)
// Defines a function that takes twelve parameters and does not return a value.
#define __ACTION12(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) void (*Generic(Action, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12))(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12)
// Defines a function that takes thirteen parameters and does not return a value.
#define __ACTION13(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) void (*Generic(Action, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13))(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13)
// Defines a function that takes fourteen parameters and does not return a value.
#define __ACTION14(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) void (*Generic(Action, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14))(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14)
// Defines a function that takes fifteen parameters and does not return a value.
#define __ACTION15(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) void (*Generic(Action, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15))(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15)
// Defines a function that takes sixteen parameters and does not return a value.
#define __ACTION16(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) void (*Generic(Action, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16))(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16)

// Defines a function that decides whether or not two items are equal.
#define Equator(T1, T2) bool (*Equator_##T1##_##T2)(T1, T2)
// Defines a function that compares two items.
#define Comparer(T1, T2) int (*Comparer_##T1##_##T2)(T1, T2)
// Defines a function that decides whether an item fulfills a condition.
#define Predicate(T) Func(bool, T)

#endif