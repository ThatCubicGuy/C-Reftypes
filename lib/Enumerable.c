#include "Enumerable.h"
#include "Defines.h"
#include "Macros.h"

#pragma region Helpers

internal abstract_class (Enumerable, {
    implements(IEnumerable);
}, {})

internal abstract_class (Enumerator, {
    implements(IEnumerator);
})

internal subclass (CompoundEnumerable, Enumerable, {
    IEnumerable _baseEnumerable;
})
define_ctor(CompoundEnumerable)(IEnumerable baseEnumerable)
{
    alloc_init(CompoundEnumerable, result) {
        ._baseEnumerable = baseEnumerable
    };
    return result;
}

internal subclass (CompoundEnumerator, Enumerator, {
    IEnumerator _currentEnumerator;
    IEnumerable _baseEnumerable;
})
define_ctor(CompoundEnumerator, GenericName(Func, CompoundEnumerator), IEnumerator, IEnumerable)(bool abstract_method(CompoundEnumerator, moveNext), IEnumerator currentEnumerator, IEnumerable baseEnumerable)
{
    alloc_init(CompoundEnumerator, result) {
        .Dispose = CompoundDispose,
        .Reset = CompoundReset,
        ._baseEnumerable = baseEnumerable,
        ._currentEnumerator = currentEnumerator
    };
    return result;
}

private void CompoundReset(IEnumerator This)
{
    This->Current = NULL;
    CompoundEnumerator e = (CompoundEnumerator)This;
    e->_currentEnumerator->Reset(e->_currentEnumerator);
}

private void CompoundDispose(IEnumerator This)
{
    CompoundEnumerator e = (CompoundEnumerator)This;
    e->_currentEnumerator->Dispose(e->_currentEnumerator);
    free(This);
}

#pragma endregion

#pragma region Where

internal subclass (WhereEnumerable, CompoundEnumerable, {
    PredicateFunc* _filter;
})
define_ctor(WhereEnumerable)(IEnumerator currentEnumerator, IEnumerable baseEnumerable, Predicate(object))
{
    // TODO: some macro to inherit constructors
    WhereEnumerable result = (WhereEnumerable)memresize(new(CompoundEnumerable)(baseEnumerable),sizeof(storage(WhereEnumerable)));
    *result = init(WhereEnumerable) {
        .GetEnumerator = GetWhereEnumerator,
        ._filter = Func_bool_object
    };
    return result;
}

private bool WhereMoveNext(IEnumerator This)
{
    CompoundEnumerator where = (CompoundEnumerator)This;
    while (where->_currentEnumerator->MoveNext(where->_currentEnumerator)) {
        This->Current = where->_currentEnumerator->Current;
        if (((WhereEnumerable)where->_baseEnumerable)->_filter(This->Current)) return true;
    }

    return false;
}

private IEnumerator GetWhereEnumerator(IEnumerable This)
{
    WhereEnumerable where = (WhereEnumerable)This;

    alloc_init(CompoundEnumerator, result) {
        .MoveNext = WhereMoveNext,
        .Reset = CompoundReset,
        .Dispose = CompoundDispose,
        ._currentEnumerator = where->_baseEnumerable->GetEnumerator(where->_baseEnumerable),
        ._baseEnumerable = This
    };

    return as_interface(IEnumerator,result);
}

/// @brief Filters a sequence based on a predicate.
/// @param source Enumerable to filter.
/// @param filter Condition that the elements must fulfill to be taken from the sequence.
/// @return A new enumerable.
IEnumerable Enumerable_Where(IEnumerable source, PredicateFunc* filter)
{
    alloc_init(WhereEnumerable, result) {
        .GetEnumerator = GetWhereEnumerator,
        ._baseEnumerable = source,
        ._filter = filter
    };
    return as_interface(IEnumerable,result);
}

#pragma endregion

#pragma region Select

internal subclass (SelectEnumerable, CompoundEnumerable, {
    SelectorFunc* _selector;
})

