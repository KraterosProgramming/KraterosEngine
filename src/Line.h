#pragma once
#include <SDL2/SDL.h>

#include "Point.h"
#include "Rect.h"

namespace KE
{

class Line
{
public:
    Point a, b;

    Line();
    Line(int x, int y, double radians, double length);
    Line(int x1, int y1, int x2, int y2);
    Line(const Point &a, const Point &b);

    double getRadians() const;
    double getLength() const;
    double getSqaredLength() const;
    const Point normalize() const;

    const Rect getRect() const;

};
}

