#include "Enumerable.h"
#include "Defines.h"
#include "Macros.h"

#pragma region Helpers

internal abstract_class (Enumerable, {
    implements(IEnumerable);
})
inherit_vtable(Enumerable, IEnumerable)

internal abstract_class (Enumerator, {
    implements(IEnumerator);
})
inherit_vtable(Enumerator, IEnumerator)

internal subclass (CompoundEnumerable, Enumerable, {
    IEnumerable _baseEnumerable;
})
inherit_vtable(CompoundEnumerable, Enumerable)
define_ctor(CompoundEnumerable)(IEnumerator abstract_method(getEnumerator,()), IEnumerable baseEnumerable)
ctor_body(CompoundEnumerable, {
    this->GetEnumerator = getEnumerator;
    this->_baseEnumerable = baseEnumerable;
})
CompoundEnumerable_VTable;
internal subclass (CompoundEnumerator, Enumerator, {
    IEnumerator _currentEnumerator;
    IEnumerable _baseEnumerable;
})
inherit_vtable(CompoundEnumerator, Enumerator)
private void method_sig(CompoundEnumerator, Reset,())
{
    call(this->_currentEnumerator,Reset,());
    this->Current = NULL;
}
private void method_sig(CompoundEnumerator, Dispose,())
{
    this->_currentEnumerator->Dispose(this->_currentEnumerator);
    free(this);
}
define_vtable(CompoundEnumerator, (void,Dispose,()), (void,Reset,()))
define_ctor(CompoundEnumerator)(bool abstract_method(moveNext,()), IEnumerator currentEnumerator, IEnumerable baseEnumerable)
ctor_body(CompoundEnumerator, {
    this->_baseEnumerable = baseEnumerable;
    this->_currentEnumerator = currentEnumerator;
})

#pragma endregion

#pragma region Where

internal subclass (WhereEnumerable, CompoundEnumerable, {
    PredicateFunc* _filter;
})
private bool WhereMoveNext(This(CompoundEnumerator))
{
    while (call(this->_currentEnumerator,MoveNext,())) {
        this->Current = this->_currentEnumerator->Current;
        if (((WhereEnumerable)this->_baseEnumerable)->_filter(this->Current)) return true;
    }

    return false;
}
private IEnumerator GetWhereEnumerator(This(WhereEnumerable))
{
    return as_interface(IEnumerator,
        new(CompoundEnumerator)(WhereMoveNext, this->_baseEnumerable->GetEnumerator(this->_baseEnumerable), this));
}
inherit_vtable(WhereEnumerable, IEnumerable)
define_ctor(WhereEnumerable)(IEnumerable baseEnumerable, Predicate(object))
ctor_body(WhereEnumerable, {
    inherit_ctor(CompoundEnumerable, (GetWhereEnumerator, baseEnumerable));
    this->_filter = Func_bool_object;
})

/// @brief Filters a sequence based on a predicate.
/// @param source Enumerable to filter.
/// @param filter Condition that the elements must fulfill to be taken from the sequence.
/// @return A new enumerable.
IEnumerable Enumerable_Where(IEnumerable source, PredicateFunc* filter)
{
    return as_interface(IEnumerable,
        new(WhereEnumerable)(source, filter));
}

#pragma endregion

#pragma region Select

internal subclass (SelectEnumerable, CompoundEnumerable, {
    SelectorFunc* _selector;
})
private bool SelectMoveNext(This(CompoundEnumerator))
{
    CompoundEnumerator select = (CompoundEnumerator)this;
    if (select->_currentEnumerator->MoveNext(select->_currentEnumerator)) {
        select->Current = ((SelectEnumerable)select->_baseEnumerable)->_selector(select->_currentEnumerator->Current);
        return true;
    }

    return false;
}
private IEnumerator GetSelectEnumerator(This(SelectEnumerable))
{
    return as_interface(IEnumerator,
        new(CompoundEnumerator)(SelectMoveNext, this->_baseEnumerable->GetEnumerator(this->_baseEnumerable), this));
}
define_ctor(SelectEnumerable)(IEnumerable baseEnumerable, Func(object, object))
ctor_body(SelectEnumerable, {
    inherit_ctor(CompoundEnumerable, (GetSelectEnumerator, baseEnumerable));
    this->_selector = Func_object_object;
})

