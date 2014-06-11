#include "Rect.h"

namespace KE
{

Rect::Rect()
{
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
}

Rect::Rect(int w, int h)
{
    this->x = 0;
    this->y = 0;
    this->w = w;
    this->h = h;
}

Rect::Rect(const Point &size)
{
    this->x = 0;
    this->y = 0;
    this->w = size.x;
    this->h = size.y;
}

Rect::Rect(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect::Rect(const Point &position, const Point &size)
{
    this->x = position.x;
    this->y = position.y;
    this->w = size.x;
    this->h = size.y;
}

Rect::operator SDL_Rect*() const
{
    return (SDL_Rect*)(this);
}

Rect::operator bool() const
{
    return w != 0 && h != 0;
}

const Rect Rect::move(const Point &p) const
{
    return Rect(x + p.x, y + p.y, w, h);
}

const Rect Rect::grow(const Point &p) const
{
    return Rect(x, y, w + p.x, h + p.y);
}

const Point Rect::getPosition() const
{
    return Point(x, y);
}

const Point Rect::getSize() const
{
    return Point(w, h);
}

const Point Rect::getCenter() const
{
    return Point(x + w/2, y + h/2);
}

Rect Rect::parseXML(const tinyxml2::XMLElement *elem)
{
    return Rect(elem->IntAttribute("x"), elem->IntAttribute("y"), elem->IntAttribute("w"), elem->IntAttribute("h"));
}

}
