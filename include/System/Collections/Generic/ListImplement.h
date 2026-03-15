#ifndef COLLECTIONS_GENERIC_LIST_IMPLEMENTATIONS
#define COLLECTIONS_GENERIC_LIST_IMPLEMENTATIONS
#include "Collections/Generic/ListT.h"

#pragma region Implement

#define LIST_IMPLEMENT(T)                                                                       \
public interface (ListEnumerator_##T, {                                                         \
    implements(IEnumerator_##T);                                                                \
    int _currentIndex;                                                                          \
    List_##T _list;                                                                             \
})                                                                                              \
private bool method_sig(ListEnumerator_##T, MoveNext,())                                        \
{                                                                                               \
    ListEnumerator_##T e = (ListEnumerator_##T)this;                                            \
    if (e->_currentIndex < e->_list->Count) {                                                   \
        e->Current = e->_list->Values[e->_currentIndex];                                        \
        e->_currentIndex += 1;                                                                  \
        return true;                                                                            \
    }                                                                                           \
    return false;                                                                               \
}                                                                                               \
private void method_sig(ListEnumerator_##T, Reset,())                                           \
{                                                                                               \
    ((ListEnumerator_##T)this)->_currentIndex = 0;                                              \
    this->Current = default(T);                                                                 \
}                                                                                               \
private void ListDispose_##T(IEnumerator_##T this)                                              \
{                                                                                               \
    free(this);                                                                                 \
}                                                                                               \
private IEnumerator_##T ListGetEnumerator_##T(const IEnumerable_##T this)                       \
{                                                                                               \
    ListEnumerator_##T result = alloc(ListEnumerator_##T);                                      \
    *result = (struct ListEnumerator_##T##_s) {                                                 \
        ._parent = (struct IEnumerator_##T##_s) {                                               \
            .MoveNext = ListMoveNext_##T,                                                       \
            .Reset = ListReset_##T,                                                             \
            .Dispose = ListDispose_##T                                                          \
        },                                                                                      \
        ._currentIndex = 0,                                                                     \
        ._list = (List_##T)this                                                                 \
    };                                                                                          \
    return base(result);                                                                        \
}                                                                                               \
void List_##T##_EnsureCapacity(List_##T source, int capacity)                                   \
{                                                                                               \
    if (source->Capacity < capacity) {                                                          \
        source->Values = realloc(source->Values, sizeof(T) * capacity);                         \
        source->Capacity = capacity;                                                            \
    }                                                                                           \
}                                                                                               \
void List_##T##_TrimExcess(List_##T source)                                                     \
{                                                                                               \
    if (source->Count < source->Capacity * 0.9) {                                               \
        source->Values = realloc(source->Values, sizeof(T) * source->Count);                    \
        source->Capacity = source->Count;                                                       \
    }                                                                                           \
}                                                                                               \
void List_##T##_Add(List_##T source, T item)                                                    \
{                                                                                               \
    if (source->Count >= source->Capacity) {                                                    \
        List_##T##_EnsureCapacity(source, source->Capacity * 2);                                \
    }                                                                                           \
    source->Values[source->Count++] = item;                                                     \
}                                                                                               \
void List_##T##_Remove(List_##T source, T item)                                                 \
{                                                                                               \
    for (int i = 0; i < source->Count; ++i) {                                                   \
        if (ValueEquator(sizeof(T), &source->Values[i], &item)) {                               \
            source->Count -= 1;                                                                 \
            for (int j = i; j < source->Count; ++j) {                                           \
                source->Values[j] = source->Values[j + 1];                                      \
            }                                                                                   \
            source->Values[source->Count] = default(T);                                         \
            return;                                                                             \
        }                                                                                       \
    }                                                                                           \
}                                                                                               \
void List_##T##_Clear(List_##T source)                                                          \
{                                                                                               \
    for (int i = 0; i < source->Count; ++i) {                                                   \
        source->Values[i] = default(T);                                                         \
    }                                                                                           \
    source->Count = 0;                                                                          \
}                                                                                               \
void List_##T##_Insert(List_##T source, T item, int index)                                      \
{                                                                                               \
    if (source->Count >= source->Capacity) {                                                    \
        List_##T##_EnsureCapacity(source, source->Capacity * 2);                                \
    }                                                                                           \
    for (int i = source->Count; i >= index; --i) {                                              \
        source->Values[i + 1] = source->Values[i];                                              \
    }                                                                                           \
    source->Values[index] = item;                                                               \
}                                                                                               \
void List_##T##_ForEach(List_##T source, void (*action)(T*))                                    \
{                                                                                               \
    for (int i = 0; i < source->Count; ++i) {                                                   \
        action(&source->Values[i]);                                                             \
    }                                                                                           \
}                                                                                               \
List_##T List_##T##__ctor(int capacity)                                                         \
{                                                                                               \
    List_##T result = alloc(List_##T);                                                          \
    *result = (struct List_##T##_s) {                                                           \
        .Capacity = capacity,                                                                   \
        .Count = 0,                                                                             \
        ._parent = (struct IEnumerable_##T##_s) {                                               \
            .GetEnumerator = ListGetEnumerator_##T                                              \
        }                                                                                       \
    };                                                                                          \
    if (capacity > 0) {                                                                         \
        result->Values = alloc_array(T, capacity);                                              \
    }                                                                                           \
    return result;                                                                              \
}                                                                                               \
void DestroyList_##T(List_##T* list)                                                            \
{                                                                                               \
    free((*list)->Values);                                                                      \
    free(*list);                                                                                \
    *list = NULL;                                                                               \
}                                                                                               \
List_##T Enumerable_##T##_ToList(IEnumerable_##T source)                                        \
{                                                                                               \
    /* Assume initial capacity */                                                               \
    int capacity = 16;                                                                          \
    List_##T result = alloc(List_##T);                                                          \
    *result = (struct List_##T##_s) {                                                           \
        ._parent = (struct IEnumerable_##T##_s) {                                               \
            .GetEnumerator = ListGetEnumerator_##T                                              \
        },                                                                                      \
        .Count = 0,                                                                             \
        .Capacity = capacity,                                                                   \
        .Values = alloc_array(T, capacity)                                                      \
    };                                                                                          \
    for (IEnumerator_##T e = source->GetEnumerator(source); e->MoveNext(e); ++result->Count) {  \
        if (result->Count == capacity) {                                                        \
            List_##T##_EnsureCapacity(result, capacity * 2);                                    \
        }                                                                                       \
        result->Values[result->Count] = e->Current;                                             \
    }                                                                                           \
    List_##T##_TrimExcess(result);                                                              \
    return result;                                                                              \
}

#pragma endregion
#endif