#pragma once
#include <SDL2/SDL.h>

namespace KE
{

class Point : public SDL_Point
{
public:
    Point();
    Point(int x, int y);

    static const Point fromAngle(double radians, double length = 1);

    operator SDL_Point*() const;
    operator bool() const;

    const Point operator- () const;

    const Point operator+ (const Point &o) const;
    const Point operator- (const Point &o) const;
    const Point operator* (float f) const;
    const Point operator/ (float f) const;

    Point &operator+= (const Point &o);
    Point &operator-= (const Point &o);
    Point &operator* (float f);
    Point &operator/ (float f);

    bool operator== (const Point &o) const;
    bool operator!= (const Point &o) const;

    double getRadians() const;
    double getLength() const;
    double getSquaredLength() const;
    const Point normalize() const;

};
}
