#ifndef C_DELEGATES
#define C_DELEGATES
#define delegate typedef
// Defines a function pointer with a given name.
#define lambda(NAME, ...) (*NAME)(__VA_ARGS__)
// Defines a function that takes a certain number of parameters and returns a value.
#define Func(TReturn, ...) __FUNC_SELECT(,##__VA_ARGS__, Func16, Func15, Func14, Func13, Func12, Func11, Func10, Func9, Func8, Func7, Func6, Func5, Func4, Func3, Func2, Func1, Func0)(TReturn,##__VA_ARGS__)
#define __FUNC_SELECT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, NAME, ...) NAME
// Defines a function that takes no parameters and returns a value.
#define Func0(TResult) TResult (*Func_##TResult)(void)
// Defines a function that takes one parameter and returns a value.
#define Func1(TResult, T1) TResult (*Func_##TResult##_##T1)(T1)
// Defines a function that takes two parameters and returns a value.
#define Func2(TResult, T1, T2) TResult (*Func_##TResult##_##T1##_##T2)(T1, T2)
// Defines a function that takes three parameters and returns a value.
#define Func3(TResult, T1, T2, T3) TResult (*Func_##TResult##_##T1##T2_##T3)(T1, T2, T3)
// Defines a function that takes four parameters and returns a value.
#define Func4(TResult, T1, T2, T3, T4) TResult (*Func_##TResult##_##T1##T2_##T3##_T4)(T1, T2, T3, T4)
// Defines a function that takes five parameters and returns a value.
#define Func5(TResult, T1, T2, T3, T4, T5) TResult (*Func_##TResult##_##T1##T2_##T3##_T4##_##T5)(T1, T2, T3, T4, T5)
// Defines a function that takes six parameters and returns a value.
#define Func6(TResult, T1, T2, T3, T4, T5, T6) TResult (*Func_##TResult##_##T1##T2_##T3##_T4##_##T5##_##T6)(T1, T2, T3, T4, T5, T6)
// Defines a function that takes seven parameters and returns a value.
#define Func7(TResult, T1, T2, T3, T4, T5, T6, T7) TResult (*Func_##TResult##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7)(T1, T2, T3, T4, T5, T6, T7)
// Defines a function that takes eight parameters and returns a value.
#define Func8(TResult, T1, T2, T3, T4, T5, T6, T7, T8) TResult (*Func_##TResult##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8)(T1, T2, T3, T4, T5, T6, T7, T8)
// Defines a function that takes nine parameters and returns a value.
#define Func9(TResult, T1, T2, T3, T4, T5, T6, T7, T8, T9) TResult (*Func_##TResult##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9)(T1, T2, T3, T4, T5, T6, T7, T8, T9)
// Defines a function that takes ten parameters and returns a value.
#define Func10(TResult, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) TResult (*Func_##TResult##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)
// Defines a function that takes eleven parameters and returns a value.
#define Func11(TResult, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) TResult (*Func_##TResult##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11)
// Defines a function that takes twelve parameters and returns a value.
#define Func12(TResult, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) TResult (*Func_##TResult##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12)
// Defines a function that takes thirteen parameters and returns a value.
#define Func13(TResult, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) TResult (*Func_##TResult##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12##_##T13)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13)
// Defines a function that takes fourteen parameters and returns a value.
#define Func14(TResult, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) TResult (*Func_##TResult##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12##_##T13##_##T14)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14)
// Defines a function that takes fifteen parameters and returns a value.
#define Func15(TResult, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) TResult (*Func_##TResult##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12##_##T13##_##T14##_##T15)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15)
// Defines a function that takes sixteen parameters and returns a value.
#define Func16(TResult, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) TResult (*Func_##TResult##_##T1##T2_##T3##_T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12##_##T13##_##T14##_##T15##_##T16)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16)

#define Equator(T1, T2) bool (*Equator_##T1##_##T2)(T1, T2)
#define Comparer(T1, T2) int (*Comparer_##T1##_##T2)(T1, T2)
// Defines a function that takes a certain number of parameters and does not return a value.
#define Action(...) __ACTION_SELECT(,##__VA_ARGS__, Action16, Action15, Action14, Action13, Action12, Action11, Action10, Action9, Action8, Action7, Action6, Action5, Action4, Action3, Action2, Action1, Action0)(__VA_ARGS__)
#define __ACTION_SELECT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, NAME, ...) NAME
// Defines a function that takes no parameters and does not 
#define Action0() void (*Action)()
// Defines a function that takes one parameter and does not return a value.
#define Action1(T1) void (*Action_##T1)(T1)
// Defines a function that takes two parameters and does not return a value.
#define Action2(T1, T2) void (*Action_##T1##_##T2)(T1, T2)
// Defines a function that takes three parameters and does not return a value.
#define Action3(T1, T2, T3) void (*Action_##T1##_##T2##_##T3)(T1, T2, T3)
// Defines a function that takes four parameters and does not return a value.
#define Action4(T1, T2, T3, T4) void (*Action_##T1##_##T2##_##T3##_##T4)(T1, T2, T3, T4)
// Defines a function that takes five parameters and does not return a value.
#define Action5(T1, T2, T3, T4, T5) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5)(T1, T2, T3, T4, T5)
// Defines a function that takes six parameters and does not return a value.
#define Action6(T1, T2, T3, T4, T5, T6) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6)(T1, T2, T3, T4, T5, T6)
// Defines a function that takes seven parameters and does not return a value.
#define Action7(T1, T2, T3, T4, T5, T6, T7) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7)(T1, T2, T3, T4, T5, T6, T7)
// Defines a function that takes eight parameters and does not return a value.
#define Action8(T1, T2, T3, T4, T5, T6, T7, T8) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8)(T1, T2, T3, T4, T5, T6, T7, T8)
// Defines a function that takes nine parameters and does not return a value.
#define Action9(T1, T2, T3, T4, T5, T6, T7, T8, T9) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9)(T1, T2, T3, T4, T5, T6, T7, T8, T9)
// Defines a function that takes ten parameters and does not return a value.
#define Action10(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)
// Defines a function that takes eleven parameters and does not return a value.
#define Action11(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11)
// Defines a function that takes twelve parameters and does not return a value.
#define Action12(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12)
// Defines a function that takes thirteen parameters and does not return a value.
#define Action13(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12##_##T13)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13)
// Defines a function that takes fourteen parameters and does not return a value.
#define Action14(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##T12##_##T13##_##T14)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14)
// Defines a function that takes fifteen parameters and does not return a value.
#define Action15(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##12##_##T13##_##T14##_##T15)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15)
// Defines a function that takes sixteen parameters and does not return a value.
#define Action16(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) void (*Action_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9##_##T10##_##T11##_##12##_##T13##_##T14##_##T15##_##T16)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16)

#endif