private bool SelectMoveNext(IEnumerator This)
{
    CompoundEnumerator select = (CompoundEnumerator)This;
    if (select->_currentEnumerator->MoveNext(select->_currentEnumerator)) {
        This->Current = ((SelectEnumerable)select->_baseEnumerable)->_selector(select->_currentEnumerator->Current);
        return true;
    }

    return false;
}

private IEnumerator GetSelectEnumerator(IEnumerable This)
{
    SelectEnumerable select = (SelectEnumerable)This;

    alloc_init(CompoundEnumerator, result) {
        .MoveNext = SelectMoveNext,
        .Reset = CompoundReset,
        .Dispose = CompoundDispose,
        ._currentEnumerator = select->_baseEnumerable->GetEnumerator(select->_baseEnumerable),
        ._baseEnumerable = This
    };

    return as_interface(IEnumerator,result);
}

/// @brief Projects each element of a sequence into a new form.
/// @param source Enumerable to project.
/// @param selector Function to apply to each element.
/// @return A new enumerable.
IEnumerable Enumerable_Select(IEnumerable source, SelectorFunc* selector)
{
    alloc_init(SelectEnumerable, result) {
        .GetEnumerator = GetSelectEnumerator,
        ._baseEnumerable = source,
        ._selector = selector,
    };
    return as_interface(IEnumerable,result);
}

#pragma endregion

#pragma region SelectMany

internal subclass (SelectManyEnumerable, CompoundEnumerable, {
    SelectManyFunc* _selector;
})

internal subclass (SelectManyEnumerator, Enumerator, {
    IEnumerable _baseEnumerable;
    IEnumerator _innerEnumerator;
    IEnumerator _outerEnumerator;
})

private bool SelectManyMoveNext(IEnumerator This)
{
    SelectManyEnumerator selectMany = (SelectManyEnumerator)This;

    if (selectMany->_innerEnumerator != NULL && selectMany->_innerEnumerator->MoveNext(selectMany->_innerEnumerator)) {
        This->Current = selectMany->_innerEnumerator->Current;
        return true;
    } else if (selectMany->_outerEnumerator->MoveNext(selectMany->_outerEnumerator)) {
        if (selectMany->_innerEnumerator != NULL) selectMany->_innerEnumerator->Dispose(selectMany->_innerEnumerator);
        IEnumerable result = ((SelectManyEnumerable)selectMany->_baseEnumerable)->_selector(selectMany->_outerEnumerator->Current);
        selectMany->_innerEnumerator = result->GetEnumerator(result);
        return SelectManyMoveNext(This);
    }

    return false;
}

private void SelectManyReset(IEnumerator This)
{
    SelectManyEnumerator selectMany = (SelectManyEnumerator)This;
    selectMany->_innerEnumerator = NULL;
    selectMany->_outerEnumerator->Reset(selectMany->_outerEnumerator);
}

private void SelectManyDispose(IEnumerator This)
{
    SelectManyEnumerator selectMany = (SelectManyEnumerator)This;
    if (selectMany->_innerEnumerator != NULL) selectMany->_innerEnumerator->Dispose(selectMany->_innerEnumerator);
    selectMany->_outerEnumerator->Dispose(selectMany->_outerEnumerator);
    free(This);
}

private IEnumerator GetSelectManyEnumerator(IEnumerable This)
{
    SelectManyEnumerable selectMany = (SelectManyEnumerable)This;

    alloc_init(SelectManyEnumerator, result) {
        .MoveNext = SelectManyMoveNext,
        .Reset = SelectManyReset,
        .Dispose = SelectManyDispose,
        ._outerEnumerator = selectMany->_baseEnumerable->GetEnumerator(selectMany->_baseEnumerable),
        ._baseEnumerable = This
    };

    return as_interface(IEnumerator,result);
}

/// @brief Projects each element of the collection into a new collection, then flattens the result.
/// @param source Source enumerable to project the elements of.
/// @param selector Selector function for the resulting collection.
/// @return A new enumerable.
IEnumerable Enumerable_SelectMany(IEnumerable source, SelectManyFunc* selector)
{
    alloc_init(SelectManyEnumerable, result) {
        .GetEnumerator = GetSelectManyEnumerator,
        ._baseEnumerable = source,
        ._selector = selector
    };
    return as_interface(IEnumerable,result);
}

