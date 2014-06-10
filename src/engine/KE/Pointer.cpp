#include "Pointer.h"

namespace KE
{

Pointer::Pointer(Object *object)
{
    this->object = object;
    this->count = 0;
}

Pointer::~Pointer()
{
    destroy();
}

Object* Pointer::getObject()
{
    return object;
}

int Pointer::getCount()
{
    return count;
}

void Pointer::inc()
{
    ++count;
}

void Pointer::dec()
{
    --count;
}

void Pointer::destroy()
{
    if (object)
    {
        delete object;
        object = nullptr;
    }
}

}
