#pragma once

#include "Point.h"
#include "Rect.h"
#include "Line.h"
#include "Circle.h"

namespace KE
{

namespace Geometry
{

bool collides(const Point &a, const Point &b);
bool collides(const Point &p, const Line &l);
bool collides(const Point &p, const Rect &r);
bool collides(const Point &p, const Circle &c);

bool collides(const Line &a, const Line &b);
bool collides(const Line &l, const Rect &r);
bool collides(const Line &l, const Circle &c);

bool collides(const Rect &a, const Rect &b);
bool collides(const Rect &r, const Circle &c);

bool collides(const Circle &a, const Circle &b);

Line intersect(const Line &a, const Line &b);
Line intersect(const Line &l, const Rect &r);
Rect intersect(const Rect &a, const Rect &b);

}

}
