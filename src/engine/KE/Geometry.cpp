#include "Geometry.h"

namespace KE
{

// TODO: Geometry

namespace Geometry
{

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
    Line l2 (l);
    return SDL_IntersectRectAndLine(r, &l2.a.x, &l2.a.y, &l2.b.x, &l2.b.y);
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

Line intersect(const Line &a, const Line &b)
{
    return Line(0, 0, 0, 0);
}

Line intersect(const Line &l, const Rect &r)
{
    Line intersection (l);
    SDL_IntersectRectAndLine(r, &intersection.a.x, &intersection.a.y, &intersection.b.x, &intersection.b.y);
    return intersection;
}

Rect intersect(const Rect &a, const Rect &b)
{
    Rect intersection;
    SDL_IntersectRect(a, b, intersection);
    return intersection;
}

}

}