#pragma endregion

#pragma region Take / Skip

internal subclass (LimitedEnumerable, CompoundEnumerable, {
    int Count;
})

internal subclass (LimitedEnumerator, CompoundEnumerator, {
    int Count;
})

private void LimitedReset(IEnumerator This)
{
    ((LimitedEnumerator)This)->Count = ((LimitedEnumerable)((CompoundEnumerator)This)->_baseEnumerable)->Count;
    CompoundReset(This);
}

private bool TakeMoveNext(IEnumerator This)
{
    if (((LimitedEnumerator)This)->Count == 0) return false;
    ((LimitedEnumerator)This)->Count -= 1;
    CompoundEnumerator modified = (CompoundEnumerator)This;
    if (modified->_currentEnumerator->MoveNext(modified->_currentEnumerator)) {
        This->Current = modified->_currentEnumerator->Current;
        return true;
    }
    return false;
}

private IEnumerator GetTakeEnumerator(IEnumerable This)
{
    LimitedEnumerable limited = (LimitedEnumerable)This;

    alloc_init(LimitedEnumerator, result) {
        .MoveNext = TakeMoveNext,
        .Reset = LimitedReset,
        .Dispose = CompoundDispose,
        .Count = limited->Count,
        ._currentEnumerator = limited->_baseEnumerable->GetEnumerator(limited->_baseEnumerable),
        ._baseEnumerable = This,
    };

    return as_interface(IEnumerator,result);
}

private bool SkipMoveNext(IEnumerator This)
{
    CompoundEnumerator modified = (CompoundEnumerator)This;
    while (((LimitedEnumerator)This)->Count > 0) {
        ((LimitedEnumerator)This)->Count -= 1;
        modified->_currentEnumerator->MoveNext(modified->_currentEnumerator);
    }
    if (modified->_currentEnumerator->MoveNext(modified->_currentEnumerator)) {
        This->Current = modified->_currentEnumerator->Current;
        return true;
    }
    return false;
}

private IEnumerator GetSkipEnumerator(IEnumerable This)
{
    LimitedEnumerable limited = (LimitedEnumerable)This;

    alloc_init(LimitedEnumerator, result) {
        .MoveNext = SkipMoveNext,
        .Reset = LimitedReset,
        .Dispose = CompoundDispose,
        ._currentEnumerator = limited->_baseEnumerable->GetEnumerator(limited->_baseEnumerable),
        ._baseEnumerable = This,
        .Count = limited->Count
    };

    return as_interface(IEnumerator,result);
}

/// @brief Returns the first count items from a sequence.
/// @param source Enumerable to take items from.
/// @param count Amount of items to take.
/// @return A new enumerable.
IEnumerable Enumerable_Take(IEnumerable source, int count)
{
    alloc_init(LimitedEnumerable, result) {
        .GetEnumerator = GetTakeEnumerator,
        ._baseEnumerable = source,
        .Count = count
    };

    return as_interface(IEnumerable,result);
}

/// @brief Skips the first count items from a sequence before returning the rest.
/// @param source Enumerable to skip items from.
/// @param count Amount of items to skip.
/// @return A new enumerable.
IEnumerable Enumerable_Skip(IEnumerable source, int count)
{
    alloc_init(LimitedEnumerable, result) {
        .GetEnumerator = GetSkipEnumerator,
        ._baseEnumerable = source,
        .Count = count
    };

    return as_interface(IEnumerable,result);
}

#pragma endregion

#pragma region Append / Prepend

internal subclass (ExtendEnumerable, CompoundEnumerable, {
    object _added;
})

internal subclass (ExtendEnumerator, CompoundEnumerator, {
    bool _hasEnumeratedExtra;
})

private void ExtendReset(IEnumerator This)
{
    ((ExtendEnumerator)This)->_hasEnumeratedExtra = false;
    CompoundReset(This);
}

