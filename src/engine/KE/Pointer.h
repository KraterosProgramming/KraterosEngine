#pragma once

#include "Object.h"

namespace KE
{

class Pointer
{
    Object* object;
    int count;
public:
    Pointer(Object* object);
    ~Pointer();

    Object* getObject();
    int getCount();

    void inc();
    void dec();

    void destroy();
};

}
