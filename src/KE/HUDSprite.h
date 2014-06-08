#pragma once

#include "HUDObject.h"
#include "Sprite.h"

namespace KE
{

class HUDSprite : public HUDObject
{
    const Sprite *sprite;

public:
    HUDSprite(const Point &position, int z, const const Sprite *sprite);
};