private bool AppendMoveNext(IEnumerator This)
{
    CompoundEnumerator modified = (CompoundEnumerator)This;
    if (modified->_currentEnumerator->MoveNext(modified->_currentEnumerator)) {
        This->Current = modified->_currentEnumerator->Current;
        return true;
    } else if (!((ExtendEnumerator)This)->_hasEnumeratedExtra) {
        This->Current = ((ExtendEnumerable)modified->_baseEnumerable)->_added;
        ((ExtendEnumerator)This)->_hasEnumeratedExtra = true;
        return true;
    }

    return false;
}

private IEnumerator GetAppendEnumerator(IEnumerable This)
{
    ExtendEnumerable extend = (ExtendEnumerable)This;

    alloc_init(ExtendEnumerator, result) {
        .MoveNext = AppendMoveNext,
        .Reset = ExtendReset,
        .Dispose = CompoundDispose,
        ._currentEnumerator = extend->_baseEnumerable->GetEnumerator(extend->_baseEnumerable),
        ._baseEnumerable = This,
        ._hasEnumeratedExtra = false
    };

    return as_interface(IEnumerator,result);
}

private bool PrependMoveNext(IEnumerator This)
{
    CompoundEnumerator modified = (CompoundEnumerator)This;
    if (!((ExtendEnumerator)This)->_hasEnumeratedExtra) {
        This->Current = ((ExtendEnumerable)modified->_baseEnumerable)->_added;
        ((ExtendEnumerator)This)->_hasEnumeratedExtra = true;
        return true;
    } else if (modified->_currentEnumerator->MoveNext(modified->_currentEnumerator)) {
        This->Current = modified->_currentEnumerator->Current;
        return true;
    }

    return false;
}

private IEnumerator GetPrependEnumerator(IEnumerable This)
{
    ExtendEnumerable extend = (ExtendEnumerable)This;

    alloc_init(ExtendEnumerator, result) {
        .MoveNext = PrependMoveNext,
        .Reset = ExtendReset,
        .Dispose = CompoundDispose,
        ._currentEnumerator = extend->_baseEnumerable->GetEnumerator(extend->_baseEnumerable),
        ._baseEnumerable = This,
        ._hasEnumeratedExtra = false
    };

    return as_interface(IEnumerator,result);
}

/// @brief Appends an element to the end of a sequence.
/// @param source Enumerable to append the item to.
/// @param item Item to append.
/// @return A new enumerable.
IEnumerable Enumerable_Append(IEnumerable source, object item)
{
    alloc_init(ExtendEnumerable, result) {
        .GetEnumerator = GetAppendEnumerator,
        ._baseEnumerable = source,
        ._added = item
    };

    return as_interface(IEnumerable,result);
}

/// @brief Prepends an element to the start of a sequence.
/// @param source Enumerable to prepend the item to.
/// @param item Item to prepend.
/// @return A new enumerable.
IEnumerable Enumerable_Prepend(IEnumerable source, object item)
{
    alloc_init(ExtendEnumerable, result) {
        .GetEnumerator = GetPrependEnumerator,
        ._baseEnumerable = source,
        ._added = item
    };

    return as_interface(IEnumerable,result);
}

#pragma endregion

#pragma region Concat

internal subclass (ConcatEnumerable, Enumerable, {
    IEnumerable _firstEnumerable;
    IEnumerable _secondEnumerable;
})

internal subclass (ConcatEnumerator, CompoundEnumerator, {
    bool _startedSecondEnumeration;
})

private bool ConcatMoveNext(IEnumerator This)
{
    CompoundEnumerator modified = (CompoundEnumerator)This;
    if (modified->_currentEnumerator->MoveNext(modified->_currentEnumerator)) {
        This->Current = modified->_currentEnumerator->Current;
        return true;
    } else if (!((ConcatEnumerator)This)->_startedSecondEnumeration) {
        IEnumerable secondEnum = ((ConcatEnumerable)modified->_baseEnumerable)->_secondEnumerable;
        modified->_currentEnumerator = secondEnum->GetEnumerator(secondEnum);
        ((ConcatEnumerator)This)->_startedSecondEnumeration = true;
        return ConcatMoveNext(This);
    }

    return false;
}

