#ifndef CUBIC_MACROS
#define CUBIC_MACROS

#define EVAL1(...) __VA_ARGS__
#define EVAL2(...) EVAL1(EVAL1(EVAL1(EVAL1(__VA_ARGS__))))
#define EVAL3(...) EVAL2(EVAL2(EVAL2(EVAL2(__VA_ARGS__))))
#define EVAL4(...) EVAL3(EVAL3(EVAL3(EVAL3(__VA_ARGS__))))
#define EVAL(...) EVAL4(EVAL4(EVAL4(EVAL4(__VA_ARGS__))))

#define EMPTY(...)
#define DEFER(id) id EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()

#define CAT_I(a,b) a##b
#define CAT(a,b) CAT_I(a,b)
#define CAT3_I(a,b,c) a##b##c
#define CAT3(a,b,c) CAT3_I(a,b,c)

#define UNWRAP(...) __VA_ARGS__

#define IFNEMPTY(EXECUTE, ...) __VA_OPT__(EXECUTE)

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

#endif