#pragma once
#include "Point.h"
#include "Rect.h"

namespace KE
{

class Circle : public Point
{
public:
    double radius;

    Circle();
    Circle(int x, int y, double radius);

    const Circle move(const Point &p) const;
    const Circle grow(double radius) const;

    const Point getPosition() const;
    const Point getSize() const;

};
}