/// @brief Projects each element of a sequence into a new form.
/// @param source Enumerable to project.
/// @param selector Function to apply to each element.
/// @return A new enumerable.
IEnumerable Enumerable_Select(IEnumerable source, SelectorFunc* selector)
{
    return as_interface(IEnumerable,
        new(SelectEnumerable)(source, selector));
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
define_vtable(SelectManyEnumerator,
    (bool,MoveNext,()),
    (void,Reset,()),
    (void,Dispose,())
)
define_ctor(SelectManyEnumerator)(IEnumerator outerEnumerator, IEnumerable baseEnumerable)
ctor_body(SelectManyEnumerator, {})
private bool method_sig(SelectManyEnumerator, MoveNext,())
{
    if (this->_innerEnumerator != NULL && this->_innerEnumerator->MoveNext(this->_innerEnumerator)) {
        this->Current = this->_innerEnumerator->Current;
        return true;
    } else if (this->_outerEnumerator->MoveNext(this->_outerEnumerator)) {
        if (this->_innerEnumerator != NULL) this->_innerEnumerator->Dispose(this->_innerEnumerator);
        IEnumerable result = ((SelectManyEnumerable)this->_baseEnumerable)->_selector(this->_outerEnumerator->Current);
        this->_innerEnumerator = result->GetEnumerator(result);
        return SelectManyMoveNext(this);
    }

    return false;
}
private void method_sig(SelectManyEnumerator, Reset,())
{
    this->_outerEnumerator->Reset(this->_outerEnumerator);
    this->_innerEnumerator = NULL;
}
private void method_sig(SelectManyEnumerator, Dispose,())
{
    if (this->_innerEnumerator != NULL) this->_innerEnumerator->Dispose(this->_innerEnumerator);
    this->_outerEnumerator->Dispose(this->_outerEnumerator);
    free(this);
}
private IEnumerator GetSelectManyEnumerator(This(SelectManyEnumerable))
{
    return as_interface(IEnumerator,
        new(SelectManyEnumerator)(this->_baseEnumerable->GetEnumerator(this->_baseEnumerable), this));
}
define_ctor(SelectManyEnumerable)(IEnumerable baseEnumerable, Func(IEnumerable, object))
ctor_body(SelectManyEnumerable, {
    inherit_ctor(CompoundEnumerable, (GetSelectManyEnumerator, baseEnumerable));
    this->_selector = Func_IEnumerable_object;
})

/// @brief Projects each element of the collection into a new collection, then flattens the result.
/// @param source Source enumerable to project the elements of.
/// @param selector Selector function for the resulting collection.
/// @return A new enumerable.
IEnumerable Enumerable_SelectMany(IEnumerable source, SelectManyFunc* selector)
{
    return as_interface(IEnumerable,
        new(SelectManyEnumerable)(source, selector));
}

#pragma endregion

#pragma region Take / Skip

internal subclass (LimitedEnumerable, CompoundEnumerable, {
    int Count;
})

internal subclass (LimitedEnumerator, CompoundEnumerator, {
    int Count;
})
private void method_sig(LimitedEnumerator, Reset,())
{
    this->Count = ((LimitedEnumerable)this->_baseEnumerable)->Count;
    CompoundEnumerator_Reset(this);
}
private bool TakeMoveNext(This(CompoundEnumerator))
{
    if (((LimitedEnumerator)this)->Count == 0) return false;
    ((LimitedEnumerator)this)->Count -= 1;
    CompoundEnumerator modified = (CompoundEnumerator)this;
    if (modified->_currentEnumerator->MoveNext(modified->_currentEnumerator)) {
        modified->Current = modified->_currentEnumerator->Current;
        return true;
    }
    return false;
}
private IEnumerator GetTakeEnumerator(This(LimitedEnumerable))
{
    LimitedEnumerable limited = (LimitedEnumerable)this;

    alloc_init(LimitedEnumerator, result) {
        .MoveNext = TakeMoveNext,
        .Reset = LimitedReset,
        .Dispose = CompoundDispose,
        .Count = limited->Count,
        ._currentEnumerator = limited->_baseEnumerable->GetEnumerator(limited->_baseEnumerable),
        ._baseEnumerable = this,
    };

    return as_interface(IEnumerator,result);
}
private bool SkipMoveNext(This(CompoundEnumerator))
{
    LimitedEnumerator limited = (LimitedEnumerator)this;
    while (limited->Count > 0) {
        limited->Count -= 1;
        limited->_currentEnumerator->MoveNext(limited->_currentEnumerator);
    }
    if (limited->_currentEnumerator->MoveNext(limited->_currentEnumerator)) {
        limited->Current = limited->_currentEnumerator->Current;
        return true;
    }
    return false;
}
private IEnumerator GetSkipEnumerator(This(LimitedEnumerable))
{
    LimitedEnumerable limited = (LimitedEnumerable)this;

    alloc_init(LimitedEnumerator, result) {
        .MoveNext = SkipMoveNext,
        .Reset = LimitedReset,
        .Dispose = CompoundDispose,
        ._currentEnumerator = limited->_baseEnumerable->GetEnumerator(limited->_baseEnumerable),
        ._baseEnumerable = this,
        .Count = limited->Count
    };

    return as_interface(IEnumerator,result);
}
define_ctor(LimitedEnumerable)(IEnumerator abstract_method(getEnumerator,()), IEnumerable baseEnumerable, int count)
ctor_body(LimitedEnumerable, {
    inherit_ctor(CompoundEnumerable, (getEnumerator, baseEnumerable));
    this->Count = count;
})

/// @brief Returns the first count items from a sequence.
/// @param source Enumerable to take items from.
/// @param count Amount of items to take.
/// @return A new enumerable.
IEnumerable Enumerable_Take(IEnumerable source, int count)
{
    return as_interface(IEnumerable,
        new(LimitedEnumerable)(GetTakeEnumerator, source, count));
}

/// @brief Skips the first count items from a sequence before returning the rest.
/// @param source Enumerable to skip items from.
/// @param count Amount of items to skip.
/// @return A new enumerable.
IEnumerable Enumerable_Skip(IEnumerable source, int count)
{
    return as_interface(IEnumerable,
        new(LimitedEnumerable)(GetSkipEnumerator, source, count));
}

#pragma endregion

#pragma region Append / Prepend

internal subclass (ExtendEnumerable, CompoundEnumerable, {
    object _added;
})

internal subclass (ExtendEnumerator, CompoundEnumerator, {
    bool _hasEnumeratedExtra;
})
define_ctor(ExtendEnumerator)(bool method(MoveNext,()))
ctor_body(ExtendEnumerator, {
    inherit_ctor(CompoundEnumerator)()
})
private void ExtendReset(This(ExtendEnumerator))
{
    ((ExtendEnumerator)this)->_hasEnumeratedExtra = false;
    CompoundReset(this);
}

private bool AppendMoveNext(This(ExtendEnumerator))
{
    ExtendEnumerator extend = (ExtendEnumerator)this;
    if (extend->_currentEnumerator->MoveNext(extend->_currentEnumerator)) {
        extend->Current = extend->_currentEnumerator->Current;
        return true;
    } else if (!extend->_hasEnumeratedExtra) {
        extend->Current = ((ExtendEnumerable)extend->_baseEnumerable)->_added;
        extend->_hasEnumeratedExtra = true;
        return true;
    }

    return false;
}

private IEnumerator GetAppendEnumerator(This(ConcatEnumerable))
{
    ExtendEnumerable extend = (ExtendEnumerable)this;

    alloc_init(ExtendEnumerator, result) {
        .MoveNext = AppendMoveNext,
        .Reset = ExtendReset,
        .Dispose = CompoundDispose,
        ._currentEnumerator = extend->_baseEnumerable->GetEnumerator(extend->_baseEnumerable),
        ._baseEnumerable = this,
        ._hasEnumeratedExtra = false
    };

    return as_interface(IEnumerator,result);
}

private bool PrependMoveNext(This(CompoundEnumerator))
{
    ExtendEnumerator extend = (ExtendEnumerator)this;
    if (!extend->_hasEnumeratedExtra) {
        extend->Current = ((ExtendEnumerable)extend->_baseEnumerable)->_added;
        extend->_hasEnumeratedExtra = true;
        return true;
    } else if (extend->_currentEnumerator->MoveNext(extend->_currentEnumerator)) {
        extend->Current = extend->_currentEnumerator->Current;
        return true;
    }

    return false;
}

private IEnumerator GetPrependEnumerator(This(CompoundEnumerator))
{
    ExtendEnumerable extend = (ExtendEnumerable)this;

    alloc_init(ExtendEnumerator, result) {
        .MoveNext = PrependMoveNext,
        .Reset = ExtendReset,
        .Dispose = CompoundDispose,
        ._currentEnumerator = extend->_baseEnumerable->GetEnumerator(extend->_baseEnumerable),
        ._baseEnumerable = this,
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

private bool ConcatMoveNext(This(CompoundEnumerator))
{
    ConcatEnumerator concat = (ConcatEnumerator)this;
    if (concat->_currentEnumerator->MoveNext(concat->_currentEnumerator)) {
        concat->Current = concat->_currentEnumerator->Current;
        return true;
    } else if (!concat->_startedSecondEnumeration) {
        IEnumerable secondEnum = ((ConcatEnumerable)concat->_baseEnumerable)->_secondEnumerable;
        concat->_currentEnumerator = secondEnum->GetEnumerator(secondEnum);
        concat->_startedSecondEnumeration = true;
        return ConcatMoveNext(this);
    }

    return false;
}

private void ConcatReset(This(CompoundEnumerator))
{
    ((ConcatEnumerator)this)->_startedSecondEnumeration = false;
    CompoundReset(this);
}

private IEnumerator GetConcatEnumerator(This(CompoundEnumerator))
{
    ConcatEnumerable concat = (ConcatEnumerable)this;

    alloc_init(ConcatEnumerator, result) {
        .MoveNext = ConcatMoveNext,
        .Reset = ConcatReset,
        .Dispose = CompoundDispose,
        ._currentEnumerator = concat->_firstEnumerable->GetEnumerator(concat->_firstEnumerable),
        ._baseEnumerable = this,
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
    IEnumerator e = source->GetEnumerator(source);
    while (e->MoveNext(e)) {
        count += 1;
    }
    e->Dispose(e);
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
private bool IndexMoveNext(This(CompoundEnumerator))
{
    IndexEnumerator index = (IndexEnumerator)this;
    if (!index->_currentEnumerator->MoveNext(index->_currentEnumerator)) return false;
    index->_currentIndex += 1;
    index->Current = box(int_object);
    *(int_object*)index->Current = new(int_object)(index->_currentIndex, index->_currentEnumerator->Current);
    return true;
}
private IEnumerator GetIndexEnumerator(This(CompoundEnumerator))
{
    CompoundEnumerable index = (CompoundEnumerable)this;
    alloc_init(IndexEnumerator, result) {
        .MoveNext = IndexMoveNext,
        .Reset = CompoundReset,
        .Dispose = CompoundDispose,
        ._currentEnumerator = index->_baseEnumerable->GetEnumerator(index->_baseEnumerable),
        ._baseEnumerable = this,
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