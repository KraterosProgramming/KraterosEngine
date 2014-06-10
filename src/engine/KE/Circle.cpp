#include "Circle.h"

namespace KE
{

Circle::Circle() : Point()
{
    this->radius = 0;
}

Circle::Circle(int x, int y, double radius) : Point(x, y)
{
    this->radius = radius;
}

Circle::operator bool() const
{
    return radius;
}

const Circle Circle::move(const Point &p) const
{
    return Circle(x + p.x, y + p.y, radius);
}

const Circle Circle::grow(double radius) const
{
    return Circle(x, y, this->radius + radius);
}

const Point Circle::getPosition() const
{
    return Point(x, y);
}

const Point Circle::getSize() const
{
    return Point(radius * 2, radius * 2);
}

}
