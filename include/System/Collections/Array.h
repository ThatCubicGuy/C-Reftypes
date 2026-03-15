#ifndef COLLECTIONS_ARRAY
#define COLLECTIONS_ARRAY
#include "Defines.h"
#include "Enumerable.h"
#include "Class.h"

#pragma region Defines

public class (Array, {
    implements(IEnumerable);
    // Amount of items contained in the array.
    int Length;
    // Maximum amount of items that this array can hold without resizing.
    int MaxLength;
    // Size of each member, in bytes.
    int _memberSize;
    // Values contained in this array.
    void* Values;
})

define_ctor(Array)(int memberSize, int maxLength);

void method_sig(Array, Clear, ());

void method_sig(Array, CopyTo, (Array dest));

void method_sig(Array, Destroy, ());

void method_sig(Array, Fill, (object itemRef));

/**
 * @brief Returns a reference to the given element in the array.
 * @param source Array to get the item from.
 * @param index Index of the item to get.
 */
object method_sig(Array, Get, (int index));

void method_sig(Array, Resize, (int newMaxLength));

/**
 * @brief Sets the value at the index to the value at the given reference.
 * @param source Array to set the item in.
 * @param index Index at which to set the item.
 * @param valueRef Reference to the value which should be set.
 */
void method_sig(Array, Set, (int index, object valueRef));

void method_sig(Array, Sort, (Comparer(object, object)));

#pragma region Generics

#ifdef COLLECTIONS_GENERIC_ENUMERABLE
#define DEF_ENUMERABLE_TO_ARRAY(T) Array Enumerable_##T##_ToArray(IEnumerable_##T source);
#define IMPL_ENUMERABLE_TO_ARRAY(T)                                 \
Array Enumerable_##T##_ToArray(IEnumerable_##T source)              \
{                                                                   \
    /* Assume initial capacity to avoid useless enumeration */      \
    int maxLength = 16;                                             \
    Array allocinit(Array, result) {                                \
        ._parent = (struct IEnumerable_s) {                         \
            .GetEnumerator = ArrayGetEnumerator                     \
        },                                                          \
        .Length = 0,                                                \
        .MaxLength = maxLength,                                     \
        .Values = alloc_array(T, maxLength)                         \
    };                                                              \
    foreach(T, item, source, {                                      \
        if (result->Length >= result->MaxLength) {                  \
            Array_Resize(result, result->MaxLength * 2);            \
        }                                                           \
        ((T*)result->Values)[result->Length] = item;                \
        result->Length += 1;                                        \
    });                                                             \
    Array_Resize(result, result->Length);                           \
    return result;                                                  \
}
#else
#define DEF_ENUMERABLE_TO_ARRAY(T)
#define IMPL_ENUMERABLE_TO_ARRAY(T)
#endif
#define ARRAY_DEFINE(T)                                     \
Array Array_##T##__ctor(int maxLength);                     \
T Array_##T##_Get(Array source, int index);                 \
void Array_##T##_Set(Array source, int index, T value);     \
int Array_##T##_IndexOf(Array source, T item);              \
void Array_##T##_Fill(Array source, T item);                \
void Array_##T##_Initialize(Array source);                  \
DEF_ENUMERABLE_TO_ARRAY(T)

#define new_array(T) Array_##T##__ctor

#pragma endregion

#pragma endregion

#pragma region Implement

IEnumerator ArrayGetEnumerator(IEnumerable this);

#define ARRAY_IMPLEMENT(T)                                                      \
Array Array_##T##__ctor(int maxLength)                                          \
{                                                                               \
    if (maxLength < 0) return NULL;                                             \
    if (maxLength == 0) return alloc(Array);                                    \
    Array allocinit(Array, result) {                                            \
        ._parent = (struct IEnumerable_s) {                                     \
            .GetEnumerator = ArrayGetEnumerator                                 \
        },                                                                      \
        .Length = 0,                                                            \
        .MaxLength = maxLength,                                                 \
        .Values = alloc_array(T, maxLength),                                    \
        ._memberSize = sizeof(T)                                                \
    };                                                                          \
    return result;                                                              \
}                                                                               \
T Array_##T##_Get(Array source, int index)                                      \
{                                                                               \
    return ((T*)source->Values)[index];                                         \
}                                                                               \
void Array_##T##_Set(Array source, int index, T value)                          \
{                                                                               \
    ((T*)source->Values)[index] = value;                                        \
}                                                                               \
int Array_##T##_IndexOf(Array source, T item)                                   \
{                                                                               \
    for (int i = 0; i < source->Length; ++i) {                                  \
        if (ValueEquator(sizeof(T), &((T*)source->Values)[i], &item)) {         \
            return i;                                                           \
        }                                                                       \
    }                                                                           \
    return -1;                                                                  \
}                                                                               \
void Array_##T##_Fill(Array source, T item)                                     \
{                                                                               \
    for (int i = 0; i < source->MaxLength; ++i) {                               \
        ((T*)source->Values)[i] = item;                                         \
    }                                                                           \
}                                                                               \
void Array_##T##_Initialize(Array source)                                       \
{                                                                               \
    for (int i = 0; i < source->MaxLength; ++i) {                               \
        ((T*)source->Values)[i] = new(T)();                                     \
    }                                                                           \
    source->Length = source->MaxLength;                                         \
}                                                                               \
IMPL_ENUMERABLE_TO_ARRAY(T)

#pragma endregion

#endif