private void ConcatReset(IEnumerator This)
{
    ((ConcatEnumerator)This)->_startedSecondEnumeration = false;
    CompoundReset(This);
}

private IEnumerator GetConcatEnumerator(IEnumerable This)
{
    ConcatEnumerable concat = (ConcatEnumerable)This;

    alloc_init(ConcatEnumerator, result) {
        .MoveNext = ConcatMoveNext,
        .Reset = ConcatReset,
        .Dispose = CompoundDispose,
        ._currentEnumerator = concat->_firstEnumerable->GetEnumerator(concat->_firstEnumerable),
        ._baseEnumerable = This,
        ._startedSecondEnumeration = false
    };

    return as_interface(IEnumerator,result);
}

/// @brief Concatenates two sequences.
/// @param first The first sequence to concatenate.
/// @param second The second sequence to concatenate.
/// @return A new enumerable.
IEnumerable Enumerable_Concat(IEnumerable first, IEnumerable second)
{
    alloc_init(ConcatEnumerable, result) {
        .GetEnumerator = GetConcatEnumerator,
        ._firstEnumerable = first,
        ._secondEnumerable = second
    };

    return as_interface(IEnumerable,result);
}

#pragma endregion

#pragma region Non-Tunnels

/// @brief Returns the element at the given zero-based index of the sequence.
/// @param source Enumerable to extract the element from.
/// @param index Index of the element.
/// @return The element at the specified index.
object Enumerable_ElementAt(IEnumerable source, int index)
{
    IEnumerator e = source->GetEnumerator(source);
    while(e->MoveNext(e) && index > 0) { index -= 1; }
    object item = e->Current;
    e->Dispose(e);
    return item;
}

/// @brief Determines if any element of a sequence satisfies a condition.
/// @param source The enumerable to check.
/// @param predicate Condition to satisfy.
/// @return True if any element satisfies the condition, false otherwise.
bool Enumerable_Any(IEnumerable source, PredicateFunc* predicate)
{
    IEnumerator e = source->GetEnumerator(source);
    while(e->MoveNext(e)) {
        if (predicate(e->Current)) {
            e->Dispose(e);
            return true;
        }
    }

    e->Dispose(e);
    return false;
}

/// @brief Determines if all elements of a sequence satisfy a condition.
/// @param source The enumerable to check.
/// @param predicate Condition to satisfy.
/// @return True if all elements satisfy the condition, false otherwise.
bool Enumerable_All(IEnumerable source, PredicateFunc* predicate)
{
    IEnumerator e = source->GetEnumerator(source);
    while(e->MoveNext(e)) {
        if (!predicate(e->Current)) {
            e->Dispose(e);
            return false;
        }
    }

    e->Dispose(e);
    return true;
}

/// @brief Applies an accumulator function over a sequence.
/// @param source Enumerable to aggregate.
/// @param aggregate Accumulator function to apply.
/// @return The final accumulation value.
object Enumerable_Aggregate(IEnumerable source, AggregateFunc* aggregate)
{
    IEnumerator e = source->GetEnumerator(source);
    if (!e->MoveNext(e)) {
        e->Dispose(e);
        return NULL;
    }
    object current = e->Current;
    while(e->MoveNext(e)) {
        current = aggregate(current, e->Current);
    }
    e->Dispose(e);
    return current;
}

/// @brief Searches for the given element in a sequence and returns the zero-based index of this element.
/// @param source Enumerable to search in.
/// @param item Item to search for.
/// @return The zero-based index of this item in the sequence.
int Enumerable_IndexOf(IEnumerable source, object item)
{
    IEnumerator e = source->GetEnumerator(source);
    
    for (int i = 0; e->MoveNext(e); ++i) {
        if (e->Current == item) {
            e->Dispose(e);
            return i;
        }
    }

    e->Dispose(e);
    return -1;
}

