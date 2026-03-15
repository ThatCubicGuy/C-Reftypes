#ifndef COLLECTIONS_GENERIC_LIST
#define COLLECTIONS_GENERIC_LIST

#include "Collections/Generic/EnumerableT.h"

#pragma region Define

#define LIST_DEFINE(T)                                                  \
public class (List_##T, {                                               \
    implements(IEnumerable_##T);                                        \
    int Capacity;                                                       \
    int Count;                                                          \
    T* Values;                                                          \
})                                                                      \
/**                                                                     \
 * @brief Ensures the given list has the capacity                       \
 * to hold a given amount of items.                                     \
 * @param source List to ensure the capacity for.                       \
 * @param capacity Capacity to ensure.                                  \
 */                                                                     \
define_ctor(List_##T)(int capacity);                                    \
/**                                                                     \
 * @brief Sets the capacity of the list to the amount of elements,      \
 * if that amount is less than 90% of current capacity.                 \
 * @param source List to trim the excess of.                            \
 */                                                                     \
void static_method(List_##T, Destroy,(List_##T* list));                 \
/**                                                                     \
 * @brief Add an element to the end of the list.                        \
 * @param list List to add an element to.                               \
 * @param item Item to add to the end of the list.                      \
 */                                                                     \
List_##T static_method(Enumerable_##T, ToList,(IEnumerable_##T source));\
/**                                                                     \
 * @brief Removes an element from the list.                             \
 * @param source List to remove the element from.                       \
 * @param item Item to remove from the list.                            \
 */                                                                     \
void method_sig(List_##T, (Add,(T item)));                              \
/**                                                                     \
 * @brief Removes all elements from the list.                           \
 * @param source List to clear.                                         \
 */                                                                     \
void method_sig(List_##T, (Remove,(T item)));                           \
/**                                                                     \
 * @brief Insert an item into the list at the given index.              \
 * @param source List to insert the element into.                       \
 * @param item Item to insert into the list.                            \
 * @param index Index to insert the item at.                            \
 */                                                                     \
void method_sig(List_##T, (Clear,()));                                  \
/**                                                                     \
 * @brief Performs an action on each element of the list.               \
 * @param source List to execute the action on.                         \
 * @param action Action to execute on each item.                        \
 */                                                                     \
void method_sig(List_##T, (Insert,(T item, int index)));                \
/**                                                                     \
 * @brief Creates a new List with the given capacity.                   \
 * @param capacity Initial capacity for the created list.               \
 * @return A new List with the given capacity.                          \
 */                                                                     \
void method_sig(List_##T, (ForEach,(void (*action)(T*))));              \
/**                                                                     \
 * @brief Frees all memory relating to a list.                          \
 * @param list List to destroy.                                         \
 */                                                                     \
void method_sig(List_##T, (EnsureCapacity,(int capacity)));             \
/**                                                                     \
 * @brief Creates a List from an IEnumerable.                           \
 * @param source Enumerable to take items from.                         \
 * @return A new list.                                                  \
 */                                                                     \
void method_sig(List_##T, (TrimExcess,()));

#pragma endregion

#endif