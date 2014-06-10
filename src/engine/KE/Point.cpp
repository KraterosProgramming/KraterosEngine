#include "Point.h"
#include <cmath>

namespace KE
{

Point::Point()
{
    this->x = 0;
    this->y = 0;
}

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

const Point Point::fromAngle(double radians, double length)
{
    return Point(length * std::cos(radians), length * std::sin(radians));
}

Point::operator SDL_Point*() const
{
    return (SDL_Point*)(this);
}

Point::operator bool() const
{
    return x != 0 && y != 0;
}

const Point Point::operator- () const
{
    return Point(-x, -y);
}

const Point Point::operator+ (const Point &o) const
{
    return Point(x + o.x, y + o.y);
}

const Point Point::operator- (const Point &o) const
{
    return Point(x - o.x, y - o.y);
}

const Point Point::operator* (float f) const
{
    return Point(x * f, y * f);
}

const Point Point::operator/ (float f) const
{
    return Point(x / f, y / f);
}

Point &Point::operator+= (const Point &o)
{
    x += o.x;
    y += o.y;
    return *this;
}

Point &Point::operator-= (const Point &o)
{
    x -= o.x;
    y -= o.y;
    return *this;
}

Point &Point::operator* (float f)
{
    x *= f;
    y *= f;
    return *this;
}

Point &Point::operator/ (float f)
{
    x /= f;
    y /= f;
    return *this;
}

bool Point::operator== (const Point &o) const
{
    return x == o.x && y == o.y;
}

bool Point::operator!= (const Point &o) const
{
    return x != o.x || y != o.y;
}

double Point::getRadians() const
{
    if (x == 0 && y == 0)
    {
        return 0;
    }

    return std::atan2(y, x);
}

double Point::getLength() const
{
    return std::sqrt(x * x + y * y);
}

double Point::getSquaredLength() const
{
    return x * x + y * y;
}

const Point Point::normalize() const
{
    int l = getLength();
    return Point(x / l, y / l);
}

}
