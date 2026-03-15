#include "VTable.h"
#include "Defines.h"

public class (Animal, {
    object __VTable[64];
    char species[3];
})

define_vtable(Animal,
    (void,Speak,()),
    (int,Walk,(int steps))
)

public void Meow(This(Animal))
{
    printf("Meow! I'm a %s\n", this->species);
}

public void Bark(This(Animal))
{
    printf("Bark! I'm a %s\n", this->species);
}

int main()
{
    Animal car;
    // I literally have no idea what I'm doing with this system.
}