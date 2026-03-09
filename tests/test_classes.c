#include "Defines.h"

public class (Car, {
    string Brand;
    string Name;
    int Year;
})

subclass (Truck, Car, {
    int Capacity;
})

public interface (Thing1, {
    int thing1;
})

public interface (Thing2, {
    int thing2;
    implements(Thing1);
})

int main()
{
    Car a;
    Truck b;
    Thing2 yhing = alloc_ref(Thing2);
    yhing->thing2 = 13;
    yhing->thing1 = 99;
    printf("Distance is %d\n", offset_of(__impl_Thing1, yhing));
    printf("Stuff in yhing: %d %d\n", yhing->thing1, yhing->thing2);
    printf("Stuff in yhing as parent interface: %d\n", as_interface(Thing1, yhing)->thing1);
    Thing1 thingamajig = as_interface(Thing1, yhing);
    thingamajig->thing1 = 17;
    printf("Stuff in thingamajig as inheritor: %d %d\n", as_inheritor(Thing2, Thing1, thingamajig)->thing1, as_inheritor(Thing2, Thing1, thingamajig)->thing2);
}