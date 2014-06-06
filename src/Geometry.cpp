#include "Geometry.h"

namespace KE
{

// TODO: Geometry

namespace Geometry
{

// TODO: collides lines

bool collides(const Point &a, const Point &b)
{
    return a == b;
}

bool collides(const Point &p, const Line &l)
{
    return false;
}

bool collides(const Point &p, const Rect &r)
{
    return p.x >= r.x && p.y >= r.y && p.x <= r.x + r.w && p.y <= r.y + r.h;
}

bool collides(const Point &p, const Circle &c)
{
    return (c.getPosition() - p).getSquaredLength() <= c.radius * c.radius;
}

bool collides(const Line &a, const Line &b)
{
    return false;
}

bool collides(const Line &l, const Rect &r)
{
    return false;
}

bool collides(const Line &l, const Circle &c)
{
    return false;
}

bool collides(const Rect &a, const Rect &b)
{
    return false;
}

bool collides(const Rect &r, const Circle &c)
{
    return false;
}

bool collides(const Circle &a, const Circle &b)
{
    int maxDist = a.radius + b.radius;
    return (a.getPosition() - b.getPosition()).getSquaredLength() <= maxDist * maxDist;
}

}

}