/// @brief Returns the first element of the sequence that satisfies the condition.
/// @param source Enumerable to search in.
/// @param predicate Condition to satisfy.
/// @return The first element that satisfies the predicate.
object Enumerable_FirstOrDefault(IEnumerable source, PredicateFunc* predicate)
{
    IEnumerator e = source->GetEnumerator(source);
    while (e->MoveNext(e)) {
        if (predicate(e->Current)) {
            object item = e->Current;
            e->Dispose(e);
            return item;
        }
    }

    e->Dispose(e);
    return NULL;
}

/// @brief Performs an action on each element of a collection.
/// @param source Enumerable to execute the action on.
/// @param Action_object Action to execute on each item.
void Enumerable_ForEach(IEnumerable source, Action(object))
{
    IEnumerator e = source->GetEnumerator(source);
    while (e->MoveNext(e)) action(e->Current);
    e->Dispose(e);
}

/// @brief Determines whether a sequence contains a specified element.
/// @param source Enumerable to search in.
/// @param item Item to search for.
bool Enumerable_Contains(IEnumerable source, object item)
{
    IEnumerator e = source->GetEnumerator(source);
    while (e->MoveNext(e)) {
        if (e->Current == item) {
            e->Dispose(e);
            return true;
        }
    }

    e->Dispose(e);
    return false;
}

/// @brief Returns a number that represents the amount of elements in the specified enumerable.
/// @param source Enumerable whose length to count.
/// @return A number representing the amount of items in source.
int Enumerable_Count(IEnumerable source)
{
    int count = 0;
    foreach_ref(object, _=_, source, {
        count += 1;
    });
    return count;
}

/// @brief Determines whether two sequences are equal by comparing each element individually.
/// @param first First enumerable to compare.
/// @param second Second enumerable to compare.
/// @return True if every element from first is equal to second, false otherwise.
bool Enumerable_SequenceEqual(IEnumerable first, IEnumerable second)
{
    IEnumerator e1 = first->GetEnumerator(first);
    IEnumerator e2 = second->GetEnumerator(second);
    while (e1->MoveNext(e1) && e2->MoveNext(e2)) {
        if (e1->Current != e2->Current) {
            e1->Dispose(e1);
            e2->Dispose(e2);
            return false;
        }
    }

    if (e1->MoveNext(e1) || e2->MoveNext(e2)) {
        e1->Dispose(e1);
        e2->Dispose(e2);
        return false;
    }

    e1->Dispose(e1);
    e2->Dispose(e2);
    return true;
}

TUPLE_2_DEFINE(int, object)

internal subclass (IndexEnumerator, CompoundEnumerator, {
    int _currentIndex;
})
private bool IndexMoveNext(IEnumerator This)
{
    IndexEnumerator index = (IndexEnumerator)This;
    if (!index->_currentEnumerator->MoveNext(index->_currentEnumerator)) return false;
    index->_currentIndex += 1;
    This->Current = box(int_object);
    *(int_object*)This->Current = new(int_object)(index->_currentIndex, index->_currentEnumerator->Current);
    return true;
}
private IEnumerator GetIndexEnumerator(IEnumerable This)
{
    CompoundEnumerable index = (CompoundEnumerable)This;
    alloc_init(IndexEnumerator, result) {
        .MoveNext = IndexMoveNext,
        .Reset = CompoundReset,
        .Dispose = CompoundDispose,
        ._currentEnumerator = index->_baseEnumerable->GetEnumerator(index->_baseEnumerable),
        ._baseEnumerable = This,
        ._currentIndex = -1
    };
    return as_interface(IEnumerator,result);
}
IEnumerable Enumerable_Index(IEnumerable source)
{
    alloc_init(CompoundEnumerable, result) {
        .GetEnumerator = GetIndexEnumerator,
        ._baseEnumerable = source
    };
    return as_interface(IEnumerable,result);
}

#pragma endregion

#pragma region Generic Implementations
TUPLE_2_IMPLEMENT(int, object)
#pragma endregion