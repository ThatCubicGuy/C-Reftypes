#include "Class.h"
#include "String.h"

class(Car, {
    string Brand, Name;
    int Year;
})

define_ctor(Car)(int year, string brand)
{
    Car result = alloc_ref(Car);
    *result = init(Car) {
        .Brand = new(string)(brand),
        .Year = year
    };
    return result;
}

class(Truck, {
    inherits(Car);
})
