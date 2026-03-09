#ifndef COLLECTIONS_LINKED_LIST
#define COLLECTIONS_LINKED_LIST

#include "Enumerable.h"
#include "Defines.h"

/// @brief A node inside a linked list.
public class (LinkedNode, {
    storage(LinkedNode) *Next;
    object Value;
})

/// @brief A list of items stored by reference.
public class (LinkedList, {
    implements(IEnumerable);
    LinkedNode _start;
    LinkedNode _end;
    int Count;
})

/// @brief Creates a new instance of the LinkedList enumerable.
/// @return A new LinkedList with no elements.
define_ctor(LinkedList)();

/// @brief Creates a LinkedList from a static array.
/// @param itemCount Amount of items in the array.
/// @param items Array of items.
/// @return A new LinkedList with elements from the array.
LinkedList CreateLinkedListFromArray(int itemCount, object items[]);
#define class_define(TYPE, ...) __VA_ARGS__
class_define
(
/// @brief Add an element to the end of the list.
/// @param list List to add an element to.
/// @param item Item to add to the end of the list.
void Add(object item);

/// @brief Insert an item into the list at the given index.
/// @param source List to insert the element into.
/// @param item Item to insert into the list.
/// @param index Index to insert the item at.
void Insert(object item, int index);

/// @brief Removes all elements from the linked list.
/// @param source Linked list to clear.
void Clear();

/// @brief Frees up all memory occupied by a linked list.
/// @param source List to destroy.
void Destroy();
)
#endif