#ifndef CUBIC_MACROS
#define CUBIC_MACROS

#define __EVAL_1(...) __VA_ARGS__
#define __EVAL_2(...) __EVAL_1(__EVAL_1(__EVAL_1(__EVAL_1(__VA_ARGS__))))
#define __EVAL_3(...) __EVAL_2(__EVAL_2(__EVAL_2(__EVAL_2(__VA_ARGS__))))
#define __EVAL_4(...) __EVAL_3(__EVAL_3(__EVAL_3(__EVAL_3(__VA_ARGS__))))
#define EVAL(...) __EVAL_4(__EVAL_4(__EVAL_4(__EVAL_4(__VA_ARGS__))))

// 1 step
#define EMPTY(...)
// 2 steps
#define DEFER(id) id EMPTY()
// 4 steps
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()

// EMPTY(x) ->

// DEFER(x) -> x EMPTY()
// x EMPTY() -> x

// OBSTRUCT(x) -> x DEFER(EMPTY)()
// x DEFER(EMPTY)() -> x EMPTY EMPTY() ()
// x EMPTY EMPTY() () -> x EMPTY ()
// x EMPTY () -> x

#define CAT_I(a,b) a##b
#define CAT(a,b) CAT_I(a,b)
#define CAT3_I(a,b,c) a##b##c
#define CAT3(a,b,c) CAT3_I(a,b,c)

#define EXPAND(...) __VA_ARGS__


// Source - https://stackoverflow.com/a/62984543
// Posted by Nero
// Retrieved 2026-03-10, License - CC BY-SA 4.0

#define VANISH
#define ESC_(...) VAN##__VA_ARGS__
#define ESC(...) ESC_(__VA_ARGS__)
#define ISH(...) ISH __VA_ARGS__
#define DEPAREN(x) ESC(ISH x)


#define __SELECT_1(id, ...) id
#define __SELECT_2(_1, id, ...) id
#define __SELECT_3(_1, _2, id, ...) id
#define __SELECT_4(_1, _2, _3, id, ...) id
#define __SELECT_8(_1, _2, _3, _4, id, ...) id
#define __SELECT_8(_1, _2, _3, _4, _5, id, ...) id
#define __SELECT_8(_1, _2, _3, _4, _5, _6, id, ...) id
#define __SELECT_8(_1, _2, _3, _4, _5, _6, _7, id, ...) id
#define SELECT(NUMBER, ...) CAT(__SELECT_, NUMBER)(__VA_ARGS__)

#define __EXTRACT_1(id1, ...) id1
#define __EXTRACT_2(id1, id2, ...) id1, id2
#define __EXTRACT_3(id1, id2, id3, ...) id1, id2, id3
#define __EXTRACT_4(id1, id2, id3, id4, ...) id1, id2, id3, id4
#define EXTRACT(COUNT, ...) CAT(__EXTRACT_, COUNT)(__VA_ARGS__)

#define __JOIN_8(SEPARATOR, _1, ...) CAT(SEPARATOR, _1)
#define __JOIN_7(SEPARATOR, _1, ...) CAT(CAT(SEPARATOR, _1), __VA_OPT__(__JOIN_8(SEPARATOR, __VA_ARGS__)))
#define __JOIN_6(SEPARATOR, _1, ...) CAT(CAT(SEPARATOR, _1), __VA_OPT__(__JOIN_7(SEPARATOR, __VA_ARGS__)))
#define __JOIN_5(SEPARATOR, _1, ...) CAT(CAT(SEPARATOR, _1), __VA_OPT__(__JOIN_6(SEPARATOR, __VA_ARGS__)))
#define __JOIN_4(SEPARATOR, _1, ...) CAT(CAT(SEPARATOR, _1), __VA_OPT__(__JOIN_5(SEPARATOR, __VA_ARGS__)))
#define __JOIN_3(SEPARATOR, _1, ...) CAT(CAT(SEPARATOR, _1), __VA_OPT__(__JOIN_4(SEPARATOR, __VA_ARGS__)))
#define __JOIN_2(SEPARATOR, _1, ...) CAT(CAT(SEPARATOR, _1), __VA_OPT__(__JOIN_3(SEPARATOR, __VA_ARGS__)))
#define __JOIN_1(SEPARATOR, _1, ...) CAT(CAT(SEPARATOR, _1), __VA_OPT__(__JOIN_2(SEPARATOR, __VA_ARGS__)))
#define JOIN(SEPARATOR, _1, ...) CAT(_1, __VA_OPT__(__JOIN_1(SEPARATOR, __VA_ARGS__)))

#define __FOREACH_8(id, _0, _1, _2, _3, _4, _5, _6, _7, ...) DEFER(id)(_0) DEFER(id)(_1) DEFER(id)(_2) DEFER(id)(_3) DEFER(id)(_4) DEFER(id)(_5) DEFER(id)(_6) DEFER(id)(_7)

#endif