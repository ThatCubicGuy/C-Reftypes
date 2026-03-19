#ifndef CUBE_STRING
#define CUBE_STRING
#include "Class.h"
#include "Defines.h"

/**
 * @brief Represents the empty string.
 * This field is constant.
 */
extern const string string_Empty;

/**
 * @brief Copies a string and returns the result.
 * @return A new string with characters from the other.
 * @pure
 */
primary_ctor(string)(string other);

/**
 * @brief Gets the length of the given string.
 * @returns An integer representing the
 * amount of characters in the string.
 * @pure
 */
int string_Length(string source);

/**
 * @brief Concatenates two strings and returns the result.
 * @return A new string.
 * @pure
 */
string string_Concat(string first, string second);

#ifdef STRING_ENUMERABLE_DEFINED
#include "System/Collections/Generic/EnumerableT.h"
ENUMERABLE_DEFINE(string)
ENUMERABLE_DEFINE_SELECT(string, string)
ENUMERABLE_DEFINE_SELECTMANY(string, string)
ENUMERABLE_DEFINE_AGGREGATE(string, string)
/**
 * @brief Joins the values of a string collection into one string,
 * using the specified separator.
 * @pure
 */
string string_Join(string separator, IEnumerable_string values);
#endif


#endif