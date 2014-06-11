#pragma once
#include <SDL2/SDL.h>

#include "tinyxml2.h"
#include "Point.h"

namespace KE
{

class Rect : public SDL_Rect
{
public:
    Rect();
    Rect(int w, int h);
    Rect(const Point &size);
    Rect(int x, int y, int w, int h);
    Rect(const Point &position, const Point &size);

    operator SDL_Rect*() const;
    operator bool() const;

    const Rect move(const Point &p) const;
    const Rect grow(const Point &p) const;

    const Point getPosition() const;
    const Point getSize() const;
    const Point getCenter() const;

    static Rect parseXML(const tinyxml2::XMLElement *elem);
};

}
