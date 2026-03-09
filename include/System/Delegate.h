#ifndef C_DELEGATES
#define C_DELEGATES
#define delegate typedef
// Defines a function that takes a certain number of parameters and returns a value.
#define Func(TReturn, ...) __FUNC_SELECT(,##__VA_ARGS__, FUNC16, FUNC15, FUNC14, FUNC13, FUNC12, FUNC11, FUNC10, FUNC9, FUNC8, FUNC7, FUNC6, FUNC5, FUNC4, FUNC3, FUNC2, FUNC1, FUNC0)(TReturn,##__VA_ARGS__)
#define __FUNC_SELECT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, NAME, ...) NAME
// Defines a function that takes no parameters and returns a value.
#define FUNC0(TReturn) TReturn (*Func_##TReturn)(void)
// Defines a function that takes one parameter and returns a value.
#define FUNC1(TReturn, T1) TReturn (*Func_##TReturn##_##T1)(T1)
// Defines a function that takes two parameters and returns a value.
#define FUNC2(TReturn, T1, T2) TReturn (*Func_##TReturn##_##T1##_##T2)(T1, T2)
// Defines a function that takes three parameters and returns a value.
#define FUNC3(TReturn, T1, T2, T3) TReturn (*Func_##TReturn##_##T1##T2_##T3)(T1, T2, T3)
// Defines a function that takes four parameters and returns a value.
#define FUNC4(TReturn, T1, T2, T3, T4) TReturn (*Func_##TReturn##_##T1##T2_##T3##_T4)(T1, T2, T3, T4)
// Defines a function that takes five parameters and returns a value.
#define FUNC5(TReturn, T1, T2, T3, T4, T5) TReturn (*Func_##TReturn##_##T1##T2_##T3##_T4##_##T5)(T1, T2, T3, T4, T5)
// Defines a function that takes six parameters and returns a value.
#define FUNC6(TReturn, T1, T2, T3, T4, T5, T6) TReturn (*Func_##TReturn##_##T1##T2_##T3##_T4##_##T5##_##T6)(T1, T2, T3, T4, T5, T6)
// Defines a function that takes seven parameters and returns a value.
#define FUNC7(TReturn, T1, T2, T3, T4, T5, T6, T7) TReturn (*Func_##TReturn##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7)(T1, T2, T3, T4, T5, T6, T7)
// Defines a function that takes eight parameters and returns a value.
#define FUNC8(TReturn, T1, T2, T3, T4, T5, T6, T7, T8) TReturn (*Func_##TReturn##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8)(T1, T2, T3, T4, T5, T6, T7, T8)
// Defines a function that takes nine parameters and returns a value.
#define FUNC9(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9) TReturn (*Func_##TReturn##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9)(T1, T2, T3, T4, T5, T6, T7, T8, T9)
// Defines a function that takes ten parameters and returns a value.
#define FUNC10(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) TReturn (*Func_##TReturn##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)
// Defines a function that takes eleven parameters and returns a value.
#define FUNC11(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) TReturn (*Func_##TReturn##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11)
// Defines a function that takes twelve parameters and returns a value.
#define FUNC12(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) TReturn (*Func_##TReturn##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12)
// Defines a function that takes thirteen parameters and returns a value.
#define FUNC13(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) TReturn (*Func_##TReturn##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12##_##T13)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13)
// Defines a function that takes fourteen parameters and returns a value.
#define FUNC14(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) TReturn (*Func_##TReturn##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12##_##T13##_##T14)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14)
// Defines a function that takes fifteen parameters and returns a value.
#define FUNC15(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) TReturn (*Func_##TReturn##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12##_##T13##_##T14##_##T15)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15)
// Defines a function that takes sixteen parameters and returns a value.
#define FUNC16(TReturn, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) TReturn (*Func_##TReturn##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12##_##T13##_##T14##_##T15##_##T16)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16)

// Defines a function that takes a certain number of parameters and does not return a value.
#define Action(...) __ACTION_SELECT(,##__VA_ARGS__, ACTION16, ACTION15, ACTION14, ACTION13, ACTION12, ACTION11, ACTION10, ACTION9, ACTION8, ACTION7, ACTION6, ACTION5, ACTION4, ACTION3, ACTION2, ACTION1, ACTION0)(__VA_ARGS__)
#define __ACTION_SELECT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, NAME, ...) NAME
// Defines a function that takes no parameters and does not return a value.
#define ACTION0() void (*Action)()
// Defines a function that takes one parameter and does not return a value.
#define ACTION1(T1) void (*Action_##T1)(T1)
// Defines a function that takes two parameters and does not return a value.
#define ACTION2(T1, T2) void (*Action_##T1##_##T2)(T1, T2)
// Defines a function that takes three parameters and does not return a value.
#define ACTION3(T1, T2, T3) void (*Action_##T1##_##T2##_##T3)(T1, T2, T3)
// Defines a function that takes four parameters and does not return a value.
#define ACTION4(T1, T2, T3, T4) void (*Action_##T1##_##T2##_##T3##_##T4)(T1, T2, T3, T4)
// Defines a function that takes five parameters and does not return a value.
#define ACTION5(T1, T2, T3, T4, T5) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5)(T1, T2, T3, T4, T5)
// Defines a function that takes six parameters and does not return a value.
#define ACTION6(T1, T2, T3, T4, T5, T6) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6)(T1, T2, T3, T4, T5, T6)
// Defines a function that takes seven parameters and does not return a value.
#define ACTION7(T1, T2, T3, T4, T5, T6, T7) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7)(T1, T2, T3, T4, T5, T6, T7)
// Defines a function that takes eight parameters and does not return a value.
#define ACTION8(T1, T2, T3, T4, T5, T6, T7, T8) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8)(T1, T2, T3, T4, T5, T6, T7, T8)
// Defines a function that takes nine parameters and does not return a value.
#define ACTION9(T1, T2, T3, T4, T5, T6, T7, T8, T9) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9)(T1, T2, T3, T4, T5, T6, T7, T8, T9)
// Defines a function that takes ten parameters and does not return a value.
#define ACTION10(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)
// Defines a function that takes eleven parameters and does not return a value.
#define ACTION11(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11)
// Defines a function that takes twelve parameters and does not return a value.
#define ACTION12(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12)
// Defines a function that takes thirteen parameters and does not return a value.
#define ACTION13(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12##_##T13)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13)
// Defines a function that takes fourteen parameters and does not return a value.
#define ACTION14(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12##_##T13##_##T14)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14)
// Defines a function that takes fifteen parameters and does not return a value.
#define ACTION15(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##12##_##T13##_##T14##_##T15)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15)
// Defines a function that takes sixteen parameters and does not return a value.
#define ACTION16(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##12##_##T13##_##T14##_##T15##_##T16)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16)

// Defines a function pointer with a given name.
#define lambda(NAME) (*NAME)
// Defines a function that decides whether or not two items are equal.
#define Equator(T1, T2) bool (*Equator_##T1##_##T2)(T1, T2)
// Defines a function that compares two items.
#define Comparer(T1, T2) int (*Comparer_##T1##_##T2)(T1, T2)
// Defines a function that decides whether an item fulfills a condition.
#define Predicate(T) Func(bool, T)

#endif