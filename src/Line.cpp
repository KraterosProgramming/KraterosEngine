#include "Line.h"
#include "Tools.h"

namespace KE
{

Line::Line()
{

}

Line::Line(int x, int y, double radians, double length)
{
    this->a = Point(x, y);
    this->b = Point::fromAngle(radians, length);
}

Line::Line(int x1, int y1, int x2, int y2)
{
    this->a = Point(x1, y1);
    this->b = Point(x2, y2);
}

Line::Line(const Point &a, const Point &b)
{
    this->a = a;
    this->b = b;
}

double Line::getRadians() const
{
    return (b - a).getRadians();
}

double Line::getLength() const
{
    return (b - a).getLength();
}

double Line::getSqaredLength() const
{
    return (b - a).getSquaredLength();
}

const Point Line::normalize() const
{
    return (b - a).normalize();
}

const Rect Line::getRect() const
{
    return Rect(std::min(a.x, b.x),
                std::min(a.y, b.y),
                std::abs(a.x - b.x),
                std::abs(a.y - b.y));
}

}
