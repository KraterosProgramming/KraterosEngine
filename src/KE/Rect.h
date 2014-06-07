#pragma once
#include <SDL2/SDL.h>
#include "Point.h"

namespace KE
{

class Rect : public SDL_Rect
{
public:
    Rect();
    Rect(int x, int y, int w, int h);

    operator SDL_Rect*() const;

    const Rect move(const Point &p) const;
    const Rect grow(const Point &p) const;

    const Point getPosition() const;
    const Point getSize() const;
    const Point getCenter() const;
};

}
