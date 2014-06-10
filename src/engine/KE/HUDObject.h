#pragma once

#include "Object.h"

namespace KE
{

class HUDObject : public Object
{
public:
    HUDObject(const Point &position, int z) : Object(position, z) { }
};

}
